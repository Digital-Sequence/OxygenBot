cmake_minimum_required(VERSION 3.15)
project(OxygenBot VERSION 0.4.0 DESCRIPTION "All-in-one discord bot which is necessary for your server" LANGUAGES CXX)

find_library(LIBRARY_DPP dpp)
find_library(LIBRARY_FMT fmt)
find_library(LIBRARY_SPDLOG spdlog)
find_library(LIBRARY_MYSQL mariadb)
if (NOT LIBRARY_MYSQL)
    find_library(LIBRARY_MYSQL libmysqlclient)
endif()

if(NOT LIBRARY_DPP)
message( FATAL_ERROR "Install all required dependencies (no DPP library found)" )
endif()

if(NOT LIBRARY_FMT)
message( FATAL_ERROR "Install all required dependencies (no fmt library found)" )
endif()

if(NOT LIBRARY_SPDLOG)
message( FATAL_ERROR "Install all required dependencies (no spdlog library found)" )
endif()

if(NOT LIBRARY_MYSQL)
message( FATAL_ERROR "Install all required dependencies (no MySQL library found)" )
endif()

add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(parse_config_test tests/parse_config_test.cpp)
add_executable(DB_statement_test tests/DB_statement_test.cpp)
target_include_directories (${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include/)
target_include_directories(parse_config_test PRIVATE ${PROJECT_SOURCE_DIR}/include/)
target_include_directories(DB_statement_test PRIVATE ${PROJECT_SOURCE_DIR}/include/)

add_subdirectory(src/)
add_subdirectory(src/utils/)
add_subdirectory(src/commands/)
add_subdirectory(src/events/)

enable_testing()

add_test(
    NAME parse_config_test
    COMMAND $<TARGET_FILE:parse_config_test>
)

add_test(
    NAME DB_statement_test
    COMMAND $<TARGET_FILE:DB_statement_test>
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE ${LIBRARY_DPP}
    ${LIBRARY_FMT} ${LIBRARY_SPDLOG} ${LIBRARY_MYSQL}
)

target_link_libraries(
    DB_statement_test PRIVATE ${LIBRARY_MYSQL}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
