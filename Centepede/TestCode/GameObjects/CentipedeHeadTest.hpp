#include "../../lib/test_lib.hpp"
#include "../../SourceCode/Common/CentipedeSettings.hpp"
#include "../../SourceCode/GameObjects/CentipedeBody.hpp"
#include "../../SourceCode/GameObjects/CentipedeHead.hpp"

bool centipedeHead_initNew1Test()
{
	printSubTestName("CentipedeHead init new 1 test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(7, 2, settings);
	
	auto head = new CentipedeHead(position->getLine(), position->getColumn(), CentipedeMovingDirection::cRight, settings, 1);
	auto headPosition = head->getPosition();
	auto result = assertEquals(true, position->equals(headPosition));
	result &= assertEquals(CentipedeMovingDirection::cRight, head->getMovingDirection());
	result &= assertEquals<std::shared_ptr<CentipedeBody>>(nullptr, head->getTail());

	delete head;
	endTest();
	return result;
}

bool centipedeHead_initNewSmaller1Test()
{
	printSubTestName("CentipedeHead init new smaller 1 test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(7, 2, settings);
	
	auto head = new CentipedeHead(position->getLine(), position->getColumn(), CentipedeMovingDirection::cRight, settings, 0);
	auto headPosition = head->getPosition();
	auto result = assertEquals(true, position->equals(headPosition));
	result &= assertEquals(CentipedeMovingDirection::cRight, head->getMovingDirection());
	result &= assertEquals<std::shared_ptr<CentipedeBody>>(nullptr, head->getTail());

	delete head;
	endTest();
	return result;
}

bool centipedeHead_initNewBigger1Test()
{
	printSubTestName("CentipedeHead init new bigger 1 test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(7, 2, settings);
	
    // 3 means: Centipede of 3 parts -> Head Body1 Body2
	auto head = new CentipedeHead(position->getLine(), position->getColumn(), CentipedeMovingDirection::cRight, settings, 3);
    auto body1 = head->getTail();
    auto body2 = body1->getTail();
	auto headPosition = head->getPosition();
	auto body1Position = body1->getPosition();
	auto body2Position = body2->getPosition();

	auto result = assertEquals(true, position->equals(headPosition));
    result &= assertEquals(true, position->equals(body1Position));
    result &= assertEquals(true, position->equals(body2Position));
	result &= assertEquals(CentipedeMovingDirection::cRight, head->getMovingDirection());
	result &= assertEquals(CentipedeMovingDirection::cRight, body1->getMovingDirection());
	result &= assertEquals(CentipedeMovingDirection::cRight, body2->getMovingDirection());
	result &= assertEquals<std::shared_ptr<CentipedeBody>>(nullptr, body2->getTail()); // End of Centipede

	delete head;
	endTest();
	return result;
}

bool centipedeHead_initFromTailTest()
{
	printSubTestName("CentipedeHead init from tail test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(7, 2, settings);
	auto positionTail = std::make_shared<Position>(7, 1, settings);
    auto tail = std::make_shared<CentipedeBody>(*positionTail, nullptr, CentipedeMovingDirection::cRight);
    auto body = std::make_shared<CentipedeBody>(*position, tail, CentipedeMovingDirection::cRight);
	
    // 3 means: Centipede of 3 parts -> Head Body1 Body2
	auto head = new CentipedeHead(body);
	auto headPosition = head->getPosition();

	auto result = assertEquals(true, position->equals(headPosition));
    result &= assertEquals(CentipedeMovingDirection::cRight, head->getMovingDirection());
    result &= assertEquals(tail, head->getTail());

	delete head;
	endTest();
	return result;
}

bool centipedeHead_moveLeftTest()
{
	printSubTestName("CentipedeHead move left test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto mushroomMap = std::make_shared<MushroomMap>(settings);
	auto centipedes = std::make_shared<std::vector<CentipedeHead>>(settings);
	auto position = std::make_shared<Position>(7, 2, settings);
	auto head = new CentipedeHead(position->getLine(), position->getColumn(), CentipedeMovingDirection::cLeft, settings, 2);
    
    head->move(*mushroomMap, *centipedes);

	auto headPosition = head->getPosition();
    auto tailPosition = head->getTail()->getPosition();

	auto result = assertEquals(true, position->equals(tailPosition));
    position->left();
	result &= assertEquals(true, position->equals(headPosition));

	delete head;
	endTest();
	return result;
}

bool centipedeHead_moveRightTest()
{
	printSubTestName("CentipedeHead move right test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto mushroomMap = std::make_shared<MushroomMap>(settings);
	auto centipedes = std::make_shared<std::vector<CentipedeHead>>(settings);
	auto position = std::make_shared<Position>(7, 2, settings);
	auto head = new CentipedeHead(position->getLine(), position->getColumn(), CentipedeMovingDirection::cRight, settings, 2);
    
    head->move(*mushroomMap, *centipedes);

	auto headPosition = head->getPosition();
    auto tailPosition = head->getTail()->getPosition();

	auto result = assertEquals(true, position->equals(tailPosition));
    position->right();
	result &= assertEquals(true, position->equals(headPosition));

	delete head;
	endTest();
	return result;
}

bool centipedeHead_moveObstacleMushroomTest()
{
	printSubTestName("CentipedeHead move obstacle test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto mushroomMap = std::make_shared<MushroomMap>(settings);
    mushroomMap->spawnMushroom(7,3);
	auto centipedes = std::make_shared<std::vector<CentipedeHead>>(settings);
	auto position = std::make_shared<Position>(7, 2, settings);
	auto head = new CentipedeHead(position->getLine(), position->getColumn(), CentipedeMovingDirection::cRight, settings, 2);
    
    head->move(*mushroomMap, *centipedes);

	auto headPosition = head->getPosition();
    auto tailPosition = head->getTail()->getPosition();

	auto result = assertEquals(true, position->equals(tailPosition));
	result &= assertEquals(CentipedeMovingDirection::cRight, head->getTail()->getMovingDirection());
    position->down();
	result &= assertEquals(true, position->equals(headPosition));
	result &= assertEquals(CentipedeMovingDirection::cLeft, head->getMovingDirection());

	delete head;
	endTest();
	return result;
}

bool centipedeHead_moveObstacleFieldEndTest()
{
	printSubTestName("CentipedeHead move obstacle test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto mushroomMap = std::make_shared<MushroomMap>(settings);
	auto centipedes = std::make_shared<std::vector<CentipedeHead>>(settings);
	auto position = std::make_shared<Position>(7, settings->getPlayingFieldWidth()-1, settings);
	auto head = new CentipedeHead(position->getLine(), position->getColumn(), CentipedeMovingDirection::cRight, settings, 2);
    
    head->move(*mushroomMap, *centipedes);

	auto headPosition = head->getPosition();
    auto tailPosition = head->getTail()->getPosition();

	auto result = assertEquals(true, position->equals(tailPosition));
	result &= assertEquals(CentipedeMovingDirection::cRight, head->getTail()->getMovingDirection());
    position->down();
	result &= assertEquals(true, position->equals(headPosition));
	result &= assertEquals(CentipedeMovingDirection::cLeft, head->getMovingDirection());

	delete head;
	endTest();
	return result;
}

bool centipedeHead_moveObstacleCentipedeTest()
{
	printSubTestName("CentipedeHead move obstacle test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto mushroomMap = std::make_shared<MushroomMap>(settings);
	auto centipedes = std::make_shared<std::vector<CentipedeHead>>(settings);
	CentipedeHead obstacle(7, 3, CentipedeMovingDirection::cRight, settings, 1);
    centipedes->push_back(obstacle);
	auto position = std::make_shared<Position>(7, 2, settings);
	auto head = new CentipedeHead(position->getLine(), position->getColumn(), CentipedeMovingDirection::cRight, settings, 2);
    
    head->move(*mushroomMap, *centipedes);

	auto headPosition = head->getPosition();
    auto tailPosition = head->getTail()->getPosition();

	auto result = assertEquals(true, position->equals(tailPosition));
	result &= assertEquals(CentipedeMovingDirection::cRight, head->getTail()->getMovingDirection());
    position->down();
	result &= assertEquals(true, position->equals(headPosition));
	result &= assertEquals(CentipedeMovingDirection::cLeft, head->getMovingDirection());

	delete head;
	endTest();
	return result;
}

void runCentipedeHeadTest()
{
	printTestName("CentipedeHead Test");
	auto result = centipedeHead_initNew1Test();
	result &= centipedeHead_initNewSmaller1Test();
	result &= centipedeHead_initNewBigger1Test();
	result &= centipedeHead_initFromTailTest();
	result &= centipedeHead_moveLeftTest();
	result &= centipedeHead_moveRightTest();
	result &= centipedeHead_moveObstacleMushroomTest();
	result &= centipedeHead_moveObstacleFieldEndTest();
	result &= centipedeHead_moveObstacleCentipedeTest();
	printTestSummary(result);
}

