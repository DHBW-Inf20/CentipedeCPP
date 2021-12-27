#ifndef KEYLISTENER_HPP
#define KEYLISTENER_HPP
#include <map>
#include <mutex>
#include <shared_mutex>

class Keylistener{
    private:
        std::map<char, std::function<void>> eventHandlers;
        bool running;
        mutable std::shared_mutex eventHandlerMutex;
        mutable std::shared_mutex runningMutex;

        bool isRunning();
        void pollingLoop();
    public:
        Keylistener();
        void startMultithreaded();
        void stop();
        void registerHandler(char key, std::function<void> handler);
        void removeHandler(char key);
        ~Keylistener();
};

#endif