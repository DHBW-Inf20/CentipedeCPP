#ifndef CENTIPEDE_PART_HPP
#define CENTIPEDE_PART_HPP
#include "CentipedeBody.hpp"
#include "Position.hpp"
#include <memory>

class CentipedePart
{
    private:
        std::shared_ptr<CentipedeBody> tail_ptr;
        std::shared_ptr<Position> position_ptr;

    public:
        
};

#endif