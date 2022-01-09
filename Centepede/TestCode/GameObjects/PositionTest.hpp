#include "../../lib/test_lib.hpp"
#include "../../SourceCode/Common/CentipedeSettings.hpp"
#include "../../SourceCode/GameObjects/Position.hpp"

bool position_init0Test(){
    printSubTestName("Position init 0 test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto position = new Position(0, 0, settings);
    auto result = assertEquals(0, position->getLine());
    result &= assertEquals(0, position->getColumn());
    delete position;
    endTest();
    return result;
}

bool position_getLineTest(){
    printSubTestName("Position get line test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto position = new Position(5, 0, settings);
    auto result = assertEquals(5, position->getLine());
    delete position;
    endTest();
    return result;
}

bool position_getColumnTest(){
    printSubTestName("Position get column test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto position = new Position(0, 5, settings);
    auto result = assertEquals(5, position->getColumn());
    delete position;
    endTest();
    return result;
}

bool position_initMaxTest(){
    printSubTestName("Position init max test");
    auto settings = std::make_shared<CentipedeSettings>();
    // If there are 10 Columns on the Field, they are given the Indizes 0 to 9.
    auto position = new Position(9, 10, settings);
    auto result = assertEquals(9, position->getLine());
    result &= assertEquals(10, position->getColumn());
    delete position;
    endTest();
    return result;
}

bool position_initBelow0Test(){
    printSubTestName("Position init below 0 test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto position = new Position(-1, -1, settings);
    auto result = assertEquals(0, position->getLine());
    result &= assertEquals(0, position->getColumn());
    delete position;
    endTest();
    return result;
}

bool position_initAboveMaxTest(){
    printSubTestName("Position init above max test");
    auto settings = std::make_shared<CentipedeSettings>();
    // If there are 10 Columns on the Field, they are given the indizes 0 to 9.
    auto position = new Position(10, 11, settings);
    auto result = assertEquals(0, position->getLine());
    result &= assertEquals(0, position->getColumn());
    delete position;
    endTest();
    return result;
}

bool position_upTest(){
    printSubTestName("Position up test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto position = new Position(9, 0, settings);
    auto moved = position->up();
    auto result = assertEquals(true, moved);
    result &= assertEquals(8, position->getLine());
    delete position;
    endTest();
    return result;
}

bool position_upOutOfBoundsTest(){
    printSubTestName("Position up out of bounds test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto position = new Position(0, 0, settings);
    auto moved = position->up();
    auto result = assertEquals(false, moved);
    result &= assertEquals(0, position->getLine());
    delete position;
    endTest();
    return result;
}

bool position_downTest(){
    printSubTestName("Position down test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto position = new Position(0, 0, settings);
    auto moved = position->down();
    auto result = assertEquals(true, moved);
    result &= assertEquals(1, position->getLine());
    delete position;
    endTest();
    return result;
}

bool position_downOutOfBoundsTest(){
    printSubTestName("Position down out of bounds test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto position = new Position(9, 0, settings);
    auto moved = position->down();
    auto result = assertEquals(false, moved);
    result &= assertEquals(9, position->getLine());
    delete position;
    endTest();
    return result;
}

bool position_leftTest(){
    printSubTestName("Position left test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto position = new Position(0, 10, settings);
    auto moved = position->left();
    auto result = assertEquals(true, moved);
    result &= assertEquals(9, position->getColumn());
    delete position;
    endTest();
    return result;
}

bool position_leftOutOfBoundsTest(){
    printSubTestName("Position left out of bounds test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto position = new Position(0, 0, settings);
    auto moved = position->left();
    auto result = assertEquals(false, moved);
    result &= assertEquals(0, position->getColumn());
    delete position;
    endTest();
    return result;
}

bool position_rightTest(){
    printSubTestName("Position right test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto position = new Position(0, 0, settings);
    auto moved = position->right();
    auto result = assertEquals(true, moved);
    result &= assertEquals(1, position->getColumn());
    delete position;
    endTest();
    return result;
}

bool position_rightOutOfBoundsTest(){
    printSubTestName("Position right out of bounds test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto position = new Position(0, 10, settings);
    auto moved = position->right();
    auto result = assertEquals(false, moved);
    result &= assertEquals(10, position->getColumn());
    delete position;
    endTest();
    return result;
}

bool position_equalsTrueTest(){
    printSubTestName("Position equals true test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto position = new Position(9, 5, settings);
    Position other(9, 5, settings);
    auto equals = position->equals(other);
    auto result = assertEquals(true, equals);
    delete position;
    endTest();
    return result;
}

bool position_equalsFalseTest(){
    printSubTestName("Position equals false test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto position = new Position(9, 5, settings);
    Position other(3, 7, settings);
    auto equals = position->equals(other);
    auto result = assertEquals(false, equals);
    delete position;
    endTest();
    return result;
}

bool position_equalsLineColumnTrueTest(){
    printSubTestName("Position equals line column true test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto position = new Position(9, 5, settings);
    auto equals = position->equals(9, 5);
    auto result = assertEquals(true, equals);
    delete position;
    endTest();
    return result;
}

bool position_equalsLineColumnFalseTest(){
    printSubTestName("Position equals line column false test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto position = new Position(9, 5, settings);
    auto equals = position->equals(3, 7);
    auto result = assertEquals(false, equals);
    delete position;
    endTest();
    return result;
}

void runPositionTest(){
    printTestName("Position Test");
    auto result = position_init0Test();
    result &= position_getLineTest();
    result &= position_getColumnTest();
    result &= position_initMaxTest();
    result &= position_initBelow0Test();
    result &= position_initAboveMaxTest();
    result &= position_upTest();
    result &= position_upOutOfBoundsTest();
    result &= position_downTest();
    result &= position_downOutOfBoundsTest();
    result &= position_leftTest();
    result &= position_leftOutOfBoundsTest();
    result &= position_rightTest();
    result &= position_rightOutOfBoundsTest();
    result &= position_equalsTrueTest();
    result &= position_equalsFalseTest();
    result &= position_equalsLineColumnTrueTest();
    result &= position_equalsLineColumnFalseTest();
    printTestSummary(result);
}