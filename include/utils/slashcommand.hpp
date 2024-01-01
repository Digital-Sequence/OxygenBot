#pragma once
#include <string>
#include <dpp/dpp.h>

namespace utils {

struct slashcommand {
    std::string     command_name;
    dpp::snowflake  guild_id;
    dpp::snowflake  channel_id;
    dpp::snowflake  sender_id;
    std::string     sender_username;
    std::string     sender_global_name;
    std::string     sender_nickname;
    bool            sender_bot;
    std::string     sender_mention;
    uint64_t        sender_joined;
    uint64_t        sender_registered;
    dpp::snowflake  member_id;
    std::string     member_global_name;
    std::string     member_nickname;
    bool            member_bot;
    std::string     member_mention;
    std::string     member_username;
    uint64_t        member_joined;
    uint64_t        member_registered;
    uint32_t        duration;
    int64_t         messages_amount;
    std::string     reason;
    std::string     original_message;
    slashcommand() {};
    slashcommand(const dpp::slashcommand_t&);
};

}