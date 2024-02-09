#include "events/on_message_create.hpp"
#include <stdexcept>
#include <string>
#include "utils/DB_statement.hpp"

using std::runtime_error;
using std::string;
using std::to_string;
using dpp::snowflake;
using utils::DB_statement;

void events::on_message_create(dpp::cluster& bot) {
    bot.on_message_create(
        [&bot](const dpp::message_create_t& event) {
            snowflake GUILD_ID      = event.msg.guild_id;
            snowflake CHANNEL_ID    = event.msg.channel_id;
            snowflake USER_ID       = event.msg.author.id;
            snowflake MESSAGE_ID    = event.msg.id;
            try {
                DB_statement statement(
                    "INSERT INTO bot.MESSAGES VALUES(?, ?, ?, ?, NULL)"
                );
                statement.add_bind(GUILD_ID);
                statement.add_bind(CHANNEL_ID);
                statement.add_bind(USER_ID);
                statement.add_bind(MESSAGE_ID);
                statement.exec();
                statement.finish();
            } catch(const runtime_error& error) {
                bot.log(
                    dpp::ll_error,
                    to_string(GUILD_ID) +
                    string("| error occured while saving message info. ") +
                    error.what()
                );
            }
        }
    );
}