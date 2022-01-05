#include "CentipedeSettings.hpp"

CentipedeSettings::CentipedeSettings()
{
    this->playingFieldHeight = 28;
    this->playingFieldWidth = 29;
    this->initialMushroomHealth = 3;
    this->starshipModuloGametickSlowdown = 4;
    this->initialCentipedeModuloGametickSlowdown = 8;
    this->gameTickLength = 10;
    this->initialStarshipLine = 27;
    this->initialStarshipColumn = 14;
    this->centipedeSpawnLine = 0;
    this->centipedeSpawnColumn = 14;
    this->initialCentipedeSize = 5;
    this->centipedeSizeIncrementAmount = 1;
    this->centipedeSizeIncrementRoundModuloSlowdown = 1;
    this->centipedeSpeedIncrementAmount = 1;
    this->centipedeSpeedIncrementRoundModuloSlowdown = 5;
}