#pragma once
#include <functional>
#include <string>
#include <mysql/mysql.h>
#include "utils/DB_bind_vector.hpp"

typedef std::function<void(MYSQL_STMT*)> DB_callback;

namespace utils {

void DB_exec(std::string, DB_callback = {});
void DB_exec(std::string, utils::DB_bind_vector&, DB_callback = {});

}