#include<common.hpp>
#include <libconfig.h++>
#include<iostream>
typedef Singleton<libconfig::Config> Config;
typedef Singleton<libconfig::Config>* ConfigPtr;
typedef Singleton<std::mutex> ConfigMutex;

class asConfig {
        public:
                asConfig() {
                        lock->lock();
                        confObj = new Config;
                }
                ~asConfig() {
                        delete confObj;
                        lock->unlock();
                }
        private:
                ConfigMutex lock;
                ConfigPtr confObj;
};