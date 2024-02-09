#pragma once
#include <map>
#include <set>
#include <string>

extern std::string config_path;
const static std::set<std::string> config_parameters = {
    "token", "DB_host", "DB_user", "DB_password", "DB_unix_socket",
    "default_warn_punishment"
};

const static std::set<std::string> numerics_config_parameters = {
    "DB_port", "default_max_warns"
};

const static std::set<std::string> allowed_warn_punishments = {
    "ban", "mute"
};

extern std::map<std::string, std::string> config;

extern std::map<std::string, int> numerics_config;