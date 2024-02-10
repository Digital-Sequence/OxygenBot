#include "events/on_message_delete.hpp"
#include <stdexcept>
#include <string>
#include "utils/DB_statement.hpp"

using std::runtime_error;
using std::string;
using std::to_string;
using dpp::snowflake;
using utils::DB_statement;

void events::on_message_delete(dpp::cluster& bot) {
    bot.on_message_delete(
        [&bot](const dpp::message_delete_t& event) {
            snowflake GUILD_ID      = event.guild_id;
            snowflake CHANNEL_ID    = event.channel_id;
            snowflake MESSAGE_ID    = event.id;
            try {
                DB_statement statement(
                    "UPDATE bot.MESSAGES SET DELETED = ? "
                    "WHERE GUILD_ID = ? AND CHANNEL_ID = ? "
                    "AND MESSAGE_ID = ? AND DELETED IS NULL"
                );
                statement.add_bind(std::time(nullptr));
                statement.add_bind(GUILD_ID);
                statement.add_bind(CHANNEL_ID);
                statement.add_bind(MESSAGE_ID);
                statement.exec();
                statement.finish();
            } catch(const runtime_error& error) {
                bot.log(
                    dpp::ll_error,
                    to_string(GUILD_ID) +
                    string("| error occured while marking deleted message. ") +
                    error.what()
                );
            }
        }
    );
}