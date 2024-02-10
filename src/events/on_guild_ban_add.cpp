#include "events/on_guild_ban_add.hpp"
#include <stdexcept>
#include <string>
#include "utils/DB_statement.hpp"

using std::runtime_error;
using std::string;
using std::to_string;
using dpp::snowflake;
using utils::DB_statement;

void events::on_guild_ban_add(dpp::cluster& bot) {
    bot.on_guild_ban_add(
        [&bot](const dpp::guild_ban_add_t& event) {
            const snowflake GUILD_ID  = event.banning_guild->id;
            const snowflake USER_ID   = event.banned.id;
            try {
                DB_statement statement(
                    "INSERT INTO bot.BANS VALUES(?, ?, ?, ?, NULL)"
                );
                statement.add_bind(GUILD_ID);
                statement.add_bind(USER_ID);
                dpp::user_identified user =
                    bot.user_get_cached_sync(USER_ID);
                statement.add_bind(user.username);
                statement.add_bind(std::time(nullptr));
                try {
                    statement.exec();
                    statement.finish();
                } catch(const std::runtime_error& error) {
                    statement.finish();
                    string error_message = error.what();
                    error_message = error_message.substr(0, 15);
                    if(error_message != "Duplicate entry") throw error;
                }
            } catch(const runtime_error& error) {
                bot.log(
                    dpp::ll_error,
                    to_string(GUILD_ID) +
                    string("| error occured while marking deleted ban. ") +
                    error.what()
                );
            }
        }
    );
}