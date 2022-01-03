#include "../Common/CentipedeSettings.hpp"
#include "../Common/Directions.hpp"
#include "Position.hpp"
#include "Bullet.hpp"
#include <memory>

class Starship
{
private:
	std::shared_ptr<Position> position_ptr;
	std::shared_ptr<CentipedeSettings> settings_ptr;

public:
	Starship(int line, int column, std::shared_ptr<CentipedeSettings> settings_ptr)
	{
		this->settings_ptr = settings_ptr;
		this->position_ptr = std::make_unique<Position>(line, column, settings_ptr);
	}

	std::shared_ptr<Position> getPosition()
	{
		return *(this->position_ptr);
	}

	bool move(Direction direction)
	{
		switch (direction)
		{
		case none:
			return true;
			break;
		case up:
			return this->position_ptr->up();
			break;
		case down:
			return this->position_ptr->down();
			break;
		case left:
			return this->position_ptr->left();
			break;
		case right:
			return this->position_ptr->right();
			break;
		default:
			break;
		}
		return false;
	}

	std::shared_ptr<Bullet> shoot()
	{
		int line = this->position_ptr->getLine();
		int column = this->position_ptr->getColumn();

		return Bullet(line, column).getPosition();
	}

	~Starship()
	{
		delete position_ptr;
		delete settings_ptr;
	}
};