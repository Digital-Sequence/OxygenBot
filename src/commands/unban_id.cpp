#include "commands/unban_id.hpp"
#include "utils/DB_statement.hpp"

using std::string;
using utils::DB_statement;
using utils::slashcommand;

string commands::unban_id(dpp::cluster& bot, const slashcommand& event) {
    bot.guild_ban_delete_sync(event.guild_id, event.member_id);

    string reply =
        string("Done! ") + event.member_mention + " has been unbanned";
    if(!event.reason.empty()) reply = reply + ". Reason: " + event.reason;
    return reply;
}