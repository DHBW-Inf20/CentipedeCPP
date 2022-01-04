#ifndef MUSHROOM_MAP_HPP
#define MUSHROOM_MAP_HPP
#include "Bullet.hpp"
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

    public:
        /**
         * Initialized map in fieldsize.
         */
        MushroomMap(std::shared_ptr<CentipedeSettings> settings_ptr)
        {
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
        }

        /**
         * Returns the remaining mushroom health at the given coordinates.
         * Returns -1 if the coordinates are out of bounds.
         */
        int getMushroom(int line, int column)
        {
            if(isOutOfBoundsOrAtCentipedeEntry(line, column))
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
            if(isOutOfBoundsOrAtCentipedeEntry(line, column))
            {
                return;
            }
            this->mushroomMap[line][column] = this->settings_ptr->getInitialMushroomHealth();
        }

        // Methode hinzugefügt
        bool isOutOfBoundsOrAtCentipedeEntry(int line, int column)
        {
            return lineOutOfBounds(line, this->settings_ptr)
                || columnOutOfBounds(column, this->settings_ptr)
                || (line == 0 && column == (this-settings_ptr->getPlayingFieldWidth - 1) / 2);
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