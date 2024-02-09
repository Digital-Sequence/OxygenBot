#include "commands/unban.hpp"
#include "utils/DB_statement.hpp"

using std::string;
using utils::DB_statement;
using utils::slashcommand;

string commands::unban(dpp::cluster& bot, const slashcommand& event) {
    DB_statement statement(
        "SELECT USER_ID FROM bot.BANS "
        "WHERE GUILD_ID = ? AND USERNAME = ? LIMIT 1"
    );
    uint64_t USER_ID(0);
    statement.add_buffer<uint64_t>(USER_ID, MYSQL_TYPE_LONGLONG);
    statement.add_bind(event.guild_id);
    statement.add_bind(event.member_username);
    statement.exec();
    statement.fetch();
    statement.free_result();
    statement.finish();
    
    if(!USER_ID)
        return string("Member @") + event.member_username + " isn't banned";
    
    bot.guild_ban_delete_sync(event.guild_id, USER_ID);

    string reply =
        string("Done! ") + event.member_mention + " has been unbanned";
    if(!event.reason.empty()) reply = reply + ". Reason: " + event.reason;
    return reply;
}