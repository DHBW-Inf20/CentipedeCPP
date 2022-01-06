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
	bool isNoTakenPosition(bool freeDirection, MushroomMap& mushroomMap, int line, int column)
	{
		return freeDirection
			&& mushroomMap.getMushroom(line, column) == 0;
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
			break;
		case Direction::up:
			return isNoTakenPosition(this->position_ptr->up(), mushroomMap, line - 1, column);
			break;
		case Direction::down:
			return isNoTakenPosition(this->position_ptr->down(), mushroomMap, line + 1, column);
			break;
		case Direction::left:
			return isNoTakenPosition(this->position_ptr->left(), mushroomMap, line, column - 1);
			break;
		case Direction::right:
			return isNoTakenPosition(this->position_ptr->right(), mushroomMap, line, column + 1);
			break;
		default:
			break;
		}
		return false;
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