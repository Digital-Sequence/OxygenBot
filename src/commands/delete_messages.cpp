#include <queue>
#include <stdexcept>
#include "commands/delete_messages.hpp"
#include "utils/delete_old_messages.hpp"
#include "utils/DB_bind_vector.hpp"
#include "utils/DB_exec.hpp"
#include "utils/DB_fetch_prepare.hpp"

using std::string;
using std::to_string;
using std::vector;
using dpp::snowflake;
using utils::delete_old_messages;
using utils::DB_bind_vector;
using utils::DB_exec;
using utils::DB_fetch_prepare;
using utils::slashcommand;

string commands::delete_messages(dpp::cluster& bot, slashcommand& event) {
    DB_bind_vector binds;
    binds.push<uint64_t>(event.guild_id, MYSQL_TYPE_LONGLONG);
    binds.push<uint64_t>(event.channel_id, MYSQL_TYPE_LONGLONG);
    binds.push<uint64_t>(event.user_id, MYSQL_TYPE_LONGLONG);
    binds.push<int64_t>(event.messages_amount, MYSQL_TYPE_SHORT);
    string query =
        "SELECT MESSAGE_ID FROM bot.MESSAGES WHERE GUILD_ID = ? "
        "AND CHANNEL_ID = ? AND USER_ID = ? ORDER BY rowid DESC LIMIT ?";
    std::queue<snowflake> messages = {};

    DB_exec(query, binds, [&messages](MYSQL_STMT* statement) {
        snowflake MESSAGE_ID(0);
        DB_bind_vector binds;
        binds.push<uint64_t>(MESSAGE_ID, MYSQL_TYPE_LONGLONG);
        MYSQL_RES* prepare_meta_result =
            DB_fetch_prepare(statement, binds);
        while(!mysql_stmt_fetch(statement) && MESSAGE_ID) messages.push(MESSAGE_ID);
        mysql_free_result(prepare_meta_result);
    });

    int amount = messages.size();
    if(amount < 2) {
        string reply =
            "Done! 0 messages of " + event.member_mention + string(" deleted");
        if(event.reason != "") reply = reply + ". Reason: " + event.reason;
        return reply;
    };
    for(int i = messages.size(); i > 0; i = messages.size()) {
        if(i > 100) i = 100;
        vector<snowflake> messages_to_delete;
        for(int j = 0; j < i; j++) {
            messages_to_delete.push_back(messages.front());
            messages.pop();
        };
        bot.set_audit_reason(event.reason).
        message_delete_bulk(messages_to_delete, event.channel_id);
    };
    string reply =
        "Done! " + to_string(amount) + " messages of " +
        event.member_mention + string(" deleted");
    if(event.reason != "") reply = reply + ". Reason: " + event.reason;
    return reply;
}