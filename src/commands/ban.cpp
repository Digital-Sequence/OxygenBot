#include "commands/ban.hpp"
#include <stdexcept>
#include "commands/delete_messages.hpp"
#include "utils/DB_statement.hpp"

using std::string;
using commands::delete_messages;
using utils::DB_statement;
using utils::slashcommand;

string commands::ban(dpp::cluster& bot, const slashcommand& event) {
    DB_statement statement("INSERT INTO bot.BANS VALUES(?, ?, ?, ?, ?)");
    statement.add_bind(event.guild_id);
    statement.add_bind(event.member_id);
    statement.add_bind(event.member_username);
    statement.add_bind(std::time(0));
    if(event.duration) statement.add_bind(std::time(0) + event.duration);
    else statement.add_bind();
    try {
        statement.exec();
        statement.finish();
    } catch(const std::runtime_error& error) {
        statement.finish();
        string error_message = error.what();
        error_message = error_message.substr(0, 15);
        if(error_message == "Duplicate entry")
            return string("Member ") + event.member_mention +
                " has already been banned";
        else throw error;
    }

    bot.set_audit_reason(event.reason).
    guild_ban_add_sync(event.guild_id, event.member_id);

    if(event.messages_amount) delete_messages(bot, event);

    string reply =
        string("Done! User ") + event.member_mention + " has been banned";
    if(!event.reason.empty()) reply = reply + ". Reason: " + event.reason;
    
    return reply;
}