#include "../../lib/test_lib.hpp"
#include "../../SourceCode/Common/CentipedeSettings.hpp"
#include "../../SourceCode/GameObjects/MushroomMap.hpp"
#include "../../SourceCode/GameObjects/Bullet.hpp"

bool mushroomMap_initDefault0Test(){
    printSubTestName("MushroomMap init default 0 test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto map = new MushroomMap(settings);
    auto result = assertEquals(0, map->getMushroom(0, 0));
    delete map;
    endTest();
    return result;
}

bool mushroomMap_getMushroomOutOfBoundsTest(){
    printSubTestName("MushroomMap get mushroom out of bounds test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto map = new MushroomMap(settings);
    auto result = assertEquals(0, map->getMushroom(0, 0));
    delete map;
    endTest();
    return result;
}

bool mushroomMap_mapSizeInitTest(){
    printSubTestName("MushroomMap map size init test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto map = new MushroomMap(settings);
    auto result = assertEquals(0, map->getMushroom(9, 10));
    result &= assertEquals(-1, map->getMushroom(10, 10));
    result &= assertEquals(-1, map->getMushroom(9, 11));
    delete map;
    endTest();
    return result;
}

bool mushroomMap_spawnAndGetMushroomTest(){
    printSubTestName("MushroomMap spawn and get mushroom test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto map = new MushroomMap(settings);
    map->spawnMushroom(5,5);
    auto result = assertEquals(settings->getInitialMushroomHealth(), map->getMushroom(5, 5));
    delete map;
    endTest();
    return result;
}

bool mushroomMap_collideNoHitTest(){
    printSubTestName("MushroomMap collide no hit test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto map = new MushroomMap(settings);
    Bullet bullet(5, 5, settings);
    auto collision = map->collide(bullet);
    auto result = assertEquals(false, collision);
    delete map;
    endTest();
    return result;
}

bool mushroomMap_collideHitTest(){
    printSubTestName("MushroomMap collide hit test");
    auto settings = std::make_shared<CentipedeSettings>();
    auto map = new MushroomMap(settings);
    map->spawnMushroom(5,5);
    Bullet bullet(5, 5, settings);
    auto collision = map->collide(bullet);
    auto result = assertEquals(settings->getInitialMushroomHealth() - 1, map->getMushroom(5, 5));
    result &= assertEquals(true, collision);
    delete map;
    endTest();
    return result;
}

void runMushroomMapTest(){
    printTestName("MushroomMap Test");
    auto result = mushroomMap_initDefault0Test();
    result &= mushroomMap_getMushroomOutOfBoundsTest();
    result &= mushroomMap_mapSizeInitTest();
    result &= mushroomMap_spawnAndGetMushroomTest();
    result &= mushroomMap_collideNoHitTest();
    result &= mushroomMap_collideHitTest();
    printTestSummary(result);
}