#ifndef CENTIPEDE_PART_HPP
#define CENTIPEDE_PART_HPP
#include "CentipedeBody.hpp"
#include "Position.hpp"
#include "Starship.hpp"
#include "Bullet.hpp"
#include "MushroomMap.hpp"
#include "CentipedeHead.hpp"
#include <memory>

enum CentipedeHit : int 
{
	noHit = 0,
	directHit = 1,
	tailHit = 2
};

class CentipedePart
{
    protected:				// von private -> protected ge�ndert
        std::shared_ptr<CentipedeBody> tail_ptr;
        Position position;
		CentipedeMovingDirection movingDirection;

    public:
		bool isAtPosition(Position &position)
		{
			// TODO JF von RE: Use Position.equals();
			auto starshipPos = starship.getPosition();
			this->position_ptr->equals(starshipPos);

			int starshipLine = starship.getPosition().getLine();
			int starshipColumn = starship.getPosition().getColumn();
			int bodyPartLine = this->position_ptr->getLine();
			int bodyPartColumn = this->position_ptr->getColumn();
			// TODO JF von RE: Use recursion to call tail.

			return starshipLine == bodyPartLine && starshipColumn == bodyPartColumn;
		}

		CentipedeHit collide(Bullet &bullet, std::shared_ptr<MushroomMap> mushroomMap, std::shared_ptr<std::vector<CentipedeHead>> centipedes_ptr)
		{
			// TODO JF von RE: Use Position.equals();
			int bulletLine = bullet.getPosition().getLine();
			int bulletColumn = bullet.getPosition().getColumn();
			int bodyPartLine = this->position_ptr->getLine();
			int bodyPartColumn = this->position_ptr->getColumn();

			// TODO JF von RE: Use recursion:
			// 1. Check if there is collision on this part
			// if so a) construct new centipedeHead from Tail
			//       b) add new mushroom at own position to mushroom Map (request as parameter)
			//       c) add new centipede to centipede list (request as parameter)
			//       d) return directHit
			// else  a) call tail->collide()
			//       b) if returns true: set tail to nullptr
			//       c) return tailHit
			//  	 else return noHit
			// B->HBBBBBB MHBBBB

			return bulletLine == bodyPartLine && bulletColumn == bodyPartColumn;
		}

		Position getPosition()
		{
			return *(this->position_ptr);
		}

		std::shared_ptr<CentipedeBody> getTail()
		{
			return this->tail_ptr;
		}

		CentipedeMovingDirection getMovingDirection()
		{
			return this->movingDirection;
		}
};

#endif