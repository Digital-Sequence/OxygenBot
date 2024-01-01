#include <time.h>
#include "utils/time_str.hpp"

using std::string;
using std::to_string;

string utils::time_str(const time_t& unix_timestamp) {
    tm* tm_time = gmtime(&unix_timestamp);
    string result = "";
    if(!(tm_time->tm_hour / 10))
    result = '0' + to_string(tm_time->tm_hour) + string(":");
    else result = to_string(tm_time->tm_hour) + ':';
    if(!(tm_time->tm_min / 10))
        result = result + '0' + to_string(tm_time->tm_min) + string(":");
    else result = result + to_string(tm_time->tm_min) + ':';
    if(!(tm_time->tm_sec / 10))
        result = result + '0' + to_string(tm_time->tm_sec);
    else result = result + to_string(tm_time->tm_sec);
    return result;
}