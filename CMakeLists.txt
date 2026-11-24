cmake_minimum_required(VERSION 3.20)

project(psbbv_network VERSION 0.1.0 LANGUAGES CXX)

option(PSBBV_NETWORK_BUILD_TESTS "Build portable network contract tests" ON)

add_library(psbbv_network STATIC
    src/Status.cpp
)
target_include_directories(psbbv_network PUBLIC include)
target_compile_features(psbbv_network PUBLIC cxx_std_17)
target_compile_options(psbbv_network PRIVATE -Wall -Wextra -Wpedantic -Werror)

if(PSBBV_NETWORK_BUILD_TESTS)
    enable_testing()
    add_executable(psbbv_network_status_tests
        tests/NetworkStatusTests.cpp
    )
    target_link_libraries(psbbv_network_status_tests PRIVATE psbbv_network)
    target_compile_options(psbbv_network_status_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
    add_test(NAME network_status_contract COMMAND psbbv_network_status_tests)
endif()
