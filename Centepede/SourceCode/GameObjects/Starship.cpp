#include <memory>
#include "Position.cpp"
#include "Bullet.cpp"

class Starship
{
private:
	std::shared_ptr<Position> position_ptr;
	std::shared_ptr<FieldInfo> fieldInfo_ptr;

public:
	Starship(int line, int column, std::shared_ptr<FieldInfo> fieldInfo_ptr)
	{
		fieldInfo_ptr = fieldInfo_ptr;
		position_ptr = Position(line, column, fieldInfo_ptr)
	}

	std::shared_ptr<Position> getPosition()
	{
		return position_ptr;
	}

	void move()
	{

	}

	std::shared_ptr<Bullet> shoot()
	{
		int line = position_ptr->getLine();
		int column = position_ptr->getColumn();

		return Bullet(line, column).getPosition();
	}

	~Starship()
	{
		delete position_ptr;
		delete fieldInfo_ptr;
	}
};