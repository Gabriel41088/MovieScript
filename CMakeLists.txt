cmake_minimum_required(VERSION 3.16)

project(MovieScript)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(MovieScript
    main.cpp
    lexer.cpp
    parser.cpp
    semantic.cpp
)

target_link_libraries(MovieScript
    Qt6::Widgets
)
