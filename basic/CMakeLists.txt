cmake_minimum_required(VERSION 3.1)

project(PROJECT_NAME_HERE_CHANGE_ME)
set (CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_LIBRARIES -lstdc++fs)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#Add files
set(SOURCES 
    src/Main.cpp
)

#Define the executable
add_executable(
    ${PROJECT_NAME} 
    ${SOURCES} 
)

find_package(Threads)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
