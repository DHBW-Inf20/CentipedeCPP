#ifndef CENTIPEDE_SETTINGS_HPP
#define CENTIPEDE_SETTINGS_HPP

class CentipedeSettings
{
    private:
        int playingFieldHeight = 28;
        int playingFieldWidth = 30;
    public:
        int getPlayingFieldHeigt();

        int getPlayingFieldWidth();
};

#endif