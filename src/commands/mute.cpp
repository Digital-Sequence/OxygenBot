#include "commands/mute.hpp"
#include <stdexcept>
#include "commands/delete_messages.hpp"
#include "utils/DB_statement.hpp"

using std::string;
using utils::DB_statement;
using utils::slashcommand;

string commands::mute(dpp::cluster& bot, const slashcommand& event) {
    DB_statement statement(
        "SELECT ROLE_ID FROM bot.ROLES "
        "WHERE GUILD_ID = ? AND NAME = 'muted' LIMIT 1");
    uint64_t ROLE_ID(0);
    statement.add_buffer<uint64_t>(ROLE_ID, MYSQL_TYPE_LONGLONG);
    statement.add_bind(event.guild_id);
    statement.exec();
    statement.fetch();
    statement.free_result();
    if(!ROLE_ID) {
        statement.finish();
        return string("Cannot mute member ") + event.member_mention +
            ". Reason: no muted role found. Try to use /create_muted_role or "
            "contact admin";
    }
    
    statement.set_query("INSERT INTO bot.MUTES VALUES(?, ?, ?, ?)");
    statement.add_bind(event.member_id);
    statement.add_bind(std::time(nullptr));
    if(event.duration) statement.add_bind(std::time(nullptr) + event.duration);
    else statement.add_bind();
    try { statement.exec(); }
    catch(const std::runtime_error& error) {
        statement.finish();
        string error_message = error.what();
        error_message = error_message.substr(0, 15);
        if(error_message == "Duplicate entry")
            return string("Member ") + event.member_mention +
                " has already been muted";
        else throw error;
    }
    statement.finish();

    bot.guild_member_add_role(event.guild_id, event.member_id, ROLE_ID);

    if(event.messages_amount) delete_messages(bot, event);
    
    string reply =
        string("Done! Member ") + event.member_mention +
        string(" has been muted");
    if(event.reason != "") reply = reply + ". Reason: " + event.reason;
    return reply;
}