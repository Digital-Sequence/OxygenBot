#include "commands/create_muted_role.hpp"
#include "globals.hpp"
#include "utils/DB_bind_vector.hpp"
#include "utils/DB_exec.hpp"
#include "utils/DB_fetch_prepare.hpp"

using std::to_string;
using std::string;
using std::vector;
using dpp::snowflake;
using utils::DB_bind_vector;
using utils::DB_exec;
using utils::DB_fetch_prepare;
using utils::slashcommand;

const static uint64_t muted_role_permissions = 
    dpp::p_add_reactions |
    dpp::p_send_messages |
    dpp::p_send_tts_messages |
    dpp::p_speak |
    dpp::p_send_messages_in_threads |
    dpp::p_send_voice_messages;

string commands::create_muted_role(dpp::cluster& bot, const slashcommand& event) {
    uint64_t GUILD_ID(event.guild_id);
    dpp::role role;
    role.set_name("muted").set_bot_id(bot.me.id).set_guild_id(GUILD_ID);
    role = bot.role_create_sync(role);
    dpp::channel_map channels = bot.channels_get_sync(GUILD_ID);
    for(auto& i : channels) {
        bot.channel_edit_permissions_sync(
            i.second, role.id, 0,
            muted_role_permissions, false
        );
    }
    uint64_t rowid(0);
    uint64_t ROLE_ID(role.id);
    long unsigned int length(6);
    char NAME[100];
    DB_bind_vector binds;
    binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
    binds.push<uint64_t>(GUILD_ID, MYSQL_TYPE_LONGLONG);
    binds.push<uint64_t>(ROLE_ID, MYSQL_TYPE_LONGLONG);
    binds.push(NAME, MYSQL_TYPE_STRING, &length);
    strcpy(NAME, "muted");
    string query = "INSERT INTO bot.ROLES VALUES(?, ?, ?, ?)";
    DB_exec(query, binds);

    return "Done! Now, you can use /mute command";
}