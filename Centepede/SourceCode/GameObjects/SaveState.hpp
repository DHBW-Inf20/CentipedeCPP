#ifndef SAFE_STATE_HPP
#define SAFE_STATE_HPP

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
		int gameTick;
		std::shared_ptr<CentipedeSettings> settings_ptr;
		std::shared_ptr<std::vector<Bullet>> bullets_ptr;
		std::shared_ptr<Starship> starship_ptr;
		std::shared_ptr<MushroomMap> mushroomMap_ptr;
		std::shared_ptr<std::vector<CentipedeHead>> centipedes_ptr;
        int currentCentipedeModuloGametickSlowdown;
		int currentRound;

	public:
		SaveState(std::shared_ptr<CentipedeSettings> settings_ptr,
			std::shared_ptr<std::vector<Bullet>> bullets_ptr,
			std::shared_ptr<Starship> starship_ptr,
			std::shared_ptr<MushroomMap> mushroomMap_ptr,
			std::shared_ptr<std::vector<CentipedeHead>> centipedes_ptr,
			int currentCentipedeModuloGametickSlowdown,
			int currentRound)
		{
			this->gameTick = 0;
			this->settings_ptr = settings_ptr;
			this->bullets_ptr = bullets_ptr;
			this->starship_ptr = starship_ptr;
			this->mushroomMap_ptr = mushroomMap_ptr;
			this->centipedes_ptr = centipedes_ptr;
			this->currentCentipedeModuloGametickSlowdown = currentCentipedeModuloGametickSlowdown;
			this->currentRound = currentRound;
		}

		std::shared_ptr<CentipedeSettings> getSettings()
		{
			return this->settings_ptr;
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
			return this->centipedes_ptr;
		}

		int getGameTick()
		{
			return this->gameTick;
		}

		void incrementGameTick()
		{
			this->gameTick++;
			// Overflow protection.
			if(this->gameTick < 0)
			{
				this->gameTick = 0;
			}
		}

		int getCurrentCentipedeModuloGametickSlowdown()
		{
			return this->currentCentipedeModuloGametickSlowdown;
		}
		
		void setCurrentCentipedeModuloGametickSlowdown(int slowdown)
		{
			this->currentCentipedeModuloGametickSlowdown = slowdown;
		}

		int getCurrentRound()
		{
			return this->currentRound;
		}

		void incrementCurrentRound()
		{
			this->currentRound++;
		}
};

#endif