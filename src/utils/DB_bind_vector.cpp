#include "utils/DB_bind_vector.hpp"

MYSQL_BIND* utils::DB_bind_vector::data() {
    return binds.data();
}

void utils::DB_bind_vector::push() {
    MYSQL_BIND bind = {};
    bind.buffer_type = MYSQL_TYPE_NULL;
    bind.buffer = nullptr;
    bind.length = nullptr;
    bind.is_null = nullptr;
    binds.push_back(bind);
}
		
void utils::DB_bind_vector::push(
    char variable[], enum enum_field_types buffer_type,
    int buffer_length
) {
    MYSQL_BIND bind = {};
    bind.buffer_type = buffer_type;
    bind.buffer = variable;
    bind.buffer_length = buffer_length;
    bind.is_null = nullptr;
    binds.push_back(bind);
}

void utils::DB_bind_vector::push(
    char variable[], enum enum_field_types buffer_type,
    unsigned long int* length
) {
    MYSQL_BIND bind = {};
    bind.buffer_type = buffer_type;
    bind.buffer = variable;
    bind.length = length;
    bind.is_null = nullptr;
    binds.push_back(bind);
}

void utils::DB_bind_vector::clear() {
    binds.clear();
}