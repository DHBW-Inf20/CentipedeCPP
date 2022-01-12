#ifndef KEYLISTENER_HPP
#define KEYLISTENER_HPP
#include "Keylistener.hpp"
#include "../../lib/keylib.h"
#include <thread>
#include <chrono>
#include <future>
#include <map>
#include <mutex>
#include <shared_mutex>

class Keylistener
{
    private:
        /** 
         * The map to store the event handlers.
         */
        std::map<char, std::function<void()>> eventHandlers;
        /** 
         * Is true, while the keylistener is active.
         */
        bool running;
        /** 
         * Used to synchronize the two threads on the eventHandlers-map.
         */
        mutable std::shared_mutex eventHandlerMutex;
        /** 
         * Used to synchronize the two threads on accessing the running-variable.
         */
        mutable std::shared_mutex runningMutex;
        /** 
         * The thread, in which the keylistener is running. 
         */
        std::shared_ptr<std::thread> keylistenerThread_ptr;

        /**
         * Synchronized reading access on the 'running' attribute.
         */
        bool continuePolling()
        {
            std::shared_lock(this->runningMutex);
            return this->running;
        }

        /**
         * threadsafe change of the 'running' attribute.
         */
        void changeRunning(bool to){
            std::unique_lock runningLock(this->runningMutex);
            this->running = to;
        }

        /**
         * The actual Keylistener, started in the keylistener thread.
         */
        void doPolling()
        {
            // Polling loop
            while(this->continuePolling()){
                // blocking call to get next character.
                auto key = key_press();
                std::shared_lock handlerLock(this->eventHandlerMutex);
                if(!this->eventHandlers.count(key))
                {
                    // No event handler for this key.
                    continue;
                }

                // call event handler.
                this->eventHandlers[key]();
            }
        }
        
    public:
        /**
         * Initializes the keylistener without starting it's polling
         */
        Keylistener()
        {
            this->running = false;
            this->keylistenerThread_ptr = nullptr;
        }

        /**
         * Starts the polling in a background-thread
         */
        void startMultithreaded()
        {
            if(this->keylistenerThread_ptr != nullptr){
                // already running
                return;
            }
            this->changeRunning(true);
            this->keylistenerThread_ptr = std::make_shared<std::thread>(&Keylistener::doPolling, this);
        }

        /**
         * Stops and joins the background-thread
         */
        void stop()
        {
            if(this->keylistenerThread_ptr == nullptr){
                // already stopped
                return;
            }
            this->changeRunning(false);
            this->keylistenerThread_ptr->join();
            this->keylistenerThread_ptr = nullptr;
        }

        /**
         * Registers a new function, that is called each time the 'key' on the keyboard is hit.
         * If another handler for this key is allready registered, this will be replaced. There can only be one handler per key at a time.
         */
        void registerHandler(char key, std::function<void()> handler)
        {
            std::unique_lock handlerLock(this->eventHandlerMutex);
            this->eventHandlers[key] = handler;
        }

        /**
         * Removes the registered handler-function for this key, if there is one registered.
         */
        void removeHandler(char key)
        {
            std::unique_lock handlerLock(this->eventHandlerMutex);
            this->eventHandlers.erase(key);
        }

        /**
         * stops the keylistener, if it is currently active.
         */
        ~Keylistener()
        {
            if(this->keylistenerThread_ptr != nullptr){
                // keylistener still active -> needs to be stopped first
                this->stop();
            }
        }
};

#endif