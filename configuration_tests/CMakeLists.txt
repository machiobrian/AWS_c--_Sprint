cmake_minimum_required(VERSION 3.2)
project(configuration_tests)

set(CMAKE_CXX_STANDARD 11) #aws recommended 

add_executable(configuration_tests main.cpp)

target_include_directories(configuration_tests PRIVATE /home/ix502iv/sdk-workspace/include)
target_link_libraries(configuration_tests aws-iot-device-sdk-cpp-v2)