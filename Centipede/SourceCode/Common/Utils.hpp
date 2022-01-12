#ifndef UTILS_HPP
#define UTILS_HPP
#include "../Common/CentipedeSettings.hpp"
#include "../../lib/CppRandom.hpp"
#include <memory>

/**
 * Checks wheather the line is inside the field boundaries.
 */
bool lineOutOfBounds(int line, std::shared_ptr<CentipedeSettings> settings_ptr)
{
    if(line < 0) return true;
    if(line >= settings_ptr->getPlayingFieldHeight()) return true;
    return false;
}

/**
 * Checks wheather the column is inside the field boundaries.
 */
bool columnOutOfBounds(int column, std::shared_ptr<CentipedeSettings> settings_ptr)
{
    if(column < 0) return true;
    if(column >= settings_ptr->getPlayingFieldWidth()) return true;
    return false;
}

/**
 * Generates a random true/false result with the given chance of dividend/divisor for true;
 */
bool rollRandomWithChance(int dividend, int divisor)
{
    auto random = GetRandomNumberBetween(1, divisor);
    return random <= dividend;
}

#endif