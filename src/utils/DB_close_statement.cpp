#include <stdexcept>
#include "utils/DB_close_statement.hpp"

void utils::DB_close_statement(MYSQL* con, MYSQL_STMT*& statement) {
	if(mysql_stmt_close(statement)) throw std::runtime_error(mysql_error(con));
}