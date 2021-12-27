#ifndef INPUT_BUFFER_HPP
#define INPUT_BUFFER_HPP

#include "../Common/Directions.hpp"
#include "IInputBufferReader.hpp"
#include "IInputBufferWriter.hpp"

class InputBuffer : public IInputBufferReader, public IInputBufferWriter
{
    private:
        Direction direction;
        bool shot;
        bool breakoutMenu;

    public:
        /**
         * Constructor for value initialization.
         */
        InputBuffer()
        {
            direction = Direction::none;
            shot = false;
            breakoutMenu = false;
        }

        /**
         * sets the direction according to the parameter. Only 'up', 'down', 'left', 'right' are allowed. 'none' will throw an error. 
         */
        void setDirection(Direction direction) override
        {
            if(direction == Direction::none){
                throw std::logic_error("It is not allowed to set the direction to 'none' manually.");
            }
            this->direction = direction;
        }

        /**
         * sets the flag to true. 
         */
        void setShot() override
        {
            this->shot = true;
        }

        /**
         * sets the flag to true. 
         */
        void setBreakoutMenu() override
        {
            this->breakoutMenu = true;
        }

        /**
         * returns the direction and sets the buffer to 'none'. 
         */
        Direction getAndResetDirection() override
        {
            auto temp = this->direction;
            this->direction = none;
            return temp;
        }

        /**
         * returns true if shot was triggered and sets the buffer to 'false'. 
         */
        bool getAndResetShot() override
        {
            auto temp = this->shot;
            this->shot = false;
            return temp;
        }

        /**
         * returns true if breakout menu was triggered and sets the buffer to 'false'. 
         */
        bool getAndResetBreakoutMenu() override
        {
            auto temp = this->breakoutMenu;
            this->breakoutMenu = false;
            return temp;
        }
};

#endif