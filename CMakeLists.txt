cmake_minimum_required(VERSION 3.10.0)
project(myapp VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)
FetchContent_Declare(
        opencv
        GIT_REPOSITORY https://github.com/opencv/opencv.git
        GIT_TAG 4.11.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        QUIET FALSE
)
# 关闭OpenCV测试和示例以避免编译错误
set(BUILD_JAVA OFF CACHE INTERNAL "" FORCE)
set(BUILD_opencv_java OFF CACHE INTERNAL "" FORCE)
set(BUILD_opencv_java_bindings_generator OFF CACHE INTERNAL "" FORCE)
set(BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
set(BUILD_PERF_TESTS OFF CACHE INTERNAL "" FORCE)
set(BUILD_opencv_apps OFF CACHE INTERNAL "" FORCE)
FetchContent_MakeAvailable(opencv)

add_executable(Experiment main.cpp)

# 使用相对路径设置 OpenCV 包含目录
set(__OpenCV_INCLUDE_DIRS 
    "${CMAKE_BINARY_DIR}"
    "${opencv_SOURCE_DIR}/include"
    "${opencv_SOURCE_DIR}/modules/core/include"
    "${opencv_SOURCE_DIR}/modules/flann/include"
    "${opencv_SOURCE_DIR}/modules/imgproc/include"
    "${opencv_SOURCE_DIR}/modules/ml/include"
    "${opencv_SOURCE_DIR}/modules/photo/include"
    "${opencv_SOURCE_DIR}/modules/dnn/include"
    "${opencv_SOURCE_DIR}/modules/features2d/include"
    "${opencv_SOURCE_DIR}/modules/imgcodecs/include"
    "${opencv_SOURCE_DIR}/modules/calib3d/include"
    "${opencv_SOURCE_DIR}/modules/gapi/include"
    "${opencv_SOURCE_DIR}/modules/highgui/include"
    "${opencv_SOURCE_DIR}/modules/videoio/include"
    "${opencv_SOURCE_DIR}/modules/video/include"
    "${opencv_SOURCE_DIR}/modules/objdetect/include"
    "${opencv_SOURCE_DIR}/modules/stitching/include"
)

set(OpenCV_INCLUDE_DIRS "")
foreach(d ${__OpenCV_INCLUDE_DIRS})
  get_filename_component(__d "${d}" REALPATH)
  if(NOT EXISTS "${__d}")
    if(NOT OpenCV_FIND_QUIETLY)
      message(WARNING "OpenCV: Include directory doesn't exist: '${d}'. OpenCV installation may be broken. Skip...")
    endif()
  else()
    list(APPEND OpenCV_INCLUDE_DIRS "${__d}")
  endif()
endforeach()



target_include_directories(${PROJECT_NAME} PRIVATE
        ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        opencv_core
        opencv_highgui
        opencv_imgcodecs
)