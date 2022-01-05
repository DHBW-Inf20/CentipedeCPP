#ifndef I_THEME_HPP
#define I_THEME_HPP
#include <string>

class ITheme 
{
    public:
        virtual std::string getColourSetupStart();
        virtual std::string getColourSetupEnd();
        virtual std::string getWhiteSpace();
        virtual std::string getCentipedeBody();
        virtual std::string getCentipedeHead();
        virtual std::string getMushroom(int health);
        virtual std::string getStarship();
        virtual std::string getBullet();
        virtual std::string getFieldEdgeTop();
        virtual std::string getFieldEdgeLeft();
        virtual std::string getFieldEdgeBottom();
        virtual std::string getFieldEdgeRight();
        virtual std::string getFieldEdgeTopRightCorner();
        virtual std::string getFieldEdgeTopLeftCorner();
        virtual std::string getFieldEdgeBottomRightCorner();
        virtual std::string getFieldEdgeBottomLeftCorner();
};

#endif