#pragma once
#include <map>
#include <string>
#include <dpp/dpp.h>

extern std::map<
    dpp::snowflake, std::map<dpp::snowflake, std::string>
> roles;

extern std::map<dpp::snowflake, dpp::snowflake> muted_roles;