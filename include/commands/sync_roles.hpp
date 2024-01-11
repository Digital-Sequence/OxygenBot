#pragma once
#include <string>
#include <dpp/dpp.h>
#include "utils/slashcommand.hpp"

namespace commands {

std::string sync_roles(dpp::cluster&, const utils::slashcommand&);

}