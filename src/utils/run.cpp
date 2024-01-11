#include <stdexcept>
#include "commands/commands.hpp"
#include "utils/run.hpp"
#include "utils/slashcommand.hpp"

using std::map;
using std::string;
using std::to_string;
using commands::ban;
using commands::delete_messages;
using commands::delwarn;
using commands::member_info;
using commands::mute;
using commands::sync_roles;
using commands::unban;
using commands::unmute;
using commands::warn;
using utils::run;
using utils::slashcommand;

void utils::run(dpp::cluster& bot, const dpp::slashcommand_t& event) {
    try {
        slashcommand event_details(event);
        bot.log(dpp::ll_info, "received " + event_details.original_message);
        string reply = "";

        if(event_details.command_name == "warn")
            reply = warn(bot, event_details);
        if(event_details.command_name == "delete_messages")
            reply = delete_messages(bot, event_details);
        if(event_details.command_name == "delwarn")
            reply = delwarn(bot, event_details);
        if(event_details.command_name == "mute")
            reply = mute(bot, event_details);
        if(event_details.command_name == "unmute")
            reply = unmute(
                bot, event_details.guild_id, event_details.member_id,
                event_details.reason
            );
        // if(command_name == "kick") {
        //     commands::kick(event_details, bot);
        //     return;
        // }
        if(event_details.command_name == "ban")
            reply = ban(bot, event_details);
        if(event_details.command_name == "unban") {
            int length = event_details.member_username.length() + 1;
            char username[length];
            strcpy(username, event_details.member_username.c_str());
            reply = unban(
                bot, event_details.guild_id, username,
                event_details.reason
            );
        }
        if(event_details.command_name == "member_info")
            reply = member_info(bot, event_details);
        bool thinking = false;
        if(event_details.command_name == "sync_roles") {
            event.thinking();
            thinking = true;
            reply = sync_roles(bot, event_details);
        }
        // if statement, for commands that don't reply (will be added in future)
        if(reply != "")
            if(thinking) event.edit_response(reply);
            else event.reply(reply);
    } catch(const dpp::rest_exception& error) {
        bot.log(dpp::ll_error, error.what());
        event.reply(
            "Command failed. Reason: internal error "
            "or wrong command usage. In first case, contact admin"
        );
    } catch(const dpp::logic_exception& error) {
        event.reply("Wrong command usage (logic exception)");
    } catch(const std::invalid_argument& error) {
        event.reply(string("Command failed: Reason: ") + error.what());
    } catch(const std::runtime_error& error) {
        bot.log(dpp::ll_error, error.what());
        event.reply(
            "Command failed. Reason: internal error "
            "or wrong command usage. In first case, contact admin"
        );
    }
}