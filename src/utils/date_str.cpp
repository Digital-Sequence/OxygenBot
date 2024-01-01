#include <time.h>
#include "utils/date_str.hpp"

using std::string;
using std::to_string;

string utils::date_str(const time_t& unix_timestamp) {
    tm* tm_date = gmtime(&unix_timestamp);
    string result = "";
    if(!(tm_date->tm_mday / 10))
        result = '0' + to_string(tm_date->tm_mday) + string(".");
    else result = to_string(tm_date->tm_mday) + '.';
    if(!((1 + tm_date->tm_mon) / 10))
        result = result + '0' + to_string(1 + tm_date->tm_mon) + string(".");
    else result = result + to_string(1 + tm_date->tm_mon) + '.';
    result = result + to_string(1900 + tm_date->tm_year);
    return result;
}