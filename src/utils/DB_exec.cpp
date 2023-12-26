#include <stdexcept>
#include <string>
#include "Connection_pool.hpp"
#include "utils/DB_bind_vector.hpp"
#include "utils/DB_close_statement.hpp"
#include "utils/DB_connect.hpp"
#include "utils/DB_create_statement.hpp"
#include "utils/DB_exec.hpp"

using std::runtime_error;
using std::string;
using utils::DB_create_statement;
using utils::DB_close_statement;
using utils::DB_connect;

void utils::DB_exec(string query, DB_callback cb) {
	MYSQL* con = 0;
	MYSQL_STMT* statement = 0;
	try {
		if(connections.empty()) DB_connect(con);
		else con = connections.pop();
		if(mysql_ping(con)) DB_connect(con);

		statement = DB_create_statement(con, query);

		if(mysql_stmt_execute(statement))
			throw runtime_error(mysql_stmt_error(statement));
		if(cb) cb(statement);

		utils::DB_close_statement(con, statement);
	} catch(const runtime_error& error) {
		try {
			utils::DB_close_statement(con, statement);
		} catch(const runtime_error& e) {
			throw
				runtime_error(string(error.what()) + "->" + string(e.what()));
		}
	}
	if(con) connections.push(con);	
}

void utils::DB_exec(string query, DB_bind_vector& binds, DB_callback cb) {
	MYSQL* con = 0;
	MYSQL_STMT* statement = 0;
	try {
		if(connections.empty()) DB_connect(con);
		else con = connections.pop();
		if(mysql_ping(con)) DB_connect(con);

		statement = DB_create_statement(con, query, binds.data());

		if(mysql_stmt_execute(statement))
			throw runtime_error(mysql_stmt_error(statement));
		if(cb) cb(statement);

		utils::DB_close_statement(con, statement);
	} catch(const runtime_error& error) {
		try {
			utils::DB_close_statement(con, statement);
		} catch(const runtime_error& e) {
			throw
				runtime_error(string(error.what()) + "->" + string(e.what()));
		}
	}
	if(con) connections.push(con);	
}