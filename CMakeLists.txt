cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cppServer VERSION 0.0.1 LANGUAGES C CXX)

file(GLOB SOURCES "src/*.cc" "src/*.cpp")

add_executable(test ${CMAKE_SOURCE_DIR}/test/main.cc ${SOURCES} ${CMAKE_SOURCE_DIR})
add_executable(runServer ${CMAKE_SOURCE_DIR}/test/runServer.cc ${SOURCES} ${CMAKE_SOURCE_DIR})
add_executable(runClient ${CMAKE_SOURCE_DIR}/test/runClient.cc ${SOURCES} ${CMAKE_SOURCE_DIR})

function(setup_target target_name)
  target_include_directories(${target_name} PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/util)
endfunction()

setup_target(test)
setup_target(runServer)
setup_target(runClient)


