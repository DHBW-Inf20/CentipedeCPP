#ifndef CENTIPEDE_BODY_HPP
#define CENTIPEDE_BODY_HPP
#include "CentipedePart.hpp"

class CentipedeBody: public CentipedePart
{
public:
	// Hier wird bewusst die Position kopiert!!
	CentipedeBody(Position position_ptr, std::shared_ptr<CentipedeBody> tail_ptr, CentipedeMovingDirection direction)
	{
		this->position_ptr = position_ptr;
		this->tail_ptr = tail_ptr;
	}

	// Hier wird bewusst die Position kopiert!!
	/**
	 * TODO JF von RE
	 */
	void move(Position position_ptr, CentipedeMovingDirection direction)
	{
		this->position_ptr = position_ptr;
	}
};

#endif