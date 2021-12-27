#ifndef CONSOLE_LIB_HPP
#define CONSOLE_LIB_HPP

#include <iostream>
#include <fstream>

int showOptions(std::shared_ptr<std::vector<std::string>> options);

std::string readSingleConsoleInput();

void println(std::string content);

void print(std::string content);

bool askYN(std::string question);

class AnsiExcapeCodes{
    public:
    static std::string clearFormat;

    static std::string boldOn;
    static std::string italicsOn;
    static std::string underlineOn;
    static std::string inverseColoursOn;
    static std::string strikethroughOn;
    static std::string boldOff;
    static std::string italicsOff;
    static std::string underlineOff;
    static std::string inverseColoursOff;
    static std::string strikethroughOff;

    static std::string foregroundBlack;
    static std::string foregroundRed;
    static std::string foregroundGreen;
    static std::string foregroundYellow;
    static std::string foregroundBlue;
    static std::string foregroundMagenta;
    static std::string foregroundCyan;
    static std::string foregroundWhite;
    static std::string foregroundDefault;

    static std::string backgroundBlack;
    static std::string backgroundRed;
    static std::string backgroundGreen;
    static std::string backgroundYellow;
    static std::string backgroundBlue;
    static std::string backgroundMagenta;
    static std::string backgroundCyan;
    static std::string backgroundWhite;
    static std::string backgroundDefault;

    static std::string eraseInDisplay;
    static std::string clearScrollback;
};

#endif