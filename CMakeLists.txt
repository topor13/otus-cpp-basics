cmake_minimum_required(VERSION 3.12)

project(07.containers_tests)

if (MSVC)
    # @see https://github.com/google/googletest/blob/master/googletest/README.md
    # Visual Studio Dynamic vs Static Runtimes
    #By default, new Visual Studio projects link the C runtimes dynamically
    #but GoogleTest links them statically. This will generate an error
    #Enabling this option will make gtest link the runtimes dynamically too
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
# Build googletest
add_subdirectory(
    #"${CMAKE_CURRENT_SOURCE_DIR}/googletest" 
    "googletest"
)

# Main target
add_executable(containers 
    src/containers.cpp
    src/include/list_container.hpp
    src/include/serial_container.hpp
)

# Test target
add_executable(
    containers_tests
    test/include/list_container_tests.hpp
    test/include/serial_container_tests.hpp
    test/containers_tests.cpp
)


# Add src to the include directories for the test target
target_include_directories(
    containers_tests PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Link test target against gtest libraries
target_link_libraries(
    containers_tests PRIVATE
    gtest
)


set_target_properties(containers PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)