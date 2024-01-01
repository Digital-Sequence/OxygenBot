#include "commands/ban.hpp"
#include "commands/warn.hpp"
#include "utils/DB_bind_vector.hpp"
#include "utils/DB_exec.hpp"
#include "utils/DB_fetch_prepare.hpp"
#include "utils/slashcommand.hpp"

using std::string;
using std::to_string;
using commands::ban;
using utils::DB_bind_vector;
using utils::DB_exec;
using utils::slashcommand;

string commands::warn(dpp::cluster& bot, slashcommand& event) {
    DB_bind_vector binds;
    binds.push<uint64_t>(event.guild_id, MYSQL_TYPE_LONGLONG);
    binds.push<uint64_t>(event.member_id, MYSQL_TYPE_LONGLONG);
    string query =
        "SELECT rowid,COUNT FROM bot.WARNS WHERE GUILD_ID = ? AND USER_ID = ?";
    int c(0);
    DB_exec(query, binds, [&bot, &event, &c](MYSQL_STMT* statement) {
        uint64_t rowid(0);
        int COUNT(0);
        DB_bind_vector binds;
        binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
        binds.push<int>(COUNT, MYSQL_TYPE_TINY);
        MYSQL_RES* prepare_meta_result = DB_fetch_prepare(statement, binds);
        mysql_stmt_fetch(statement);
        if(!rowid) return;
        c = COUNT + 1;
        if(COUNT == 2) {
            string query =
                "DELETE FROM bot.WARNS WHERE rowid = ?";
            binds.clear();
            binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
            DB_exec(query, binds);
            ban(bot, event);
            return;
        }
        binds.clear();
        binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
        string query =
            "UPDATE bot.WARNS SET COUNT = COUNT + 1 "
            "WHERE rowid = ?";
        DB_exec(query, binds);
        mysql_free_result(prepare_meta_result);
    });
    if(!c) {
        query =
            "INSERT INTO bot.WARNS VALUES(?, ?, ?, ?, ?)";
        binds.clear();
        uint64_t rowid(0);
        int COUNT(1);
        binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
        binds.push<uint64_t>(event.guild_id, MYSQL_TYPE_LONGLONG);
        binds.push<uint64_t>(event.member_id, MYSQL_TYPE_LONGLONG);
        binds.push<int>(COUNT, MYSQL_TYPE_TINY);
        binds.push();
        DB_exec(query, binds);
        return
            string("Done! Member ") + event.member_mention + " has 1/3 warnings";
    }
    if(c == 3)
        return
            string("Done! Member ") + event.member_mention +
            string(" has been banned due to 3 warnings");
    return
        string("Done! Member ") + event.member_mention +
        string(" has 2/3 warnings");
}