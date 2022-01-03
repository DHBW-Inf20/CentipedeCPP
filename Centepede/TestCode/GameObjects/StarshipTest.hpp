#include "../../lib/test_lib.hpp"
#include "../../SourceCode/Common/CentipedeSettings.hpp"
#include "../../SourceCode/GameObjects/Starship.hpp"

bool starship_init0Test()
{
	printSubTestName("Starship init 0 test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto starship = new Starship(0, 0, settings);
    auto result = assertEquals(0, starship->getPosition().getLine());
    result &= assertEquals(0, starship->getPosition().getColumn());
    delete starship;
    endTest();
    return result;
}

bool starship_getPositionTest() 
{
    printSubTestName("Starship get position test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto starship = new Starship(7, 2, settings);
    auto result = assertEquals(7, starship->getPosition().getLine());
    result &= assertEquals(2, starship->getPosition().getColumn());
    delete starship;
    endTest();
    return result;
}

bool starship_moveNoneLineTest() 
{
    printSubTestName("Starship move none line test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto starship = new Starship(7, 2, settings);
    auto moved = starship->move(Direction none);
    auto result = assertEquals(7, starship->getPosition().getLine());
    result &= assertEquals(true, moved);
    delete starship;
    endTest();
    return result;
}

bool starship_moveNoneColumnTest() 
{
    printSubTestName("Starship move none column test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto starship = new Starship(7, 2, settings);
    auto moved = starship->move(Direction none);
    auto result = assertEquals(2, starship->getPosition().getColumn());
    result &= assertEquals(true, moved);
    delete starship;
    endTest();
    return result;
}

bool starship_moveUpTest() 
{
    printSubTestName("Starship move up test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto starship = new Starship(7, 2, settings);
    auto moved = starship->move(Direction up);
    auto result = assertEquals(6, starship->getPosition().getLine());
    result &= assertEquals(true, moved);
    delete starship;
    endTest();
    return result;
}

bool starship_moveDownTest() 
{
    printSubTestName("Starship move down test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto starship = new Starship(7, 2, settings);
    auto moved = starship->move(Direction down);
    auto result = assertEquals(8, starship->getPosition().getLine());
    result &= assertEquals(true, moved);
    delete starship;
    endTest();
    return result;
}

bool starship_moveRightTest() 
{
    printSubTestName("Starship move right test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto starship = new Starship(7, 2, settings);
    auto moved = starship->move(Direction right);
    auto result = assertEquals(3, starship->getPosition().getColumn());
    result &= assertEquals(true, moved);
    delete starship;
    endTest();
    return result;
}

bool starship_moveLeftTest() 
{
    printSubTestName("Starship move left test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto starship = new Starship(7, 2, settings);
    auto moved = starship->move(Direction left);
    auto result = assertEquals(1, starship->getPosition().getColumn());
    result &= assertEquals(true, moved);
    delete starship;
    endTest();
    return result;
}

bool starship_moveOutOfBoundsUpTest() 
{
    printSubTestName("Starship move out of bounds at top test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto starship = new Starship(0, 2, settings);
    auto moved = starship->move(Direction up);
    auto result = assertEquals(false, moved);
    delete starship;
    endTest();
    return result;
}

bool starship_moveOutOfBoundsDownTest() 
{
    printSubTestName("Starship move out of bounds at bottom test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto starship = new Starship(settings->getPlayingFieldHeight() - 1, 2, settings);
    auto moved = starship->move(Direction down);
    auto result = assertEquals(false, moved);
    delete starship;
    endTest();
    return result;
}

bool starship_moveOutOfBoundsLeftTest()
{
    printSubTestName("Starship move out of bounds at left test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto starship = new Starship(2, 0, settings);
    auto moved = starship->move(Direction left);
    auto result = assertEquals(false, moved);
    delete starship;
    endTest();
    return result;
}

bool starship_moveOutOfBoundsRightTest()
{
    printSubTestName("Starship move out of bounds at right test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto starship = new Starship(2, settings->getPlayingFieldWidth() - 1, settings);
    auto moved = starship->move(Direction right);
    auto result = assertEquals(false, moved);
    delete starship;
    endTest();
    return result;
}

void runStarshipTest() 
{
    printTestName("Starship Test");
    auto result = starship_init0Test();
    result &= starship_getPositionTest();
    result &= starship_moveNoneLineTest();
    result &= starship_moveNoneColumnTest();
    result &= starship_moveUpTest();
    result &= starship_moveDownTest();
    result &= starship_moveRightTest();
    result &= starship_moveLeftTest();
    result &= starship_moveOutOfBoundsUpTest();
    result &= starship_moveOutOfBoundsDownTest();
    result &= starship_moveOutOfBoundsLeftTest();
    result &= starship_moveOutOfBoundsRightTest();
    printTestSummary(result);
}