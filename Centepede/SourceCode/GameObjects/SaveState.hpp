#include <memory>
#include <vector>
#include "../Common/CentipedeSettings.hpp"
#include "Bullet.hpp"
#include "Starship.hpp"
#include "MushroomMap.hpp"
#include "CentipedeHead.hpp"

class SaveState
{
private:
	std::shared_ptr<CentipedeSettings> settings_ptr;
	std::shared_ptr<std::vector<Bullet>> bullets_ptr;
	std::shared_ptr<Starship> starship_ptr;
	std::shared_ptr<MushroomMap> mushroomMap_ptr;
	std::shared_ptr<std::vector<CentipedeHead>> centipedes_ptr;

public:
	SaveState(std::shared_ptr<CentipedeSettings> settings_ptr,
		std::shared_ptr<std::vector<Bullet>> bullets_ptr,
		std::shared_ptr<Starship> starship_ptr,
		std::shared_ptr<MushroomMap> mushroomMap_ptr,
		std::shared_ptr<std::vector<CentipedeHead>> centipedes_ptr)
	{
		this->settings_ptr = settings_ptr;
		this->bullets_ptr = bullets_ptr;
		this->starship_ptr = starship_ptr;
		this->mushroomMap_ptr = mushroomMap_ptr;
		this->centipedes_ptr = centipedes_ptr;
	}

	std::shared_ptr<std::vector<Bullet>> getBullets()
	{
		return this->bullets_ptr;
	}

	std::shared_ptr<Starship> getStarship()
	{
		return this->starship_ptr;
	}

	std::shared_ptr<MushroomMap> getMushroomMap()
	{
		return this->mushroomMap_ptr;
	}

	std::shared_ptr<std::vector<CentipedeHead>> getCentipedes()
	{
		return centipedes_ptr;
	}

	~SaveState()
	{
		delete settings_ptr;
		delete bullets_ptr;
		delete starship_ptr;
		delete mushroomMap_ptr;
		delete centipedes_ptr;
	}
};