#pragma once
#include <string>
#include <dpp/dpp.h>
#include "utils/slashcommand.hpp"

namespace commands {

std::string unmute(dpp::cluster&, const utils::slashcommand&);

void unmute(
    dpp::cluster&, const dpp::snowflake, const dpp::snowflake, const uint64_t
);

}