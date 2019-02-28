# dunno, guess nobody uses older ones anymore?
cmake_minimum_required(VERSION 3.0)

project(shiny-spork)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

file(GLOB INCLUDE include/*.hpp)
file(GLOB SOURCE src/*.cpp)
add_executable(start ${SOURCE} ${INCLUDE})
target_include_directories(start PRIVATE include)
target_link_libraries(start sfml-graphics sfml-audio)
