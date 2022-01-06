#include "../../lib/test_lib.hpp"
#include "../../SourceCode/Common/CentipedeSettings.hpp"
#include "../../SourceCode/GameObjects/CentipedeBody.hpp"

bool centipedeBody_initTest()
{
	printSubTestName("CentipedeBody init test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(0, 0, settings);
	auto tail = std::make_shared<CentipedeBody>(position, nullptr);
	
	auto body = new CentipedeBody(*position, tail, CentipedeMovingDirection::cRight);
	auto bodyPosition = body->getPosition();
	auto result = assertEquals(true, position->equals(bodyPosition));
	result &= assertEquals(tail, body->getTail());
	delete body;
	endTest();
	return result;
}

bool centipedeBody_moveTest()
{
	printSubTestName("CentipedeBody move test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(7, 2, settings);
	auto body = new CentipedeBody(*position, nullptr, CentipedeMovingDirection::cRight);
	auto newPosition = std::make_shared<Position>(6, 2, settings);

	body->move(*newPosition, CentipedeMovingDirection::cRight);
	auto bodyPosition = body->getPosition();

	auto result = assertEquals(true, newPosition->equals(bodyPosition));
	result &= assertEquals(CentipedeMovingDirection::cRight, body->getMovingDirection());
	delete body;
	endTest();
	return result;
}

void runCentipedeBodyTest()
{
	printTestName("CentipedeBody Test");
	auto result = centipedeBody_initTest();
	result &= centipedeBody_moveTest();
	printTestSummary(result);
}

