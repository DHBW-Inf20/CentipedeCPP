#ifndef GAME_LOGIC_HPP
#define GAME_LOGIC_HPP
#include "../Input/Keylistener.hpp"
#include "../Input/IInputBufferReader.hpp"
#include "../GameObjects/SaveState.hpp"
#include "../GameObjects/Bullet.hpp"
#include "../Common/Tuple.hpp"
#include "../Common/IUI.hpp"
#include "../Common/ITheme.hpp"
#include "../../lib/concurrency_lib.hpp"
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <chrono>
#include <iostream>

class GameLogic
{
    private:
        bool gameRunning;
        std::shared_mutex runningMutex;
        std::shared_ptr<IInputBufferReader> inputBuffer_ptr;
        std::shared_ptr<SaveState> saveState_ptr;
        std::unique_ptr<std::thread> gameClock_thread_ptr;
        std::shared_ptr<IUI> ui_ptr;
        std::shared_ptr<ITheme> theme_ptr;

        // //////////////////////////////////////////////////
        // Additional Methods
        // //////////////////////////////////////////////////

        /**
         * Starts an endless-loop in this thread and runs the game on the current SafeState.
         * To stop the game, it eather needs to be lost or interrupted by calling breakGame() from another thread.
         */
        void gameLoop()
        {
            auto saveState_ptr = this->saveState_ptr;
            auto inputBuffer_ptr = this->inputBuffer_ptr;
            auto settings_ptr = saveState_ptr->getSettings();
            auto gameClock = startGameClock(settings_ptr->getGameTickLength());
            // Outer game loop.
            while(this->isRunning())
            {
                // Start a new Round
                this->startNextRound(saveState_ptr);

                // Play through the round
                while(this->isRunning() && this->continueRound(saveState_ptr->getCentipedes()))
                {
                    // Await next game tick.
                    gameClock->await();

                    // Do the calculations.
                    this->handlePlayerControlledEntities(inputBuffer_ptr, saveState_ptr);
                    this->handleCentipedes(saveState_ptr);
                    this->handleGlobalCollisions(saveState_ptr);

                    // Print the current state to the UI.
                    // TODO RE score.
                    this->printGame(0, saveState_ptr, settings_ptr);
                }
            }

            this->waitForGameClock();
        }

        /**
         * Starts the clock in a separate thread.
         */
        std::shared_ptr<Signal> startGameClock(int gameTickLength)
        {
            if(gameClock_thread_ptr != nullptr)
            {
                // already running!
                throw std::logic_error("Game Clock already running.");
            }
            auto gameClock = std::make_shared<Signal>();
            this->gameClock_thread_ptr = std::make_unique<std::thread>(&GameLogic::executeGameClock, this, gameTickLength, gameClock);
            return gameClock;
        }

        /**
         * Runs the clock, that outputs the game tick signals to the given signal.
         */
        void executeGameClock(int gameTickLength, std::shared_ptr<Signal> gameClock)
        {
            while(this->isRunning())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(gameTickLength));
                gameClock->signal();
            }
        }

        /**
         * The clock is ended by this->isRunning() returning false;
         */
        void waitForGameClock()
        {
            // reset the clock.
            this->gameClock_thread_ptr->join();
            this->gameClock_thread_ptr = nullptr;
        }

        /**
         * Threadsafe check, wheather the game should continue running.
         */
        bool isRunning()
        {
            std::shared_lock runningLock(this->runningMutex);
            return this->gameRunning;
        }

        /**
         * Threadsafe method to change the running attribute.
         */
        void changeRunning(bool to)
        {
            std::unique_lock runningLock(this->runningMutex);
            this->gameRunning = to;
        }

        /**
         * Prints the safeState to the UI.
         */
        void printGame(int score, std::shared_ptr<SaveState> saveState_ptr, std::shared_ptr<CentipedeSettings> settings_ptr)
        {
            this->ui_ptr->drawImage(score, *(this->theme_ptr), *saveState_ptr, *settings_ptr);
        }

        /**
         * Determines wheather a path with the given slowdown should be executed within the current gametick.
         */
        bool executePathForGametick(int gameTick, int moduloSlowdown)
        {
            return gameTick % moduloSlowdown == 0;
        }

        // //////////////////////////////////////////////////
        // High Level Logic Methods
        // //////////////////////////////////////////////////

        /**
         * Handles all starship and bullet actions.
         * This is path 1, executed after a constant gametick delay.
         */
        void handlePlayerControlledEntities(std::shared_ptr<IInputBufferReader> inputBuffer_ptr, std::shared_ptr<SaveState> saveState_ptr)
        {
            auto settings_ptr = saveState_ptr->getSettings();
            auto starshipModuloGametickSlowdown = settings_ptr->getStarshipModuloGametickSlowdown();
            auto currentGameTick = saveState_ptr->getGameTick();
            if(!executePathForGametick(currentGameTick, starshipModuloGametickSlowdown)){
                // Player controlled entities won't move this gametick-> skip path.
                return;
            }

            auto starship_ptr = saveState_ptr->getStarship();
            auto bullets_ptr = saveState_ptr->getBullets();
            auto mushroomMap_ptr = saveState_ptr->getMushroomMap();
            spawnBulletIfNecessary(inputBuffer_ptr, starship_ptr, bullets_ptr);
            moveBullets(bullets_ptr);
            collideBulletsMushrooms(bullets_ptr, mushroomMap_ptr);
            moveStarshipIfNecessary(inputBuffer_ptr, starship_ptr, mushroomMap_ptr);
        }
        
        /**
         * Handles centipede movement.
         * This is path 2, executed after a varying gametick delay.
         */
        void handleCentipedes(std::shared_ptr<SaveState> saveState_ptr)
        {
            auto currentGameTick = saveState_ptr->getGameTick();
            auto currentCentipedeModuloGametickSlowdown = saveState_ptr->getCurrentCentipedeModuloGametickSlowdown();
            if(!executePathForGametick(currentGameTick, currentCentipedeModuloGametickSlowdown)){
                // Centiepedes won't move this gametick-> skip path.
                return;
            }

            auto centipedes_ptr = saveState_ptr->getCentipedes();
            auto mushroomMap_ptr = saveState_ptr->getMushroomMap();
            auto settings_ptr = saveState_ptr->getSettings();
            moveCentipedes(centipedes_ptr, mushroomMap_ptr, settings_ptr);
        }

        /**
         * Handles collisions with objects of both pathes at once: bullet-centipede and player-centipede.
         */
        void handleGlobalCollisions(std::shared_ptr<SaveState> saveState_ptr)
        {
            auto settings_ptr = saveState_ptr->getSettings();
            auto currentCentipedeModuloGametickSlowdown = saveState_ptr->getCurrentCentipedeModuloGametickSlowdown();
            auto starshipModuloGametickSlowdown = saveState_ptr->getSettings()->getStarshipModuloGametickSlowdown();
            auto currentGameTick = saveState_ptr->getGameTick();

            // Collision can only be skipped, if neither path was executed.
            if(!executePathForGametick(currentGameTick, starshipModuloGametickSlowdown)
               && !executePathForGametick(currentGameTick,currentCentipedeModuloGametickSlowdown)){
                return;
            }

            auto centipedes_ptr = saveState_ptr->getCentipedes();
            auto bullets_ptr = saveState_ptr->getBullets();
            auto mushroomMap_ptr = saveState_ptr->getMushroomMap();
            auto starship_ptr = saveState_ptr->getStarship();
            
            this->collideBulletsCentipedes(centipedes_ptr, bullets_ptr, mushroomMap_ptr);
            this->collidePlayerCentipedes(centipedes_ptr, starship_ptr);
        }

        /**
         * Determines wheather the round continues or a new has to be started.
         */
        bool continueRound(std::shared_ptr<std::vector<CentipedeHead>> centipedes_ptr)
        {
            // A round continues, while there are still centipedes left.
            return centipedes_ptr->size() > 0;
        }

        /**
         * Adjusts centipede-lenght and speed and spawns a new centipede to start the next round.
         */
        void startNextRound(std::shared_ptr<SaveState> saveState_ptr)
        {
            saveState_ptr->incrementCurrentRound();
            
            auto currentRound = saveState_ptr->getCurrentRound();
            auto settings_ptr = saveState_ptr->getSettings();

            // Calculate and set new slowdown.
            auto currentSlowdown = this->calculateCentipedeSlowdown(settings_ptr, currentRound);
            saveState_ptr->setCurrentCentipedeModuloGametickSlowdown(currentSlowdown);

            // Calculate Size.
            auto currentSize = this->calculateCentipedeSize(settings_ptr, currentRound);

            // Evaluate initial position and movement
            auto movingDirection = this->getRandomCentipedeMovingDirection();
            auto line = settings_ptr->getCentipedeSpawnLine();
            auto column = settings_ptr->getCentipedeSpawnColumn();

            CentipedeHead newCentipede(line, column, movingDirection, settings_ptr, currentSize);
            saveState_ptr->getCentipedes()->push_back(newCentipede);
        }

        int calculateCentipedeSlowdown(std::shared_ptr<CentipedeSettings> settings_ptr, int currentRound)
        {
            auto initialSlowdown = settings_ptr->getInitialCentipedeModuloGametickSlowdown();
            auto numberOfSpeedups = currentRound / settings_ptr->getCentipedeSpeedIncrementRoundModuloSlowdown();
            auto currentSlowdown = initialSlowdown - (numberOfSpeedups * settings_ptr->getCentipedeSpeedIncrementAmount());
            return currentSlowdown;
        }

        int calculateCentipedeSize(std::shared_ptr<CentipedeSettings> settings_ptr, int currentRound)
        {
            auto initialSize = settings_ptr->getInitialCentipedeSize();
            auto numberOfSizeIncrements = currentRound / settings_ptr->getCentipedeSizeIncrementRoundModuloSlowdown();
            auto currentSize = initialSize + (numberOfSizeIncrements * settings_ptr->getCentipedeSizeIncrementAmount());
            return currentSize;
        }

        CentipedeMovingDirection getRandomCentipedeMovingDirection()
        {
            // TODO RE
            return CentipedeMovingDirection::cLeft;
        }

        // //////////////////////////////////////////////////
        // Low Level Logic Methods
        // //////////////////////////////////////////////////

        /**
         * Spawns a bullet if required button was pressed.
         */
        void spawnBulletIfNecessary(std::shared_ptr<IInputBufferReader> inputBuffer_ptr, 
                                    std::shared_ptr<Starship> starship_ptr, 
                                    std::shared_ptr<std::vector<Bullet>> bullets_ptr)
        {
            auto shot = inputBuffer_ptr->getAndResetShot();
            if(shot)
            {
                auto newBullet_ptr = starship_ptr->shoot();
                bullets_ptr->push_back(*newBullet_ptr);
            }
        }

        /**
         * Moves all bullets one line up.
         */
        void moveBullets(std::shared_ptr<std::vector<Bullet>> bullets_ptr)
        {
            auto bullet_ptr = bullets_ptr->begin();
            while(bullet_ptr != bullets_ptr->end())
            {
                auto hasMoved = bullet_ptr->move();
                if(!hasMoved)
                {
                    // Bullet has reached top.
                    bullet_ptr = bullets_ptr->erase(bullet_ptr);
                    continue;
                }
                bullet_ptr++;
            }
        }

        /**
         * Takes Care of Collisions between bullets and mushrooms.
         */
        void collideBulletsMushrooms(std::shared_ptr<std::vector<Bullet>> bullets_ptr,
                                     std::shared_ptr<MushroomMap> mushroomMap_ptr)
        {
            // no simple for loop because vector may be edited while looping through.
            auto bullet_ptr = bullets_ptr->begin();
            while(bullet_ptr != bullets_ptr->end())
            {
                if(mushroomMap_ptr->collide(*bullet_ptr))
                {
                    // Collision bullet & mushroom -> remove bullet.
                    bullet_ptr = bullets_ptr->erase(bullet_ptr);
                    // no increment here, since bullet_ptr already points to the following element.
                    continue;
                }
                // No collision, bullet remains in list.
                // check next bullet.
                bullet_ptr++;
            }
        }

        /**
         * Moves the starship if any direction was set by button press.
         */
        void moveStarshipIfNecessary(std::shared_ptr<IInputBufferReader> inputBuffer_ptr,
                                     std::shared_ptr<Starship> starship_ptr,
                                     std::shared_ptr<MushroomMap> mushroomMap_ptr)
        {
            auto direction = inputBuffer_ptr->getAndResetDirection();
            if(direction == Direction::none)
            {
                // no direction was picked.
                return;
            }

            // valid direction was picked.
            starship_ptr->move(direction, *mushroomMap_ptr);
        }

        // //////////////////////////////////////////////////

        /**
         * Moves all centipedes if possible.
         */
        void moveCentipedes(std::shared_ptr<std::vector<CentipedeHead>> centipedes_ptr,
                            std::shared_ptr<MushroomMap> mushroomMap_ptr,
                            std::shared_ptr<CentipedeSettings> settings_ptr)
        {
            auto centipede_ptr = centipedes_ptr->begin();
            while(centipede_ptr != centipedes_ptr->end())
            {
                centipede_ptr->move(*mushroomMap_ptr, *centipedes_ptr, settings_ptr);
                centipede_ptr++;
            }
        }

        // //////////////////////////////////////////////////

        /**
         * Handles collisions between bullets and centipedes.
         */
        void collideBulletsCentipedes(std::shared_ptr<std::vector<CentipedeHead>> centipedes_ptr,
                                      std::shared_ptr<std::vector<Bullet>> bullets_ptr,
                                      std::shared_ptr<MushroomMap> mushroomMap_ptr)
        {
            auto centipede_ptr = centipedes_ptr->begin();
            while(centipede_ptr != centipedes_ptr->end())
            {
                // Indicator wheather the head was hit.
                bool headHit = false;
                // Check bullets.
                // No simple "for" loop because vector may be edited while looping through.
                auto bullet_ptr = bullets_ptr->begin();
                // TODO RE WHY is that needed?
                if(bullet_ptr == bullets_ptr->end()) break;
                while(bullet_ptr != bullets_ptr->end())
                {
                    auto collisionResult = centipede_ptr->collide(*bullet_ptr, mushroomMap_ptr);
                    auto hitIndicator = collisionResult.getItem1();
                    auto splitOfTail_ptr = collisionResult.getItem2();
                    if(hitIndicator == CentipedeHit::noHit)
                    {
                        // Nothing left to do, just continue checking the others.
                        bullet_ptr++;
                        continue;
                    }

                    // Bullet has hit -> remove from list.
                    bullet_ptr = bullets_ptr->erase(bullet_ptr);
                    // Create new centipede from split of tail if necessary.
                    if(splitOfTail_ptr != nullptr)
                    {
                        auto splitOfBody_ptr = std::reinterpret_pointer_cast<CentipedeBody>(splitOfTail_ptr);
                        CentipedeHead newCentipedeFromSplitOfTail(splitOfBody_ptr);
                        centipedes_ptr->push_back(newCentipedeFromSplitOfTail);
                    }

                    if(hitIndicator == CentipedeHit::tailHit)
                    {
                        // Nothing left to do, just continue checking the others.
                        // bullet_ptr already points to next item.
                        continue;
                    }

                    // The head of the Centipede was hit -> return true and do NOT continue checking more bullets.
                    headHit = true;
                    break;
                }

                if(headHit)
                {
                    // Head needs to be removed.
                    centipede_ptr = centipedes_ptr->erase(centipede_ptr);
                    continue;
                }

                // No hit or only tail hit -> continue regulary.
                centipede_ptr++;
            }
        }

        /**
         * Handles collisions between centipedes and the starship.
         */
        void collidePlayerCentipedes(std::shared_ptr<std::vector<CentipedeHead>> centipedes_ptr,
                                     std::shared_ptr<Starship> starship_ptr)
        {
            auto starshipPosition = starship_ptr->getPosition();
            for(auto centipede : *centipedes_ptr)
            {
                if(!centipede.isAtPosition(starshipPosition))
                {
                    // No collision, game continues running.
                    continue;
                }

                // Collision player & centipede -> lose game.
                this->loseGame();
            }
        }

        void loseGame()
        {
            std::unique_lock(this->runningMutex);
            this->gameRunning = false;
        }

    public:
        GameLogic(std::shared_ptr<IInputBufferReader> inputBuffer_ptr,
                  std::shared_ptr<IUI> ui_ptr,
                  std::shared_ptr<ITheme> theme_ptr)
        {
            this->inputBuffer_ptr = inputBuffer_ptr;

            this->ui_ptr = ui_ptr;
            this->theme_ptr = theme_ptr;

            this->gameClock_thread_ptr = nullptr;
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
            while(this->gameClock_thread_ptr != nullptr);
            // return the current state of the game.
            return this->saveState_ptr; 
        }

        /**
         * Continues the game of the given Safe State.
         */
        void continueGame(std::shared_ptr<SaveState> state)
        {
            this->saveState_ptr = state;
            this->changeRunning(true);
            this->gameLoop();
        }
};

#endif