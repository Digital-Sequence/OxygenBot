## Supported Systems

### Linux only. Tested on arch linux x86_64

## Dependencies

### Build requirements

* [cmake](https://cmake.org/) (version 3.15+)
* A supported C++ compiler from the list below

### Supported compilers

* [g++](https://gcc.gnu.org) (version 8 or higher)

### External Dependencies (You must install these)

* [DPP](https://dpp.dev)
* [fmt](https://fmt.dev)
* [spdlog](https://github.com/gabime/spdlog)
* [MySQL C API](https://dev.mysql.com/downloads/)

## Commands
* ban
* delete_messages
* delwarn
* member_info
* mute
* unban
* unmute
* warn

## How to compile
```
git clone https://github.com/Digital-Sequence/OxygenBot.git
cd OxygenBot
cmake -B build .
cd build
make
```

## How to setup
1. Configure MySQL (find how to do it in your OS)
2. Create user with administrative rights in MySQL (https://tableplus.com/blog/2018/10/how-to-create-a-superuser-in-mysql.html)
3. If you're using MySQL Workbench open file->run sql script, and choose mysql-schema/mysql-schema.sql
4. Create ~/.config/oxygenBot/config
Config example:
```
token=discord_bot_token_here
DB_user=something
DB_password=nothing
DB_unix_socket=/run/mysqld/mysqld.sock
```
Allowed config parameters:
token, DB_host, DB_user, DB_password, DB_port, DB_unix_socket

## How to use
Simply run ./OxygenBot -r (-r used to register commands, and isn't needed in further startups)
