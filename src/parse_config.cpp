#include <cctype>
#include <fstream>
#include <map>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include "parse_config.hpp"
#include "globals.hpp"

using std::map;
using std::runtime_error;
using std::string;

void parse_config() {
    struct stat sb;
    if(stat(config_path.c_str(), &sb)) throw runtime_error(
        string("there's no \"") + config_path + "\" config file"
    );
    std::fstream config_file;
    config_file.open(config_path.c_str(), std::ios::in);
    if (config_file.is_open()) {
        string line;
        while(getline(config_file, line)) {
            if(!line.length() || line[0] == '#') continue;
            int i(0);
            while(i < line.length() && isspace(line[i])) i++;
            if(i == line.length()) continue;
            i = 0;
            string parameter;
            while(line[i] != '=') {
                parameter = parameter + line[i];
                if(++i == line.length()) throw runtime_error(
                    string("parameter \"") + parameter + "\" value not specified"
                );
            }
            if(config_parameters.find(parameter) == config_parameters.end())
                throw runtime_error(
                    string("parameter \"") + parameter + "\" isn't allowed"
                );
            if(++i == line.length()) throw runtime_error(
                string("parameter \"") + parameter + "\" value not specified"
            );
            string value = line.substr(i);
            config[parameter] = value;
        }
        config_file.close(); //close the file object.
    } else throw runtime_error("cannot open config file");
}