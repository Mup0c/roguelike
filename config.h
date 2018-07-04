#pragma once
#include <nlohmann/json.hpp>

class Config {
public:
    Config();
    nlohmann::json json() const { return json_; }

private:
    nlohmann::json json_;

};
