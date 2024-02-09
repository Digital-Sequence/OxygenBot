#include "events/on_message_delete_bulk.hpp"
#include <stdexcept>
#include <string>
#include "utils/DB_statement.hpp"

using std::runtime_error;
using std::string;
using std::to_string;
using dpp::snowflake;
using std::vector;
using utils::DB_statement;

void events::on_message_delete_bulk(dpp::cluster& bot) {
    bot.on_message_delete_bulk(
        [&bot](const dpp::message_delete_bulk_t& event) {
            snowflake GUILD_ID      = event.deleting_guild->id;
            snowflake CHANNEL_ID    = event.deleting_channel->id;
            try {
                vector<snowflake> messages  = event.deleted;

                DB_statement statement(
                    "UPDATE bot.MESSAGES SET DELETED = ? "
                    "WHERE GUILD_ID = ? AND CHANNEL_ID = ? "
                    "AND MESSAGE_ID = ? AND DELETED IS NULL"
                );
                statement.add_bind(std::time(0));
                statement.add_bind(GUILD_ID);
                statement.add_bind(CHANNEL_ID);
                statement.add_bind(0);
                    
                for(auto& i : messages) {
                    statement.set_bind_value(3, i);
                    statement.exec();
                }
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