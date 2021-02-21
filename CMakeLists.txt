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

add_executable(set1_challenge2 src/challenges/set1/challenge2.cpp)
target_link_libraries(set1_challenge2 barelycrypto)

add_executable(set1_challenge3 src/challenges/set1/challenge3.cpp)
target_link_libraries(set1_challenge3 barelycrypto)

add_executable(set1_challenge4 src/challenges/set1/challenge4.cpp)
target_link_libraries(set1_challenge4 barelycrypto)

add_executable(set1_challenge6 src/challenges/set1/challenge6.cpp)
target_link_libraries(set1_challenge6 barelycrypto)

add_executable(set1_challenge5 src/challenges/set1/challenge5.cpp)
target_link_libraries(set1_challenge5 barelycrypto)
