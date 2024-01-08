#include <stdexcept>
#include <sys/stat.h>
#include "bot.hpp"
#include "Connection_pool.hpp"
#include "constants.hpp"

using std::invalid_argument;
using std::map;
using std::string;
using std::to_string;
using std::runtime_error;
using dpp::snowflake;

Connection_pool connections;
string config_path;
map<string, string> config;

int main(int argc, char* argv[]) {
    try {
        /* Parse command line arguments */
        map<string, bool> cl_arguments_bool = {
            {"r", false},
            {"register_commands", false},
        };
        map<string, string> cl_arguments = {
            {"c", ""},
            {"config", ""}
        };
        parse_cl_arguments(argc, cl_arguments_bool, cl_arguments, argv);
        
        if(cl_arguments["c"] != "")
            config_path = cl_arguments["c"];
        else if(cl_arguments["config"] != "")
            config_path = cl_arguments["config"];
        else {
            config_path =
            string("/home/") + string(getenv("USER")) + "/.config/oxygenBot";
            struct stat sb;
            if(stat(config_path.c_str(), &sb))
                mkdir(config_path.c_str(), 0755);
            config_path = config_path + "/config";
        };
        parse_config();
        if(config["token"] == "") config["token"] = secret();
        
        dpp::cluster bot(
            config["token"], dpp::i_default_intents | dpp::i_message_content
        );
        
        spdlog_setup(bot);

        bot.on_ready([&bot, &cl_arguments_bool](const dpp::ready_t& event) {
            register_events(bot);
            start_timer(bot);
            if(
                cl_arguments_bool["r"] ||
                cl_arguments_bool["register_commands"]
            ) {
                bot.log(
                    dpp::ll_info,
                    "Registering slashcommands..."
                );
                register_slashcommands(bot);
            };
            welcome_message();
        });

        bot.start(dpp::st_return);

        catch_exit_signal();

        shutdown(bot);
    } catch(const runtime_error& err) {
        std::cerr << err.what() << std::endl;
        return 1;
    } catch(const invalid_argument& err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }

    return 0;
}