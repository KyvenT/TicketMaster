cmake_minimum_required(VERSION 3.20)
add_subdirectory(thirdParty)
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
        src/TicketManager.h
        src/User.cpp
        src/User.h
        src/UserManager.cpp
        src/UserManager.h
        src/UserWindow.cpp
        src/UserWindow.h
        src/DepartmentTicketsGUI.cpp
        src/DepartmentTicketsGUI.h
        src/TicketGUI.cpp
        src/TicketGUI.h
        src/Login.cpp
        src/Login.h
        src/AdminWindow.cpp
        src/AdminWindow.h
        src/MessageGUI.cpp
        src/MessageGUI.h
)

target_link_libraries(TicketMaster Qt5::Widgets)
target_link_libraries(TicketMaster jsoncpp_lib)
target_link_libraries(TicketMaster sodium)
target_include_directories(TicketMaster PRIVATE ${CMAKE_SOURCE_DIR}/thirdParty/jsoncpp/include)
target_include_directories(TicketMaster PRIVATE ${CMAKE_SOURCE_DIR}/thirdParty/libsodium/libsodium/src/libsodium/include)
