cmake_minimum_required(VERSION 3.6)
project(compareResult)
# avoid "can not find -lopencv_dep_cudart"
set(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost COMPONENTS system filesystem regex REQUIRED)

find_package( OpenCV REQUIRED )
message("Open CV version is ${OpenCV_VERSION}")

include_directories(src)
FILE(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(compareResult ${SOURCE_FILES} )
target_link_libraries(compareResult ${OpenCV_LIBS} ${Boost_LIBRARIES})
