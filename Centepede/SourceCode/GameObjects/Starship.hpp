#ifndef STARSHIP_HPP
#define STARSHIP_HPP
#include "../Common/CentipedeSettings.hpp"
#include "../Common/Directions.hpp"
#include "Position.hpp"
#include "Bullet.hpp"
#include <memory>

class Starship
{
private:
	std::unique_ptr<Position> position_ptr;
	std::shared_ptr<CentipedeSettings> settings_ptr;

	/**
	* Checks whether the next position is accessible for the Starship.
	* */
	bool isPossibleMove(MushroomMap& mushroomMap, int line, int column)
	{
		// Mushroom map returns -1 if coordinates are out of bounds.
		return mushroomMap.getMushroom(line, column) == 0;
	}

public:
	Starship(int line, int column, std::shared_ptr<CentipedeSettings> settings_ptr)
	{
		this->settings_ptr = settings_ptr;
		this->position_ptr = std::make_unique<Position>(line, column, settings_ptr);
	}

	/**
	* Gives back the position of the object.
	* */
	Position getPosition()
	{
		return *(this->position_ptr);
	}

	/**
	* Checks wheter the required moving direction ist possible.
	* */
	bool move(Direction direction, MushroomMap &mushroomMap)
	{
		int line = this->getPosition().getLine();
		int column = this->getPosition().getColumn();

		switch (direction)
		{
		case Direction::none:
			return true;
		case Direction::up:
			if(isPossibleMove(mushroomMap, line - 1, column))
			{
				return this->position_ptr->up();
			}
			// out of bounds or mushroom.
			return false;
		case Direction::down:
			if(isPossibleMove(mushroomMap, line + 1, column))
			{
				return this->position_ptr->down();
			}
			// out of bounds or mushroom.
			return false;
		case Direction::left:
			if(isPossibleMove(mushroomMap, line, column - 1))
			{
				return this->position_ptr->left();
			}
			// out of bounds or mushroom.
			return false;
		case Direction::right:
			if(isPossibleMove(mushroomMap, line, column + 1))
			{
				return this->position_ptr->right();
			}
			// out of bounds or mushroom.
			return false;
		default: // unknown direction.
			return false;
		}
	}

	/**
	* Gives back the pointer of the bullet.
	* */
	std::shared_ptr<Bullet> shoot()
	{
		int line = this->position_ptr->getLine();
		int column = this->position_ptr->getColumn();
		return std::make_shared<Bullet>(line, column, this->settings_ptr);
	}
};

#endif