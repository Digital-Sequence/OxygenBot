#pragma once
#include <utils/DB_bind_vector.hpp>

namespace utils {

MYSQL_RES* DB_fetch_prepare(MYSQL_STMT*, DB_bind_vector&);

}