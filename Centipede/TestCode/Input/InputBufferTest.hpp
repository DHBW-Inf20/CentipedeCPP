#include "../../lib/test_lib.hpp"
#include "../../SourceCode/Input/InputBuffer.hpp"
#include "../../SourceCode/Common/Directions.hpp"

bool inputBuffer_DefaultValueTest(){
    printSubTestName("InputBuffer default value test");
    auto buffer = new InputBuffer;
    auto result = assertEquals(Direction::none, buffer->getAndResetDirection());
    result = assertEquals(false, buffer->getAndResetShot()) & result;
    result = assertEquals(false, buffer->getAndResetBreakoutMenu()) & result;
    delete buffer;
    endTest();
    return result;
}

bool inputBuffer_SetDirectionTest(){
    printSubTestName("InputBuffer set direction test");
    auto buffer = new InputBuffer;
    auto newDirection = Direction::left;
    buffer->setDirection(newDirection);
    auto result = assertEquals(newDirection, buffer->getAndResetDirection());
    delete buffer;
    endTest();
    return result;
}

bool inputBuffer_SetDirectionFailAtNoneTest(){
    printSubTestName("InputBuffer set direction: fail at 'none' test");
    auto buffer = new InputBuffer;
    bool error = false;
    try{
        buffer->setDirection(Direction::none);
    }catch(std::logic_error e){
        error = true;
    }
    auto result = assertEquals(true, error);
    delete buffer;
    endTest();
    return result;
}

bool inputBuffer_SetShotTest(){
    printSubTestName("InputBuffer set shot test");
    auto buffer = new InputBuffer;
    buffer->setShot();
    auto result = assertEquals(true, buffer->getAndResetShot());
    delete buffer;
    endTest();
    return result;
}

bool inputBuffer_SetBreakoutMenuTest(){
    printSubTestName("InputBuffer set breakout menu test");
    auto buffer = new InputBuffer;
    buffer->setBreakoutMenu();
    auto result = assertEquals(true, buffer->getAndResetBreakoutMenu());
    delete buffer;
    endTest();
    return result;
}

bool inputBuffer_ResetAfterGetDirectionTest(){
    printSubTestName("InputBuffer reset after get direction test");
    auto buffer = new InputBuffer;
    buffer->setDirection(Direction::left);
    buffer->getAndResetDirection();
    auto result = assertEquals(none, buffer->getAndResetDirection());
    delete buffer;
    endTest();
    return result;
}

bool inputBuffer_ResetAfterGetShotTest(){
    printSubTestName("InputBuffer reset after get shot test");
    auto buffer = new InputBuffer;
    buffer->setShot();
    buffer->getAndResetShot();
    auto result = assertEquals(false, buffer->getAndResetShot());
    delete buffer;
    endTest();
    return result;
}

bool inputBuffer_ResetAfterGetBreakoutMenuTest(){
    printSubTestName("InputBuffer reset after get breakout menu test");
    auto buffer = new InputBuffer;
    buffer->setBreakoutMenu();
    buffer->getAndResetBreakoutMenu();
    auto result = assertEquals(false, buffer->getAndResetBreakoutMenu());
    delete buffer;
    endTest();
    return result;
}

void runInputBufferTest(){
    printTestName("InputBuffer Test");
    auto result = inputBuffer_DefaultValueTest();
    result &= inputBuffer_SetDirectionTest();
    result &= inputBuffer_SetDirectionFailAtNoneTest();
    result &= inputBuffer_SetShotTest();
    result &= inputBuffer_SetBreakoutMenuTest();
    result &= inputBuffer_ResetAfterGetDirectionTest();
    result &= inputBuffer_ResetAfterGetShotTest();
    result &= inputBuffer_ResetAfterGetBreakoutMenuTest();
    printTestSummary(result);
}