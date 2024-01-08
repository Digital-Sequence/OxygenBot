#pragma once
#include <map>
#include <set>
#include <string>

extern std::string config_path;
const static std::set<std::string> config_parameters = {
    "token", "DB_host", "DB_user", "DB_password", "DB_port", "DB_unix_socket"
};
extern std::map<std::string, std::string> config;