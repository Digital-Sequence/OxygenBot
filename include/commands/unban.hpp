#pragma once
#include <string>
#include <dpp/dpp.h>

namespace commands {

std::string unban(
    dpp::cluster&, const dpp::snowflake, const dpp::snowflake,
    const std::string = ""
);

std::string unban(
    dpp::cluster&, const dpp::snowflake, char*,
    const std::string = ""
);

}