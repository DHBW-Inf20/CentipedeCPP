#ifndef I_INPUT_BUFFER_READER_HPP
#define I_INPUT_BUFFER_READER_HPP

#include "../Common/Directions.hpp"

class IInputBufferReader
{
    public:
        /**
         * returns the direction and sets the buffer to 'none'. 
         */
        virtual Direction getAndResetDirection() = 0;

        /**
         * returns true if shot was triggered and sets the buffer to 'false'. 
         */
        virtual bool getAndResetShot() = 0;

        /**
         * returns true if breakout menu was triggered and sets the buffer to 'false'. 
         */
        virtual bool getAndResetBreakoutMenu() = 0;
};

#endif