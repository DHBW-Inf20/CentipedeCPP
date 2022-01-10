#ifndef CENTIPEDE_HEAD_HPP
#define CENTIPEDE_HEAD_HPP
#include "CentipedePart.hpp"
#include "CentipedeBody.hpp"
#include "Position.hpp"
#include "../Common/Directions.hpp"
#include "../Common/Utils.hpp"
#include <memory>

class CentipedeHead : public CentipedePart
{
	private:
		void changeDirection()
		{
			switch(this->movingDirection)
			{
				case CentipedeMovingDirection::cLeft:
					{
						this->movingDirection = CentipedeMovingDirection::cRight;
					}
				case CentipedeMovingDirection::cRight:
					{
						this->movingDirection = CentipedeMovingDirection::cLeft;
					}
			}
		}

		bool freeOfCentipede(int line, int column, std::vector<CentipedeHead> &centipedeList)
		{
			bool noCentipede = true;
			for(auto centipede : centipedeList)
			{
				// no need to filter centipede List for own, since this centipede never wants to go to a location it is already in.
				noCentipede = noCentipede && !centipede.isAtPosition(line, column);
			}
			return noCentipede;
		}

		/**
		* Checks wheter the next position is taken from a mushroom or another centipede.
		*/
		bool isValidPosition(int line, int column, MushroomMap& mushroomMap, std::vector<CentipedeHead> &centipedeList)
		{
			if(mushroomMap.getMushroom(line, column) != 0)
			{
				// If position out of bounds (returns -1) or there is a mushroom (returns value > 0).
				return false;
			}
			// Is possible position for a centipede to be -> check others.
			return this->freeOfCentipede(line, column, centipedeList);
		}

		bool changeLane(std::vector<CentipedeHead> &centipedeList, std::shared_ptr<CentipedeSettings> settings_ptr)
		{
			auto line = this->position.getLine();
			auto column = this->position.getColumn();
			if(lineOutOfBounds(line + 1, settings_ptr) || !freeOfCentipede(line + 1, column, centipedeList))
			{
				// Can't go down, either out of bounds or centipede.
				if(lineOutOfBounds(line - 1, settings_ptr) || !freeOfCentipede(line - 1, column, centipedeList))
				{
					// Can't go up either, do nothing.
					return false;
				}
				// can go up
				this->position.up();
				this->changeDirection();
				return true;
			}
			// can go down
			this->position.down();
			this->changeDirection();
			return true;
		}

	public:
		/**
		* Constructor for new Centipede at the field.
		*/
		CentipedeHead(int line, int column, CentipedeMovingDirection direction, std::shared_ptr<CentipedeSettings> settings_ptr, int bodySize)
			: CentipedePart(line, column, settings_ptr, direction, nullptr)
		{
			std::shared_ptr<CentipedeBody> tail_ptr = nullptr;

			for (int centipedePartCount = 1; centipedePartCount < bodySize; centipedePartCount++)
			{
				tail_ptr = std::make_shared<CentipedeBody>(this->position, tail_ptr, direction);
			}

			this->tail_ptr = tail_ptr;
		}

		/**
		* Constructor for Centipede part after hit with bullet.
		*/
		CentipedeHead(std::shared_ptr<CentipedeBody> splitOfTail_ptr)
			: CentipedePart(splitOfTail_ptr->getPosition(), splitOfTail_ptr->getMovingDirection(), splitOfTail_ptr->getTail())
		{
		}

		/**
		* Checks wheter the centipede head meets a mushroom.
		*/
		bool move(MushroomMap &mushroomMap, std::vector<CentipedeHead> &centipedeList, std::shared_ptr<CentipedeSettings> settings_ptr)
		{
			int line = this->position.getLine();
			int column = this->position.getColumn();

			switch (this->movingDirection)
			{
				case CentipedeMovingDirection::cLeft:
					if (isValidPosition(line, column - 1, mushroomMap, centipedeList))
					{
						return this->position.left(); // always true;
					}
					// way is blocked
					return this->changeLane(centipedeList, settings_ptr);
				case CentipedeMovingDirection::cRight:
					if (isValidPosition(line, column + 1, mushroomMap, centipedeList))
					{
						return this->position.right(); // always true;
					}
					// way is blocked
					return this->changeLane(centipedeList, settings_ptr);
			}
			return false;
		}
};

#endif