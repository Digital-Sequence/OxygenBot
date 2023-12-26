#include <stdexcept>
#include <string>
#include "events/on_message_delete_bulk.hpp"
#include "utils/DB_bind_vector.hpp"
#include "utils/DB_exec.hpp"

using std::runtime_error;
using std::string;
using std::to_string;
using dpp::snowflake;
using std::vector;
using utils::DB_bind_vector;

void events::on_message_delete_bulk(dpp::cluster& bot) {
    bot.on_message_delete_bulk(
        [&bot](const dpp::message_delete_bulk_t& event) {
            snowflake GUILD_ID          = event.deleting_guild->id;
            snowflake CHANNEL_ID        = event.deleting_channel->id;
            snowflake MESSAGE_ID(0);
            try {
                vector<snowflake> messages  = event.deleted;

                DB_bind_vector binds;
                binds.push<uint64_t>(GUILD_ID, MYSQL_TYPE_LONGLONG);
                binds.push<uint64_t>(CHANNEL_ID, MYSQL_TYPE_LONGLONG);
                binds.push<uint64_t>(MESSAGE_ID, MYSQL_TYPE_LONGLONG);
                string query =
                    "DELETE FROM bot.MESSAGES WHERE GUILD_ID = ? "
                    "AND CHANNEL_ID = ? AND MESSAGE_ID = ?";
                    
                for(auto& i : messages) {
                    MESSAGE_ID = i;
                    utils::DB_exec(query, binds);
                };
            } catch(const runtime_error& error) {
                bot.log(
                    dpp::ll_error,
                    to_string(GUILD_ID) +
                    string("| error occured while deleting message. ") +
                    error.what()
                );
            }
        }
    );
}