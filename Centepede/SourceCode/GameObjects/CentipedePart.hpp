#ifndef CENTIPEDE_PART_HPP
#define CENTIPEDE_PART_HPP
#include "../Common/CentipedeSettings.hpp"
#include "Position.hpp"
#include "Starship.hpp"
#include "Bullet.hpp"
#include "MushroomMap.hpp"
#include "../Common/Tuple.hpp"
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
        std::shared_ptr<CentipedePart> tail_ptr;
        Position position;
		CentipedeMovingDirection movingDirection;

		CentipedePart(int line, int column, std::shared_ptr<CentipedeSettings> settings_ptr, CentipedeMovingDirection movingDirection, std::shared_ptr<CentipedePart> tail_ptr)
			: position(line, column, settings_ptr), movingDirection(movingDirection), tail_ptr(tail_ptr)
		{
		}

		CentipedePart(Position position, CentipedeMovingDirection movingDirection, std::shared_ptr<CentipedePart> tail_ptr)
			: position(position), movingDirection(movingDirection), tail_ptr(tail_ptr)
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
		* Gives back the hit type with the Bullet and nullptr or the split of tail. Direct hit -> this CentipedePart got hit, tail hit -> a CentipedePart of the tail got hit.
		*/
		Tuple<CentipedeHit, std::shared_ptr<CentipedePart>> collide(Bullet &bullet, std::shared_ptr<MushroomMap> mushroomMap)
		{
			auto hit = bullet.getPosition().equals(this->position);
			if(hit)
			{
				// Direct hit on this part of the centipede.
				// Tail needs to become new Centipede in list.
				// The Centipede Creation is done by the logic.
				Tuple result(CentipedeHit::directHit, this->tail_ptr);
				// Spawn the mushroom.
				mushroomMap->spawnMushroom(this->position.getLine(), this->position.getColumn());
				// This object will be disposed, when parent removes Tail ptr.
				return result;
			}

			// No direct hit -> check on tail.
			if(this->tail_ptr == nullptr)
			{
				// No more tail to check on -> no place to hit.
				Tuple<CentipedeHit, std::shared_ptr<CentipedePart>> result(CentipedeHit::noHit, nullptr);
				return result;
			}

			auto tailResult = this->tail_ptr->collide(bullet, mushroomMap);
			if(tailResult.getItem1() == CentipedeHit::noHit || tailResult.getItem1() == CentipedeHit::tailHit)
			{
				return tailResult;
			}
			// tailResult == CentipedeHit::directHit:
			// This part is now end of the centipede.
			this->tail_ptr = nullptr;
			Tuple result(CentipedeHit::tailHit, tailResult.getItem2());
			return result;
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
		std::shared_ptr<CentipedePart> getTail()
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