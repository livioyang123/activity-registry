cmake_minimum_required(VERSION 3.30)
project(activity_registry)

set(CMAKE_CXX_STANDARD 20)

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
