#include <cctype>
#include <map>
#include <stdexcept>
#include <string>
#include "parse_cl_arguments.hpp"

using std::invalid_argument;
using std::map;
using std::string;

void parse_cl_arguments(
    int argc, map<string, bool>& cl_arguments_bool, map<string, string>& cl_arguments, char* argv[]
) {
    // Skip first argument (executable filename) or
    // return if no arguments provided
    if(argc > 1) argv++;
    else return;
    for(int i = 0; i < argc - 1; i++) {
        if(argv[i][0] != '-')
            throw invalid_argument("forgot '-' before argument");
        else argv[i]++;
        bool double_hyphen = false;
        if(argv[i][0] == '-') {
            double_hyphen = true;
            argv[i]++;
        }
        if(!argv[i][0])
            throw invalid_argument("provided '-' with no value");
        string argument;
        while(argv[i][0] && argv[i][0] != '=') {
            argument = argument +
                (char)std::tolower(static_cast<unsigned char>(argv[i][0]));
            argv[i]++;
        }
        try {
            if(double_hyphen) {
                cl_arguments_bool.at(argument);
                cl_arguments_bool[argument] = true;
            } else {
                for(int j = 0; j < argument.length(); j++) {
                    cl_arguments_bool.at(string(1, argument[j]));
                    cl_arguments_bool[string(1, argument[j])] = true;
                }
            }
            argument.clear();
        } catch(const std::out_of_range& ex) {};
        if(argument.empty()) continue;
        try {
            cl_arguments.at(argument);
            if(double_hyphen) {
                if(argv[i][0] != '=') throw invalid_argument(
                    string("argument '") + argument +
                    "' must be followed by '=' and value"
                );
                argv[i]++;
                if(!argv[i][0]) throw invalid_argument(
                    string("argument '") + argument +
                    "' must be followed by '=' and value"
                );
                cl_arguments[argument] = argv[i];
            } else {
                i++;
                if(!argv[i]) throw invalid_argument(
                    string("argument '") + argument +
                    "' must be followed by value"
                );
                cl_arguments[argument] = argv[i];
            }
            argument.clear();
        } catch(const std::out_of_range& ex) {};
        if(!argument.empty()) {
            string message = "argument '-";
            if(double_hyphen) message = message + '-';
            throw invalid_argument(
                message + argument + "' is invalid"
            );
        }
    }
}