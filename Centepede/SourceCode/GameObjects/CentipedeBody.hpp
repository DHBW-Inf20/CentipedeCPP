#ifndef CENTIPEDE_BODY_HPP
#define CENTIPEDE_BODY_HPP
#include "CentipedePart.hpp"

class CentipedeBody: public CentipedePart
{
public:
	CentipedeBody(std::shared_ptr<CentipedeBody> tail_ptr)
	{

	}

	bool move(std::shared_ptr<Position> position_ptr, CentipedeMovingDirection direction)
	{

	}
};

#endif