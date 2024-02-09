#include <iostream>
#include <stdexcept>
#include <sys/stat.h>
#include <vector>
#include "globals.hpp"
#include "parse_config.hpp"

using std::map;
using std::runtime_error;
using std::string;

string config_path;
map<string, string> config;
map<string, int> numerics_config;

int main() {
    config_path = "../testdata/config";
    try {
        parse_config();
        std::cout <<
            "config: " << '\n' <<
            config["token"] << '\n' <<
            config["DB_user"] << '\n' <<
            config["DB_password"] << '\n' <<
            numerics_config["DB_port"] << '\n' <<
            config["DB_unix_socket"] << '\n' <<
            numerics_config["default_max_warns"] << '\n' <<
            config["default_warn_punishment"] << std::endl;
        return 1;
    } catch(const std::runtime_error& error) {
        string error_what = error.what();
        if(
            error_what != "default_max_warns parameter must be greater than 1"
        ) {
            std::cout << error_what << '\n' << 
                "config: " << '\n' <<
                config["token"] << '\n' <<
                config["DB_user"] << '\n' <<
                config["DB_password"] << '\n' <<
                numerics_config["DB_port"] << '\n' <<
                config["DB_unix_socket"] << '\n' <<
                numerics_config["default_max_warns"] << '\n' <<
                config["default_warn_punishment"] << std::endl;
            return 1;
        }
    }

    config_path = "../testdata/config_1";
    parse_config();
    std::cout <<
        config["token"] << '\n' <<
        config["DB_user"] << '\n' <<
        config["DB_password"] << '\n' <<
        numerics_config["DB_port"] << '\n' <<
        config["DB_unix_socket"] << '\n' <<
        numerics_config["default_max_warns"] << '\n' <<
        config["default_warn_punishment"] << std::endl;
    if(
        config["token"] != "Deux Ex" ||
        config["DB_user"] != "jmanderley" ||
        config["DB_password"] != "knight_killer" ||
        numerics_config["DB_port"] != 6 ||
        config["DB_unix_socket"] != "/unatco/system/run/DB.sock" ||
        numerics_config["default_max_warns"] != 451 ||
        config["default_warn_punishment"] != "ban"
    ) {
        return 1;
    }
    
    config_path = "../testdata/config_2";
    try {
        parse_config();
        std::cout <<
            "config_2: " << '\n' <<
            config["token"] << '\n' <<
            config["DB_user"] << '\n' <<
            config["DB_password"] << '\n' <<
            numerics_config["DB_port"] << '\n' <<
            config["DB_unix_socket"] << '\n' <<
            numerics_config["default_max_warns"] << '\n' <<
            config["default_warn_punishment"] << std::endl;
        return 1;
    } catch(const std::runtime_error& error) {
        string error_what = error.what();
        if(error_what != "parameter \"token\" has no value") {
            std::cout << error_what << '\n' << 
                "config_2: " << '\n' <<
                config["token"] << '\n' <<
                config["DB_user"] << '\n' <<
                config["DB_password"] << '\n' <<
                numerics_config["DB_port"] << '\n' <<
                config["DB_unix_socket"] << '\n' <<
                numerics_config["default_max_warns"] << '\n' <<
                config["default_warn_punishment"] << std::endl;
            return 1;
        }
    }
    
    config_path = "../testdata/config_3";
    try {
        parse_config();
        std::cout <<
            "config_3: " << '\n' <<
            config["token"] << '\n' <<
            config["DB_user"] << '\n' <<
            config["DB_password"] << '\n' <<
            numerics_config["DB_port"] << '\n' <<
            config["DB_unix_socket"] << '\n' <<
            numerics_config["default_max_warns"] << '\n' <<
            config["default_warn_punishment"] << std::endl;
        return 1;
    } catch(const std::runtime_error& error) {
        string error_what = error.what();
        if(error_what != "parameter \"Deus Ex\" isn't allowed") {
            std::cout <<
                error_what << '\n' << 
                "config_3: " << '\n' <<
                config["token"] << '\n' <<
                config["DB_user"] << '\n' <<
                config["DB_password"] << '\n' <<
                numerics_config["DB_port"] << '\n' <<
                config["DB_unix_socket"] << '\n' <<
                numerics_config["default_max_warns"] << '\n' <<
                config["default_warn_punishment"] << std::endl;
            return 1;
        }
    }

    config_path = "../testdata/config_4";
    try {
        parse_config();
        std::cout <<
            "config_4: " << '\n' <<
            config["token"] << '\n' <<
            config["DB_user"] << '\n' <<
            config["DB_password"] << '\n' <<
            numerics_config["DB_port"] << '\n' <<
            config["DB_unix_socket"] << '\n' <<
            numerics_config["default_max_warns"] << '\n' <<
            config["default_warn_punishment"] << std::endl;
        return 1;
    } catch(const std::runtime_error& error) {
        string error_what = error.what();
        if(error_what != "parameter \"token \" isn't allowed") {
            std::cout <<
                error_what << '\n' << 
                "config_4: " << '\n' <<
                config["token"] << '\n' <<
                config["DB_user"] << '\n' <<
                config["DB_password"] << '\n' <<
                numerics_config["DB_port"] << '\n' <<
                config["DB_unix_socket"] << '\n' <<
                numerics_config["default_max_warns"] << '\n' <<
                config["default_warn_punishment"] << std::endl;
            return 1;
        }
    }

    config_path = "../testdata/config_5";
    try {
        parse_config();
        std::cout <<
            "config_5: " << '\n' <<
            config["token"] << '\n' <<
            config["DB_user"] << '\n' <<
            config["DB_password"] << '\n' <<
            numerics_config["DB_port"] << '\n' <<
            config["DB_unix_socket"] << '\n' <<
            numerics_config["default_max_warns"] << '\n' <<
            config["default_warn_punishment"] << std::endl;
        return 1;
    } catch(const std::runtime_error& error) {
        string error_what = error.what();
        if(error_what != "parameter \"DB_pasword\" isn't allowed") {
            std::cout <<
                error_what << '\n' << 
                "config_5: " << '\n' <<
                config["token"] << '\n' <<
                config["DB_user"] << '\n' <<
                config["DB_password"] << '\n' <<
                numerics_config["DB_port"] << '\n' <<
                config["DB_unix_socket"] << '\n' <<
                numerics_config["default_max_warns"] << '\n' <<
                config["default_warn_punishment"] << std::endl;
            return 1;
        }
    }

    config_path = "../testdata/config_6";
    try {
        parse_config();
        std::cout <<
            "config_6: " << '\n' <<
            config["token"] << '\n' <<
            config["DB_user"] << '\n' <<
            config["DB_password"] << '\n' <<
            numerics_config["DB_port"] << '\n' <<
            config["DB_unix_socket"] << '\n' <<
            numerics_config["default_max_warns"] << '\n' <<
            config["default_warn_punishment"] << std::endl;
        return 1;
    } catch(const std::runtime_error& error) {
        string error_what = error.what();
        if(error_what != "parameter \"\" isn't allowed") {
            std::cout <<
                error_what << '\n' << 
                "config_6: " << '\n' <<
                config["token"] << '\n' <<
                config["DB_user"] << '\n' <<
                config["DB_password"] << '\n' <<
                numerics_config["DB_port"] << '\n' <<
                config["DB_unix_socket"] << '\n' <<
                numerics_config["default_max_warns"] << '\n' <<
                config["default_warn_punishment"] << std::endl;
            return 1;
        }
    }

    config_path = "../testdata/config_7";
    try {
        parse_config();
        std::cout <<
            "config_7: " << '\n' <<
            config["token"] << '\n' <<
            config["DB_user"] << '\n' <<
            config["DB_password"] << '\n' <<
            numerics_config["DB_port"] << '\n' <<
            config["DB_unix_socket"] << '\n' <<
            numerics_config["default_max_warns"] << '\n' <<
            config["default_warn_punishment"] << std::endl;
        return 1;
    } catch(const std::out_of_range& error) {}

    config_path = "../testdata/config_8";
    try {
        parse_config();
        std::cout <<
            "config_8: " << '\n' <<
            config["token"] << '\n' <<
            config["DB_user"] << '\n' <<
            config["DB_password"] << '\n' <<
            numerics_config["DB_port"] << '\n' <<
            config["DB_unix_socket"] << '\n' <<
            numerics_config["default_max_warns"] << '\n' <<
            config["default_warn_punishment"] << std::endl;
        return 1;
    } catch(const std::runtime_error& error) {
        string error_what = error.what();
        if(error_what != "parameter \"default_max_warns\" has no value") {
            std::cout <<
                error_what << '\n' << 
                "config_8: " << '\n' <<
                config["token"] << '\n' <<
                config["DB_user"] << '\n' <<
                config["DB_password"] << '\n' <<
                numerics_config["DB_port"] << '\n' <<
                config["DB_unix_socket"] << '\n' <<
                numerics_config["default_max_warns"] << '\n' <<
                config["default_warn_punishment"] << std::endl;
            return 1;
        }
    }

    config_path = "../testdata/config_9";
    try {
        parse_config();
        std::cout <<
            "config_9: " << '\n' <<
            config["token"] << '\n' <<
            config["DB_user"] << '\n' <<
            config["DB_password"] << '\n' <<
            numerics_config["DB_port"] << '\n' <<
            config["DB_unix_socket"] << '\n' <<
            numerics_config["default_max_warns"] << '\n' <<
            config["default_warn_punishment"] << std::endl;
        return 1;
    } catch(const std::runtime_error& error) {
        string error_what = error.what();
        if(
            error_what !=
            "value kill isn't allowed for default_warn_punishment"
        ) {
            std::cout <<
                error_what << '\n' << 
                "config_9: " << '\n' <<
                config["token"] << '\n' <<
                config["DB_user"] << '\n' <<
                config["DB_password"] << '\n' <<
                numerics_config["DB_port"] << '\n' <<
                config["DB_unix_socket"] << '\n' <<
                numerics_config["default_max_warns"] << '\n' <<
                config["default_warn_punishment"] << std::endl;
            return 1;
        }
    }

    config_path = "../testdata/config_10";
    try {
        parse_config();
        std::cout <<
            "config_10: " << '\n' <<
            config["token"] << '\n' <<
            config["DB_user"] << '\n' <<
            config["DB_password"] << '\n' <<
            numerics_config["DB_port"] << '\n' <<
            config["DB_unix_socket"] << '\n' <<
            numerics_config["default_max_warns"] << '\n' <<
            config["default_warn_punishment"] << std::endl;
        return 1;
    } catch(const std::invalid_argument& error) {}

    config_path = "../testdata/config_11";
    parse_config();
    std::cout <<
        config["token"] << '\n' <<
        config["DB_user"] << '\n' <<
        config["DB_password"] << '\n' <<
        numerics_config["DB_port"] << '\n' <<
        config["DB_unix_socket"] << '\n' <<
        numerics_config["default_max_warns"] << '\n' <<
        config["default_warn_punishment"] << std::endl;
    if(
        config["token"] != "Deux Ex" ||
        config["DB_user"] != "jmanderley" ||
        config["DB_password"] != "knight_killer" ||
        numerics_config["DB_port"] != 6 ||
        config["DB_unix_socket"] != "/unatco/system/run/DB.sock" ||
        numerics_config["default_max_warns"] != 451 ||
        config["default_warn_punishment"] != "ban"
    ) {
        return 1;
    }

    config_path = "../testdata/config_12";
    parse_config();
    std::cout <<
        config["token"] << '\n' <<
        config["DB_user"] << '\n' <<
        config["DB_password"] << '\n' <<
        numerics_config["DB_port"] << '\n' <<
        config["DB_unix_socket"] << '\n' <<
        numerics_config["default_max_warns"] << '\n' <<
        config["default_warn_punishment"] << std::endl;
    if(
        config["token"] != "Deux Ex" ||
        config["DB_user"] != "jmanderley" ||
        config["DB_password"] != "knight_killer" ||
        numerics_config["DB_port"] != 6 ||
        config["DB_unix_socket"] != "/unatco/system/run/DB.sock" ||
        numerics_config["default_max_warns"] != 451 ||
        config["default_warn_punishment"] != "ban"
    ) {
        return 1;
    }

    return 0;
}