# CMakeList.txt : CMake project for VmiWin32, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)




# Add source to this project's executable.
project(main)
add_executable (${CMAKE_PROJECT_NAME})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(driver)