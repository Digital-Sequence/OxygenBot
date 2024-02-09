#include "utils/DB_buffer_vector.hpp"

using std::string;

MYSQL_BIND* utils::DB_buffer_vector::data() {
	return buffers.data();
}

void utils::DB_buffer_vector::push() {
	MYSQL_BIND buffer = {};
	buffer.buffer_type = MYSQL_TYPE_NULL;
	buffer.buffer = nullptr;
	buffer.length = nullptr;
	buffer.is_null = nullptr;
	buffers.push_back(buffer);
}

void utils::DB_buffer_vector::push(string& arg) {
	MYSQL_BIND buffer = {};
	buffer.buffer_type = MYSQL_TYPE_STRING;
	buffer.buffer = arg.data();
	buffer.buffer_length = arg.length() + 1;
	buffer.is_null = nullptr;
	buffers.push_back(buffer);
}

void utils::DB_buffer_vector::clear() {
	buffers.clear();
	buffers.shrink_to_fit();
}