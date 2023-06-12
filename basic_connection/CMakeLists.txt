cmake_minimum_required(VERSION 3.22.1)
project(basic_connection)

file(
    GLOB SRC_FILES 
    "*.cpp"
    "CommandLineUtils.cpp"
    "CommandLineUtils.h"    
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14)
# cxx-17 requires cmake 3.8, ccxx-20 cmake 3.12

#set warnings
if (MSVC)
    target_link_options(${PROJECT_NAME} PRIVATE /W4 /WX /wd4068)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wno-long-long -pendatic -Werror)
endif ()

set(CMAKE_PREFIX_PATH "/home/ix502iv/sdk-cpp-workspace/lib/aws-crt-cpp/cmake/;/home/ix502iv/sdk-cpp-workspace/lib/aws-c-http/cmake;/home/ix502iv/sdk-cpp-workspace/lib/aws-c-io/cmake;/home/ix502iv/sdk-cpp-workspace/lib/s2n/cmake;/home/ix502iv/sdk-cpp-workspace/lib/aws-c-common/cmake;/home/ix502iv/sdk-cpp-workspace/lib/aws-c-cal/cmake;/home/ix502iv/sdk-cpp-workspace/lib/aws-c-compression/cmake;/home/ix502iv/sdk-cpp-workspace/lib/aws-c-mqtt/cmake;/home/ix502iv/sdk-cpp-workspace/lib/aws-c-auth/cmake;/home/ix502iv/sdk-cpp-workspace/lib/aws-checksums/cmake;/home/ix502iv/sdk-cpp-workspace/lib/aws-c-event-stream/cmake;/home/ix502iv/sdk-cpp-workspace/lib/aws-c-s3/cmake;/home/ix502iv/sdk-cpp-workspace/lib/aws-c-sdkutils/cmake")

find_package(aws-crt-cpp REQUIRED)
find_package(aws-c-http REQUIRED)
find_package(aws-c-io REQUIRED)
find_package(s2n REQUIRED)
find_package(aws-c-common REQUIRED)
find_package(aws-c-compression REQUIRED)
find_package(aws-c-cal REQUIRED)
find_package(aws-c-mqtt REQUIRED)
find_package(aws-c-auth REQUIRED)

find_package(aws-checksums REQUIRED)
find_package(aws-c-sdkutils REQUIRED)
find_package(aws-c-event-stream REQUIRED)
find_package(aws-c-s3 REQUIRED)


target_link_libraries(${PROJECT_NAME} AWS::aws-crt-cpp AWS::aws-c-http AWS::aws-c-io AWS::s2n AWS::aws-c-common AWS::aws-c-cal AWS::aws-c-compression AWS::aws-c-mqtt AWS::aws-c-auth AWS::aws-c-s3 AWS::aws-c-sdkutils AWS::aws-c-event-stream AWS::aws-checksums)