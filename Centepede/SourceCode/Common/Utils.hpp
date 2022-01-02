#ifndef UTILS_HPP
#define UTILS_HPP
#include "../Common/CentipedeSettings.hpp"
#include <memory>

bool lineOutOfBounds(int line, std::shared_ptr<CentipedeSettings> settings_ptr)
{
    if(line < 0) return true;
    if(line >= settings_ptr->getPlayingFieldHeight()) return true;
    return false;
}

bool columnOutOfBounds(int column, std::shared_ptr<CentipedeSettings> settings_ptr)
{
    if(column < 0) return true;
    if(column >= settings_ptr->getPlayingFieldWidth()) return true;
    return false;
}

#endif