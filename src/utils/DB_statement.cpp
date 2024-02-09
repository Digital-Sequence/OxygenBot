#include "utils/DB_statement.hpp"
#include <stdexcept>
#include "Connection_pool.hpp"
#include "utils/DB_connect.hpp"

using std::runtime_error;
using std::string;
using utils::DB_connect;

utils::DB_statement::DB_statement() {
    connection = 0;
	statement = 0;
    prepare_meta_result = 0;
}

utils::DB_statement::DB_statement(const string q): query(q) {
    connection = 0;
	statement = 0;
    prepare_meta_result = 0;
}

void utils::DB_statement::set_query(const string q) {
	query = q;
	close();
}

void utils::DB_statement::create() {
	statement = mysql_stmt_init(connection);
	if(!statement) {
		runtime_error error("out of memory { mysql_stmt_init() }");
		throw error;
	}

	int result = mysql_stmt_prepare(statement, query.c_str(), query.length());
	
	if(result) {
		runtime_error error(mysql_stmt_error(statement));
		try { close(); } catch(const runtime_error& e) {
			throw runtime_error(
				string(error.what()) + "->" + string(e.what())
			);
		}
		throw error;
  	}

	if(!binds.empty()) {
		result = mysql_stmt_bind_param(statement, binds.data());
		if(result) {
			runtime_error error(mysql_stmt_error(statement));
			try {
				close();
			} catch(const runtime_error& e) {
				throw runtime_error(
					string(error.what()) + "->" + string(e.what())
				);
			}
			throw error;
		}
	}
}

void utils::DB_statement::close() {
	if(statement) {
		if(mysql_stmt_close(statement))
			throw runtime_error(mysql_error(connection));
		statement = 0;
	}
}

int utils::DB_statement::exec(DB_callback cb) {
	try {
        if(!connection)
            if(connections.empty()) DB_connect(connection);
            else connection = connections.pop();

		if(mysql_ping(connection)) {
			DB_connect(connection);
			close();
		}

		if(!binds.empty() && !binds.is_prepared()) {
			binds.prepare();
			close();
		}

		if(!statement) create();

		if(mysql_stmt_execute(statement))
			throw runtime_error(mysql_stmt_error(statement));
		if(cb) cb(statement);
		
		return mysql_stmt_affected_rows(statement);
	} catch(const runtime_error& error) {
		try { close(); } catch(const runtime_error& e) {
			throw runtime_error(
                string(error.what()) + "->" + string(e.what())
            );
		}
		throw error;
	}
}

void utils::DB_statement::add_bind() { binds.push(); };

void utils::DB_statement::add_bind(const string arg) { binds.push(arg); }

void utils::DB_statement::add_bind(const uint64_t arg) { binds.push(arg); }

void utils::DB_statement::set_bind_value(
	const size_t index, const string value
) { binds.set_bind_value(index, value); }

void utils::DB_statement::set_bind_value(
	const size_t index, const uint64_t value
) { binds.set_bind_value(index, value); }

void utils::DB_statement::add_buffer(string& arg) { buffers.push(arg); }

int utils::DB_statement::fetch() {
	if(!prepare_meta_result) {
		prepare_meta_result = mysql_stmt_result_metadata(statement);
		if(!prepare_meta_result)
			throw runtime_error(mysql_stmt_error(statement));
		if(!mysql_num_fields(prepare_meta_result)) return MYSQL_NO_DATA;
		if(mysql_stmt_bind_result(statement, buffers.data()))
			throw runtime_error(mysql_stmt_error(statement));
		if(mysql_stmt_store_result(statement))
			throw runtime_error(mysql_stmt_error(statement));
	}

    return mysql_stmt_fetch(statement);
}

void utils::DB_statement::free_result() {
	if(prepare_meta_result) {
		mysql_free_result(prepare_meta_result);
		prepare_meta_result = 0;
	}
}

void utils::DB_statement::clear_binds() { binds.clear(); }

void utils::DB_statement::clear_buffers() { buffers.clear(); }

void utils::DB_statement::clear() {
	query = "";
	if(!connection)
		if(connections.empty()) DB_connect(connection);
		else connection = connections.pop();
	if(mysql_ping(connection))
		DB_connect(connection);
	close();
}

void utils::DB_statement::clear_all() {
    clear();
	clear_binds();
	clear_buffers();
}


void utils::DB_statement::finish() {
	clear_all();
	if(connection) {
		connections.push(connection);
		connection = 0;
	}
}