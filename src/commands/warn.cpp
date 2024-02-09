#include "commands/warn.hpp"
#include "globals.hpp"
#include "commands/commands.hpp"
#include "utils/DB_statement.hpp"
#include "utils/slashcommand.hpp"

using std::string;
using std::to_string;
using utils::DB_statement;
using utils::slashcommand;

string commands::warn(dpp::cluster& bot, const slashcommand& event) {
    DB_statement statement(
        "SELECT MAX_WARNS, WARN_PUNISHMENT FROM bot.PREFERENCES "
        "WHERE GUILD_ID = ? LIMIT 1"
    );
    int MAX_WARNS(0);
    string WARN_PUNISHMENT(10, ' ');
    statement.add_buffer<int>(MAX_WARNS, MYSQL_TYPE_TINY);
    statement.add_buffer(WARN_PUNISHMENT);
    statement.add_bind(event.guild_id);
    statement.exec();
    statement.fetch();
    statement.free_result();

    if(!MAX_WARNS) {
        MAX_WARNS = numerics_config["default_max_warns"];
        WARN_PUNISHMENT = config["default_warn_punishment"];
    }

    statement.clear();
    statement.clear_buffers();
    statement.set_query(
        "SELECT rowid, COUNT FROM bot.WARNS "
        "WHERE GUILD_ID = ? AND USER_ID = ? LIMIT 1"
    );
    uint64_t rowid(0);
    int COUNT(0);
    statement.add_buffer<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
    statement.add_buffer<int>(COUNT, MYSQL_TYPE_TINY);
    statement.add_bind(event.member_id);
    statement.exec();
    statement.fetch();
    statement.free_result();

    statement.clear_buffers();
    if(!rowid) {
        statement.set_query("INSERT INTO bot.WARNS VALUES(0, ?, ?, 1, NULL)");
        statement.exec();
        statement.finish();
        return
            string("Done! Member ") + event.member_mention +
            " has 1/" + to_string(MAX_WARNS) + " warnings";
    }
    
    statement.clear_binds();
    if(++COUNT == MAX_WARNS) {
        statement.set_query(
            "DELETE FROM bot.WARNS WHERE rowid = ?"
        );
        statement.add_bind(rowid);
        statement.exec();
        statement.finish();
        slashcommand_map.at(WARN_PUNISHMENT)(bot, event);
        return 
            string("Done! Member ") + event.member_mention +
            string(" has been punished due to ") + to_string(MAX_WARNS) +
            " warnings";
    }
    statement.clear_binds();
    statement.set_query(
        "UPDATE bot.WARNS SET COUNT = ? WHERE rowid = ?"
    );
    statement.add_bind(COUNT);
    statement.add_bind(rowid);
    statement.exec();
    statement.finish();
    return
        string("Done! Member ") + event.member_mention +
        string(" has ") + to_string(COUNT) + '/' + to_string(MAX_WARNS) +
        string(" warnings");
}