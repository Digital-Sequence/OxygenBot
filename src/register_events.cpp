#include "register_events.hpp"
#include "events/events.hpp"
#include "utils/run.hpp"

using utils::run;

void register_events(dpp::cluster& bot) {
    events::on_channel_delete(bot);
    events::on_message_create(bot);
    events::on_message_delete(bot);
    events::on_message_delete_bulk(bot);
    events::on_guild_ban_add(bot);
    events::on_guild_ban_remove(bot);
    bot.on_slashcommand(
        [&bot](const dpp::slashcommand_t& event) { run(bot, event); }
    );
}