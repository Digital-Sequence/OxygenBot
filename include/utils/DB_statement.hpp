#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <utility>
#include <vector>
#include <mysql/mysql.h>
#include "utils/DB_bind_vector.hpp"
#include "utils/DB_buffer_vector.hpp"

typedef std::function<void(MYSQL_STMT*)> DB_callback;

namespace utils {

class DB_statement {
    std::string query;
    MYSQL* connection;
    MYSQL_STMT* statement;
    utils::DB_bind_vector binds;
    utils::DB_buffer_vector buffers;
    MYSQL_RES* prepare_meta_result;
    void create();
    void close();
    public:
        DB_statement();
        DB_statement(const std::string);
        void set_query(const std::string);
        int exec(DB_callback = {});
        void add_bind();
        void add_bind(const std::string);
        void add_bind(const uint64_t);
        void set_bind_value(const size_t, const std::string);
        void set_bind_value(const size_t, const uint64_t);
        void add_buffer(std::string&);
        template<typename T> void add_buffer(
            T& arg, enum enum_field_types buffer_type
        ) { buffers.push<T>(arg, buffer_type); };
        int fetch();
        void free_result();
        void clear_binds();
        void clear_buffers();
        void clear();
        void clear_all();
        void finish();
};

}