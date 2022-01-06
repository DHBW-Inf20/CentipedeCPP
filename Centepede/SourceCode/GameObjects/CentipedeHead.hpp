#ifndef CENTIPEDE_HEAD_HPP
#define CENTIPEDE_HEAD_HPP
#include "CentipedePart.hpp"
#include "CentipedeBody.hpp"
#include "Position.hpp"
#include "../Common/Directions.hpp"
#include <memory>

class CentipedeHead : public CentipedePart
{
	private:
		/**
		* Checks wheter the next position is taken from a mushroom or another centipede head.
		*/
		bool isTakenPosition(int line, int column, MushroomMap& mushroomMap, CentipedeHead& centipedeHead)
		{
			return mushroomMap.getMushroom(line, column) > 0
				&& column < 1
				&& line == centipedeHead.position_ptr->getLine()
				&& column == centipedeHead.position_ptr->getColumn();
		}

	public:
		/**
		* Constructor for new Centipede at the field.
		*/
		CentipedeHead(int line, int column, CentipedeMovingDirection direction, std::shared_ptr<CentipedeSettings> settings_ptr, int bodySize)
		{
			this->bodySize = bodySize;
			this->position_ptr = std::make_shared<Position>(line, column, settings_ptr);

			auto tail_ptr = std::make_shared<CentipedeBody>(position_ptr, nullptr);

			for (int i = 0; i < bodySize - 1; i++)
			{
				auto position_ptr = std::make_shared<Position>(line, column, settings_ptr);

				auto body = new CentipedeBody(position_ptr);

				tail_ptr = std::make_shared<CentipedeBody>(position_ptr, tail_ptr);
			}

			this->tail_ptr = tail_ptr;
		}

		/**
		* Constructor for Centipede part after hit with bullet.
		*/
		CentipedeHead(std::shared_ptr<CentipedeBody> splitOfTail_ptr)
		{
			this->position_ptr = std::make_shared<Position>(splitOfTail_ptr->getPosition());
			this->tail_ptr = splitOfTail_ptr->getTail();
		}

		/**
		* Checks wheter the centipede head meets a mushroom.
		*/
		bool move(MushroomMap &mushroomMap, std::vector<CentipedeHead> &centipedeList)
		{
			int line = this->position_ptr->getLine();
			int column = this->position_ptr->getColumn();
			bool verify = true;

			for (int i = 0; i < centipedeList.size(); i++)
			{
				switch (direction)
				{
				case CentipedeMovingDirection::left:
					if (isTakenPosition(line, column - 1, mushroomMap, centipedeList[i]))
					{
						verify = false;
					}
					break;
				}
				case CentipedeMovingDirection::right:
					if (isTakenPosition(line, column + 1, mushroomMap, centipedeList[i]))
					{
						verify = false;
					}
					break;
			}

			return verify;
		}
};

#endif