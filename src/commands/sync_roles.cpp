#include <map>
#include <utility>
#include "commands/sync_roles.hpp"
#include "globals.hpp"
#include "utils/DB_bind_vector.hpp"
#include "utils/DB_exec.hpp"
#include "utils/DB_fetch_prepare.hpp"

using std::map;
using std::pair;
using std::to_string;
using std::string;
using std::vector;
using dpp::snowflake;
using utils::DB_bind_vector;
using utils::DB_exec;
using utils::DB_fetch_prepare;
using utils::slashcommand;

const static uint64_t muted_role_permissions = 
    dpp::p_add_reactions |
    dpp::p_send_messages |
    dpp::p_send_tts_messages |
    dpp::p_speak |
    dpp::p_send_messages_in_threads |
    dpp::p_send_voice_messages;

string commands::sync_roles(dpp::cluster& bot, const slashcommand& event) {
    dpp::role_map guild_roles = bot.roles_get_sync(event.guild_id);
    map<snowflake, pair<uint64_t, string>> DB_roles;
    
    uint64_t GUILD_ID = event.guild_id;
    DB_bind_vector binds;
    binds.push<uint64_t>(GUILD_ID, MYSQL_TYPE_LONGLONG);
    string query =
        "SELECT rowid, ROLE_ID, NAME FROM bot.ROLES WHERE GUILD_ID = ?";
    DB_exec(query, binds, [&DB_roles](MYSQL_STMT* statement) {
        uint64_t rowid(0);
        uint64_t ROLE_ID(0);
        char NAME[100];
        DB_bind_vector binds;
        binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
        binds.push<uint64_t>(ROLE_ID, MYSQL_TYPE_LONGLONG);
        binds.push(NAME, MYSQL_TYPE_STRING, 100);
        MYSQL_RES* prepare_meta_result =
            DB_fetch_prepare(statement, binds);
        while(!mysql_stmt_fetch(statement) && ROLE_ID) {
            DB_roles[ROLE_ID].first = rowid;
            DB_roles[ROLE_ID].second = NAME;
        }
        mysql_free_result(prepare_meta_result);
    });

    query = "INSERT INTO bot.ROLES VALUES(?, ?, ?, ?)";
    binds.clear();
    uint64_t rowid(0);
    uint64_t ROLE_ID(0);
    long unsigned int length(0);
    char NAME[100];
    binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
    binds.push<uint64_t>(GUILD_ID, MYSQL_TYPE_LONGLONG);
    binds.push<uint64_t>(ROLE_ID, MYSQL_TYPE_LONGLONG);
    binds.push(NAME, MYSQL_TYPE_STRING, &length);
    string update_query = "UPDATE bot.ROLES SET NAME = ? WHERE rowid = ?";
    DB_bind_vector update_binds;
    update_binds.push(NAME, MYSQL_TYPE_STRING, &length);
    update_binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
    int added(0);
    int deleted(0);
    int renamed(0);
    for(const auto& i : guild_roles) {
        if(DB_roles[i.first].second == "") {
            rowid = 0;
            ROLE_ID = i.first;
            strcpy(NAME, i.second.name.c_str());
            length = i.second.name.length() + 1;
            DB_exec(query, binds);
            added++;
        } else if(DB_roles[i.first].second != i.second.name) {
            rowid = DB_roles[i.first].first;
            strcpy(NAME, i.second.name.c_str());
            length = i.second.name.length() + 1;
            DB_exec(update_query, update_binds);
            renamed++;
        }
    }

    query = "DELETE FROM bot.ROLES WHERE rowid = ?";
    binds.clear();
    binds.push<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
    for(const auto& i : DB_roles)
        if(guild_roles[i.first].name == "") {
            rowid = i.second.first;
            DB_exec(query, binds);
            deleted++;
        }
    string reply =
        string("Added ") + to_string(added) + " roles\n";
    reply =
        reply + string("Deleted ") + to_string(deleted) + " roles\n";
    reply = reply + string("Renamed ") + to_string(renamed) + " roles";
    for(const auto& i : guild_roles) if(i.second.name == "muted") return reply;

    dpp::role role;
    role.set_name("muted").set_bot_id(bot.me.id).set_guild_id(GUILD_ID);
    role = bot.role_create_sync(role);
    dpp::channel_map channels = bot.channels_get_sync(GUILD_ID);
    for(auto& i : channels) {
        bot.channel_edit_permissions_sync(
            i.second, role.id, 0,
            muted_role_permissions, false
        );
    }
    rowid = 0;
    ROLE_ID = role.id;
    length = 6;
    strcpy(NAME, "muted");
    query = "INSERT INTO bot.ROLES VALUES(?, ?, ?, ?)";
    DB_exec(query, binds);

    reply = reply + "\nCreated @muted role";
    return reply;
}