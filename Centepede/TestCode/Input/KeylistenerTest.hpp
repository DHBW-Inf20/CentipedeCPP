#ifndef KEYLISTENER_TEST_HPP
#define KEYLISTENER_TEST_HPP

#include "../../SourceCode/Input/Keylistener.hpp"
#include "../../lib/test_lib.hpp"
#include "../../lib/console_lib.hpp"
#include "../../lib/concurrency_lib.hpp"

bool keylistener_startStopTest(){
    printSubTestName("Keylistener start stop test");
    
    // Init objects
    Keylistener keylistener;

    // Check for errors
    try{
        keylistener.startMultithreaded();
    }catch(...){
        printResult(false, "Starting failed");
        return false;
    }
    try{
        keylistener.stop();
    }catch(...){
        printResult(false, "Stopping failed");
        return false;
    }

    // Print result
    printResult(true, "");
    return true;
}

bool keylistener_registerHandlerTest(){
    printSubTestName("Keylistener register handler test");
    // Init objects
    Keylistener keylistener;
    Signal tSignal;
    auto testhandler = [&tSignal]()
    { 
        tSignal.signal(); 
    };

    // Register Handler
    keylistener.registerHandler('t', testhandler);
    keylistener.startMultithreaded();

    // Wait for trigger to verify the Handler has been added
    print("Press 't': ");
    tSignal.await();
    keylistener.stop();

    // Print result
    // If fails: Never ends
    printResult(true, "");
    return true;
}

bool keylistener_overwriteHandlerTest(){
    printSubTestName("Keylistener overwrite handler test");
    // Init objects
    Keylistener keylistener;
    bool result = true;
    Signal tSignal;
    auto testhandler = [&result]()
    {
        // This should never be called
        result = false; 
    };
    auto overwrite = [&tSignal]()
    { 
        tSignal.signal(); 
    };

    // register handler to be overwritten
    keylistener.registerHandler('t', testhandler);
    // overwrite with working handler
    keylistener.registerHandler('t', overwrite);

    // wait for signal to verify working handler is active, while first one needs to be disabled
    keylistener.startMultithreaded();
    print("Press 't': ");
    tSignal.await();
    keylistener.stop();

    // print result
    printResult(result, "fist handler still active");
    return result;
}

bool keylistener_addHandlerWhileRunningTest(){
    printSubTestName("Keylistener add handler while running test");
    // First start the listener
    Keylistener keylistener;
    keylistener.startMultithreaded();
    Signal tSignal;

    // then add the handler
    auto testhandler = [&tSignal]()
    { 
        tSignal.signal(); 
    };
    keylistener.registerHandler('t', testhandler);

    // wait for signal to verify handler is working
    print("Press 't':");
    tSignal.await();
    keylistener.stop();

    // print result
    // never ends if not working
    printResult(true, "");
    return true;
}

bool keylistener_removeHandlerTest(){
    printSubTestName("Keylistener remove handler test");
    // Init objects
    Keylistener keylistener;
    bool result = true;
    Signal tSignal;
    auto testhandler = [&result]()
    {
        // This should never be called
        result = false; 
    };
    auto helper = [&tSignal]()
    { 
        tSignal.signal(); 
    };

    // register handler to be removed again
    keylistener.registerHandler('t', testhandler);
    // add helper handler
    keylistener.registerHandler('v', helper);
    // remove 't' handler
    keylistener.removeHandler('t');

    // wait for signal to verify working handler is active, while first one needs to be disabled
    keylistener.startMultithreaded();
    print("Press in order: 't' then 'v':");
    tSignal.await();
    keylistener.stop();

    // print result
    printResult(result, "fist handler still active");
    return result;
}

/**
 * ##########################
 * ! Needs User Interaction !
 * ##########################
 */
void runKeylistenerTest(){
    printTestName("Keylistener Test");
    auto result = keylistener_startStopTest();
    result = keylistener_registerHandlerTest() & result;
    result = keylistener_overwriteHandlerTest() & result;
    result = keylistener_addHandlerWhileRunningTest() & result;
    result = keylistener_removeHandlerTest() & result;
    printTestSummary(result);
}

#endif