#include "commands/unmute.hpp"
#include "utils/DB_bind_vector.hpp"
#include "utils/DB_exec.hpp"

using std::string;
using dpp::snowflake;
using dpp::utility::user_mention;
using utils::DB_bind_vector;
using utils::DB_exec;

string commands::unmute(
    dpp::cluster& bot, snowflake GUILD_ID,
    snowflake USER_ID, string reason
) {
    // if(!muted_roles[GUILD_ID]) return
    //     string("Cannot unmute ") + user_mention(USER_ID) +
    //     ". Reason: muted role has been deleted";
    // bot.guild_member_delete_role_sync(
    //     GUILD_ID, USER_ID, muted_roles[GUILD_ID]
    // );
    // DB_bind_vector binds;
    // binds.push<uint64_t>(GUILD_ID, MYSQL_TYPE_LONGLONG);
    // binds.push<uint64_t>(USER_ID, MYSQL_TYPE_LONGLONG);
    // string query = "DELETE FROM bot.MUTES WHERE GUILD_ID = ? AND USER_ID = ?";
    // DB_exec(query, binds);
    // string reply = string("Done! Member ") + user_mention(USER_ID) + " unmuted";
    // if(reason != "") reply = reply + ". Reason: " + reason;
    // return reply;
    return "";
}