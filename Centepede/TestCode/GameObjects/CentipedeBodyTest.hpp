#include "../../lib/test_lib.hpp"
#include "../../SourceCode/Common/CentipedeSettings.hpp"
#include "../../SourceCode/GameObjects/CentipedeBody.hpp"

bool centipedeBody_init0Test()
{
	printSubTestName("CentipedeBody init 0 Test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(0, 0, settings);
	auto body = new CentipedeBody(position, nullptr);
	auto result = assertEquals(0, body->getPosition().getLine());
	result &= assertEquals(0, body->getPosition().getColumn());
	delete body;
	endTest();
	return result;
}

bool centipedeBody_initMaxTest()
{
	printSubTestName("CentipedeBody init Max Test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(settings->getPlayingFieldHeight() - 1, settings->getPlayingFieldWidth() - 1, settings);
	auto body = new CentipedeBody(position, nullptr);
	auto result = assertEquals(settings->getPlayingFieldHeight() - 1, body->getPosition().getLine());
	result &= assertEquals(settings->getPlayingFieldWidth() - 1, body->getPosition().getColumn());
	delete body;
	endTest();
	return result;
}

bool centipedeBody_initOutOfBoundsTest()
{
	printSubTestName("CentipedeBody init out of bounds Test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(-1, settings->getPlayingFieldWidth(), settings);
	auto body = new CentipedeBody(position, nullptr);
	auto result = assertEquals(0, body->getPosition().getLine());
	result &= assertEquals(0, body->getPosition().getColumn());
	delete body;
	endTest();
	return result;
}

bool centipedeBody_getPositionTest()
{
	printSubTestName("CentipedeBody get position Test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(7, 2, settings);
	auto body = new CentipedeBody(position, nullptr);
	auto result = assertEquals(7, body->getPosition().getLine());
	result &= assertEquals(2, body->getPosition().getColumn());
	delete body;
	endTest();
	return result;
}

bool centipedeBody_moveUpTest()
{
	printSubTestName("CentipedeBody move up Test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(7, 2, settings);
	auto body = new CentipedeBody(position, nullptr);
	auto newPosition = std::make_shared<Position>(6, 2, settings);
	body->move(newPosition);
	auto result = assertEquals(6, body->getPosition().getLine());
	result &= assertEquals(2, body->getPosition().getColumn());
	delete body;
	endTest();
	return result;
}

bool centipedeBody_moveDownTest()
{
	printSubTestName("CentipedeBody move down Test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(7, 2, settings);
	auto body = new CentipedeBody(position, nullptr);
	auto newPosition = std::make_shared<Position>(8, 2, settings);
	body->move(newPosition);
	auto result = assertEquals(8, body->getPosition().getLine());
	result &= assertEquals(2, body->getPosition().getColumn());
	delete body;
	endTest();
	return result;
}

bool centipedeBody_moveRightTest()
{
	printSubTestName("CentipedeBody move right Test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(7, 2, settings);
	auto body = new CentipedeBody(position, nullptr);
	auto newPosition = std::make_shared<Position>(7, 3, settings);
	body->move(newPosition);
	auto result = assertEquals(7, body->getPosition().getLine());
	result &= assertEquals(3, body->getPosition().getColumn());
	delete body;
	endTest();
	return result;
}

bool centipedeBody_moveLeftTest()
{
	printSubTestName("CentipedeBody move left Test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(7, 2, settings);
	auto body = new CentipedeBody(position, nullptr);
	auto newPosition = std::make_shared<Position>(7, 1, settings);
	body->move(newPosition);
	auto result = assertEquals(7, body->getPosition().getLine());
	result &= assertEquals(1, body->getPosition().getColumn());
	delete body;
	endTest();
	return result;
}

bool centipedeBody_moveOutOfBoundsUpTest()
{
	printSubTestName("CentipedeBody move up out of bounds Test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(0, 2, settings);
	auto body = new CentipedeBody(position, nullptr);
	auto newPosition = std::make_shared<Position>(-1, 2, settings);
	body->move(newPosition);
	auto result = assertEquals(0, body->getPosition().getLine());
	result &= assertEquals(2, body->getPosition().getColumn());
	delete body;
	endTest();
	return result;
}

bool centipedeBody_moveOutOfBoundsDownTest()
{
	printSubTestName("CentipedeBody move down out of bounds Test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(settings->getPlayingFieldHeight - 1, 2, settings);
	auto body = new CentipedeBody(position, nullptr);
	auto newPosition = std::make_shared<Position>(settings->getPlayingFieldHeight, 2, settings);
	body->move(newPosition);
	auto result = assertEquals(settings->getPlayingFieldHeight - 1, body->getPosition().getLine());
	result &= assertEquals(2, body->getPosition().getColumn());
	delete body;
	endTest();
	return result;
}

bool centipedeBody_moveOutOfBoundsRightTest()
{
	printSubTestName("CentipedeBody move right out of bounds Test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(7, settings->getPlayingFieldWidth - 1, settings);
	auto body = new CentipedeBody(position, nullptr);
	auto newPosition = std::make_shared<Position>(7, settings->getPlayingFieldWidth, settings);
	body->move(newPosition);
	auto result = assertEquals(7, body->getPosition().getLine());
	result &= assertEquals(settings->getPlayingFieldWidth - 1, body->getPosition().getColumn());
	delete body;
	endTest();
	return result;
}

bool centipedeBody_moveOutOfBoundsLeftTest()
{
	printSubTestName("CentipedeBody move left out of bounds Test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(7, 0, settings);
	auto body = new CentipedeBody(position, nullptr);
	auto newPosition = std::make_shared<Position>(7, -1, settings);
	body->move(newPosition);
	auto result = assertEquals(7, body->getPosition().getLine());
	result &= assertEquals(0, body->getPosition().getColumn());
	delete body;
	endTest();
	return result;
}

void runCentipedeBodyTest()
{
	printTestName("Centipede Test");
	auto result = centipedeBody_init0Test();
	result &= centipedeBody_initMaxTest();
	result &= centipedeBody_initOutOfBoundsTest();
	result &= centipedeBody_getPositionTest();
	result &= centipedeBody_moveUpTest();
	result &= centipedeBody_moveDownTest();
	result &= centipedeBody_moveLeftTest();
	result &= centipedeBody_moveRightTest();
	result &= centipedeBody_moveOutOfBoundsUpTest();
	result &= centipedeBody_moveOutOfBoundsDownTest();
	result &= centipedeBody_moveOutOfBoundsLeftTest();
	result &= centipedeBody_moveOutOfBoundsRightTest();
	printTestSummary(result);
}

