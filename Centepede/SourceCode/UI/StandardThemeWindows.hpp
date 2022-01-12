#include "../Common/ITheme.hpp"
#include "../../lib/console_lib.hpp"

class StandardThemeWindows
    : public ITheme
{
    private:
        AnsiExcapeCodes ansiExcapeCodes;
        std::string backgroundColour;
        std::string foregroundColour;

    public:
        StandardThemeWindows()
        {
            this->backgroundColour = this->ansiExcapeCodes.backgroundBlack;
            this->foregroundColour = this->ansiExcapeCodes.foregroundWhite;
        }

        std::string getColourSetupStart() override
        {
            return this->backgroundColour + this->foregroundColour;
        }

        std::string getColourSetupEnd() override
        {
            return this->ansiExcapeCodes.backgroundDefault + this->ansiExcapeCodes.foregroundDefault;
        }

        std::string getWhiteSpace() override
        {
            return " ";
        }

        std::string getCentipedeBody() override
        {
            return "B";
        }

        std::string getCentipedeHead() override
        {
            return "H";
        }

        std::string getMushroom(int health) override
        {
            std::string mushroom = "M";
            switch (health)
            {
            case 0:
                return this->getWhiteSpace();
                break;
            case 1:
                return this->ansiExcapeCodes.foregroundRed + mushroom + this->foregroundColour;
                break;
            case 2:
                return this->ansiExcapeCodes.foregroundYellow + mushroom + this->foregroundColour;
                break;
            default: // health >= 3
                return this->ansiExcapeCodes.foregroundGreen + mushroom + this->foregroundColour;
                break;
            }
        }

        std::string getStarship() override
        {
            return "A";
        }

        std::string getBullet() override
        {
            return "^";
        }

        std::string getHeart() override
        {
            return "*";
        }

        std::string getFieldEdgeTop() override
        {
            return "#";
        }

        std::string getFieldEdgeLeft() override
        {
            return "#";
        }

        std::string getFieldEdgeBottom() override
        {
            return "#";
        }

        std::string getFieldEdgeRight() override
        {
            return "#";
        }

        std::string getFieldEdgeTopRightCorner() override
        {
            return "#";
        }

        std::string getFieldEdgeTopLeftCorner() override
        {
            return "#";
        }

        std::string getFieldEdgeBottomRightCorner() override
        {
            return "#";
        }

        std::string getFieldEdgeBottomLeftCorner() override
        {
            return "#";
        }

};