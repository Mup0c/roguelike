#include "config.h"
#include <fstream>

Config::Config() {
    std::ifstream config_stream("../config.json");
    config_stream >> json_;
}
