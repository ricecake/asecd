#ifndef __CONFIG_HPP_
#define __CONFIG_HPP_

#include<common.hpp>
#include <libconfig.h++>

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
		libconfig::Config* conf() {
			return &(**confObj);
		}
        private:
                ConfigMutex lock;
                ConfigPtr confObj;
};

#endif

