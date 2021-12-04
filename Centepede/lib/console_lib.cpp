#include "console_lib.hpp"
#include "string_helper.hpp"
#include <vector>
#include <iostream>
#include <fstream>

int showOptions(std::shared_ptr<std::vector<std::string>> options){
    int choice;
    bool isInvalidChoice;
    int maxNumItem = options->size();

    do{
        std::cout << "Please choose one of the following options:" << std::endl;
        std::cout << "0) Exit" << std::endl;
        for(int i = 0; i < maxNumItem; i++){
            std::cout << i + 1 << ") " << (*options)[i] << std::endl;
        }

        std::cin >> choice;
        isInvalidChoice = choice < 0 || choice > maxNumItem;

        if(isInvalidChoice){
            std::cout << "Please type a number between " << 0 << " and " << maxNumItem << "!" << std::endl;
        }
    }while(isInvalidChoice);
    
    return choice;
}

std::string readSingleConsoleInput(){
    std::string input;
    std::cin >> input;
    return input;
}

void println(std::string content){
    std::cout << content << std::endl;
}

bool askYN(std::string question){
    println(question + " (y/n)");
    bool hasAnswer;
    bool answer;
    while(!hasAnswer){
        auto answerString = readSingleConsoleInput();
        try{
            answer = parseYN(answerString);
            hasAnswer = true;
        }catch(std::logic_error error){
            println("Bitte antworte mit y oder n:");
        }
    }
    return answer;
}

std::string AnsiExcapeCodes::clearFormat="\e[0m";

std::string AnsiExcapeCodes::boldOn="\e[1m";
std::string AnsiExcapeCodes::italicsOn="\e[3m";
std::string AnsiExcapeCodes::underlineOn="\e[4m";
std::string AnsiExcapeCodes::inverseColoursOn="\e[7m";
std::string AnsiExcapeCodes::strikethroughOn="\e[9m";
std::string AnsiExcapeCodes::boldOff="\e[22m";
std::string AnsiExcapeCodes::italicsOff="\e[23m";
std::string AnsiExcapeCodes::underlineOff="\e[24m";
std::string AnsiExcapeCodes::inverseColoursOff="\e[27m";
std::string AnsiExcapeCodes::strikethroughOff="\e[29m";

std::string AnsiExcapeCodes::foregroundBlack="\e[30m";
std::string AnsiExcapeCodes::foregroundRed="\e[31m";
std::string AnsiExcapeCodes::foregroundGreen="\e[32m";
std::string AnsiExcapeCodes::foregroundYellow="\e[33m";
std::string AnsiExcapeCodes::foregroundBlue="\e[34m";
std::string AnsiExcapeCodes::foregroundMagenta="\e[35m";
std::string AnsiExcapeCodes::foregroundCyan="\e[36m";
std::string AnsiExcapeCodes::foregroundWhite="\e[37m";
std::string AnsiExcapeCodes::foregroundDefault="\e[39m";

std::string AnsiExcapeCodes::backgroundBlack="\e[40m";
std::string AnsiExcapeCodes::backgroundRed="\e[41m";
std::string AnsiExcapeCodes::backgroundGreen="\e[42m";
std::string AnsiExcapeCodes::backgroundYellow="\e[43m";
std::string AnsiExcapeCodes::backgroundBlue="\e[44m";
std::string AnsiExcapeCodes::backgroundMagenta="\e[45m";
std::string AnsiExcapeCodes::backgroundCyan="\e[46m";
std::string AnsiExcapeCodes::backgroundWhite="\e[47m";
std::string AnsiExcapeCodes::backgroundDefault="\e[49m";

std::string AnsiExcapeCodes::eraseInDisplay="\x1B[2J\x1B[H";
std::string AnsiExcapeCodes::clearScrollback="\x1B[3J\x1B[H";