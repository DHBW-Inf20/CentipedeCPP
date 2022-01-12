#ifndef IUI_HPP
#define IUI_HPP
#include "ITheme.hpp"
#include "CentipedeSettings.hpp"
#include "../GameObjects/SaveState.hpp"

enum ConsoleColour : int
{
	Black,
	Blue,
	Cyan,
	Default,
	Green,
	Magenta,
	Red,
	White,
	Yellow
};

enum ConsoleTextDecoration : int
{
	Bold,
	Italics,
	Strikethrough,
	Underlined
};

class IUI 
{
    public:
		/**
		 * Displays the image that reflects the current saveState.
		 */
		virtual void displayImage(SaveState& state, CentipedeSettings &settings, ITheme& theme) = 0;
		
		/**
		 * Displays a menu of options.
		 */
    virtual void displayMenu(std::string &title, 
						                 ConsoleColour titleColour, 
						                 std::vector<std::string> &options, 
						                 int selected, 
						                 ITheme &theme, 
						                 CentipedeSettings &settings) = 0;
};

#endif