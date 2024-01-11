#include <vector>
#include "register_slashcommands.hpp"

using std::vector;
using dpp::command_option;
using dpp::slashcommand;

dpp::command_option member(
    dpp::co_user, "member", "Target member", true
);

dpp::command_option member_username(
    dpp::co_string, "member_username", "Member's username", true
);

dpp::command_option duration(
    dpp::co_string, "duration", "Command effect duration", false
);

dpp::command_option messages_amount(
    dpp::co_integer, "messages_amount",
    "Amount of member's messages to delete", false
);

dpp::command_option reason(
    dpp::co_string, "reason", "Reason for your act", false
);

uint64_t delete_messages_p =    dpp::p_manage_messages |
                                dpp::p_use_application_commands;

uint64_t warn_p =   dpp::p_ban_members  |
                    dpp::p_kick_members |
                    delete_messages_p   |
                    dpp::p_moderate_members;

uint64_t mute_p = dpp::p_moderate_members | delete_messages_p;
uint64_t ban_p  = dpp::p_ban_members | delete_messages_p;
uint64_t kick_p = dpp::p_kick_members | delete_messages_p;
uint64_t sync_p = dpp::p_administrator;

void register_slashcommands(dpp::cluster& bot) {
    messages_amount.set_min_value(10);
    messages_amount.set_max_value(500);

    vector<slashcommand> commands = {
        slashcommand().
            set_name("delete_messages").
            set_description("Delete user's messages").
            set_application_id(bot.me.id).
            set_default_permissions(delete_messages_p).
            add_option(member).
            add_option(messages_amount).
            add_option(reason),
        slashcommand().
            set_name("warn").
            set_description("Warn a member").
            set_application_id(bot.me.id).
            set_default_permissions(warn_p).
            add_option(member).
            add_option(messages_amount).
            add_option(reason),
        slashcommand().
            set_name("delwarn").
            set_description("Delete warn of a member").
            set_application_id(bot.me.id).
            set_default_permissions(warn_p).
            add_option(member).
            add_option(reason),
        slashcommand().
            set_name("mute").
            set_description("Mute a member").
            set_application_id(bot.me.id).
            set_default_permissions(mute_p).
            add_option(member).
            add_option(duration).
            add_option(messages_amount).
            add_option(reason),
        slashcommand().
            set_name("unmute").
            set_description("Unmute a member").
            set_application_id(bot.me.id).
            set_default_permissions(mute_p).
            add_option(member).
            add_option(reason),
        slashcommand().
            set_name("kick").
            set_description("Kick a member").
            set_application_id(bot.me.id).
            set_default_permissions(kick_p).
            add_option(member).
            add_option(messages_amount).
            add_option(reason),
        slashcommand().
            set_name("ban").
            set_description("Ban a member").
            set_application_id(bot.me.id).
            set_default_permissions(ban_p).
            add_option(member).
            add_option(duration).
            add_option(messages_amount).
            add_option(reason),
        slashcommand().
            set_name("unban").
            set_description("Unban a member").
            set_application_id(bot.me.id).
            set_default_permissions(ban_p).
            add_option(member_username).
            add_option(reason),
        slashcommand().
            set_name("member_info").
            set_description("Get member info").
            set_application_id(bot.me.id).
            set_default_permissions(dpp::p_use_application_commands).
            add_option(member),
        slashcommand().
            set_name("sync_roles").
            set_description("Synchronize server roles with database").
            set_application_id(bot.me.id).
            set_default_permissions(sync_p)
    };
    commands[0].options[0].description = "The chatterbox";
    commands[0].options[1].required = true;
    commands[1].options[0].description = "The prankster to warn";
    commands[2].options[0].description = "The member to delete warn";
    commands[3].options[0].description = "The bad guy to mute";
    commands[4].options[0].description = "The member to unmute";
    commands[5].options[0].description = "The fool to kick";
    commands[6].options[0].description = "The villain to ban";
    commands[7].options[0].description = "The member to unban";
    commands[8].options[0].description =
        "If no member provided, your info will be shown";
    commands[8].options[0].required = false;

    bot.global_bulk_command_create(commands);
}