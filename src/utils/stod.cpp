#include <map>
#include <stdexcept>
#include "utils/stod.hpp"

using std::map;
using std::invalid_argument;
using std::string;

map<char, uint32_t> in_seconds = {
    {'y', 31556952},
    {'w', 604800},
    {'d', 86400},
    {'h', 3600},
    {'m', 60}
};

map<char, uint32_t> units_limits = {
    {'s', 4294967295},
    {'m', 71582788},
    {'h', 1193046},
    {'d', 49710},
    {'w', 7101},
    {'y', 136}
};

bool is_units(char& c) {
    c = std::tolower(static_cast<unsigned char>(c));
    if(
        c == 's' || c == 'm' || c == 'h' ||
        c == 'd' || c == 'w' || c == 'y'
    ) return true;
    else return false;
}

void compile_number(
    map<char, uint32_t>& number_parts, uint32_t& duration
) {
    duration += number_parts['y'] * in_seconds['y'];
    uint32_t prev = duration;
    duration += number_parts['w'] * in_seconds['w'];
    if(prev > duration) {
        duration = prev;
        return;
    }
    prev = duration;
    duration += number_parts['d'] * in_seconds['d'];
    if(prev > duration) {
        duration = prev;
        return;
    }
    prev = duration;
    duration += number_parts['h'] * in_seconds['h'];
    if(prev > duration) {
        duration = prev;
        return;
    }
    prev = duration;
    duration += number_parts['m'] * in_seconds['m'];
    if(prev > duration) {
        duration = prev;
        return;
    }
    prev = duration;
    duration += number_parts['s'];
    if(prev > duration) duration = prev;
}

void utils::stod(
    string line, uint32_t& duration
) {
    map<char, uint32_t> number_parts = {
        {'y', 0},
        {'w', 0},
        {'d', 0},
        {'h', 0},
        {'m', 0},
        {'s', 0}
    };

    char c;
    duration = 0;
    uint32_t t(0);
    bool next       = true;
    int line_length = line.length();
    
    for(int i = 0; i < line_length; i++) {
        c = line[i];

        if(std::isdigit(c)) {
            if(next) next = false;
            if(uint32_t(t * 10 / 10) == t) {
                t *= 10;
                t += c - '0';
            } else {
                duration = t;
                return;
            }
        } else if(is_units(c)) {
            if(next) throw invalid_argument("two modificators in a row");
            if(t >= units_limits[c]) {
                duration = units_limits['s'];
                return;
            } else {
                number_parts[c] = t;
                t = 0;
                next = true;
            }
        } else
            throw invalid_argument(string("wrong modificator '") + c + "'");
    }

    if(!next) throw invalid_argument("number without modificator");

    compile_number(number_parts, duration);
    if(duration < 10) {
        throw invalid_argument("duration is less than 10");
    }
}