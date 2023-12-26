#include <stdexcept>
#include "commands/unban.hpp"
#include "commands/unmute.hpp"
#include "start_timer.hpp"
#include "utils/DB_bind_vector.hpp"
#include "utils/DB_exec.hpp"
#include "utils/DB_fetch_prepare.hpp"

using std::runtime_error;
using std::string;
using std::to_string;
using dpp::snowflake;
using dpp::utility::user_mention;
using commands::unban;
using commands::unmute;
using utils::DB_bind_vector;
using utils::DB_exec;
using utils::DB_fetch_prepare;

void start_timer(dpp::cluster& bot) {
    bot.start_timer([&bot](dpp::timer t) {
        snowflake GUILD_ID(0);
        snowflake USER_ID(0);
        try {
            uint64_t current_time = std::time(0);
            DB_bind_vector binds;
            binds.push<uint64_t>(current_time, MYSQL_TYPE_LONGLONG);
            string query =
                string("SELECT rowid,GUILD_ID,USER_ID FROM bot.BANS ") +
                string("WHERE EXPIRES IS NOT NULL AND EXPIRES <= ?");
            DB_exec(
                query, binds,
                [&bot, &GUILD_ID, &USER_ID](MYSQL_STMT* statement) {
                    uint64_t  rowid(0);
                    DB_bind_vector binds;
                    binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
                    binds.push<uint64_t>(GUILD_ID, MYSQL_TYPE_LONGLONG);
                    binds.push<uint64_t>(USER_ID, MYSQL_TYPE_LONGLONG);
                    MYSQL_RES* prepare_meta_result =
                        DB_fetch_prepare(statement, binds);
                    if(!prepare_meta_result) return;
                    while(!mysql_stmt_fetch(statement)) {
                        DB_bind_vector binds_delete;
                        binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
                        string query = "DELETE FROM bot.BANS WHERE rowid = ?";
                        DB_exec(query, binds_delete);
                        unban(bot, GUILD_ID, USER_ID);
                    };
                    mysql_free_result(prepare_meta_result);
                }
            );
            query =
                string("SELECT rowid,GUILD_ID,USER_ID FROM bot.MUTES ") +
                string("WHERE EXPIRES IS NOT NULL AND EXPIRES <= ?");
            DB_exec(
                query, binds,
                [&bot, &GUILD_ID, &USER_ID](MYSQL_STMT* statement) {
                    uint64_t  rowid = 0;
                    DB_bind_vector binds;
                    binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
                    binds.push<uint64_t>(GUILD_ID, MYSQL_TYPE_LONGLONG);
                    binds.push<uint64_t>(USER_ID, MYSQL_TYPE_LONGLONG);
                    MYSQL_RES* prepare_meta_result =
                        DB_fetch_prepare(statement, binds);
                    if(!prepare_meta_result) return;
                    while(!mysql_stmt_fetch(statement)) {
                        DB_bind_vector binds_delete;
                        binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
                        string query = "DELETE FROM bot.MUTES WHERE rowid = ?";
                        DB_exec(query, binds_delete);
                        try {
                            unmute(bot, GUILD_ID, USER_ID);
                        } catch(const dpp::rest_exception& error) {
                            bot.log(
                                dpp::ll_info,
                                string("Cannot unmute ") + user_mention(USER_ID) +
                                string("Reason: ") + error.what()
                            );
                        };
                    };
                    mysql_free_result(prepare_meta_result);
                }
            );
        } catch(const runtime_error& error) {
            bot.log(
                dpp::ll_error,
                to_string(GUILD_ID) +
                string(
                    "| error occured while trying to "
                    "unban USER. Error message: "
                ) + error.what()
            );
        }
    }, 1);
}