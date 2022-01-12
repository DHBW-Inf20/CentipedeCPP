#ifndef MENU_LOGIC_HPP
#define MENU_LOGIC_HPP
#include <memory>
#include <functional>
#include "../Common/IUI.hpp"
#include "../Common/ITheme.hpp"
#include "../Common/Directions.hpp"
#include "../Input/IInputBufferReader.hpp"

class MenuLogic
{
    private:
        std::shared_ptr<ITheme> theme_ptr;
        std::shared_ptr<IUI> ui_ptr;
        std::shared_ptr<IInputBufferReader> inputBuffer_ptr;
        CentipedeSettings settings;

        /**
         * Prints the options, navigates the menu with arrow keys and returns the index of the selected option.
         * If the menu was quit by pressing the breakout-key again, it returns -1;
         */
        int driveMenu(std::string &title, 
					   ConsoleColour titleColour, 
					   std::vector<std::string> &textLines,
					   std::vector<std::string> &options,
                       std::function<void()> delay)
        {
            int selected = 0;
            bool optionChosen = false;
            while(!optionChosen)
            {
                // Print menu
                ui_ptr->displayMenu(title, titleColour, textLines, options, selected, *(this->theme_ptr), this->settings);

                // wait for input
                Direction arrowPressed;
                bool spaceBarPressed;
                do
                {
                    delay();
                    arrowPressed = inputBuffer_ptr->getAndResetDirection();
                    spaceBarPressed = inputBuffer_ptr->getAndResetShot();
                    // Exit menu directly without choosing an option.
                    if(inputBuffer_ptr->getAndResetBreakoutMenu())
                    {
                        return -1;
                    }
                }while(!spaceBarPressed && arrowPressed != Direction::down && arrowPressed != Direction::up);

                // adjust selection if key was pressed.
                if(arrowPressed == Direction::down && selected < options.size() - 1)
                {
                    selected++;
                }
                if(arrowPressed == Direction::up && selected > 0)
                {
                    selected--;
                }

                // choose option if key was pressed.
                if(spaceBarPressed == true)
                {
                    optionChosen = true;
                }
            }

            return selected;            
        }

    public:
        MenuLogic(std::shared_ptr<ITheme> theme_ptr, std::shared_ptr<IUI> ui_ptr, std::shared_ptr<IInputBufferReader> inputBuffer_ptr)
            : theme_ptr(theme_ptr), ui_ptr(ui_ptr), inputBuffer_ptr(inputBuffer_ptr)
        {
        }

        /**
         * Runs the breakout menu.
         * Returns true, if the game shoud resume, otherwise false.
         */
        bool runBreakoutMenu(std::function<void()> delayFunction)
        {
            std::string title = "Pause";
            ConsoleColour titleColour = ConsoleColour::Yellow;
            std::vector<std::string> textLines;
            std::vector<std::string> options;
            options.push_back("Resume");
            options.push_back("Quit");
            int selection = this->driveMenu(title, titleColour, textLines, options, delayFunction);
            if(selection == 0 || selection == -1)
            {
                return true;
            }
            return false;
        }

};

#endif