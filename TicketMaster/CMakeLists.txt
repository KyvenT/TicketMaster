cmake_minimum_required(VERSION 3.20)
project(TicketMaster)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE})

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(TicketMaster src/main.cpp
        src/Ticket.cpp
        src/Ticket.h
        src/TicketManager.cpp
        src/TicketManager.h)

target_link_libraries(TicketMaster Qt5::Widgets)