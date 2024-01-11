#include <cstring>
#include "commands/unban.hpp"
#include "utils/DB_bind_vector.hpp"
#include "utils/DB_exec.hpp"
#include "utils/DB_fetch_prepare.hpp"

using std::string;
using std::to_string;
using dpp::snowflake;
using dpp::utility::user_mention;
using utils::DB_bind_vector;
using utils::DB_fetch_prepare;

string commands::unban(
    dpp::cluster& bot, const snowflake GUILD_ID, const snowflake USER_ID,
    const string reason
) {
    bot.guild_ban_delete_sync(GUILD_ID, USER_ID);
    string reply =
        string("Done! ") + user_mention(USER_ID) +
        string(" has been unbanned");
    if(!reason.empty()) reply = reply + ". Reason: " + reason;
    return reply;
}

string commands::unban(
    dpp::cluster& bot, snowflake GUILD_ID, char* USERNAME,
    const string reason
) {
    string reply;
    snowflake USER_ID(0);
    string query =
        "SELECT USER_ID FROM bot.BANS WHERE GUILD_ID = ? AND USERNAME = ?";
    DB_bind_vector binds;
    binds.push<uint64_t>(GUILD_ID, MYSQL_TYPE_LONGLONG);
    unsigned long int length = strlen(USERNAME) + 1;
    binds.push(USERNAME, MYSQL_TYPE_STRING, &length);
    utils::DB_exec(
        query, binds,
        [&GUILD_ID, &USER_ID](MYSQL_STMT* statement) {
            DB_bind_vector binds;
            binds.push<uint64_t>(USER_ID, MYSQL_TYPE_LONGLONG);
            MYSQL_RES* prepare_meta_result =
                DB_fetch_prepare(statement, binds);
            mysql_stmt_fetch(statement);
            mysql_free_result(prepare_meta_result);
        }
    );
    if(!USER_ID) return "Member isn't banned";
    bot.guild_ban_delete_sync(GUILD_ID, USER_ID);
    reply = string("Done! ") + user_mention(USER_ID) + " has been unbanned";
    if(!reason.empty()) reply = reply + ". Reason: " + reason;
    return reply;
}