#ifndef CENTIPEDE_SETTINGS_HPP
#define CENTIPEDE_SETTINGS_HPP

class CentipedeSettings
{
    private:
        int playingFieldHeight;
        int playingFieldWidth;

        int initialPlayerHealth;
        int initialMushroomHealth;
        int initialStarshipLine;
        int initialStarshipColumn;
        int centipedeSpawnLine;
        int centipedeSpawnColumn;

        int initialCentipedeSize;
        int centipedeSizeIncrementAmount;
        int centipedeSizeIncrementRoundModuloSlowdown;

        int pointsForCentipedeHit;
        int pointsForMushroomKill;
        int pointsForRoundEnd;

        int gameTickLength;
        int starshipModuloGametickSlowdown;
        int initialCentipedeModuloGametickSlowdown;
        int centipedeSpeedIncrementAmount;
        int centipedeSpeedIncrementRoundModuloSlowdown;
        int liveLostBreakTime;
    
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
        
        int getInitialPlayerHealth()
        {
            return this->initialPlayerHealth;
        }
        int getInitialMushroomHealth()
        {
            return this->initialMushroomHealth;
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
        
        int getPointsForCentipedeHit()
        {
            return this->pointsForCentipedeHit;
        }
        int getPointsForMushroomKill()
        {
            return this->pointsForMushroomKill;
        }
        int getPointsForRoundEnd()
        {
            return this->pointsForRoundEnd;
        }

        int getGameTickLength()
        {
            return this->gameTickLength;
        }
        int getStarshipModuloGametickSlowdown()
        {
            return this->starshipModuloGametickSlowdown;
        }
        int getInitialCentipedeModuloGametickSlowdown()
        {
            return this->initialCentipedeModuloGametickSlowdown;
        }
        int getCentipedeSpeedIncrementAmount()
        {
            return this->centipedeSpeedIncrementAmount;
        }
        int getCentipedeSpeedIncrementRoundModuloSlowdown()
        {
            return this->centipedeSpeedIncrementRoundModuloSlowdown;
        }
        int getLiveLostBreakTime()
        {
            return this->liveLostBreakTime;
        }
};

#endif