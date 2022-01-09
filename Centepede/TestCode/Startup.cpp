#include "../lib/test_lib.hpp"
#include "Input/InputBufferTest.hpp"
#include "Input/KeylistenerTest.hpp"
#include "GameObjects/PositionTest.hpp"
#include "GameObjects/BulletTest.hpp"
#include "GameObjects/MushroomMapTest.hpp"
#include "GameObjects/StarshipTest.hpp"
#include "GameObjects/CentipedePartTest.hpp"
// #include "GameObjects/CentipedeBodyTest.hpp"
// #include "GameObjects/CentipedeHeadTest.hpp"

// ###############################
// Run Tests
// ###############################

/**
 * Tests for all the Input-Components.
 * ##########################
 * ! Needs User Interaction !
 * ##########################
 */
void runInputTestSuite()
{
    runInputBufferTest();
    runKeylistenerTest();
}

/**
 * Tests for all the Game-Object-Classes
 */
void runGameObjectsTestSuite()
{
    // runPositionTest();
    // runBulletTest();
    // runMushroomMapTest();
    // runStarshipTest();
    runCentipedePartTest();
    // runCentipedeBodyTest();
    // runCentipedeHeadTest();
}

int main(int argc, char** argv)
{
    // runInputTestSuite();
    runGameObjectsTestSuite();
}