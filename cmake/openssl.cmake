find_package(OpenSSL REQUIRED)

set(SSL_LIBS OpenSSL::Crypto OpenSSL::SSL)

include_directories("${OPENSSL_ROOT_DIR}/include")
target_link_libraries(${PROJECT_NAME} ${SSL_LIBS})
