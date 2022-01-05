#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP
#include "../Input/Keylistener.hpp"
#include "../Input/IInputBufferReader.hpp"
#include "../GameObjects/SaveState.hpp"
#include "../GameObjects/Bullet.hpp"
#include "../../lib/concurrency_lib.hpp"
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <chrono>

class GameLogic
{
    private:
        bool gameRunning;
        std::shared_mutex runningMutex;
        std::shared_ptr<IInputBufferReader> inputBuffer_ptr;
        std::shared_ptr<SaveState> saveState_ptr;
        std::unique_ptr<std::thread> gameClock_thread;

        // //////////////////////////////////////////////////
        // Additional Methods
        // //////////////////////////////////////////////////

        /**
         * Starts an endless-loop in this thread and runs the game on the current SafeState.
         * To stop the game, it eather needs to be lost or interrupted by calling breakGame() from another thread.
         */
        void gameLoop()
        {
            auto gameClock = startGameClock();
            // Outer game loop.
            while(this->isRunning())
            {
                // Start a new Round
                this->startNextRound();

                // Play through the round
                while(this->isRunning() && this->continueRound())
                {
                    // Await next game tick.
                    gameClock->await();

                    // Do the calculations.
                    this->handlePlayerControlledEntities();
                    this->handleCentipedes();
                    this->handleGlobalCollisions();

                    // Print the result to the UI.
                    this->printGame();
                }
            }

            // reset the clock.
            this->gameClock_thread->join();
            this->gameClock_thread = nullptr;
        }

        std::shared_ptr<Signal> startGameClock()
        {
            if(gameClock_thread != nullptr)
            {
                // already running!
                return;
            }
            auto gameClock = std::make_shared<Signal>();
            this->gameClock_thread = std::make_unique<std::thread>(&GameLogic::executeGameClock, this, gameClock);
            return gameClock;
        }

        void executeGameClock(std::shared_ptr<Signal> gameClock)
        {
            while(this->isRunning())
            {
                auto gameTickLength = this->saveState_ptr->getSettings()->getGameTickLength();
                std::this_thread::sleep_for(std::chrono::milliseconds(gameTickLength));
                gameClock->signal();
            }
        }

        /**
         * Checks, wheather the game should continue running.
         */
        bool isRunning()
        {
            std::shared_lock runningLock(this->runningMutex);
            return this->gameRunning;
        }

        void changeRunning(bool to)
        {
            std::unique_lock runningLock(this->runningMutex);
            this->gameRunning = to;
        }

        /**
         * Prints the current SafeState to the UI.
         */
        void printGame();

        /**
         * Determines wheather a path with the given slowdown should be executed within the current gametick.
         */
        bool executePathForCurrentGametick(int moduloSlowdown)
        {
            return this->saveState_ptr->getGameTick() % moduloSlowdown == 0;
        }

        // //////////////////////////////////////////////////
        // High Level Logic Methods
        // //////////////////////////////////////////////////

        /**
         * Handles all starship and bullet actions.
         * This is path 1, executed after a constant gametick delay.
         */
        void handlePlayerControlledEntities()
        {
            auto starshipModuloGametickSlowdown = this->saveState_ptr->getSettings()->getStarshipModuloGametickSlowdown();
            if(!executePathForCurrentGametick(starshipModuloGametickSlowdown)){
                // Player controlled entities won't move this gametick-> skip path.
                return;
            }
            spawnBulletIfNecessary();
            moveBullets();
            collideBulletsMushrooms();
            moveStarshipIfNecessary();
        }
        
        /**
         * Handles centipede movement.
         * This is path 2, executed after a varying gametick delay.
         */
        void handleCentipedes()
        {
            auto currentCentipedeModuloGametickSlowdown = this->saveState_ptr->getCurrentCentipedeModuloGametickSlowdown();
            if(!executePathForCurrentGametick(currentCentipedeModuloGametickSlowdown)){
                // Centiepedes won't move this gametick-> skip path.
                return;
            }
            moveCentipedes();
        }

        /**
         * Handles collisions with objects of both pathes at once: bullet-centipede and player-centipede.
         */
        void handleGlobalCollisions()
        {
            auto currentCentipedeModuloGametickSlowdown = this->saveState_ptr->getCurrentCentipedeModuloGametickSlowdown();
            auto starshipModuloGametickSlowdown = this->saveState_ptr->getSettings()->getStarshipModuloGametickSlowdown();
            if(!executePathForCurrentGametick(starshipModuloGametickSlowdown)
            && !executePathForCurrentGametick(currentCentipedeModuloGametickSlowdown)){
                // Collision can only be skipped, if neither path was executed.
                return;
            }
            this->collideBulletsCentipedes();
            this->collidePlayerCentipedes();
        }

        /**
         * Determines wheather the round continues or a new has to be started.
         */
        bool continueRound()
        {
            // A round continues, while there are still centipedes left.
            return this->saveState_ptr->getCentipedes()->size();
        }

        /**
         * Adjusts centipede-lenght and speed and spawns a new centipede to start the next round.
         */
        void startNextRound()
        {
            this->saveState_ptr->incrementCurrentRound();
            // TODO RE how do we define the rounds?
            auto currentRound = this->saveState_ptr->getCurrentRound();

            auto settings_ptr = this->saveState_ptr->getSettings();

            // Calculate and set Slowdown.
            auto initialSlowdown = settings_ptr->getInitialCentipedeModuloGametickSlowdown();
            auto numberOfSpeedups = currentRound / settings_ptr->getCentipedeSpeedIncrementRoundModuloSlowdown();
            auto currentSlowdown = initialSlowdown - (numberOfSpeedups * settings_ptr->getCentipedeSpeedIncrementAmount());
            this->saveState_ptr->setCurrentCentipedeModuloGametickSlowdown(currentSlowdown);

            // Calculate Size.
            auto initialSize = settings_ptr->getInitialCentipedeSize();
            auto numberOfSizeIncrements = currentRound / settings_ptr->getCentipedeSizeIncrementRoundModuloSlowdown();
            auto currentSize = initialSize + (numberOfSizeIncrements * settings_ptr->getCentipedeSizeIncrementAmount());

            // Evaluate initial Position
            auto position = std::make_shared<Position>(settings_ptr->getCentipedeSpawnLine(), settings_ptr->getCentipedeSpawnColumn(), settings_ptr);

            CentipedeHead newCentipede(currentSize, position);
            this->saveState_ptr->getCentipedes()->push_back(newCentipede);
        }

        // //////////////////////////////////////////////////
        // Low Level Logic Methods
        // //////////////////////////////////////////////////

        /**
         * Spawns a bullet if required button was pressed.
         */
        void spawnBulletIfNecessary()
        {
            auto shot = this->inputBuffer_ptr->getAndResetShot();
            auto starship_ptr = this->saveState_ptr->getStarship();
            auto bullets_ptr = this->saveState_ptr->getBullets();
            if(shot)
            {
                auto newBullet_ptr = starship_ptr->shoot();
                bullets_ptr->push_back(*newBullet_ptr);
            }
        }

        /**
         * Moves all bullets one line up.
         */
        void moveBullets()
        {
            auto bullets_ptr = this->saveState_ptr->getBullets();
            auto bullet_ptr = bullets_ptr->begin();
            while(bullet_ptr != bullets_ptr->end())
            {
                bullet_ptr->move();
                bullet_ptr++;
            }
        }

        /**
         * Takes Care of Collisions between bullets and mushrooms.
         */
        void collideBulletsMushrooms()
        {
            auto bullets_ptr = this->saveState_ptr->getBullets();
            auto mushroomMap_ptr = this->saveState_ptr->getMushroomMap();
            // no simple for loop because vector may be edited while looping through.
            auto bullet_ptr = bullets_ptr->begin();
            while(bullet_ptr != bullets_ptr->end())
            {
                if(!mushroomMap_ptr->collide(*bullet_ptr))
                {
                    // No collision, bullet remains in list.
                    // check next bullet.
                    bullet_ptr++;
                    continue;
                }

                // Collision bullet & mushroom -> remove bullet.
                bullet_ptr = bullets_ptr->erase(bullet_ptr);
                // no increment here, since bullet_ptr already points to the following element.
            }
        }

        /**
         * Moves the starship if any direction was set by button press.
         */
        void moveStarshipIfNecessary()
        {
            auto direction = this->inputBuffer_ptr->getAndResetDirection();
            auto starship_ptr = this->saveState_ptr->getStarship();
            if(direction == Direction::none)
            {
                // no direction was picked.
                return;
            }

            // valid direction was picked.
            starship_ptr->move(direction);
        }

        // //////////////////////////////////////////////////

        /**
         * Moves all centipedes foreward.
         */
        void moveCentipedes()
        {
            auto safeState = this->saveState_ptr;
            auto centipedes_ptr = safeState->getCentipedes();
            auto mushroomMap_ptr = safeState->getMushroomMap();
            for(auto centipede : *centipedes_ptr)
            {
                // Comparison with same centipede is handled inside.
                centipede.move(*mushroomMap_ptr, *centipedes_ptr);
            }
        }

        // //////////////////////////////////////////////////

        /**
         * Handles collisions between bullets and centipedes.
         */
        void collideBulletsCentipedes()
        {
            auto centipedes_ptr = this->saveState_ptr->getCentipedes();
            auto bullets_ptr = this->saveState_ptr->getBullets();
            for(auto centipede : *centipedes_ptr)
            {
                // no simple for loop because vector may be edited while looping through.
                auto bullet_ptr = bullets_ptr->begin();
                while(bullet_ptr != bullets_ptr->end())
                {
                    if(!centipede.collide(*bullet_ptr, *(this->saveState_ptr->getMushroomMap())))
                    {
                        // No collision, game continues running.
                        bullet_ptr++;
                        continue;
                    }

                    // Collision bullet & centipede -> remove bullet.
                    bullet_ptr = bullets_ptr->erase(bullet_ptr);
                    // no increment here, since bullet_ptr already points to the following element.
                }
            }
        }

        /**
         * Handles collisions between centipedes and the starship.
         */
        void collidePlayerCentipedes()
        {
            for(auto centipede : *(this->saveState_ptr->getCentipedes()))
            {
                if(!centipede.isCollision(*(this->saveState_ptr->getStarship())))
                {
                    // No collision, game continues running.
                    continue;
                }

                // Collision player & centipede -> lose game.
                std::unique_lock(this->runningMutex);
                this->gameRunning = false;
            }
        }

    public:
        GameLogic(std::shared_ptr<IInputBufferReader> inputBuffer_ptr)
        {
            this->inputBuffer_ptr = inputBuffer_ptr;
            this->gameClock_thread = nullptr;
        }

        // //////////////////////////////////////////////////
        // Control Methods
        // //////////////////////////////////////////////////

        /**
         * Starts a new Game.
         */
        void startNew()
        {
            auto settings_ptr = std::make_shared<CentipedeSettings>();
			auto bullets_ptr = std::make_shared<std::vector<Bullet>>();
			auto starship_ptr = std::make_shared<Starship>(settings_ptr->getInitialStarshipLine(),
                                                           settings_ptr->getInitialStarshipColumn(),
                                                           settings_ptr);
			auto mushroomMap_ptr = std::make_shared<MushroomMap>(settings_ptr);
			auto centipedes_ptr = std::make_shared<std::vector<CentipedeHead>>();
			int currentCentipedeModuloGametickSlowdown = settings_ptr->getInitialCentipedeModuloGametickSlowdown();
            int currentRound = 0;
            auto newState = std::make_shared<SaveState>(settings_ptr, 
                                                        bullets_ptr,
                                                        starship_ptr,
                                                        mushroomMap_ptr,
                                                        centipedes_ptr,
                                                        currentCentipedeModuloGametickSlowdown,
                                                        currentRound);
            this->continueGame(newState);
        }

        /**
         * Stops the game with the next gametick and returns the current Safe State.
         */
        std::shared_ptr<SaveState> breakGame()
        {
            this->changeRunning(false);
            // wait for game to finish.
            while(this->gameClock_thread != nullptr);
            // return the current state of the game.
            return this->saveState_ptr; 
        }

        /**
         * Continues the game of the given Safe State.
         */
        void continueGame(std::shared_ptr<SaveState> state)
        {
            this->changeRunning(true);
            this->saveState_ptr = state;
            this->gameLoop();
        }
};

#endif