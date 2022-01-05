#ifndef CENTIPEDE_HEAD_HPP
#define CENTIPEDE_HEAD_HPP
#include "../"
#include "CentipedePart.hpp"
#include "Position.hpp"
#include "Directions.hpp"
#include <memory>

class CentipedeHead : public CentipedePart
{
public:
	CentipedeHead(int bodySize, std::shared_ptr<Position> position_ptr)
	{
		this->bodySize = bodySize;
		this->position_ptr = position_ptr;

		auto tail_ptr = std::make_shared<CentipedeBody>(position_ptr, nullptr);
		for (int i = 0; i < bodySize - 1; i++)
		{
			tail_ptr = std::make_shared<CentipedeBody>(position_ptr, tail_ptr);
		}
		this->tail_ptr = tail_ptr;
	}

	CentipedeHead(std::shared_ptr<CentipedeBody> splitOfTail_ptr, std::shared_ptr<CentipedeSettings> settings_ptr)
	{
		this->position_ptr = splitOfTail_ptr->getPosition();
		this->tail_ptr = splitOfTail_ptr->getTail();
	}
			// Soll zusätzlich noch geprüft werden, ob unterhalb des Heads ein Pilz ist???
	bool move(MushroomMap &mushroomMap, std::vector<CentipedeHead> &centipedeList, CentipedeMovingDirection direction)
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

	bool isTakenPosition(int line, int column, MushroomMap& mushroomMap, CentipedeHead& centipedeHead)
	{
		return mushroomMap.getMushroom(line, column) > 0
			&& column < 1
			&& line == centipedeHead.position_ptr->getLine()
			&& column == centipedeHead.position_ptr->getColumn();
	}
};

#endif