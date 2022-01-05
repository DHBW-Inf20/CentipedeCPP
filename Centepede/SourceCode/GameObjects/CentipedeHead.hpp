#ifndef CENTIPEDE_HEAD_HPP
#define CENTIPEDE_HEAD_HPP
#include "../"
#include "CentipedePart.hpp"
#include "Position.hpp"
#include <memory>

class CentipedeHead : public CentipedePart
{
public:
	CentipedeHead(int bodySize, std::shared_ptr<Position> position_ptr)
	{
		this->bodySize = bodySize;
		this->position_ptr = position_ptr;

		for (int i = 0; i < bodySize; i++)
		{
			// Wo sollen die anderen Körperteile hinplatziert werden?
			// Vielleicht könnten die Körperteile in Zeitschritten erstellt werden?
		}
	}

	CentipedeHead(std::shared_ptr<CentipedeBody> splitOfTail_ptr, std::shared_ptr<CentipedeSettings> )
	{
		CentipedeHead(splitOfTail_ptr->bodySize);		// Unvollständig
	}

						// Warum besteht der Vektor aus Heads?
	bool move(MushroomMap &mushroomMap, std::vector<CentipedeHead> &centipedeList)
	{
		int line = centipedeList[0].position_ptr->getLine();
		int column = centipedeList[0].position_ptr->getColumn();


	}

	//bool isCollisionMushroom(MushroomMap& mushroomMap)	// Hinzugefügt
	//{
	//	int line = this->position_ptr->getLine();
	//	int column = this->position_ptr->getColumn();

	//	return mushroomMap.getMushroom(line, column) > 0;
	//}
};

#endif