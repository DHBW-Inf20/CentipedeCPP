#ifndef CENTIPEDE_SETTINGS_HPP
#define CENTIPEDE_SETTINGS_HPP

class CentipedeSettings
{
    private:
        int playingFieldHeight;
        int playingFieldWidth;
        int initialMushroomHealth;
        int starshipModuloGametickSlowdown;
        int initialCentipedeModuloGametickSlowdown;
        int gameTickLength;
        int initialStarshipLine;
        int initialStarshipColumn;
        int centipedeSpawnLine;
        int centipedeSpawnColumn;
        int initialCentipedeSize;
        int centipedeSizeIncrementAmount;
        int centipedeSizeIncrementRoundModuloSlowdown;
        int centipedeSpeedIncrementAmount;
        int centipedeSpeedIncrementRoundModuloSlowdown;
    
    public:
        CentipedeSettings();

        int getPlayingFieldHeight()
        {
            return this->playingFieldHeight;
        }
        int getPlayingFieldWidth()
        {
            return this->playingFieldWidth;
        }
        int getInitialMushroomHealth()
        {
            return this->initialMushroomHealth;
        }
        int getStarshipModuloGametickSlowdown()
        {
            return this->starshipModuloGametickSlowdown;
        }
        int getInitialCentipedeModuloGametickSlowdown()
        {
            return this->initialCentipedeModuloGametickSlowdown;
        }
        int getGameTickLength()
        {
            return this->gameTickLength;
        }
        int getInitialStarshipLine()
        {
            return this->initialStarshipLine;
        }
        int getInitialStarshipColumn()
        {
            return this->initialStarshipColumn;
        }
        int getCentipedeSpawnLine()
        {
            return this->centipedeSpawnLine;
        }
        int getCentipedeSpawnColumn()
        {
            return this->centipedeSpawnColumn;
        }
        int getInitialCentipedeSize()
        {
            return this->initialCentipedeSize;
        }
        int getCentipedeSizeIncrementAmount()
        {
            return this->centipedeSizeIncrementAmount;
        }
        int getCentipedeSizeIncrementRoundModuloSlowdown()
        {
            return this->centipedeSizeIncrementRoundModuloSlowdown;
        }
        int getCentipedeSpeedIncrementAmount()
        {
            return this->centipedeSpeedIncrementAmount;
        }
        int getCentipedeSpeedIncrementRoundModuloSlowdown()
        {
            return this->centipedeSpeedIncrementRoundModuloSlowdown;
        }
};

#endif