#ifndef TEST_LIB_HPP
#define TEST_LIB_HPP
#include "console_lib.hpp"

// ###############################
// Test Methods
// ###############################
// feel free to add more as you go along


/**
 * prints the Name of the current test to the console.
 */
void printTestName(std::string testName){
    AnsiExcapeCodes ansiExcapeCodes;
    std::string dividerLine = "###############################";
    println(dividerLine);
    println(ansiExcapeCodes.boldOn + testName + ansiExcapeCodes.boldOff);
    println(dividerLine);
}

/**
 * prints the Name of the current test to the console.
 */
void printSubTestName(std::string testName){
    print(testName + ": ");
}

std::string getColouredResult(bool passed, std::string errorMessage){
    AnsiExcapeCodes ansiExcapeCodes;
    if(passed){
        return ansiExcapeCodes.foregroundGreen + "passed" + ansiExcapeCodes.foregroundDefault;
    }else{ // not passed
        return ansiExcapeCodes.foregroundRed + "failed: " + errorMessage + ansiExcapeCodes.foregroundDefault;
    }
}

/**
 * prints a result to the console.
 */
void printResult(bool passed, std::string errorMessage){
    std::string result = getColouredResult(passed, errorMessage);
    print(result + " ");
}

void printTestSummary(bool passed){
    AnsiExcapeCodes ansiExcapeCodes;
    println(ansiExcapeCodes.boldOn + "Summary: " + getColouredResult(passed, "Please check previous messages for details.") + ansiExcapeCodes.boldOff);
}

/**
 * Compares the first value (expected) with the second value (actual) and prints the result to the console.
 */
template<typename TObject>
bool assertEquals(TObject expected, TObject actual){
    auto equal = expected == actual;
    std::string errorMessage = "value: " + std::to_string(actual) + ", expected: " + std::to_string(expected);
    printResult(equal, errorMessage);
    return equal;
}

void endTest(){
    println("");
}

#endif