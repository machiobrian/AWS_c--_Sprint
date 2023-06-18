cmake_minimum_required(VERSION 3.22.1)
project(shadowSync)

file(
    GLOB SRC_FILES 
    "*.cpp"
    "CommandLineUtils.cpp"
    "CommandLineUtils.h"    
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14)
# cxx-17 requires cmake 3.8, ccxx-20 cmake 3.12

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "shadowSync")
#set warnings
if (MSVC)
    target_link_options(${PROJECT_NAME} PRIVATE /W4 /WX /wd4068)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wno-long-long -pendatic -Werror)
endif ()

# Set CMAKE_PREFIX_PATH
set(CMAKE_PREFIX_PATH 
    "/home/ix502iv/sdk-workspace/lib/aws-crt-cpp/cmake/"
    "/home/ix502iv/sdk-workspace/lib/aws-c-http/cmake"
    "/home/ix502iv/sdk-workspace/lib/aws-c-io/cmake"
    "/home/ix502iv/sdk-workspace/lib/s2n/cmake"
    "/home/ix502iv/sdk-workspace/lib/aws-c-common/cmake"
    "/home/ix502iv/sdk-workspace/lib/aws-c-cal/cmake"
    "/home/ix502iv/sdk-workspace/lib/aws-c-compression/cmake"
    "/home/ix502iv/sdk-workspace/lib/aws-c-mqtt/cmake"
    "/home/ix502iv/sdk-workspace/lib/aws-c-auth/cmake"
    "/home/ix502iv/sdk-workspace/lib/aws-checksums/cmake"
    "/home/ix502iv/sdk-workspace/lib/aws-c-event-stream/cmake"
    "/home/ix502iv/sdk-workspace/lib/aws-c-s3/cmake"
    "/home/ix502iv/sdk-workspace/lib/aws-c-sdkutils/cmake"
    "/home/ix502iv/sdk-workspace/lib/IotShadow-cpp/cmake"
)

# List of required packages
set(required_packages
    aws-crt-cpp
    aws-c-http
    aws-c-io
    s2n
    aws-c-common
    aws-c-cal
    aws-c-compression
    aws-c-mqtt
    aws-c-auth
    aws-checksums
    aws-c-event-stream
    aws-c-s3
    aws-c-sdkutils
)


# Find and link against the packages
foreach(package ${required_packages})
    find_package(${package} REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE AWS::aws-crt-cpp AWS::IotShadow-cpp)
endforeach()


