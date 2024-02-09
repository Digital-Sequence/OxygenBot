#include <stdexcept>
#include "commands/commands.hpp"
#include "utils/run.hpp"
#include "utils/slashcommand.hpp"

using std::string;
using utils::run;
using utils::slashcommand;

void utils::run(dpp::cluster& bot, const dpp::slashcommand_t& event) {
    try {
        bool thinking = false;
        slashcommand event_details(bot, event);
        bot.log(dpp::ll_info, "received " + event_details.original_message);
        string reply;

        if(event_details.command_name == "create_muted_role") {
            event.thinking();
            thinking = true;
        }

        reply = 
            slashcommand_map.at(event_details.command_name)(bot, event_details);

        // for commands which don't reply (will be added in future)
        if(!reply.empty())
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