cmake_minimum_required(VERSION 3.5)

project(L_Network LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

FILE(GLOB_RECURSE LibFiles "include/*.h")
add_custom_target(_L_Network_include SOURCES ${LibFiles})

file(GLOB_RECURSE Sources "source/*.cpp")
add_library(L_Network STATIC ${Sources} )

target_include_directories(L_Network PUBLIC
                            "${PROJECT_BINARY_DIR}" 
                            "${PROJECT_SOURCE_DIR}/include"
                            "${PROJECT_SOURCE_DIR}/../L_Utility/include"
)
