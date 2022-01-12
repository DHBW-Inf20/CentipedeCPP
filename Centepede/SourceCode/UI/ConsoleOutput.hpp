#ifndef CONSOLEOUTPUT_HPP
#define CONSOLEOUTPUT_HPP
#include <iostream>
#include "../../lib/console_lib.hpp"
#include "../Common/CentipedeSettings.hpp"
#include "../Common/ITheme.hpp"
#include "../Common/IUI.hpp"
#include "../GameObjects/SaveState.hpp"
#include "../GameObjects/MushroomMap.hpp"
#include "../GameObjects/CentipedeHead.hpp"
#include "../GameObjects/Bullet.hpp"
#include "../GameObjects/Starship.hpp"

class ConsoleOutput : public IUI
{
	private:
		/**
		 * Frames the given image
		 */
		void writeToConsole(std::shared_ptr<std::string> frame, ITheme &theme)
		{
			AnsiExcapeCodes ansiExcapeCodes;

			// Clear screen
			std::cout << ansiExcapeCodes.eraseInDisplay;
			// Prepare colours
			std::cout << theme.getColourSetupStart();
			// Output frame of game
			std::cout << *frame;
			// End colours
			std::cout << theme.getColourSetupEnd();
		}

		/**
		 * Returns a string consisting of the exact number of white-spaces to fill the line.
		 */
		std::string getFillingSpaces(int numberOfColumns, int takenSpace, ITheme &theme)
		{
			std::string fillingSpaces = "";
			// "+ 2" is necessary because of the border around the game.
			int numberOfSpaces = (numberOfColumns + 2) - takenSpace;
			for(int i = 0; i < numberOfSpaces; i++)
			{
				fillingSpaces += theme.getWhiteSpace();
			}
			return fillingSpaces;
		}

        // //////////////////////////////////////////////////
        // Image rendering
        // //////////////////////////////////////////////////

		/**
		 * Renders a border and the score around a given image of GameObjects. Returns the result as single string.
		 */
		std::shared_ptr<std::string> renderFrame(int round, int lives, int score, std::shared_ptr<std::vector<std::vector<std::string>>> image, ITheme &theme)
		{
			AnsiExcapeCodes ansiExcapeCodes;
			std::string newLine = "\r\n";
			std::string output = "";
			int numberOfColumns = (*image)[0].size();

			// Top line with score and round.
			std::string scoreText = "Score: " + std::to_string(score);
			std::string roundText = "Round: " + std::to_string(round);
			output += ansiExcapeCodes.boldOn + scoreText;
			output += getFillingSpaces(numberOfColumns, scoreText.size() + roundText.size(), theme);
			output += roundText + ansiExcapeCodes.boldOff + newLine;

			// Second line with hearts.
			output += " "; // Indent to match the inner Playing-Field.
			for(int i = 0; i < lives; i++) output += theme.getHeart();
			output += getFillingSpaces(numberOfColumns, lives + 1, theme) + newLine;


			// Upper field edge:
			output += theme.getFieldEdgeTopLeftCorner();
			for(int column = 0; column < numberOfColumns; column++)
			{
				output += theme.getFieldEdgeTop();
			}
			output += theme.getFieldEdgeTopRightCorner();
			output += newLine;

			// Build image 
			for(auto line : *image)
			{
				// Start line with field edge
				output += theme.getFieldEdgeLeft();
				// Content
				for(auto column : line)
				{
					output += column;
				}
				// End line with field edge
				output += theme.getFieldEdgeRight();
				output += newLine;
			}

			// Lower field edge
			output += theme.getFieldEdgeBottomLeftCorner();
			for(int column = 0; column < (*image)[0].size(); column++)
			{
				output += theme.getFieldEdgeBottom();
			}
			output += theme.getFieldEdgeBottomRightCorner();
			output += newLine;

			return std::make_shared<std::string>(output);
		}

		/**
		 * Renders all GameObjects on the given canvas.
		 */
		void renderGameObjects(std::shared_ptr<std::vector<std::vector<std::string>>> canvas, SaveState &state, ITheme& theme)
		{
			this->renderBase(canvas, theme);
			this->renderMushrooms(canvas, state.getMushroomMap(), theme);
			this->renderCentipedes(canvas, state.getCentipedes(), theme);
			this->renderBullets(canvas, state.getBullets(), theme);
			this->renderStarship(canvas, state.getStarship(), theme);
		}

		/**
		 * Initializes the Canvas by filling it whith "spaces".
		 */
		void renderBase(std::shared_ptr<std::vector<std::vector<std::string>>> canvas, ITheme& theme)
		{

			for(int line = 0; line < canvas->size(); line++)
			{
				for(int column = 0; column < (*canvas)[line].size(); column++)
				{
					(*canvas)[line][column] = theme.getWhiteSpace();
				}
			}
		}

		/**
		 * Renders the mushrooms with individual health on the canvas.
		 */
		void renderMushrooms(std::shared_ptr<std::vector<std::vector<std::string>>> canvas, std::shared_ptr<MushroomMap> mushroomMap_ptr, ITheme& theme)
		{
			for(int line = 0; line < canvas->size(); line++)
			{
				for(int column = 0; column < (*canvas)[line].size(); column++)
				{
					auto health = mushroomMap_ptr->getMushroom(line, column);
					if(health > 0)
					{
						// Mushroom with specific health
						(*canvas)[line][column] = theme.getMushroom(health);
					}
					// no mushroom otherwise
				}
			}
		}

		/**
		 * Renders the centipedes on the canvas.
		 */
		void renderCentipedes(std::shared_ptr<std::vector<std::vector<std::string>>> canvas, std::shared_ptr<std::vector<CentipedeHead>> centipedes_ptr, ITheme& theme)
		{
			for(auto centipede : *centipedes_ptr)
			{
				// Head
				auto headPosition = centipede.getPosition();
				(*canvas)[headPosition.getLine()][headPosition.getColumn()] = theme.getCentipedeHead();
				// Tail
				auto tail = centipede.getTail();
				while(tail != nullptr)
				{
					auto tailPosition = tail->getPosition();
					(*canvas)[tailPosition.getLine()][tailPosition.getColumn()] = theme.getCentipedeBody();
					// continue recursive
					tail = tail->getTail();
				}
			}
		}

		/**
		 * Renders the bullets on the canvas.
		 */
		void renderBullets(std::shared_ptr<std::vector<std::vector<std::string>>> canvas, std::shared_ptr<std::vector<Bullet>> bullets_ptr, ITheme& theme)
		{
			for(auto bullet : *bullets_ptr)
			{
				auto bulletPosition = bullet.getPosition();
				(*canvas)[bulletPosition.getLine()][bulletPosition.getColumn()] = theme.getBullet();
			}
		}

		/**
		 * Renders the starship on the canvas.
		 */
		void renderStarship(std::shared_ptr<std::vector<std::vector<std::string>>> canvas, std::shared_ptr<Starship> starship_ptr, ITheme& theme)
		{
			auto position = starship_ptr->getPosition();
			(*canvas)[position.getLine()][position.getColumn()] = theme.getStarship();
		}

	public:
		void drawImage(int round, int lives, int score, ITheme& theme, SaveState& state, CentipedeSettings &settings)
		{
			// initialize canvas
			auto canvas = std::make_shared<std::vector<std::vector<std::string>>>(settings.getPlayingFieldHeight());
			std::vector<std::string> lineContainer(settings.getPlayingFieldWidth());
			for(int line = 0; line < settings.getPlayingFieldHeight(); line++)
			{
				(*canvas)[line] = lineContainer;
			}

			// render image.
			this->renderGameObjects(canvas, state, theme);
			auto frame = this->renderFrame(round, lives, score, canvas, theme);

			// output 
			this->writeToConsole(frame, theme);
		}
};

#endif