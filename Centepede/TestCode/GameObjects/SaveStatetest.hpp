#include "../../lib/test_lib.hpp"
#include "../../SourceCode/Common/CentipedeSettings.hpp"
#include "../../SourceCode/GameObjects/SaveState.hpp"

bool saveState_init0Test()
{
	printSubTestName("SaveState init 0 test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto bullet = new Bullet(0, 0, settings);
	std::vector<Bullet> bulletVector;
	bulletVector.push_back(bullet);
	auto starship = new Starship(2, 2, settings);
	auto mushroomMap = new MushroomMap(settings);
	auto position = new Position(0, 5, settings);
	std::shared_ptr<Position> position_ptr = &position;
	auto centipedeHead = new CentipedeHead(10, position_ptr);
	auto saveState = new SaveState(&settings, &bulletVector, &starship, &);

	// Unvollständig
}

bool saveState_getBullets()
{

}