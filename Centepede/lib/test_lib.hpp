#include "console_lib.hpp"

// ###############################
// Test Methods
// ###############################
// feel free to add more as you go along

void printTestName(std::string testName){
    std::string dividerLine = "###############################";
    println(dividerLine);
    println(testName);
    println(dividerLine);
}

void printResult(bool passed, std::string errorMessage){
    AnsiExcapeCodes ansiExcapeCodes;
    std::string result;
    if(passed){
        result = ansiExcapeCodes.foregroundGreen + "passed" + ansiExcapeCodes.foregroundDefault;
    }else{ // not passed
        result = ansiExcapeCodes.foregroundRed + "failed: " + errorMessage + ansiExcapeCodes.foregroundDefault;
    }
    println(result);
}

template<typename TObject>
void assertEquals(TObject expected, TObject actual){
    auto equal = expected == actual;
    std::string errorMessage = "value: " + std::to_string(actual) + ", expected: " + std::to_string(expected);
    printResult(equal, errorMessage);
}