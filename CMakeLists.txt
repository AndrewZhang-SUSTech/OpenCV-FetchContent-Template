cmake_minimum_required(VERSION 3.16)
project(MyProject LANGUAGES CXX)

include(FetchContent)

# Configure OpenCV remotely
FetchContent_Declare(
    opencv
    URL         https://github.com/opencv/opencv/archive/refs/tags/4.11.0.tar.gz	#choose your version here
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    EXCLUDE_FROM_ALL 
)
set(BUILD_opencv_apps OFF CACHE BOOL "" FORCE)
set(BUILD_opencv_java OFF CACHE BOOL "" FORCE)
set(BUILD_opencv_python3 OFF CACHE BOOL "" FORCE)
set(BUILD_opencv_python2 OFF CACHE BOOL "" FORCE)
set(BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_PERF_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(opencv)

foreach(module calib3d core features2d dnn flann highgui imgcodecs imgproc ml objdetect photo stitching video videoio)
    list(APPEND OpenCV_INCLUDE_DIRS ${opencv_SOURCE_DIR}/modules/${module}/include)
    list(APPEND OpenCV_LIBS opencv_${module})
endforeach()

list(APPEND OpenCV_INCLUDE_DIRS 
    ${OpenCV_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}
)
# End configuration for OpenCV

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})