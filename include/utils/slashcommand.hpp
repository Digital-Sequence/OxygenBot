#pragma once
#include <string>
#include <dpp/dpp.h>

namespace utils {

struct slashcommand {
    std::string     command_name;
    dpp::snowflake  guild_id;
    dpp::snowflake  channel_id;
    dpp::snowflake  user_id;
    std::string     member_nickname;
    std::string     member_mention;
    std::string     member_username;
    uint32_t        duration;
    int64_t         messages_amount;
    std::string     reason;
    std::string     original_message;
    slashcommand() {};
    slashcommand(const dpp::slashcommand_t&);
};

}