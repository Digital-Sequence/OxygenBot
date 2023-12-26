#pragma once
#include <string>
#include <dpp/dpp.h>

namespace commands {

std::string unmute(dpp::cluster&, dpp::snowflake, dpp::snowflake, std::string = "");

}