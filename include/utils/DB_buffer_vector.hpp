#pragma once
#include <string>
#include <vector>
#include <mysql/mysql.h>

namespace utils {

class DB_buffer_vector {
    std::vector<MYSQL_BIND> buffers;
    public:
        MYSQL_BIND* data();
        void push();
        void push(std::string&);
        template<typename T> void push(
            T& arg, enum enum_field_types buffer_type
        ) {
            MYSQL_BIND buffer = {};
            buffer.buffer_type = buffer_type;
            buffer.buffer = (char*)&arg;
            buffer.length = nullptr;
            buffer.is_null = nullptr;
            buffers.push_back(buffer);
        }
        void clear();
};

}