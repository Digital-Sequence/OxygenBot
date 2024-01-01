#pragma once
#include <string>
#include <dpp/dpp.h>
#include "utils/slashcommand.hpp"

namespace commands {

std::string member_info(dpp::cluster&, utils::slashcommand&);

}