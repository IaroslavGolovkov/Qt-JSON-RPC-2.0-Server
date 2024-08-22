cmake_minimum_required(VERSION 3.5)

project(Qt_JSON_RPC_2_0_Server
    VERSION 1.0.0
    DESCRIPTION "Qt JSON RPC 2.0 Server"
    LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Websockets REQUIRED)

file(GLOB SRCS
    ${CMAKE_SOURCE_DIR}/*.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${SRCS})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/jsonrpccxx
    ${CMAKE_SOURCE_DIR}/nlohmann
)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::WebSockets
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "JSON RPC 2.0 Server"
)
