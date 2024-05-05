cmake_minimum_required(VERSION 3.2)

set ( CMAKE_CXX_COMPILER "/usr/bin/g++" )
set ( CMAKE_C_COMPILER "/usr/bin/gcc" )

project(hello LANGUAGES CXX CUDA)
enable_language(CUDA)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CUDA_STANDARD 14)

find_package(CUDAToolkit REQUIRED)

add_executable(hello
  main.cu
  gpu_controller.h
  gpu_controller.cu
  i_balancer.h
  balancer.h
  balancer.cu
  i_connection.h
  qt_connection.h
  qt_connection.cpp
  i_connection_observer.h
  connection_observer.h
  connection_observer.cpp
  i_connection_controller.h
  connection_controller.h
  connection_controller.cpp
  i_server.h
  server.h
  server.cpp
  )

find_package(Qt6 REQUIRED COMPONENTS Network)
target_link_libraries(${PROJECT_NAME} CUDA::cudart Qt6::Network)

set_target_properties(${PROJECT_NAME} PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_features(${PROJECT_NAME} PUBLIC cuda_std_17)
