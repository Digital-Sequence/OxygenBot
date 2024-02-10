#include "commands/unmute.hpp"
#include "utils/DB_statement.hpp"
#include "utils/slashcommand.hpp"

using std::string;
using dpp::snowflake;
using dpp::utility::user_mention;
using utils::DB_statement;
using utils::slashcommand;

string commands::unmute(
    dpp::cluster& bot, const slashcommand& event
) {
    DB_statement statement(
        "SELECT DATE FROM bot.MUTES WHERE GUILD_ID = ? AND USER_ID = ?"
    );
    uint64_t DATE(0);
    statement.add_buffer<uint64_t>(DATE, MYSQL_TYPE_LONGLONG);
    statement.add_bind(event.guild_id);
    statement.add_bind(event.member_id);
    statement.exec();
    statement.fetch();
    statement.free_result();
    if(!DATE) return string("Member ") +
        user_mention(event.member_id) + " isn't muted";
    
    statement.set_query(
        "DELETE FROM bot.MUTES WHERE GUILD_ID = ? and USER_ID = ?"
    );
    statement.exec();

    statement.set_query(
        "INSERT INTO bot.MUTES_CANCELLED VALUES(0, ?, ?, ?, ?)"
    );
    statement.add_bind(DATE);
    statement.add_bind(std::time(nullptr));
    statement.exec();

    statement.clear_all();
    statement.set_query(
        "SELECT ROLE_ID FROM bot.ROLES "
        "WHERE GUILD_ID = ? AND NAME = 'muted' LIMIT 1"
    );
    uint64_t ROLE_ID(0);
    statement.add_buffer<uint64_t>(ROLE_ID, MYSQL_TYPE_LONGLONG);
    statement.add_bind(event.guild_id);
    statement.exec();
    statement.fetch();
    statement.free_result();
    bot.guild_member_delete_role(event.guild_id, event.member_id, ROLE_ID);
    statement.finish();

    return
        string("Done! Member ") + user_mention(event.member_id) + " unmuted";
}

void commands::unmute(
    dpp::cluster& bot, const snowflake GUILD_ID, const snowflake USER_ID,
    const uint64_t DATE
) { 
    DB_statement statement(
        "DELETE FROM bot.MUTES WHERE GUILD_ID = ? and USER_ID = ?"
    );
    statement.add_bind(GUILD_ID);
    statement.add_bind(USER_ID);
    statement.exec();

    statement.set_query(
        "INSERT INTO bot.MUTES_CANCELLED VALUES(0, ?, ?, ?, ?)"
    );
    statement.add_bind(DATE);
    statement.add_bind(std::time(nullptr));
    statement.exec();

    statement.clear_all();
    statement.set_query(
        "SELECT ROLE_ID FROM bot.ROLES "
        "WHERE GUILD_ID = ? AND NAME = 'muted' LIMIT 1"
    );
    uint64_t ROLE_ID(0);
    statement.add_buffer<uint64_t>(ROLE_ID, MYSQL_TYPE_LONGLONG);
    statement.add_bind(GUILD_ID);
    statement.exec();
    statement.fetch();
    statement.free_result();
    bot.guild_member_delete_role(GUILD_ID, USER_ID, ROLE_ID);
    statement.finish();
}