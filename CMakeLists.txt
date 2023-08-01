cmake_minimum_required(VERSION 3.20)

project(network)

set(HEADERS_DIR "${PROJECT_SOURCE_DIR}/include")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(SOURCES
  ${SRC_DIR}/main.cpp
  ${SRC_DIR}/MyGraphic.cpp
  ${SRC_DIR}/Network.cpp
  ${SRC_DIR}/Picture.cpp
  ${SRC_DIR}/SmartPaint.cpp
)

find_package(SFML COMPONENTS window graphics system)

add_executable(network ${SOURCES})

target_include_directories(network
  PRIVATE
    ${PROJECT_BINARY_DIR}
    ${HEADERS_DIR})

set_target_properties(network
  PROPERTIES
    INSTALL_RPATH_USE_LINK_PATH TRUE)

target_link_libraries(network sfml-graphics)