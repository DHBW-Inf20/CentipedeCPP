#ifndef MUSHROOM_MAP_HPP
#define MUSHROOM_MAP_HPP
#include "Bullet.hpp"
#include "../../lib/CppRandom.hpp"
#include "../Common/CentipedeSettings.hpp"
#include "../Common/Utils.hpp"
#include <vector>
#include <memory>
#include <iostream>

class MushroomMap
{
    private:
        /**
         * 2 dimensional Array in field-size, containing mushroom information:
         * 0         - no mushroom.
         * bigger 0  - mushroom with x hitpoints remaining.
         * smaller 0 - undefined.
         * access by mushroomMap[line][column].
         */
        std::vector<std::vector<int8_t>> mushroomMap;
        std::shared_ptr<CentipedeSettings> settings_ptr;

        bool isOutOfBounds(int line, int column)
        {
            return lineOutOfBounds(line, this->settings_ptr)
                || columnOutOfBounds(column, this->settings_ptr);
        }

        /**
         * Spawns random mushrooms above the initial starship position.
         */
        void spawnRandomMushrooms()
        {
            auto dividend = this->settings_ptr->getInitialMushroomSpawnChanceDividend();
            auto divisor = this->settings_ptr->getInitialMushroomSpawnChanceDivisor();
            auto starshipSpawnLine = this->settings_ptr->getInitialStarshipLine();

            for(int line = 0; line < starshipSpawnLine; line++)
            {
                for(int column = 0; column < this->settings_ptr->getPlayingFieldWidth(); column++)
                {
                    auto spawnMushroom = rollRandomWithChance(dividend, divisor);
                    if(spawnMushroom)
                    {
                        this->spawnMushroom(line, column);
                        auto initialDamage = GetRandomNumberBetween(0, this->settings_ptr->getInitialMushroomHealth() - 1);
                        this->mushroomMap[line][column] -= initialDamage;
                    }
                }
            }
        }

    public:
        /**
         * Initialized map in fieldsize.
         */
        MushroomMap(std::shared_ptr<CentipedeSettings> settings_ptr)
        {
            // Initialize two dimensional array.
            // first make a line with n columns.
            std::vector<int8_t> line;
            for(int j = 0; j < settings_ptr->getPlayingFieldWidth(); j++){
                line.push_back(0);
            }

            // then copy and add m times to initialize mushroomMap.
            for(int i = 0; i < settings_ptr->getPlayingFieldHeight(); i++){
                std::vector<int8_t> lineCopy(line);
                this->mushroomMap.push_back(lineCopy);
            }

            this->settings_ptr = settings_ptr;
            this->spawnRandomMushrooms();
        }

        /**
         * Returns the remaining mushroom health at the given coordinates.
         * Returns -1 if the coordinates are out of bounds.
         */
        int getMushroom(int line, int column)
        {
            if(this->isOutOfBounds(line, column))
            {
                return -1;
            }
            return this->mushroomMap[line][column];
        }

        /**
         * Spawns a mushroom with the initial health specified in the settings.
         */
        void spawnMushroom(int line, int column)
        {
            if(isOutOfBounds(line, column))
            {
                return;
            }
            this->mushroomMap[line][column] = this->settings_ptr->getInitialMushroomHealth();
        }

        /**
         * checks wheather the current position of the bullet is a collision with a mushroom.
         * If so, it reduces the mushroom's health by one and returns true.
         * Otherwise returns false.
         */
        bool collide(Bullet &bullet)
        {
            auto line = bullet.getPosition().getLine();
            auto column = bullet.getPosition().getColumn();
            if(this->getMushroom(line, column) < 1)
            {
                // no mushroom or out of bounds.
                return false;
            }
            // hit a mushroom -> decrement by 1.
            this->mushroomMap[line][column]--;
            return true;
        }
};

#endif