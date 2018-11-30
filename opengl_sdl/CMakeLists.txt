cmake_minimum_required(VERSION 3.1)

project(PROJECT_NAME)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#Include directory
include_directories(src/Dependencies/)

#Add files
set(SOURCES 
    src/Main.c
  #  src/ShaderLoader.c
    src/Glad/glad.c
   # src/Input/Keyboard.cpp
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#Define the executable
add_executable(
    ${PROJECT_NAME} 
    ${SOURCES} 
)

SET(ADDITIONAL_LINK_FLAGS)
if(UNIX)
    list(APPEND ADDITIONAL_LINK_FLAGS dl)
endif(UNIX)

find_package(Threads)
target_link_libraries(${PROJECT_NAME} Threads::Threads ${SDL2_LIBRARIES} ${ADDITIONAL_LINK_FLAGS})
