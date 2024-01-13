#include "commands/unmute.hpp"
#include "utils/DB_bind_vector.hpp"
#include "utils/DB_exec.hpp"
#include "utils/DB_fetch_prepare.hpp"

using std::string;
using dpp::snowflake;
using dpp::utility::user_mention;
using utils::DB_bind_vector;
using utils::DB_exec;

string commands::unmute(
    dpp::cluster& bot, snowflake GUILD_ID,
    snowflake USER_ID, string reason
) {
    string query =
        "SELECT rowid FROM bot.MUTES WHERE GUILD_ID = ? AND USER_ID = ?";
    DB_bind_vector binds;
    binds.push<uint64_t>(GUILD_ID, MYSQL_TYPE_LONGLONG);
    binds.push<uint64_t>(USER_ID, MYSQL_TYPE_LONGLONG);
    uint64_t rowid(0);
    DB_exec(query, binds, [&rowid](MYSQL_STMT* statement) {
        DB_bind_vector binds;
        binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
        MYSQL_RES* prepare_meta_result = DB_fetch_prepare(statement, binds);
        mysql_stmt_fetch(statement);
        mysql_free_result(prepare_meta_result);
    });
    if(!rowid)
        return string("Member ") + user_mention(USER_ID) + " isn't muted";
    
    query = "DELETE FROM bot.MUTES WHERE rowid = ?";
    binds.clear();
    binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
    DB_exec(query, binds);

    query =
        "SELECT ROLE_ID FROM bot.ROLES WHERE GUILD_ID = ? AND NAME = 'muted'";
    binds.clear();
    binds.push<uint64_t>(GUILD_ID, MYSQL_TYPE_LONGLONG);
    uint64_t ROLE_ID(0);
    DB_exec(query, binds, [&ROLE_ID](MYSQL_STMT* statement) {
        DB_bind_vector binds;
        binds.push<uint64_t>(ROLE_ID, MYSQL_TYPE_LONGLONG);
        MYSQL_RES* prepare_meta_result = DB_fetch_prepare(statement, binds);
        mysql_stmt_fetch(statement);
        mysql_free_result(prepare_meta_result);
    });
    bot.guild_member_delete_role(GUILD_ID, USER_ID, ROLE_ID);
    return string("Done! Member ") + user_mention(USER_ID) + " unmuted";
}