#include <stdexcept>
#include <string>
#include "events/on_guild_ban_remove.hpp"
#include "utils/DB_bind_vector.hpp"
#include "utils/DB_exec.hpp"

using std::runtime_error;
using std::string;
using std::to_string;
using dpp::snowflake;
using utils::DB_bind_vector;

void events::on_guild_ban_remove(dpp::cluster& bot) {
    bot.on_guild_ban_remove(
        [&bot](const dpp::guild_ban_remove_t& event) {
            snowflake GUILD_ID  = event.unbanning_guild->id;
            snowflake USER_ID   = event.unbanned.id;
            try {
                DB_bind_vector binds;
                binds.push<uint64_t>(GUILD_ID, MYSQL_TYPE_LONGLONG);
                binds.push<uint64_t>(USER_ID, MYSQL_TYPE_LONGLONG);
                string query =
                    "DELETE FROM bot.BANS WHERE GUILD_ID = ? AND USER_ID = ?";
                utils::DB_exec(query, binds);
            } catch(const runtime_error& error) {
                bot.log(
                    dpp::ll_error,
                    to_string(GUILD_ID) +
                    string("| error occured while saving ban info. ") +
                    error.what()
                );
            }
        }
    );
}