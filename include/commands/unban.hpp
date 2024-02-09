#pragma once
#include <string>
#include <dpp/dpp.h>
#include "utils/slashcommand.hpp"

namespace commands {

std::string unban(dpp::cluster&, const utils::slashcommand&);

}