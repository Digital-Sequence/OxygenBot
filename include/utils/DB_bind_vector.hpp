#pragma once
#include <cstdint>
#include <string>
#include <utility>
#include <vector>
#include <mysql/mysql.h>

namespace utils {

class DB_bind_vector {
	std::vector<MYSQL_BIND> binds;
	std::vector<uint64_t> uint64_vector;
	std::vector<std::pair<std::string, unsigned long int>> string_vector;
	bool prepared;
	public:
		MYSQL_BIND* data();
		void push();
		void push(const std::string);
		void push(const uint64_t);
		void set_bind_value(const size_t, const std::string);
		void set_bind_value(const size_t, const uint64_t);
		void prepare();
		bool is_prepared();
		void clear();
		bool empty() const;
};

}