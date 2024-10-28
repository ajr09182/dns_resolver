cmake_minimum_required(VERSION 3.10)
project(dns-resolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Poco REQUIRED Net)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

add_library(dns-resolver-lib
    src/DNSResolver.cpp
    src/DNSCache.cpp
    src/DNSQuery.cpp
    src/ConnectionPool.cpp
    src/Logger.cpp
)

add_executable(dns-resolver src/main.cpp)

target_include_directories(dns-resolver-lib
    PUBLIC include
    PRIVATE ${Poco_INCLUDE_DIRS}
)

target_link_libraries(dns-resolver-lib
    PRIVATE
    Poco::Net
    OpenSSL::SSL
    ${CMAKE_THREAD_LIBS_INIT}
)

target_link_libraries(dns-resolver
    PRIVATE dns-resolver-lib
)