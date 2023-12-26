#pragma once
#include <vector>
#include <mysql/mysql.h>

namespace utils {

class DB_bind_vector {
	std::vector<MYSQL_BIND> binds;
	public:
		MYSQL_BIND* data();
		void push();
		void push(char[], enum enum_field_types, int);
		void push(char[], enum enum_field_types, long unsigned int*);
		template<typename T> void push(
			T& variable, enum enum_field_types buffer_type
		) {
			MYSQL_BIND bind = {};
			bind.buffer_type = buffer_type;
			bind.buffer = (char*)&variable;
			bind.length = nullptr;
			bind.is_null = nullptr;
			binds.push_back(bind);
		}
		void clear();
};

}