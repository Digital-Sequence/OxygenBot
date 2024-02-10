#include "commands/clear_warns.hpp"
#include "utils/DB_statement.hpp"

using std::string;
using utils::DB_statement;
using utils::slashcommand;

string commands::clear_warns(dpp::cluster& bot, const slashcommand& event) {
    DB_statement statement(
        "DELETE FROM bot.WARNS WHERE GUILD_ID = ? AND USER_ID = ?"
    );
    statement.add_bind(event.guild_id);
    statement.add_bind(event.member_id);
    statement.exec();
    statement.finish();

    return string("Done! Warnings for ") + event.member_mention +
        " have been cleared";
}