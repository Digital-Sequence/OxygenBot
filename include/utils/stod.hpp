#pragma once
#include <string>

typedef unsigned int uint32_t;

namespace utils {

/*
        Convert string to duration in seconds
        Format of string is number
        with unit next to it. Example: 1m (1 minute)
        Units list:
                s - seconds
                m - minutes
                h - hours
                d - days
                w - weeks
                y - years
        It's allowed to use mutliple units in any order,
        separated by space. Example: 1y 3w (1 year, 3 weeks)
        When you specify too long duration (9000y, for example)
        the result will be maximum unsigned int value.
*/
void stod(std::string, uint32_t&);

}