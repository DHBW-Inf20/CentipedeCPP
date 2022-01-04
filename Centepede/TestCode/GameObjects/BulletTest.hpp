#include "../../lib/test_lib.hpp"
#include "../../SourceCode/Common/CentipedeSettings.hpp"
#include "../../SourceCode/GameObjects/Bullet.hpp"

bool bullet_init0Test()
{
    printSubTestName("Bullet init 0 test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto bullet = new Bullet(0, 0, settings);
    auto result = assertEquals(0, bullet->getPosition().getLine());
    result &= assertEquals(0, bullet->getPosition().getColumn());
    delete bullet;
    endTest();
    return result;
}

bool bullet_getPositionTest()
{
    printSubTestName("Bullet get position test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto bullet = new Bullet(7, 2, settings);
    auto result = assertEquals(7, bullet->getPosition().getLine());
    result &= assertEquals(2, bullet->getPosition().getColumn());
    delete bullet;
    endTest();
    return result;
}

bool bullet_moveTest()
{
    printSubTestName("Bullet move test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto bullet = new Bullet(7, 2, settings);
    auto moved = bullet->move();
    auto result = assertEquals(6, bullet->getPosition().getLine());
    result &= assertEquals(true, moved);
    delete bullet;
    endTest();
    return result;
}

bool bullet_moveOutOfBoundsTest()
{
    printSubTestName("Bullet move out of bounds test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto bullet = new Bullet(0, 2, settings);
    auto moved = bullet->move();
    auto result = assertEquals(0, bullet->getPosition().getLine());
    result &= assertEquals(false, moved);
    delete bullet;
    endTest();
    return result;
}

void runBulletTest()
{
    printTestName("Bullet Test");
    auto result = bullet_init0Test();
    result &= bullet_getPositionTest();
    result &= bullet_moveTest();
    result &= bullet_moveOutOfBoundsTest();
    printTestSummary(result);
}