#include "BusinessLogic/GameLogic.hpp"
#include "BusinessLogic/MenuLogic.hpp"
#include "UI/ConsoleOutput.hpp"
#include "UI/StandardTheme.hpp"
#include "UI/StandardThemeWindows.hpp"
#include "Input/IInputBufferReader.hpp"
#include "Input/InputBuffer.hpp"
#include "Input/Keycodes.hpp"
#include "Common/Directions.hpp"

int main(int argc, char** argv){
    // Initialize Objects
    auto ui_ptr = std::make_shared<ConsoleOutput>();
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    auto theme_ptr = std::make_shared<StandardThemeWindows>();
#else
    auto theme_ptr = std::make_shared<StandardTheme>();
#endif
    auto inputBuffer_ptr = std::make_shared<InputBuffer>();
    auto menuLogic = std::make_shared<MenuLogic>(theme_ptr, ui_ptr, inputBuffer_ptr);

    GameLogic gameLogic(inputBuffer_ptr, ui_ptr, theme_ptr, menuLogic);

    // Initialize Keylistener
    Keylistener keylistener;

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    // w-a-s-d keys for movement on Windows
    keylistener.registerHandler('s', [inputBuffer_ptr]() {
        inputBuffer_ptr->setDirection(Direction::down);
        });
    keylistener.registerHandler('w', [inputBuffer_ptr]() {
        inputBuffer_ptr->setDirection(Direction::up);
        });
    keylistener.registerHandler('a', [inputBuffer_ptr]() {
        inputBuffer_ptr->setDirection(Direction::left);
        });
    keylistener.registerHandler('d', [inputBuffer_ptr]() {
        inputBuffer_ptr->setDirection(Direction::right);
        });
#else
    // Arrow keys for movement on Mac
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
#endif

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