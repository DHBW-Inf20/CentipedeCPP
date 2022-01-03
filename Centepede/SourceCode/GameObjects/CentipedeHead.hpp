#ifndef CENTIPEDE_HEAD_HPP
#define CENTIPEDE_HEAD_HPP
#include "../"
#include "CentipedePart.hpp"
#include "Position.hpp"
#include <memory>

class CentipedeHead : public CentipedePart
{
private:
	enum movingDirection : int { left, right };

public:
	CentipedeHead(int bodySize, std::shared_ptr<Position> position_ptr)
	{

	}

	CentipedeHead(std::shared_ptr<CentipedeBody> splitOfTail_ptr, std::shared_ptr < CentipedeSettings)
	{

	}

	bool move(MushroomMap& mushroomMap, std::vector<CentipedeHead> centipedeList)
	{

	}

	~CentipedeHead()
	{
		delete tail_ptr;
		delete position_ptr;
	}
};

#endif