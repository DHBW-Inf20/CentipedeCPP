#include "../lib/console_lib.hpp"

// ###############################
// Framework Methods
// ###############################
// feel free to add more as you need

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

// ###############################
// Example Test Methods
// ###############################
// please write real tests their own files

void exampleTestPassing(){
    printTestName("Example Test passing");
    assertEquals(10, 10);
}

void exampleTestFailing(){
    printTestName("Example Test failing");
    assertEquals(10, 12);
}

// ###############################
// Run Tests
// ###############################

int main(int argc, char** argv){
    // example Tests, remove when real tests are run.
    exampleTestPassing();
    exampleTestFailing();

    // call tests here:
}