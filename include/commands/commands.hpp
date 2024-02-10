#pragma once
#include <map>
#include <string>
#include "commands/ban.hpp"
#include "commands/create_muted_role.hpp"
#include "commands/delete_messages.hpp"
#include "commands/delwarn.hpp"
#include "commands/member_info.hpp"
#include "commands/mute.hpp"
#include "commands/unban.hpp"
#include "commands/unban_id.hpp"
#include "commands/unmute.hpp"
#include "commands/warn.hpp"

typedef std::string (*PF) (dpp::cluster&, const utils::slashcommand&);

const static std::map<std::string, PF> slashcommand_map = {
    { "ban", commands::ban },
    { "create_muted_role", commands::create_muted_role },
    { "delete_messages", commands::delete_messages },
    { "delwarn", commands::delwarn },
    { "member_info", commands::member_info },
    { "mute", commands::mute },
    { "unban", commands::unban },
    { "unban_id", commands::unban_id },
    { "unmute", commands::unmute },
    { "warn", commands::warn }
};