#include <ctime>
#include <cstdint>
#include "utils/DB_bind_vector.hpp"
#include "utils/DB_exec.hpp"
#include "utils/delete_old_messages.hpp"

using std::string;
using utils::DB_bind_vector;
using utils::DB_exec;

void utils::delete_old_messages() {
    DB_bind_vector binds;
    // Minus 1 minute from 1209600 (two weeks)
    uint64_t current_time = std::time(0) - 1209540;
    binds.push<uint64_t>(current_time, MYSQL_TYPE_LONGLONG);
    string query = "DELETE FROM bot.MESSAGES WHERE MESSAGE_ID < ?";
    DB_exec(query, binds);
}