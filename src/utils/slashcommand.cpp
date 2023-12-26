#include <map>
#include <variant> // std::get()
#include <vector>
#include "utils/slashcommand.hpp"
#include "utils/stod.hpp"

using std::get;
using std::map;
using std::string;
using std::to_string;
using std::vector;
using dpp::command_data_option;
using dpp::guild_member;
using dpp::snowflake;
using utils::stod;

utils::slashcommand::slashcommand(
    const dpp::slashcommand_t& event
) {
    vector<command_data_option> options =
        event.command.get_command_interaction().options;
    dpp::interaction command = event.command;

    command_name    = command.get_command_name();
    guild_id        = command.guild_id;
    channel_id      = command.channel_id;
    user_id         = 0;
    member_nickname = "";
    member_mention  = "";
    member_username = "";
    duration        = 0;
    messages_amount = 0;
    reason          = "";
    
    original_message = '/' + command_name;
    string duration_str = "";
    for(auto& i : options) {
        if(i.name == "member") {
            user_id           = get<snowflake>(event.get_parameter("member"));
            guild_member member = command.get_resolved_member(user_id);
            member_nickname     = member.get_nickname();
            member_mention      = member.get_mention();
            original_message    = original_message + ' ' + member_mention;
        };
        if(i.name == "member_username") {
            member_username =
                get<string>(event.get_parameter("member_username"));
                original_message = original_message + " " + member_username;
        };
        if(i.name == "duration") {
            duration_str = get<string>(i.value);
            original_message = original_message + " duration: " + duration_str;
        };
        if(i.name == "messages_amount") {
            messages_amount = get<int64_t>(i.value);
            original_message = original_message + " messages_amount: " + to_string(messages_amount);
        };
        if(i.name == "reason") {
            reason = get<string>(i.value);
            original_message = original_message + " reason: " + reason;
        };
    };

    if(member_username == "")
        member_username = command.get_resolved_user(user_id).username;

    if(duration_str != "") stod(duration_str, duration);
}