#ifndef CONCURRENCY_LIB_HPP
#define CONCURRENCY_LIB_HPP

#include <mutex>
#include <shared_mutex>

class Signal{
    private:
        int state;
        mutable std::shared_mutex stateMutex;
        int getState();
        bool sameState(int state);

    public:
        Signal();
        void await();
        void signal();
};

#endif