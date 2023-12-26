#include "Connection_pool.hpp"
#include "shutdown.hpp"

void shutdown(dpp::cluster& bot) {
    bot.log(
        dpp::ll_info,
        "Pressed CTRL+C, stopping bot..."
    );
    bot.shutdown();
    while(connections.size()) {
        MYSQL* con = connections.pop();
        mysql_close(con);
    };
	mysql_library_end();
}