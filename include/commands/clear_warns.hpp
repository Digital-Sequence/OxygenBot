#pragma once
#include <string>
#include <dpp/dpp.h>
#include "utils/slashcommand.hpp"

namespace commands {

std::string clear_warns(dpp::cluster&, const utils::slashcommand&);

}