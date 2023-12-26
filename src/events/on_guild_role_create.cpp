#include <string>
#include "events/on_guild_role_create.hpp"
#include "roles.hpp"

using std::string;
using dpp::snowflake;

void events::on_guild_role_create(dpp::cluster& bot) {
    bot.on_guild_role_create(
        [&bot](const dpp::guild_role_create_t& event) {
            snowflake   GUILD_ID  = event.creating_guild->id;
            snowflake   ROLE_ID   = event.created->id;
            string      ROLE_NAME = event.created->name;

            roles[GUILD_ID][ROLE_ID] = ROLE_NAME;
        }
    );
}