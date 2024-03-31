cmake_minimum_required(VERSION 3.5.0)
project(Lab04 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

find_package(OpenCV REQUIRED)
add_executable(Lab04 main.cpp)
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(Lab04 ${OpenCV_LIBS})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
