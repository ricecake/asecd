#include<iostream>
#include<common.hpp>
#include<thread>
#include <mutex>
#include<string>
#include<config.hpp>
#include<dns.hpp>

typedef Singleton<std::string> Config2;
typedef Singleton<std::mutex> ConfigMutex2;
int main() {

	std::thread* array[5];
	for (int i=0; i<5;i++) {
		array[i] = new std::thread([i]{
			std::cout<< i << std::endl;
			asConfig* asc = new asConfig;
			asc->conf()->readFile("example.cfg");
			std::string setting = asc->conf()->lookup("name");
			std::cout << setting  << std::endl;
			delete asc;
		});
	}
	for (auto i : array) {
		i->join();
	}
	std::vector<std::string> txts = (new asDNS)->queryTXT(std::string("sutt.buttmuffin.org"));
	for ( auto record : txts ) { 
		std::cout<< record << std::endl;
	}
	//ConfigPtr conf = new Config;
}
