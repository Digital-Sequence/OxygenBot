#include "events/on_guild_ban_remove.hpp"
#include <stdexcept>
#include <string>
#include "utils/DB_statement.hpp"

using std::runtime_error;
using std::string;
using std::to_string;
using dpp::snowflake;
using utils::DB_statement;

void events::on_guild_ban_remove(dpp::cluster& bot) {
    bot.on_guild_ban_remove(
        [&bot](const dpp::guild_ban_remove_t& event) {
            string USERNAME(32, '\0');
            uint64_t DATE(0);
            const snowflake GUILD_ID  = event.unbanning_guild->id;
            const snowflake USER_ID   = event.unbanned.id;
            try {
                DB_statement statement(
                    "SELECT USERNAME, DATE FROM bot.BANS "
                    "WHERE GUILD_ID = ? AND USER_ID = ?"
                );
                statement.add_buffer(USERNAME);
                statement.add_buffer<uint64_t>(DATE, MYSQL_TYPE_LONGLONG);
                statement.add_bind(GUILD_ID);
                statement.add_bind(USER_ID);
                statement.exec();
                statement.fetch();
                statement.free_result();

                statement.set_query(
                    "DELETE FROM bot.BANS WHERE GUILD_ID = ? AND USER_ID = ?"
                );
                statement.exec();

                statement.set_query(
                    "INSERT INTO bot.BANS_CANCELLED VALUES(0, ?, ?, ?, ?, ?)"
                );
                statement.add_bind(USERNAME);
                statement.add_bind(DATE);
                statement.add_bind(std::time(0));
                statement.exec();
                statement.finish();
            } catch(const runtime_error& error) {
                bot.log(
                    dpp::ll_error,
                    to_string(GUILD_ID) +
                    string("| error occured while deleting ban entry. ") +
                    error.what()
                );
            }
        }
    );
}