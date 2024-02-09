#pragma once
#include <string>
#include <dpp/dpp.h>
#include "utils/slashcommand.hpp"

namespace commands {

std::string ban(dpp::cluster&, const utils::slashcommand&);

}