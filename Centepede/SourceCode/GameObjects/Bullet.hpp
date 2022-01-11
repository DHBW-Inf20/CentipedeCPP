#ifndef BULLET_HPP
#define BULLET_HPP
#include "Position.hpp"
#include "../Common/CentipedeSettings.hpp"
#include "Position.hpp"
#include <memory>

class Bullet
{
    private:
        Position position;
    
    public:
        /**
         * Creates a Bullet in the specified position.
         */
        Bullet(int line, int column, std::shared_ptr<CentipedeSettings> settings_ptr)
            : position(line, column, settings_ptr)
        {
        }

        /**
         * Returns a copy of the position object.
         */
        Position getPosition()
        {
            return this->position;
        }

        /**
         * Tries to move the Bullet one line up.
         * Returns true if successful.
         * If it would go out of bounds, it keeps it's position and returns false.
         */
        bool move()
        {
            return this->position.up();
        }
};

#endif