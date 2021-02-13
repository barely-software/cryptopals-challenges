cmake_minimum_required(VERSION 3.15)
project(BarelyCryptopals)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

# libbarelycrypto
file(GLOB PUBLIC_HEADERS ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB BARELYCRYPTO_SRC ${PROJECT_SOURCE_DIR}/src/barelycrypto/*.cpp)
add_library(barelycrypto ${BARELYCRYPTO_SRC})

install(TARGETS barelycrypto DESTINATION bin)
install(FILES ${PUBLIC_HEADERS} DESTINATION include)

add_executable(set1_challenge1 src/challenges/set1/challenge1.cpp)
target_link_libraries(set1_challenge1 barelycrypto)
