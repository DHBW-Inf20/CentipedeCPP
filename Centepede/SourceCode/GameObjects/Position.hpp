#ifndef POSITION_HPP
#define POSITION_HPP
#include "../Common/CentipedeSettings.hpp"
#include "../Common/Utils.hpp"
#include <memory>

class Position
{
    private:
        int line;
        int column;
        std::shared_ptr<CentipedeSettings> settings_ptr;

    public:
        Position(int line, int column, std::shared_ptr<CentipedeSettings> settings_ptr)
        {
            this->settings_ptr = settings_ptr;
            this->line = lineOutOfBounds(line, this->settings_ptr) ? 0 : line;
            this->column = columnOutOfBounds(column, this->settings_ptr) ? 0 : column;
        }

        /**
         * Tries to move the Position one column up (-1).
         * Returns true if successful.
         * If this would lead to the Position going out of Bounds, it returns false and retains its current coordinates.
         */
        bool up()
        {
            if(lineOutOfBounds(this->line - 1, this->settings_ptr)){
                return false;
            }
            this->line--;
            return true;
        }

        /**
         * Tries to move the Position one column down (+1).
         * Returns true if successful.
         * If this would lead to the Position going out of Bounds, it returns false and retains its current coordinates.
         */
        bool down()
        {
            if(lineOutOfBounds(this->line + 1, this->settings_ptr)){
                return false;
            }
            this->line++;
            return true;
        }

        /**
         * Tries to move the Position one line left (-1).
         * Returns true if successful.
         * If this would lead to the Position going out of Bounds, it returns false and retains its current coordinates.
         */
        bool left()
        {
            if(columnOutOfBounds(this->column - 1, this->settings_ptr)){
                return false;
            }
            this->column--;
            return true;
        }

        /**
         * Tries to move the Position one line right (+1).
         * Returns true if successful.
         * If this would lead to the Position going out of Bounds, it returns false and retains its current coordinates.
         */
        bool right()
        {
            if(columnOutOfBounds(this->column + 1, this->settings_ptr)){
                return false;
            }
            this->column++;
            return true;
        }

        /**
         * Returns the line of the current coordinate-pair.
         */
        int getLine()
        {
            return this->line;
        }

        /**
         * Returns the column of the current coordinate-pair.
         */
        int getColumn()
        {
            return this->column;
        }

        /**
         * Compares its line- and column-values to the other positon.
         * Returns true if both are equal, false otherwise.
         */
        bool equals(Position &other)
        {
            return this->line == other.getLine()
                && this->column == other.getColumn();
        }
};

#endif