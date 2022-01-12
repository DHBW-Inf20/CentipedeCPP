#include "../SourceCode/Common/CentipedeSettings.hpp"

CentipedeSettings::CentipedeSettings()
{
    this->playingFieldHeight = 10;
    this->playingFieldWidth = 11;

    this->initialPlayerHealth = 3;
    this->initialMushroomHealth = 3;
    this->initialStarshipLine = 27;
    this->initialStarshipColumn = 14;
    this->centipedeSpawnLine = 0;
    this->centipedeSpawnColumn = 14;

    this->initialCentipedeSize = 5;
    this->centipedeSizeIncrementAmount = 1;
    this->centipedeSizeIncrementRoundModuloSlowdown = 1;

    this->pointsForCentipedeHit = 1;
    this->pointsForMushroomKill = 2;
    this->pointsForRoundEnd = 10;

    this->gameTickLength = 10;
    this->starshipModuloGametickSlowdown = 4;
    this->initialCentipedeModuloGametickSlowdown = 8;
    this->centipedeSpeedIncrementAmount = 1;
    this->centipedeSpeedIncrementRoundModuloSlowdown = 5;
    this->liveLostBreakTime = 500;
}