#include "parse_config.hpp"
#include <cctype>
#include <fstream>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include "globals.hpp"

using std::runtime_error;
using std::stoi;
using std::string;

void parse_config() {
    struct stat sb;
    if(stat(config_path.c_str(), &sb)) throw runtime_error(
        string("there's no \"") + config_path + "\" config file"
    );
    std::fstream config_file;
    config_file.open(config_path.c_str(), std::ios::in);
    if(config_file.is_open()) {
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
                    string("parameter \"") +
                    parameter + "\" has no value"
                );
            }
            bool is_numeric = false;
            if(
                config_parameters.find(parameter) == config_parameters.end() &&
                numerics_config_parameters.find(parameter) ==
                    numerics_config_parameters.end()
            ) throw runtime_error(
                string("parameter \"") + parameter + "\" isn't allowed"
            );
            if(
                numerics_config_parameters.find(parameter) !=
                numerics_config_parameters.end()
            ) is_numeric = true;
            if(++i == line.length()) throw runtime_error(
                string("parameter \"") + parameter + "\" has no value"
            );
            string value = line.substr(i);
            if(is_numeric) {
                numerics_config[parameter] = stoi(value);
                continue;
            }
            config[parameter] = value;
        }
        config_file.close(); //close the file object.
        // Validate values (will be moved to separate function)
        if(numerics_config["default_max_warns"] < 2)
            throw runtime_error(
                "default_max_warns parameter must be greater than 1"
            );
        if(
            allowed_warn_punishments.find(config["default_warn_punishment"]) ==
            allowed_warn_punishments.end()
        ) throw runtime_error(
            string("value ") + config["default_warn_punishment"] +
            " isn't allowed for default_warn_punishment"
        );
    } else throw runtime_error("cannot open config file");
}