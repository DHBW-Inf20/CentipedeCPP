#ifndef POSITION_HPP
#define POSITION_HPP
#include "../Common/CentipedeSettings.hpp"
#include <memory>

class Position
{
    private:
        int line;
        int column;
        std::shared_ptr<CentipedeSettings> centipedeSettings_ptr;

        bool lineOutOfBounds(int line)
        {
            if(line < 0) return true;
            if(line >= this->centipedeSettings_ptr->getPlayingFieldWidth()) return true;
            return false;
        }

        bool columnOutOfBounds(int column)
        {
            if(column < 0) return true;
            if(column >= this->centipedeSettings_ptr->getPlayingFieldHeigt()) return true;
            return false;
        }

    public:
        Position(int line, int column, std::shared_ptr<CentipedeSettings> centipedeSettings_ptr)
        {
            this->centipedeSettings_ptr = centipedeSettings_ptr;
            this->line = this->lineOutOfBounds(line) ? 0 : line;
            this->column = this->columnOutOfBounds(column) ? 0 : column;
        }

        /**
         * Tries to move the Position one column up (-1).
         * Returns true if successful.
         * If this would lead to the Position going out of Bounds, it returns false and retains its current coordinates.
         */
        bool up()
        {
            if(this->columnOutOfBounds(this->column - 1)){
                return false;
            }
            this->column--;
            return true;
        }

        /**
         * Tries to move the Position one column down (+1).
         * Returns true if successful.
         * If this would lead to the Position going out of Bounds, it returns false and retains its current coordinates.
         */
        bool down()
        {
            if(this->columnOutOfBounds(this->column + 1)){
                return false;
            }
            this->column++;
            return true;
        }

        /**
         * Tries to move the Position one line left (-1).
         * Returns true if successful.
         * If this would lead to the Position going out of Bounds, it returns false and retains its current coordinates.
         */
        bool left()
        {
            if(this->lineOutOfBounds(this->line - 1)){
                return false;
            }
            this->line--;
            return true;
        }

        /**
         * Tries to move the Position one line right (+1).
         * Returns true if successful.
         * If this would lead to the Position going out of Bounds, it returns false and retains its current coordinates.
         */
        bool right()
        {
            if(this->columnOutOfBounds(this->line + 1)){
                return false;
            }
            this->line++;
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