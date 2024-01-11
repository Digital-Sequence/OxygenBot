#include <stdexcept>
#include <cstring>
#include "commands/ban.hpp"
#include "commands/delete_messages.hpp"
#include "utils/DB_bind_vector.hpp"
#include "utils/DB_exec.hpp"

using std::string;
using std::to_string;
using std::vector;
using dpp::to_hex;
using commands::delete_messages;
using utils::DB_bind_vector;
using utils::DB_exec;
using utils::slashcommand;

string commands::ban(dpp::cluster& bot, slashcommand& event) {
    bot.set_audit_reason(event.reason).
    guild_ban_add_sync(event.guild_id, event.member_id);

    uint64_t rowid(0);
    DB_bind_vector binds;
    binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
    binds.push<uint64_t>(event.guild_id, MYSQL_TYPE_LONGLONG);
    binds.push<uint64_t>(event.member_id, MYSQL_TYPE_LONGLONG);
    long unsigned int length = event.member_username.length() + 1;
    char USERNAME[length];
    strcpy(USERNAME, event.member_username.c_str());
    binds.push(USERNAME, MYSQL_TYPE_STRING, &length);
    uint64_t EXPIRES(0);
    if(!event.duration) binds.push();
    else {
        EXPIRES = std::time(0) + event.duration;
        binds.push<uint64_t>(EXPIRES, MYSQL_TYPE_LONGLONG);
    }
    string query = "INSERT INTO bot.BANS VALUES(?, ?, ?, ?, ?)";
    DB_exec(query, binds);
    if(event.messages_amount) delete_messages(bot, event);
    string reply = string("Done! User ") + event.member_mention + " has been banned";
    if(!event.reason.empty()) reply = reply + ". Reason: " + event.reason;
    return reply;
}