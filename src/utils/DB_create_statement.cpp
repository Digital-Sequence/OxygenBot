#include <stdexcept>
#include <utils/DB_create_statement.hpp>
#include <utils/DB_close_statement.hpp>

using std::runtime_error;
using std::string;

MYSQL_STMT* utils::DB_create_statement(
	MYSQL* con, const string query, MYSQL_BIND* binds
) {
	MYSQL_STMT* statement = mysql_stmt_init(con);
	if(!statement) {
		runtime_error error("out of memory { mysql_stmt_init() }");
		throw error;
	}

	int result = mysql_stmt_prepare(statement, query.c_str(), query.length());
	
	if(result) {
		runtime_error error(mysql_stmt_error(statement));
		try {
			DB_close_statement(con, statement);
			throw error;
		} catch(const runtime_error& e) {
			throw runtime_error(
				string(error.what()) + "->" + string(e.what())
			);
		}
  	}

	if(binds) {
		result = mysql_stmt_bind_param(statement, binds);
		if(result) {
			runtime_error error(mysql_stmt_error(statement));
			try {
				DB_close_statement(con, statement);
				throw error;
			} catch(const runtime_error& e) {
				throw runtime_error(
					string(error.what()) + "->" + string(e.what())
				);
			}
		}
	}

	return statement;
}