#include "commands/delwarn.hpp"
#include "utils/DB_statement.hpp"

using std::string;
using std::to_string;
using utils::DB_statement;
using utils::slashcommand;

string commands::delwarn(dpp::cluster& bot, const slashcommand& event) {
    DB_statement statement(
        "SELECT rowid, COUNT FROM bot.WARNS "
        "WHERE GUILD_ID = ? AND USER_ID = ? LIMIT 1"
    );
    uint64_t rowid(0);
    int COUNT(0);
    statement.add_buffer<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
    statement.add_buffer<int>(COUNT, MYSQL_TYPE_TINY);
    statement.add_bind(event.guild_id);
    statement.add_bind(event.member_id);
    statement.exec();
    statement.fetch();
    statement.free_result();

    if(!rowid)
        return "Member " + event.member_mention + string(" has no warnings");
    statement.clear_all();
    if(!--COUNT) {
        statement.set_query("DELETE FROM bot.WARNS WHERE rowid = ?");
        statement.add_bind(rowid);
        statement.exec();
    } else {
        statement.set_query(
            "UPDATE bot.WARNS SET COUNT = COUNT - 1 WHERE rowid = ?"
        );
        statement.add_bind(rowid);
        statement.exec();
    }

    statement.clear_binds();
    statement.set_query(
        "SELECT MAX_WARNS FROM bot.PREFERENCES WHERE GUILD_ID = ? LIMIT 1"
    );
    int MAX_WARNS(0);
    statement.add_buffer<int>(MAX_WARNS, MYSQL_TYPE_TINY);
    statement.add_bind(event.guild_id);
    statement.exec();
    statement.fetch();
    statement.free_result();
    statement.finish();

    if(!MAX_WARNS) MAX_WARNS = 3;
    string reply = 
        string("Done! Member ") + event.member_mention + string(" has ") +
        to_string(COUNT) + '/' + to_string(MAX_WARNS) + string(" warnings");
    return reply;
}