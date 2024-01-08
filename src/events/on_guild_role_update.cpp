#include <string>
#include "events/on_guild_role_update.hpp"

using std::string;
using dpp::snowflake;

void events::on_guild_role_update(dpp::cluster& bot) {
    bot.on_guild_role_update(
        [&bot](const dpp::guild_role_update_t& event) {
            // snowflake   GUILD_ID  = event.updating_guild->id;
            // snowflake   ROLE_ID   = event.updated->id;
            // string      ROLE_NAME = event.updated->name;

            // roles[GUILD_ID][ROLE_ID] = ROLE_NAME;
        }
    );
}