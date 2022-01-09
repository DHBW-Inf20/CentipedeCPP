#ifndef CONSOLEOUTPUT_HPP
#define CONSOLEOUTPUT_HPP
#include <iostream>
#include "ITheme.hpp"
#include "../GameObjects/SaveState.hpp"

class ConsoleOutput
{
	private:
		writeToConsole(char* image)
		{
			std::cout << image << std::endl;
		}

	public:
		drawImage(int score, ITheme& theme, SaveState& state)
		{

		}
};

#endif