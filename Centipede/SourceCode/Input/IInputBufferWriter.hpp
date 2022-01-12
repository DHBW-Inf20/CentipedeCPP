#ifndef I_INPUT_BUFFER_WRITER_HPP
#define I_INPUT_BUFFER_WRITER_HPP

#include "../Common/Directions.hpp"

class IInputBufferWriter
{
    public:
        /**
         * sets the direction according to the parameter. Only 'up', 'down', 'left', 'right' are allowed. 'none' will throw an error. 
         */
        virtual void setDirection(Direction direction) = 0;

        /**
         * sets the flag to true. 
         */
        virtual void setShot() = 0;

        /**
         * sets the flag to true. 
         */
        virtual void setBreakoutMenu() = 0;
};

#endif