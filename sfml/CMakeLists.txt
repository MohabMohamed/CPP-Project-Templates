cmake_minimum_required(VERSION 3.1)

project(PROJECT_NAME_HERE_CHANGE_ME)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_LIBRARIES -lstdc++fs)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#Find the SFML package
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED audio network graphics window system)

#Add files
set(SOURCES 
    src/Main.cpp
    src/Input/Keyboard.cpp
)

#Define the executable
add_executable(
    ${PROJECT_NAME} 
    ${SOURCES} 
)

find_package(Threads)
target_link_libraries(${PROJECT_NAME} Threads::Threads ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${ADDITIONAL_LINK_FLAGS})
