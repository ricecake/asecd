#include<common.hpp>
#include <libconfig.h++>

typedef Singleton<libconfig::Config> Config;
typedef Singleton<libconfig::Config>* ConfigPtr;
