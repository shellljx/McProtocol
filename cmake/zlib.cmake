find_package(ZLIB QUIET)
target_link_libraries(${PROJECT_NAME} ZLIB::ZLIB)