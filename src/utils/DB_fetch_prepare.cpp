#include <stdexcept>
#include "utils/DB_fetch_prepare.hpp"

using std::runtime_error;

MYSQL_RES* utils::DB_fetch_prepare(MYSQL_STMT* statement, DB_bind_vector& binds) {
    MYSQL_RES* prepare_meta_result =
        mysql_stmt_result_metadata(statement);
    if(!prepare_meta_result)
        throw runtime_error(mysql_stmt_error(statement));

    /* Get total columns in the query */
    // int column_count = mysql_num_fields(prepare_meta_result);
    // if(!column_count) {
    //     mysql_free_result(prepare_meta_result);
    //     return 0;
    // }
    if(mysql_stmt_bind_result(statement, binds.data()))
        throw runtime_error(mysql_stmt_error(statement));
    return prepare_meta_result;
}