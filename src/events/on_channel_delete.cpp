#include "events/on_channel_delete.hpp"
#include "utils/DB_statement.hpp"
#include <stdexcept>
#include <string>

using std::runtime_error;
using std::string;
using std::to_string;
using dpp::snowflake;
using utils::DB_statement;

void events::on_channel_delete(dpp::cluster& bot) {
    bot.on_channel_delete(
        [&bot](const dpp::channel_delete_t& event) {
            const snowflake GUILD_ID      = event.deleting_guild->id;
            const snowflake CHANNEL_ID    = event.deleted.id;
            try {
                DB_statement statement(
                    "UPDATE bot.MESSAGES SET DELETED = ? "
                    "WHERE GUILD_ID = ? AND CHANNEL_ID = ?"
                );
                statement.add_bind(std::time(0));
                statement.add_bind(GUILD_ID);
                statement.add_bind(CHANNEL_ID);
                statement.exec();
                statement.finish();
            } catch(const runtime_error& error) {
                bot.log(
                    dpp::ll_error,
                    to_string(GUILD_ID) +
                    string(
                        "| error occured while marking deleted messages. "
                    ) + error.what()
                );
            }
        }
    );
}