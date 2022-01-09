#ifndef CENTIPEDE_PART_HPP
#define CENTIPEDE_PART_HPP
#include "../Common/CentipedeSettings.hpp"
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

		CentipedePart(int line, int column, std::shared_ptr<CentipedeSettings> settings_ptr, CentipedeMovingDirection movingDirection, std::shared_ptr<CentipedeBody> tail_ptr)
			: position(line, column, settings_ptr), movingDirection(movingDirection), tail_ptr(nullptr)
		{
		}

		CentipedePart(Position position, CentipedeMovingDirection movingDirection, std::shared_ptr<CentipedeBody> tail_ptr)
			: position(position), movingDirection(movingDirection), tail_ptr(nullptr)
		{
		}

    public:

		/**
		* Checks wheter the CentipedePart has the same position like the Starship.
		*/
		bool isAtPosition(Position &position)
		{
			bool directHit = this->position.equals(position);
			if(this->tail_ptr == nullptr)
			{
				return directHit;
			}
			// Has Tail
			return directHit || this->tail_ptr->isAtPosition(position);
		}

		/**
		* Checks wheter the CentipedePart has the same position like the Starship.
		*/
		bool isAtPosition(int line, int column)
		{
			bool directHit = this->position.equals(line, column);
			if(this->tail_ptr == nullptr)
			{
				return directHit;
			}
			// Has Tail
			return directHit || this->tail_ptr->isAtPosition(line, column);
		}

		/**
		* Gives back the hit type with the Bullet. Direct hit -> this CentipedePart got hit, tail hit -> a CentipedePart of the tail got hit.
		*/
		CentipedeHit collide(Bullet &bullet, std::shared_ptr<MushroomMap> mushroomMap, std::shared_ptr<std::vector<CentipedeHead>> centipedes_ptr)
		{
			auto hit = bullet.getPosition().equals(this->position);
			if(hit)
			{
				// Direct hit on this part of the centipede.
				// Tail needs to become new Centipede in list.
				CentipedeHead newCentipedeFromTail(this->tail_ptr);
				centipedes_ptr->push_back(newCentipedeFromTail);
				// This object will be disposed, when parent removes Tail ptr.
				return CentipedeHit::directHit;
			}

			// No direct hit -> check on tail.
			if(this->tail_ptr == nullptr)
			{
				// No more tail to check on -> no place to hit.
				return CentipedeHit::noHit;
			}

			auto tailResult = this->collide(bullet, mushroomMap, centipedes_ptr);
			if(tailResult == CentipedeHit::noHit || tailResult == CentipedeHit::tailHit)
			{
				return tailResult;
			}
			// tailResult == CentipedeHit::directHit:
			// This part is now end of the centipede.
			this->tail_ptr = nullptr;
			return CentipedeHit::tailHit;
		}

		/**
		* Gives back the position of the CentipedePart.
		*/
		Position getPosition()
		{
			return this->position;
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