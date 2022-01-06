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
    protected:
        std::shared_ptr<CentipedeBody> tail_ptr;
        Position position;
		CentipedeMovingDirection movingDirection;

		/**
		* Checks wheter the CentipedePart got a direct hit with the Bullet.
		*/
		bool isDirectHit(Position bulletPosition, Position tempPosition)
		{
			return tempPosition.equals(bulletPosition) && tempPosition == this->getPosition();
		}

		/**
		* Checks wheter the tail of the CentipedePart got a hit with the Bullet.
		*/
		bool isTailHit(Position bulletPosition, Position tempPosition)
		{
			return tempPosition.equals(bulletPosition);
		}

    public:

		/**
		* Checks wheter the CentipedePart has the same position like the Starship.
		*/
		bool isAtPosition(Position &position)
		{
			bool hit = false;

			auto tempPosition = this->position;
			auto tempTail_ptr = this->getTail();

			while (hit == false && tempTail_ptr != nullptr)
			{
				hit = this->position.equals(position);
				tempPosition = *(tempTail_ptr)->getPosition();
				tempTail_ptr = *(tempTail_ptr)->getTail();
			}

			return hit;
		}

		/**
		* Gives back the hit type with the Bullet. Direct hit -> this CentipedePart got hit, tail hit -> a CentipedePart of the tail got hit.
		*/
		CentipedeHit collide(Bullet &bullet, std::shared_ptr<MushroomMap> mushroomMap, std::shared_ptr<std::vector<CentipedeHead>> centipedes_ptr)
		{
			auto hit = CentipedeHit::noHit;

			auto bulletPosition = bullet.getPosition();
			
			auto tempPosition = this->position;
			auto tempTail_ptr = this->getTail();

			while (hit = 0 && tempTail_ptr != nullptr)
			{
				if (isDirectHit(bulletPosition, tempPosition))
				{
					hit = CentipedeHit::directHit;

					mushroomMap->spawnMushroom(this->getPosition().getLine(), this->getPosition().getColumn());

					// int line = *(tail_ptr)->getPosition().getLine();
					// int column = *(tail_ptr)->getPosition().getColumn();
					// CentipedeMovingDirection direction = (this->getMovingDirection == 0) ? 1 : 0;
					auto head = new CentipedeHead(tail_ptr);
					centipedes_ptr->push_back(head);

					delete position;
					delete tail_ptr;
					delete movingDirection;
					
					break;
				}
				else if (isTailHit(bulletPosition, tempPosition))
				{
					hit = CentipedeHit::tailHit;
					
					if (*(tempTail_ptr)->collide(bullet, mushroomMap, centipedes_ptr))
					{
						this->tail_ptr = nullptr;
					}
					break;
				}

				tempPosition = *(tempTail_ptr)->getPosition();
				tempTail_ptr = *(tempTail_ptr)->getTail();
			}

			return hit;
		}

		/**
		* Gives back the position of the CentipedePart.
		*/
		Position getPosition()
		{
			return *(this->position_ptr);
		}

		/**
		* Gives back the pointer of the next CentipedeBody of the tail.
		*/
		std::shared_ptr<CentipedeBody> getTail()
		{
			return this->tail_ptr;
		}

		/**
		* Gives back the moving direction of the CentipedePart.
		*/
		CentipedeMovingDirection getMovingDirection()
		{
			return this->movingDirection;
		}
};

#endif