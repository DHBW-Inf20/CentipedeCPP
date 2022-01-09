#ifndef CENTIPEDE_BODY_HPP
#define CENTIPEDE_BODY_HPP
#include "CentipedePart.hpp"

class CentipedeBody : public CentipedePart
{
public:
	// Hier wird bewusst die Position kopiert!!
	CentipedeBody(Position position, std::shared_ptr<CentipedeBody> tail_ptr, CentipedeMovingDirection direction)
		:CentipedePart(position, direction, tail_ptr)
	{
	}

	// Hier wird bewusst die Position kopiert!!
	/**
	 * Sets the position pointer and the moving direction of the centipede body.
	 */
	void move(Position position, CentipedeMovingDirection direction)
	{
		this->position = position;
		this->movingDirection = direction;
	}
};

#endif