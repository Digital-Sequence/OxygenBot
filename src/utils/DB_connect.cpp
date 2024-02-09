#include <stdexcept>
#include "globals.hpp"
#include "utils/DB_connect.hpp"

void utils::DB_connect(MYSQL*& con) {
	if(!con) con = mysql_init(0);
	MYSQL* success = mysql_real_connect(
		con, config["DB_host"].c_str(), config["DB_user"].c_str(),
		config["DB_password"].c_str(), 0,
		numerics_config["DB_port"], config["DB_unix_socket"].c_str(), 0
	);
	if(!success) {
		std::runtime_error error(mysql_error(con));
		mysql_close(con);
		throw error;
	}
}