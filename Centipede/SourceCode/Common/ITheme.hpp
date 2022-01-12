#ifndef I_THEME_HPP
#define I_THEME_HPP
#include <string>

class ITheme 
{
    public:
        virtual std::string getColourSetupStart() = 0;
        virtual std::string getColourSetupEnd() = 0;
        virtual std::string getWhiteSpace() = 0;
        virtual std::string getCentipedeBody() = 0;
        virtual std::string getCentipedeHead() = 0;
        virtual std::string getMushroom(int health) = 0;
        virtual std::string getStarship() = 0;
        virtual std::string getBullet() = 0;
        virtual std::string getHeart() = 0;
        virtual std::string getFieldEdgeTop() = 0;
        virtual std::string getFieldEdgeLeft() = 0;
        virtual std::string getFieldEdgeBottom() = 0;
        virtual std::string getFieldEdgeRight() = 0;
        virtual std::string getFieldEdgeTopRightCorner() = 0;
        virtual std::string getFieldEdgeTopLeftCorner() = 0;
        virtual std::string getFieldEdgeBottomRightCorner() = 0;
        virtual std::string getFieldEdgeBottomLeftCorner() = 0;
};

#endif