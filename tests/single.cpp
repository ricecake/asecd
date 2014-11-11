#include<iostream>
#include<common.hpp>
#include <mutex>
#include<string>
#include<config.hpp>

typedef Singleton<std::string> Config2;
typedef Singleton<std::mutex> ConfigMutex2;
int main() {
	asConfig asc;
	asc.conf()->readFile("example.cfg");
	std::string setting = asc.conf()->lookup("name");
	std::cout << setting  << std::endl;
	//ConfigPtr conf = new Config;
}
