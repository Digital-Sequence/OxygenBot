#pragma once
#include <string>
#include <mysql/mysql.h>

namespace utils {

MYSQL_STMT* DB_create_statement(MYSQL*, const std::string, MYSQL_BIND* = 0);

}