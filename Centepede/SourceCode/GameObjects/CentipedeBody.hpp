#ifndef CENTIPEDE_BODY_HPP
#define CENTIPEDE_BODY_HPP
#include "CentipedePart.hpp"

class CentipedeBody: public CentipedePart
{
public:
	CentipedeBody(std::shared_ptr<Position> position_ptr, std::shared_ptr<CentipedeBody> tail_ptr)
	{
		this->position_ptr = position_ptr;
		this->tail_ptr = tail_ptr;
	}

	void move(std::shared_ptr<Position> position_ptr)
	{
		this->position_ptr = position_ptr;
	}
};

#endif