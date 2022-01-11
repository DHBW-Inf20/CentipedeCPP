#ifndef IUI_HPP
#define IUI_HPP
#include "ITheme.hpp"
#include "CentipedeSettings.hpp"
#include "../GameObjects/SaveState.hpp"

class IUI 
{
    public:
		virtual void drawImage(int round, int score, ITheme& theme, SaveState& state, CentipedeSettings &settings) = 0;
};

#endif