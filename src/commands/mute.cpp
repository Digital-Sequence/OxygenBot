#include <stdexcept>
#include <variant>
#include "commands/delete_messages.hpp"
#include "commands/mute.hpp"
#include "utils/DB_bind_vector.hpp"
#include "utils/DB_exec.hpp"
#include "utils/DB_fetch_prepare.hpp"

using std::string;
using std::to_string;
using dpp::snowflake;
using utils::DB_bind_vector;
using utils::DB_exec;
using utils::DB_fetch_prepare;
using utils::slashcommand;

string commands::mute(dpp::cluster& bot, slashcommand& event) {
    // snowflake muted_role = muted_roles[event.guild_id];
    // std::cout << "Muted role: " << muted_role << std::endl;
    // if(!muted_role)
    //     return
    //         string("Member ") + event.member_mention +
    //         " can't be muted. Reason: muted role is deleted by someone";
    // bot.guild_member_add_role(event.guild_id, event.member_id, muted_role);
    // DB_bind_vector binds;
    // binds.push<uint64_t>(event.guild_id, MYSQL_TYPE_LONGLONG);
    // binds.push<uint64_t>(event.member_id, MYSQL_TYPE_LONGLONG);
    // string query =
    //     "SELECT rowid FROM bot.MUTES WHERE GUILD_ID = ? AND USER_ID = ?";
    // bool muted = false;
    // DB_exec(query, binds, [&muted](MYSQL_STMT* statement) {
    //     uint64_t rowid(0);
    //     DB_bind_vector binds;
    //     binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
    //     MYSQL_RES* prepare_meta_result =
    //         DB_fetch_prepare(statement, binds);
    //     if(!rowid) return;
    //     muted = true;
    //     mysql_free_result(prepare_meta_result);
    // });
    // if(muted) return
    //     string("Member ") + event.member_mention + " has already been muted";
    // uint64_t rowid(0);
    // uint64_t EXPIRES(0);
    // binds.clear();
    // binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
    // binds.push<uint64_t>(event.guild_id, MYSQL_TYPE_LONGLONG);
    // binds.push<uint64_t>(event.member_id, MYSQL_TYPE_LONGLONG);
    // if(event.duration) {
    //     EXPIRES = std::time(0) + event.duration;
    //     binds.push<uint64_t>(EXPIRES, MYSQL_TYPE_LONGLONG);
    // } else binds.push();
    // query = "INSERT INTO bot.MUTES VALUES(?, ?, ?, ?)";
    // DB_exec(query, binds);
    // if(event.messages_amount) delete_messages(bot, event);
    // string reply =
    //     string("Done! Member ") + event.member_mention +
    //     string(" has been muted");
    // if(event.reason != "") reply = reply + ". Reason: " + event.reason;
    // return reply;
    return "";
}