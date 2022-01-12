#include "BusinessLogic/GameLogic.hpp"
#include "BusinessLogic/MenuLogic.hpp"
#include "UI/ConsoleOutput.hpp"
#include "UI/StandardTheme.hpp"
#include "Input/IInputBufferReader.hpp"
#include "Input/InputBuffer.hpp"
#include "Input/Keycodes.hpp"
#include "Common/Directions.hpp"

int main(int argc, char** argv){
    // Initialize Objects
    auto ui_ptr = std::make_shared<ConsoleOutput>();
    auto theme_ptr = std::make_shared<StandardTheme>();
    auto inputBuffer_ptr = std::make_shared<InputBuffer>();
    auto menuLogic = std::make_shared<MenuLogic>(theme_ptr, ui_ptr, inputBuffer_ptr);

    GameLogic gameLogic(inputBuffer_ptr, ui_ptr, theme_ptr, menuLogic);

    // Initialize Keylistener
    Keylistener keylistener;

    // Arrow keys for movement
    keylistener.registerHandler(KeyCodes::arrowKeyDown, [inputBuffer_ptr](){
        inputBuffer_ptr->setDirection(Direction::down);
    });
    keylistener.registerHandler(KeyCodes::arrowKeyUp, [inputBuffer_ptr](){
        inputBuffer_ptr->setDirection(Direction::up);
    });
    keylistener.registerHandler(KeyCodes::arrowKeyLeft, [inputBuffer_ptr](){
        inputBuffer_ptr->setDirection(Direction::left);
    });
    keylistener.registerHandler(KeyCodes::arrowKeyRight, [inputBuffer_ptr](){
        inputBuffer_ptr->setDirection(Direction::right);
    });

    // Space bar for shooting
    keylistener.registerHandler(KeyCodes::spaceBarKey, [inputBuffer_ptr](){
        inputBuffer_ptr->setShot();
    });

    // EscapeKey for breakout
    keylistener.registerHandler('q', [inputBuffer_ptr](){
        inputBuffer_ptr->setBreakoutMenu();
    });

    // Run game
    keylistener.startMultithreaded();
    gameLogic.startNew();
    keylistener.stop();
}