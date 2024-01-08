#include <string>
#include "events/on_guild_role_delete.hpp"

using std::string;
using dpp::snowflake;

void events::on_guild_role_delete(dpp::cluster& bot) {
    bot.on_guild_role_delete(
        [&bot](const dpp::guild_role_delete_t& event) {
            // snowflake   GUILD_ID    = event.deleting_guild->id;
            // snowflake   ROLE_ID     = event.deleted->id;
            // string      ROLE_NAME   = event.deleted->name;

            // roles[GUILD_ID].erase(ROLE_ID);
            // if(ROLE_ID == muted_roles[GUILD_ID]) muted_roles[GUILD_ID] = 0;
        }
    );
}