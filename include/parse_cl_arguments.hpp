#pragma once
#include <map>
#include <string>

void parse_cl_arguments(
    int, std::map<std::string, bool>&,
    std::map<std::string, std::string>&, char**
);