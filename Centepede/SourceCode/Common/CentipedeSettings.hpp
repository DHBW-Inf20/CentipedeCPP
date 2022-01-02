#ifndef CENTIPEDE_SETTINGS_HPP
#define CENTIPEDE_SETTINGS_HPP

class CentipedeSettings
{
    private:
        int playingFieldHeight = 28;
        int playingFieldWidth = 30;
        int initialMushroomHealth = 3;
    
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

};

#endif