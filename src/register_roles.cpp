#include <stdexcept>
#include <variant> // std::get()
#include "register_roles.hpp"
#include "roles.hpp"

using std::get;
using std::pair;
using std::runtime_error;
using std::string;
using std::to_string;
using dpp::snowflake;

static uint64_t muted_role_permissions = 
    dpp::p_add_reactions |
    dpp::p_send_messages |
    dpp::p_send_tts_messages |
    dpp::p_speak |
    dpp::p_send_messages_in_threads |
    dpp::p_send_voice_messages;

void register_roles(dpp::cluster& bot) {
    dpp::guild_map guilds = bot.current_user_get_guilds_sync();
    for(auto& i : guilds) {
        snowflake GUILD_ID = i.first;
        muted_roles[GUILD_ID] = 0;
        try {
            dpp::role_map role_map = bot.roles_get_sync(GUILD_ID);
            for(auto& i : role_map) {
                roles[GUILD_ID][i.first] = i.second.name;
                if(i.second.name == "muted") muted_roles[GUILD_ID] = i.first;
            }
            if(!muted_roles[GUILD_ID]) {
                dpp::role role;
                role.set_name("muted").set_bot_id(bot.me.id).
                set_guild_id(GUILD_ID);
                role = bot.role_create_sync(role);
                muted_roles[GUILD_ID] = role.id;
                dpp::channel_map channels = bot.channels_get_sync(GUILD_ID);
                for(auto& i : channels) {
                    bot.channel_edit_permissions_sync(
                        i.second, role.id, 0,
                        muted_role_permissions, false
                    );
                };
            }
        } catch(const dpp::rest_exception& error) {
            bot.log(
                dpp::ll_error,
                to_string(GUILD_ID) +
                string("| error occured while registering roles. Error message: ") +
                error.what()
            );
        }
    }
}