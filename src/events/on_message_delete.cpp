#include <stdexcept>
#include <string>
#include "events/on_message_delete.hpp"
#include "utils/DB_bind_vector.hpp"
#include "utils/DB_exec.hpp"

using std::runtime_error;
using std::string;
using std::to_string;
using dpp::snowflake;
using utils::DB_bind_vector;

void events::on_message_delete(dpp::cluster& bot) {
    bot.on_message_delete(
        [&bot](const dpp::message_delete_t& event) {
            snowflake GUILD_ID      = event.guild_id;
            snowflake CHANNEL_ID    = event.channel_id;
            snowflake MESSAGE_ID    = event.id;
            try {
                DB_bind_vector binds;
                binds.push<uint64_t>(GUILD_ID, MYSQL_TYPE_LONGLONG);
                binds.push<uint64_t>(CHANNEL_ID, MYSQL_TYPE_LONGLONG);
                binds.push<uint64_t>(MESSAGE_ID, MYSQL_TYPE_LONGLONG);
                string query =
                    "DELETE FROM bot.MESSAGES WHERE GUILD_ID = ? "
                    "AND CHANNEL_ID = ? AND MESSAGE_ID = ?";
                utils::DB_exec(query);
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