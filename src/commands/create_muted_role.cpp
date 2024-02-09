#include "commands/create_muted_role.hpp"
#include "globals.hpp"
#include "utils/DB_statement.hpp"

using std::string;
using utils::DB_statement;
using utils::slashcommand;

string commands::create_muted_role(
    dpp::cluster& bot, const slashcommand& event
) {
    const static uint64_t muted_role_permissions = 
        dpp::p_add_reactions |
        dpp::p_send_messages |
        dpp::p_send_tts_messages |
        dpp::p_speak |
        dpp::p_send_messages_in_threads |
        dpp::p_send_voice_messages;
    
    dpp::role role;
    role.set_name("muted").set_bot_id(bot.me.id).set_guild_id(event.guild_id);
    role = bot.role_create_sync(role);
    dpp::channel_map channels = bot.channels_get_sync(event.guild_id);
    for(auto& i : channels) {
        bot.channel_edit_permissions_sync(
            i.second, role.id, 0,
            muted_role_permissions, false
        );
    }

    DB_statement statement(
        "DELETE FROM bot.ROLES WHERE GUILD_ID = ? AND NAME = 'muted'"
    );
    statement.add_bind(event.guild_id);
    statement.exec();

    statement.set_query("INSERT INTO bot.ROLES VALUES(?, ?, 'muted')");
    statement.add_bind(role.id);
    statement.exec();
    statement.finish();

    return "Done! Now, you can use /mute command";
}