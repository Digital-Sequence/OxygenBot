#include "start_timer.hpp"
#include <stdexcept>
#include "commands/unmute.hpp"
#include "utils/DB_statement.hpp"

using std::runtime_error;
using std::string;
using std::to_string;
using commands::unmute;
using utils::DB_statement;

void start_timer(dpp::cluster& bot) {
    static DB_statement statement;
    static uint64_t GUILD_ID(0);
    static uint64_t USER_ID(0);
    static uint64_t DATE(0);
    statement.add_buffer<uint64_t>(GUILD_ID, MYSQL_TYPE_LONGLONG);
    statement.add_buffer<uint64_t>(USER_ID, MYSQL_TYPE_LONGLONG);
    statement.add_buffer<uint64_t>(DATE, MYSQL_TYPE_LONGLONG);
    statement.add_bind(0);
    bot.start_timer([&](dpp::timer t) {
        try {
            statement.set_bind_value(0, std::time(0));
            statement.set_query(
                "SELECT GUILD_ID, USER_ID, DATE FROM bot.BANS "
                "WHERE EXPIRES IS NOT NULL AND EXPIRES <= ?"
            );
            statement.exec();
            while(!statement.fetch())
                bot.guild_ban_delete_sync(GUILD_ID, USER_ID);
            statement.free_result();
            statement.set_query(
                "SELECT GUILD_ID, USER_ID, DATE FROM bot.MUTES "
                "WHERE EXPIRES IS NOT NULL AND EXPIRES <= ?"
            );
            statement.exec();
            while(!statement.fetch()) unmute(bot, GUILD_ID, USER_ID, DATE);
            statement.free_result();
        } catch(const runtime_error& error) {
            bot.log(
                dpp::ll_error,
                to_string(GUILD_ID) +
                string(
                    "| error occured while trying to "
                    "unban/unmute USER. Error message: "
                ) + error.what()
            );
        }
    }, 1);
}