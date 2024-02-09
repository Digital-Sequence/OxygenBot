#pragma once
#include <string>
#include <dpp/dpp.h>
#include "utils/slashcommand.hpp"

namespace commands {

std::string delete_messages(dpp::cluster&, const utils::slashcommand&);

}