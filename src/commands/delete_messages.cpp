#include "commands/delete_messages.hpp"
#include <ctime>
#include <queue>
#include <stdexcept>
#include "utils/DB_statement.hpp"

using std::string;
using std::to_string;
using std::vector;
using dpp::snowflake;
using utils::DB_statement;
using utils::slashcommand;

string commands::delete_messages(
    dpp::cluster& bot, const slashcommand& event
) {
    DB_statement statement(
        "SELECT MESSAGE_ID FROM bot.MESSAGES WHERE GUILD_ID = ? "
        "AND CHANNEL_ID = ? AND USER_ID = ? AND MESSAGE_ID > ? "
        "AND DELETED IS NULL ORDER BY MESSAGE_ID DESC LIMIT ?"
    );
    uint64_t two_weeks_ago =
        1000 * ((uint64_t)std::time(0) - 1209570 - 1420070400) << 22;
    /*
        1000 * (Current time - (2 weeks - 30 seconds) - 1420070400)
        Current time depends on your system time settings, so it's necessary
        to set to gmt. Minus 30 seconds is needed in case of
        long command executing. Minus 1420070400 because snowflakes store
        time since 2015 (1420070400 in seconds). Multiply by 1000, because
        snowflakes store time in milliseconds.
        https://discord.com/developers/docs/reference#snowflakes
    */
    snowflake MESSAGE_ID(0);
    statement.add_buffer<uint64_t>(MESSAGE_ID, MYSQL_TYPE_LONGLONG);
    statement.add_bind(event.guild_id);
    statement.add_bind(event.channel_id);
    statement.add_bind(event.member_id);
    statement.add_bind(two_weeks_ago);
    statement.add_bind(event.messages_amount);
    statement.exec();
    
    std::queue<snowflake> messages = {};
    while(!statement.fetch() && MESSAGE_ID) messages.push(MESSAGE_ID);
    statement.free_result();
    statement.finish();

    int amount = messages.size();
    if(amount < 2) {
        string reply =
            "Done! 0 messages of " + event.member_mention + string(" deleted");
        if(event.reason != "") reply = reply + ". Reason: " + event.reason;
        return reply;
    }
    
    for(int i = messages.size(); i > 0; i = messages.size()) {
        if(i > 100) i = 100;
        vector<snowflake> messages_to_delete;
        for(int j = 0; j < i; j++) {
            messages_to_delete.push_back(messages.front());
            messages.pop();
        }
        bot.set_audit_reason(event.reason).
        message_delete_bulk(messages_to_delete, event.channel_id);
    }
    string reply =
        "Done! " + to_string(amount) + " messages of " +
        event.member_mention + string(" deleted");
    if(event.reason != "") reply = reply + ". Reason: " + event.reason;
    return reply;
}