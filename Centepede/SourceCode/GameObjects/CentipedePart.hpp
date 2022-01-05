#ifndef CENTIPEDE_PART_HPP
#define CENTIPEDE_PART_HPP
#include "CentipedeBody.hpp"
#include "Position.hpp"
#include "Starship.hpp"
#include "Bullet.hpp"
#include "MushroomMap.hpp"
#include <memory>

class CentipedePart
{
    protected:				// von private -> protected geändert
        std::shared_ptr<CentipedeBody> tail_ptr;
        std::shared_ptr<Position> position_ptr;
		int bodySize;		// hinzugefügt

    public:
		bool isCollision(Starship &starship)	// Name geändert
		{
			int starshipLine = starship.getPosition().getLine();
			int starshipColumn = starship.getPosition().getColumn();
			int bodyPartLine = this->position_ptr->getLine();
			int bodyPartColumn = this->position_ptr->getColumn();

			return starshipLine == bodyPartLine && starshipColumn == bodyPartColumn;
		}

		bool collide(Bullet &bullet, MushroomMap& mushroomMap, std::shared_ptr<std::vector<CentipedeHead>> centipedes_ptr)
		{
			int bulletLine = bullet.getPosition().getLine();
			int bulletColumn = bullet.getPosition().getColumn();
			int bodyPartLine = this->position_ptr->getLine();
			int bodyPartColumn = this->position_ptr->getColumn();

			return bulletLine == bodyPartLine && bulletColumn == bodyPartColumn;
		}
};

#endif