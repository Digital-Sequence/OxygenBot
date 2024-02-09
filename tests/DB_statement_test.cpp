#include <iostream>
#include <thread>
#include "Connection_pool.hpp"
#include "globals.hpp"
#include "utils/DB_statement.hpp"

using std::map;
using std::string;
using utils::DB_statement;

Connection_pool connections;
map<string, string> config;
string config_path;
map<string, int> numerics_config;

void f(utils::DB_statement statement) {
    statement.exec();
}

int main() {
    // Change credentials, or create user with specified below
    config = {
        { "DB_user", "tester" },
        { "DB_password", "no_pass" },
        { "DB_unix_socket", "/run/mysqld/mysqld.sock" }
    };

    //   Table:         tests.BLADE_RUNNER
    //   Primary Key:   rowid

    //   rowid              bigint(20)  unsigned NOT NULL AUTO_INCREMENT
    //   IS_REPLICANT       bit(1)      DEFAULT NULL
    //   SERIES             text        DEFAULT NULL
    //   MODEL              int(10)     unsigned DEFAULT NULL
    //   SERIAL             text        DEFAULT NULL
    //   NAME               text        NOT NULL
    //   GENDER             text        NOT NULL
    //   STATUS             text        NOT NULL

    std::cout << "(Re)create table tests.BLADE_RUNNER" << std::endl;
    DB_statement statement("DROP TABLE IF EXISTS tests.BLADE_RUNNER");
    statement.exec();
    statement.set_query(
        "CREATE TABLE tests.`BLADE_RUNNER` ("
        "`rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT, "
        "`IS_REPLICANT` bit(1) DEFAULT NULL, "
        "`SERIES` text DEFAULT NULL, "
        "`MODEL` int(10) unsigned DEFAULT NULL, "
        "`SERIAL` text DEFAULT NULL, "
        "`NAME` text NOT NULL, "
        "`GENDER` text NOT NULL, "
        "`STATUS` text NOT NULL, "
        "PRIMARY KEY (`rowid`)"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 "
        "COLLATE=utf8mb4_unicode_ci"
    );
    statement.exec();
    std::cout <<
        "INSERT INTO tests.BLADE_RUNNER "
        "VALUES(0, 1, Nexus, 7, N6MAA10816, 'Roy Batty', Male, Dead)"
    << std::endl;
    statement.set_query(
        "INSERT INTO tests.BLADE_RUNNER VALUES(0, 1, ?, ?, ?, ?, ?, ?)"
    );
    statement.add_bind("Nexus");
    statement.add_bind(7);
    statement.add_bind("N6MAA10816");
    statement.add_bind("Roy Batty");
    statement.add_bind("Male");
    statement.add_bind("Dead");
    statement.exec();
    std::cout <<
        "INSERT INTO tests.BANS "
        "VALUES(0, 1, 825407338755653642, 189759562910400512, brain, "
        "1706895096, NULL, NULL)"
    << std::endl;
    utils::DB_statement statement_BANS(
        "INSERT INTO tests.BANS VALUES(0, 1, ?, ?, ?, ?, NULL, NULL)"
    );
    statement_BANS.add_bind(0);
    statement_BANS.add_bind(1);
    statement_BANS.add_bind(825407338755653642);
    statement_BANS.add_bind(189759562910400512);
    statement_BANS.add_bind("brain");
    statement_BANS.add_bind(1706895096);
    statement_BANS.exec();
    statement_BANS.finish();
    
    std::cout << "SELECT * FROM tests.BLADE_RUNNER" << std::endl;
    statement.clear_binds();
    statement.set_query("SELECT * FROM tests.BLADE_RUNNER");
    uint64_t rowid(0);
    bool IS_REPLICANT(false);
    string SERIES(10, ' ');
    int MODEL(0);
    string SERIAL(16, ' ');
    string NAME(50, ' ');
    string GENDER(10, ' ');
    string STATUS(16, ' ');
    statement.add_buffer<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
    statement.add_buffer<bool>(IS_REPLICANT, MYSQL_TYPE_TINY);
    statement.add_buffer(SERIES);
    statement.add_buffer<int>(MODEL, MYSQL_TYPE_LONG);
    statement.add_buffer(SERIAL);
    statement.add_buffer(NAME);
    statement.add_buffer(GENDER);
    statement.add_buffer(STATUS);
    statement.exec();
    while(!statement.fetch() && rowid)
        std::cout <<
            rowid << "| " << IS_REPLICANT << ' ' <<
            SERIES << ' ' << MODEL << ' ' << SERIAL << ' '
            << NAME << ' ' << GENDER << ' ' << STATUS
        << std::endl;
    
    std::cout << "DELETE FROM tests.BLADE_RUNNER" << std::endl;
    statement.clear_buffers();
    statement.set_query("DELETE FROM tests.BLADE_RUNNER");
    statement.exec();

    std::cout << "Recreate table tests.BLADE_RUNNER" << std::endl;
    statement.set_query("DROP TABLE tests.BLADE_RUNNER");
    statement.exec();
    statement.set_query(
        "CREATE TABLE tests.`BLADE_RUNNER` ("
        "`rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT, "
        "`IS_REPLICANT` bit(1) DEFAULT NULL, "
        "`NAME` text NOT NULL, "
        "`JOB` text NOT NULL, "
        "`SERIES` text DEFAULT NULL, "
        "`MODEL` int(10) unsigned DEFAULT NULL, "
        "`SERIAL` text DEFAULT NULL, "
        "`GENDER` text NOT NULL, "
        "`STATUS` text NOT NULL, "
        "PRIMARY KEY (`rowid`)"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 "
        "COLLATE=utf8mb4_unicode_ci"
    );
    statement.exec();

    std::cout <<
        "INSERT INTO tests.BLADE_RUNNER "
        "VALUES(0, 1, Roy Batty, Military/Combat, Nexus, 7, N6MAA10816, "
        "Male, Dead)"
    << std::endl;
    statement.set_query(
        "INSERT INTO tests.BLADE_RUNNER VALUES(0, 1, ?, ?, ?, ?, ?, ?, ?)"
    );
    statement.add_bind("Roy Batty");
    statement.add_bind("Military/Combat");
    statement.add_bind("Nexus");
    statement.add_bind(7);
    statement.add_bind("N6MAA10816");
    statement.add_bind("Male");
    statement.add_bind("Dead");
    statement.exec();

    std::cout <<
        "INSERT INTO tests.BLADE_RUNNER "
        "VALUES(0, NULL, Harry Bryant, "
        "LAPD captain of Blade Runner unit (retired), NULL, NULL, NULL, "
        "Male, Alive)" << std::endl;
    statement.clear_binds();
    statement.set_query(
        "INSERT INTO tests.BLADE_RUNNER "
        "VALUES(0, NULL, ?, ?, NULL, NULL, NULL, ?, ?)"
    );
    statement.add_bind("Harry Bryant");
    statement.add_bind("LAPD captain of Blade Runner unit (retired)");
    statement.add_bind("Male");
    statement.add_bind("Alive");
    statement.exec();

    std::cout <<
        "INSERT INTO tests.BLADE_RUNNER "
        "VALUES(0, NULL, ?, ?, NULL, NULL, NULL, ?, ?)" << std::endl;
    statement.set_query(
        "INSERT INTO tests.BLADE_RUNNER "
        "VALUES(0, NULL, ?, ?, NULL, NULL, NULL, ?, ?)"
    );
    statement.set_bind_value(0, "Hannibal Chew");
    statement.set_bind_value(1, "Designer of replicant eyes at Tyrell");
    statement.set_bind_value(2, "Male");
    statement.set_bind_value(3, "Dead");
    statement.exec();

    std::cout <<
        "INSERT INTO tests.BLADE_RUNNER "
        "VALUES(0, NULL, Dave Holden, LAPD captain of Blade Runner unit, "
        "NULL, NULL, NULL, Male, Alive)" << std::endl;
    statement.set_query(
        "INSERT INTO tests.BLADE_RUNNER "
        "VALUES(0, NULL, ?, ?, NULL, NULL, NULL, ?, ?)"
    );
    statement.set_bind_value(0, "Dave Holden");
    statement.set_bind_value(1, "LAPD captain of Blade Runner unit");
    statement.set_bind_value(2, "Male");
    statement.set_bind_value(3, "Alive");
    statement.exec();

    std::cout <<
        "INSERT INTO tests.BLADE_RUNNER VALUES(0, 1, Leon Kowalski, "
        "Military/Cargo loader, Nexus, 6, N6MAC41717, Male, Dead)"
    << std::endl;
    statement.clear_binds();
    statement.set_query(
        "INSERT INTO tests.BLADE_RUNNER VALUES(0, 1, ?, ?, ?, ?, ?, ?, ?)"
    );
    statement.add_bind("Leon Kowalski");
    statement.add_bind("Military/Cargo loader");
    statement.add_bind("Nexus");
    statement.add_bind(6);
    statement.add_bind("N6MAC41717");
    statement.add_bind("Male");
    statement.add_bind("Dead");
    statement.exec();

    std::cout <<
        "INSERT INTO tests.BLADE_RUNNER "
        "VALUES(0, NULL, Taffey Lewis, Owner of The Snake Pit, "
        "NULL, NULL, NULL, Male, Alive)" << std::endl;
    statement.clear_binds();
    statement.set_query(
        "INSERT INTO tests.BLADE_RUNNER "
        "VALUES(0, NULL, ?, ?, NULL, NULL, NULL, ?, ?)"
    );
    statement.add_bind("Taffey Lewis");
    statement.add_bind("Owner of The Snake Pit");
    statement.add_bind("Male");
    statement.add_bind("Alive");
    statement.exec();

    std::cout <<
        "INSERT INTO tests.BLADE_RUNNER VALUES(0, 1, Pris Stratton, "
        "Military/Leisure, Nexus, 6, N6FAB21416, Female, Dead)"
    << std::endl;
    statement.clear_binds();
    statement.set_query(
        "INSERT INTO tests.BLADE_RUNNER VALUES(0, 1, ?, ?, ?, ?, ?, ?, ?)"
    );
    statement.add_bind("Pris Stratton");
    statement.add_bind("Military/Leisure");
    statement.add_bind("Nexus");
    statement.add_bind(6);
    statement.add_bind("N6FAB21416");
    statement.add_bind("Female");
    statement.add_bind("Dead");
    statement.exec();

    std::cout <<
        "INSERT INTO tests.BLADE_RUNNER "
        "VALUES(0, NULL, J. F. Sebastian, Genetic designer at Tyrell, "
        "NULL, NULL, NULL, Male, Dead)" << std::endl;
    statement.clear_binds();
    statement.set_query(
        "INSERT INTO tests.BLADE_RUNNER "
        "VALUES(0, NULL, ?, ?, NULL, NULL, NULL, ?, ?)"
    );
    statement.add_bind("J. F. Sebastian");
    statement.add_bind("Genetic designer at Tyrell");
    statement.add_bind("Male");
    statement.add_bind("Dead");
    statement.exec();

    std::cout <<
        "INSERT INTO tests.BLADE_RUNNER "
        "VALUES(0, NULL, ?, ?, NULL, NULL, NULL, ?, ?)" << std::endl;
    statement.set_query(
        "INSERT INTO tests.BLADE_RUNNER "
        "VALUES(0, NULL, ?, ?, NULL, NULL, NULL, ?, ?)"
    );
    statement.set_bind_value(0, "Eldon Tyrell");
    statement.set_bind_value(1, "CEO and founder of Tyrell Corporation");
    statement.set_bind_value(2, "Male");
    statement.set_bind_value(3, "Dead");
    statement.exec();

    std::cout <<
        "INSERT INTO tests.BLADE_RUNNER VALUES(0, 1, Zhora Salome, "
        "Exotic dancer at The Snake Pit, Nexus, 6, N6FAB61216, Female, Dead)"
    << std::endl;
    statement.clear_binds();
    statement.set_query(
        "INSERT INTO tests.BLADE_RUNNER VALUES(0, 1, ?, ?, ?, ?, ?, ?, ?)"
    );
    statement.add_bind("Zhora Salome");
    statement.add_bind("Exotic dancer at The Snake Pit");
    statement.add_bind("Nexus");
    statement.add_bind(6);
    statement.add_bind("N6FAB61216");
    statement.add_bind("Female");
    statement.add_bind("Dead");
    statement.exec();

    std::cout << "SELECT rowid, NAME FROM tests.BLADE_RUNNER" << std::endl;
    rowid = 0;
    statement.clear_binds();
    statement.set_query("SELECT rowid, NAME FROM tests.BLADE_RUNNER");
    statement.add_buffer<uint64_t>(rowid, MYSQL_TYPE_LONGLONG);
    statement.add_buffer(NAME);
    statement.exec();
    while(!statement.fetch() && rowid)
        std::cout << rowid << "| " << NAME << std::endl;
    statement.free_result();

    std::cout <<
        "SELECT rowid, NAME FROM tests.BLADE_RUNNER WHERE IS_REPLICANT = 1"
    << std::endl;
    std::cout << "--- Replicants ---" << std::endl;
    statement.set_query(
        "SELECT rowid, NAME FROM tests.BLADE_RUNNER WHERE IS_REPLICANT = 1"
    );
    statement.exec();
    while(!statement.fetch() && rowid)
        std::cout << rowid << "| " << NAME << std::endl;
    statement.free_result();

    statement.clear_all();
    statement.set_query(
        "CREATE TABLE IF NOT EXISTS tests.`BANS_UNIQUE` ("
            "`rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT, "
            "`GUILD_ID` bigint(20) unsigned NOT NULL, "
            "`USER_ID` bigint(20) unsigned NOT NULL, "
            "`USERNAME` text DEFAULT NULL, "
            "`DATE` bigint(20) unsigned NOT NULL, "
            "`EXPIRES` bigint(20) unsigned DEFAULT NULL, "
            "PRIMARY KEY (`rowid`,`GUILD_ID`,`USER_ID`)"
        ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci"
    );
    statement.exec();

    statement.set_query("DELETE FROM tests.BANS_UNIQUE");
    statement.exec();

    statement.set_query(
        "INSERT INTO tests.BANS_UNIQUE VALUES(4, 4, 'test', 98, NULL)"
    );
    statement.exec();
    try { statement.exec(); }
    catch(const std::runtime_error& error) {
        string error_message = error.what();
        error_message = error_message.substr(0, 15);
        if(error_message != "Duplicate entry") return 1;
    }

    std::cout << "Connection pool test" << std::endl;

    for(int i = 0; i < 100; i++) {
        // Used to check at Mysql-workbench (for example) amount of connections
        if(i == 50) std::cin.ignore();
        if(i == 70) std::cin.ignore();
        std::thread* t = new std::thread([]() {
            utils::DB_statement statement(
                "INSERT into tests.BANS "
                "VALUES(0, 1, 52, 84, 'Idea', 9, 1, NULL)"
            );
            statement.exec();
            statement.finish();
        });
        t->detach();
    }
    
    statement.finish();

    return 0;
}