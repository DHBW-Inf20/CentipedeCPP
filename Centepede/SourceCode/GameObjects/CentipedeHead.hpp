#ifndef CENTIPEDE_HEAD_HPP
#define CENTIPEDE_HEAD_HPP
#include "../"
#include "CentipedePart.hpp"
#include "Position.hpp"
#include <memory>

class CentipedeHead : public CentipedePart
{
private:
	enum movingDirection : int { left, right };		// Wie ist geplant dieses Enum zu verwenden?
	int direction = 0;								// Hinzzgefügt

public:
	CentipedeHead(int bodySize, std::shared_ptr<Position> position_ptr)
	{
		this->position_ptr = position_ptr;

		for (int i = 0; i < bodySize; i++)
		{
			// Wo sollen die anderen Körperteile hinplatziert werden?
			// Vielleicht könnten die Körperteile in Zeitschritten erstellt werden?
		}
	}

	CentipedeHead(std::shared_ptr<CentipedeBody> splitOfTail_ptr, std::shared_ptr<CentipedeSettings> )
	{
		CentipedeHead(, splitOfTail_ptr);		// Unvollständig
	}

						// Warum besteht der Vektor aus Heads?
	bool move(MushroomMap &mushroomMap, std::vector<CentipedeHead> &centipedeList)
	{
		int line = centipedeList[0].position_ptr->getLine();
		int column = centipedeList[0].position_ptr->getColumn();


	}

	~CentipedeHead()
	{
		delete tail_ptr;
		delete position_ptr;
	}
};

#endif