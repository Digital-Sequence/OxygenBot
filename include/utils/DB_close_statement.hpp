#pragma once
#include <mysql/mysql.h>

namespace utils {

void DB_close_statement(MYSQL*, MYSQL_STMT*&);

}