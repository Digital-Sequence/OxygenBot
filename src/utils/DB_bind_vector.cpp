#include "utils/DB_bind_vector.hpp"

using std::string;

MYSQL_BIND* utils::DB_bind_vector::data() {
	return binds.data();
}

void utils::DB_bind_vector::push() {
	prepared = false;
	MYSQL_BIND bind = {};
	bind.buffer_type = MYSQL_TYPE_NULL;
	bind.buffer = nullptr;
	bind.length = nullptr;
	bind.is_null = nullptr;
	binds.push_back(bind);
}

void utils::DB_bind_vector::push(const string arg) {
	prepared = false;
	string_vector.push_back({ arg, arg.length() });
	MYSQL_BIND bind = {};
	bind.buffer_type = MYSQL_TYPE_STRING;
	bind.is_null = nullptr;
	binds.push_back(bind);
}

void utils::DB_bind_vector::push(const uint64_t arg) {
	prepared = false;
	uint64_vector.push_back(arg);
	MYSQL_BIND bind = {};
	bind.buffer_type = MYSQL_TYPE_LONGLONG;
	bind.length = nullptr;
	bind.is_null = nullptr;
	binds.push_back(bind);
}

void utils::DB_bind_vector::set_bind_value(
	const size_t index, const std::string value
) {
	prepared = false;
	string_vector[index] = { value, value.length() };
}

void utils::DB_bind_vector::set_bind_value(
	const size_t index, const uint64_t value
) {
	prepared = false;
	uint64_vector[index] = value;
}

void utils::DB_bind_vector::prepare() {
	auto uint64_iterator = uint64_vector.begin();
	auto pair_iterator = string_vector.begin();
	for(auto& i : binds) {
		if(i.buffer_type == MYSQL_TYPE_LONGLONG) {
			i.buffer = (char*)&*uint64_iterator;
			uint64_iterator++;
		}
		if(i.buffer_type == MYSQL_TYPE_STRING) {
			if(pair_iterator->first != "")
				i.buffer = pair_iterator->first.data();
			i.length = &pair_iterator->second;
			pair_iterator++;
		}
	}
	prepared = true;
}

bool utils::DB_bind_vector::is_prepared() { return prepared; }

void utils::DB_bind_vector::clear() {
	binds.clear();
	binds.shrink_to_fit();
	string_vector.clear();
	string_vector.shrink_to_fit();
	uint64_vector.clear();
	uint64_vector.shrink_to_fit();
	prepared = false;
}

bool utils::DB_bind_vector::empty() const {
	return binds.empty();
}