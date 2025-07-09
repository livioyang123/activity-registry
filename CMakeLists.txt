cmake_minimum_required(VERSION 3.30)
project(activity_registry)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.1/mingw_64/lib/cmake")
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

include_directories(include)

add_executable(activity_registry src/main.cpp
        include/core/Activity.h
        include/core/Observer.h
        include/gui/ActivityWindow.h
        include/core/Registry.h
        src/core/Activity.cpp
        src/core/Registry.cpp
        src/gui/ActivityWindow.cpp
        tests/test_main.cpp
        tests/core/test_Activity.cpp
        tests/core/test_Registry.cpp)

# Link Qt
target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Widgets)

# Tests
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    enable_testing()
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/heads/main.zip
    )
    # Per evitare installazione automatica
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)



    add_executable(run_tests
            tests/test_main.cpp
            tests/core/test_Activity.cpp
            src/core/Activity.cpp
    )

    target_link_libraries(run_tests gtest_main)
    add_test(NAME ${PROJECT_NAME}Tests COMMAND run_tests)
endif()