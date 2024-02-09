file(GLOB src CONFIGURE_DEPENDS "*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${src})
target_sources(parse_config_test PRIVATE parse_config.cpp)