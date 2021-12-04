#include "concurrency_lib.hpp"

#include <mutex>
#include <shared_mutex>

Signal::Signal(){
    this->state = 0;
}

int Signal::getState(){
    std::shared_lock<std::shared_mutex> lock(this->stateMutex);
    return this->state;
}

bool Signal::sameState(int state){
    // It is important to periodically release the lock here, so that the signal Method has a Chance to increment.
    std::shared_lock<std::shared_mutex> lock(this->stateMutex);
    return this->state == state;
}

void Signal::await(){
    int savedState = this->getState();
    while(sameState(savedState)){
        // wait...
    }
}

void Signal::signal(){
    std::unique_lock<std::shared_mutex> lock(this->stateMutex);
    // Overflow isn't an issue here, since it is still different from the value before;
    this->state++;
}