#include <stdexcept>
#include <string>
#include "events/on_message_create.hpp"
#include "utils/DB_bind_vector.hpp"
#include "utils/DB_exec.hpp"

using std::runtime_error;
using std::string;
using std::to_string;
using dpp::snowflake;
using utils::DB_bind_vector;

void events::on_message_create(dpp::cluster& bot) {
    bot.on_message_create(
        [&bot](const dpp::message_create_t& event) {
            uint64_t  rowid(0);
            snowflake GUILD_ID      = event.msg.guild_id;
            snowflake CHANNEL_ID    = event.msg.channel_id;
            snowflake USER_ID       = event.msg.author.id;
            snowflake MESSAGE_ID    = event.msg.id;
            try {
                DB_bind_vector binds;
                binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
                binds.push<uint64_t>(GUILD_ID, MYSQL_TYPE_LONGLONG);
                binds.push<uint64_t>(CHANNEL_ID, MYSQL_TYPE_LONGLONG);
                binds.push<uint64_t>(USER_ID, MYSQL_TYPE_LONGLONG);
                binds.push<uint64_t>(MESSAGE_ID, MYSQL_TYPE_LONGLONG);
                string query =
                    "INSERT INTO bot.MESSAGES VALUES(?, ?, ?, ?, ?)";

                utils::DB_exec(query, binds);
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