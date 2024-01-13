#pragma once
#include <string>
#include <dpp/dpp.h>
#include "utils/slashcommand.hpp"

namespace commands {

std::string create_muted_role(dpp::cluster&, const utils::slashcommand&);

}