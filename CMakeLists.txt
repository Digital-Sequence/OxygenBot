cmake_minimum_required(VERSION 3.15)
project(OxygenBot VERSION 0.2.3 DESCRIPTION "All-in-one discord bot which is necessary for your server" LANGUAGES CXX)

find_library(LIBRARY_DPP dpp)
find_library(LIBRARY_FMT fmt)
find_library(LIBRARY_SPDLOG spdlog)
find_library(LIBRARY_MYSQL mariadb)
if (NOT LIBRARY_MYSQL)
    find_library(LIBRARY_MYSQL libmysqlclient)
endif()

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories (${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

add_subdirectory(src/)
add_subdirectory(src/utils/)
add_subdirectory(src/commands/)
add_subdirectory(src/events/)

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

target_link_libraries(
    ${PROJECT_NAME} PRIVATE ${LIBRARY_DPP}
    ${LIBRARY_FMT} ${LIBRARY_SPDLOG} ${LIBRARY_MYSQL}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
