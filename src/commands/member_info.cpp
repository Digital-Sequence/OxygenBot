#include <time.h>
#include "commands/member_info.hpp"
#include "utils/date_str.hpp"
#include "utils/time_str.hpp"

using std::string;
using std::to_string;
using utils::date_str;
using utils::slashcommand;
using utils::time_str;

string commands::member_info(dpp::cluster& bot, slashcommand& event) {
    string reply = "";
    if(event.member_id) {
        reply =
            string("Snowflake: ") + to_string(event.member_id) +
            string("\nGlobal Name: ") + event.member_global_name +
            // code block used to discard formatting. Example: ___username___
            string("\nUsername: `") + event.member_username +
            string("`\nNickname: ") + event.member_nickname +
            string("\nBot: ");
        if(event.member_bot) reply = reply + " true";
        else reply = reply + " false";
        reply = 
            reply + string("\nJoined: ") + date_str(event.member_joined) +
            string(", ") + time_str(event.member_joined) +
            string("\nRegistered: ") + date_str(event.member_registered) +
            string(", ") + time_str(event.member_registered);
    } else {
        reply =
            string("Snowflake: ") + to_string(event.sender_id) +
            string("\nGlobal Name: ") + event.sender_global_name +
            string("\nUsername: `") + event.sender_username +
            string("`\nNickname: ") + event.sender_nickname +
            string("\nBot: ");
        if(event.sender_bot) reply = reply + " true";
        else reply = reply + " false";
        reply = 
            reply + string("\nJoined: ") + date_str(event.sender_joined) +
            string(", ") + time_str(event.sender_joined) +
            string("\nRegistered: ") + date_str(event.sender_registered) +
            string(", ") + time_str(event.sender_registered);
    }
    return reply;
}