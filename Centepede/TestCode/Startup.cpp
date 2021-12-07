#include "../lib/test_lib.hpp"

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