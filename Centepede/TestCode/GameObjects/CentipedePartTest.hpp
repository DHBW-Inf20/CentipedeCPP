#include "../../lib/test_lib.hpp"
#include "../../SourceCode/Common/CentipedeSettings.hpp"
#include "../../SourceCode/GameObjects/MushroomMap.hpp"
#include "../../SourceCode/GameObjects/CentipedeBody.hpp"
#include <vector>
#include <memory>

bool centipedePart_getPositionTest()
{
	printSubTestName("CentipedePart get position test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(7, 2, settings);
	auto part = new CentipedeBody(*position, nullptr, CentipedeMovingDirection::cRight);
    auto partPosition = part->getPosition();
	auto result = assertEquals(true, position->equals(partPosition));
	delete part;
	endTest();
	return result;
}

bool centipedePart_getTailTest()
{
	printSubTestName("CentipedePart get tail test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(0, 0, settings);
	auto tail = std::make_shared<CentipedeBody>(*position, nullptr, CentipedeMovingDirection::cRight);
	auto part = new CentipedeBody(*position, tail, CentipedeMovingDirection::cRight);
	auto result = assertEquals(tail, part->getTail());
	delete part;
	endTest();
	return result;
}

bool centipedePart_getMovingDirectionTest()
{
	printSubTestName("CentipedePart get tail test");
	auto settings = std::make_shared<CentipedeSettings>();
	auto position = std::make_shared<Position>(0, 0, settings);
	auto part = new CentipedeBody(*position, nullptr, CentipedeMovingDirection::cRight);
	auto result = assertEquals(CentipedeMovingDirection::cRight, part->getMovingDirection());
	delete part;
	endTest();
	return result;
}

bool centipedePart_isAtPositionFalseTest()
{
	printSubTestName("CentipedePart is at position false test");
	auto settings = std::make_shared<CentipedeSettings>();
    Position position(7, 2, settings);
	auto part = new CentipedeBody(position, nullptr, CentipedeMovingDirection::cRight);
    Position otherPosition(7, 3, settings);
	auto result = assertEquals(false, part->isAtPosition(otherPosition));
	delete part;
	endTest();
	return result;
}

bool centipedePart_isAtPositionTrueTest()
{
	printSubTestName("CentipedePart is at position true test");
	auto settings = std::make_shared<CentipedeSettings>();
    Position position(7, 2, settings);
	auto part = new CentipedeBody(position, nullptr, CentipedeMovingDirection::cRight);
	auto result = assertEquals(true, part->isAtPosition(position));
	delete part;
	endTest();
	return result;
}

bool centipedePart_isAtPositionTailTrueTest()
{
	printSubTestName("CentipedePart is at position false");
	auto settings = std::make_shared<CentipedeSettings>();
	Position positionTail(7, 2, settings);

    Position position(0, 0, settings);
	auto tail = std::make_shared<CentipedeBody>(positionTail, nullptr, CentipedeMovingDirection::cRight);
	auto part = new CentipedeBody(position, tail, CentipedeMovingDirection::cRight);

	auto result = assertEquals(true, part->isAtPosition(positionTail));
	delete part;
	endTest();
	return result;
}

bool centipedePart_isAtPositionLineColumnFalseTest()
{
	printSubTestName("CentipedePart is at position line column false test");
	auto settings = std::make_shared<CentipedeSettings>();
    Position position(7, 2, settings);
	auto part = new CentipedeBody(position, nullptr, CentipedeMovingDirection::cRight);
	auto result = assertEquals(false, part->isAtPosition(7, 3));
	delete part;
	endTest();
	return result;
}

bool centipedePart_isAtPositionLineColumnTrueTest()
{
	printSubTestName("CentipedePart is at position line column true test");
	auto settings = std::make_shared<CentipedeSettings>();
    Position position(7, 2, settings);
	auto part = new CentipedeBody(position, nullptr, CentipedeMovingDirection::cRight);
	auto result = assertEquals(true, part->isAtPosition(7, 2));
	delete part;
	endTest();
	return result;
}

bool centipedePart_isAtPositionLineColumnTailTrueTest()
{
	printSubTestName("CentipedePart is at position line column false");
	auto settings = std::make_shared<CentipedeSettings>();
	Position positionTail(7, 2, settings);

    Position position(0, 0, settings);
	auto tail = std::make_shared<CentipedeBody>(positionTail, nullptr, CentipedeMovingDirection::cRight);
	auto part = new CentipedeBody(position, tail, CentipedeMovingDirection::cRight);

	auto result = assertEquals(true, part->isAtPosition(0, 0));
	delete part;
	endTest();
	return result;
}

bool centipedePart_collideNoHitTest()
{
	printSubTestName("CentipedePart collide no hit test");
	auto settings = std::make_shared<CentipedeSettings>();
    auto mushroomMap = std::make_shared<MushroomMap>(settings);
	auto position = std::make_shared<Position>(0, 0, settings);
    auto centipedes = std::make_shared<std::vector<CentipedeHead>>();
    Bullet bullet(7, 2, settings);

	auto part = new CentipedeBody(*position, nullptr, CentipedeMovingDirection::cRight);
	auto result = assertEquals(CentipedeHit::noHit, part->collide(bullet, mushroomMap, centipedes));
    result &= assertEquals(0, mushroomMap->getMushroom(7, 2));
    result &= assertEquals(0, mushroomMap->getMushroom(0, 0));
    result &= assertEquals(0, (int)(centipedes->size()));
	delete part;

	endTest();
	return result;
}

bool centipedePart_collideDirectHitNoTailTest()
{
	printSubTestName("CentipedePart collide direct hit no tail test");
	auto settings = std::make_shared<CentipedeSettings>();
    auto mushroomMap = std::make_shared<MushroomMap>(settings);
	auto position = std::make_shared<Position>(7, 2, settings);
    auto centipedes = std::make_shared<std::vector<CentipedeHead>>();
    Bullet bullet(position->getLine(), position->getColumn(), settings);

	auto part = new CentipedeBody(*position, nullptr, CentipedeMovingDirection::cRight);
	auto result = assertEquals(CentipedeHit::directHit, part->collide(bullet, mushroomMap, centipedes));
    result &= assertEquals(settings->getInitialMushroomHealth(), mushroomMap->getMushroom(position->getLine(), position->getColumn()));
    result &= assertEquals(0, (int)(centipedes->size()));
	delete part;
    
	endTest();
	return result;
}

bool centipedePart_collideDirectHitTest()
{
	printSubTestName("CentipedePart collide direct hit test");
	auto settings = std::make_shared<CentipedeSettings>();
    auto mushroomMap = std::make_shared<MushroomMap>(settings);
	auto positionTail = std::make_shared<Position>(7, 1, settings);
	auto position = std::make_shared<Position>(7, 2, settings);
    auto centipedes = std::make_shared<std::vector<CentipedeHead>>();
    Bullet bullet(position->getLine(), position->getColumn(), settings);

	auto tail = std::make_shared<CentipedeBody>(*positionTail, nullptr, CentipedeMovingDirection::cRight);
	auto part = new CentipedeBody(*position, tail, CentipedeMovingDirection::cRight);
	auto result = assertEquals(CentipedeHit::directHit, part->collide(bullet, mushroomMap, centipedes));
    result &= assertEquals(settings->getInitialMushroomHealth(), mushroomMap->getMushroom(position->getLine(), position->getColumn()));
    result &= assertEquals(1, (int)(centipedes->size()));
	delete part;
    
	endTest();
	return result;
}

bool centipedePart_collideTailHitTest()
{
	printSubTestName("CentipedePart collide tail hit test");
	auto settings = std::make_shared<CentipedeSettings>();
    auto mushroomMap = std::make_shared<MushroomMap>(settings);
	auto positionTailTail = std::make_shared<Position>(7, 3, settings);
	auto positionTail = std::make_shared<Position>(7, 2, settings);
	auto position = std::make_shared<Position>(0, 0, settings);
    auto centipedes = std::make_shared<std::vector<CentipedeHead>>();
    Bullet bullet(positionTail->getLine(), positionTail->getColumn(), settings);

	auto tailTail = std::make_shared<CentipedeBody>(*positionTailTail, nullptr, CentipedeMovingDirection::cRight);
	auto tail = std::make_shared<CentipedeBody>(*positionTail, tailTail, CentipedeMovingDirection::cRight);
	auto part = new CentipedeBody(*position, tail, CentipedeMovingDirection::cRight);
	auto result = assertEquals(CentipedeHit::tailHit, part->collide(bullet, mushroomMap, centipedes));
    result &= assertEquals(0, mushroomMap->getMushroom(position->getLine(), position->getColumn()));
    result &= assertEquals(settings->getInitialMushroomHealth(), mushroomMap->getMushroom(positionTail->getLine(), positionTail->getColumn()));
    result &= assertEquals(1, (int)(centipedes->size()));
	delete part;
    
	endTest();
	return result;
}

void runCentipedePartTest()
{
    // Using Centipede Body as implementation, but needs to be irrellevant.
	printTestName("CentipedePart Test");
	auto result = centipedePart_getPositionTest();
	result &= centipedePart_getTailTest();
	result &= centipedePart_isAtPositionFalseTest();
	result &= centipedePart_isAtPositionTrueTest();
	result &= centipedePart_isAtPositionTailTrueTest();
	result &= centipedePart_isAtPositionLineColumnFalseTest();
	result &= centipedePart_isAtPositionLineColumnTrueTest();
	result &= centipedePart_isAtPositionLineColumnTailTrueTest();
	result &= centipedePart_collideNoHitTest();
	result &= centipedePart_collideDirectHitNoTailTest();
	result &= centipedePart_collideDirectHitTest();
	result &= centipedePart_collideTailHitTest();
	printTestSummary(result);
}

