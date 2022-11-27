file(GLOB SRCS *.cpp)
target_sources(${CMAKE_PROJECT_NAME} PUBLIC ${SRCS})

file(GLOB SRCS *.c)
target_sources(${CMAKE_PROJECT_NAME} PUBLIC ${SRCS})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)