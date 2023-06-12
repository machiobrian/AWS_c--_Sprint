cmake_minimum_required(VERSION 3.1)
project(basic_connection CXX)

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
# set(PACKAGE_ROOT_DIR "/home/ix502iv/sdk-cpp-workspace/build/crt/aws-crt-cpp/crt")
find_package(aws-crt-cpp REQUIRED) # PATHS "/home/ix502iv/sdk-cpp-workspace/build/crt/aws-crt-cpp/crt")    
target_link_libraries(${PROJECT_NAME} AWS::aws-crt-cpp)