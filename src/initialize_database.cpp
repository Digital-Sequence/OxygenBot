#include <string>
#include "Connection_pool.hpp"
#include "initialize_database.hpp"

using std::string;

void initialize_database() {
    // string entry = 
    //     "CREATE TABLE `BANS` (
    //         `rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
    //         `GUILD_ID` bigint(20) unsigned NOT NULL,
    //         `USER_ID` bigint(20) unsigned NOT NULL,
    //         `USERNAME` text DEFAULT NULL,
    //         `EXPIRES` bigint(20) unsigned DEFAULT NULL,
    //         PRIMARY KEY (`rowid`)
    //     ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci";
    

    // "CREATE TABLE `MESSAGES` (
    // `rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
    // `GUILD_ID` bigint(20) unsigned NOT NULL,
    // `CHANNEL_ID` bigint(20) unsigned NOT NULL,
    // `USER_ID` bigint(20) unsigned NOT NULL,
    // `MESSAGE_ID` bigint(20) unsigned NOT NULL,
    // PRIMARY KEY (`rowid`)
    // ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci"

    // "CREATE TABLE `MUTES` (
    // `rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
    // `GUILD_ID` bigint(20) unsigned NOT NULL,
    // `USER_ID` bigint(20) unsigned NOT NULL,
    // `EXPIRES` bigint(20) unsigned DEFAULT NULL,
    // PRIMARY KEY (`rowid`)
    // ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci"

    // "CREATE TABLE `WARNS` (
    // `rowid` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
    // `GUILD_ID` bigint(20) unsigned NOT NULL,
    // `USER_ID` bigint(20) unsigned NOT NULL,
    // `COUNT` int(10) unsigned NOT NULL,
    // `EXPIRES` bigint(20) unsigned DEFAULT NULL,
    // PRIMARY KEY (`rowid`)
    // ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci"
}