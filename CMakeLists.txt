cmake_minimum_required(VERSION 3.2)
#find_package(CUDA QUIET REQUIRED)

#cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set ( CMAKE_CXX_COMPILER "/usr/bin/g++" )
set ( CMAKE_C_COMPILER "/usr/bin/gcc" )

project(hello LANGUAGES CXX CUDA)
enable_language(CUDA)
#add_executable(hello hello.cu)

#project(MY_PROJECT)

set(CMAKE_CUDA_STANDARD 14)
# set(CMAKE_CXX_STANDARD 17)

find_package(CUDAToolkit REQUIRED)

#enable_language(CUDA)

#add_executable(${PROJECT_NAME} main.cpp)

add_executable(hello
  main.cu
  randomize.cpp
  randomize.h
  i_gpu_controller.h
  gpu_controller.h
  gpu_controller.cu
  i_balancer.h
  balancer.h
  balancer.cu
  particle.h
  particle.cu
  v3.cu
  v3.h
  )

find_package(Qt6 REQUIRED COMPONENTS Network)
target_link_libraries(${PROJECT_NAME} CUDA::cudart Qt6::Network)

#target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Network)

set_target_properties(${PROJECT_NAME} PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

#target_link_libraries(${PROJECT_NAME} pthread z)

#@set_target_properties(${PROJECT_NAME} PROPERTIES CUDA_ARCHITECTURES "35;50;72")
#target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
#target_compile_features(${PROJECT_NAME} PUBLIC cuda_std_11)

# set (CMAKE_CUDA_COMPILER "/usr/bin/nvcc")

# set(USE_CUDA ON)
# set(CMAKE_CUDA_ARCHITECTURES 86)

# # Request that particles be built with -std=c++11
# # As this is a public compile feature anything that links to particles
# # will also build with -std=c++11
# target_compile_features(particles PUBLIC cxx_std_11)

# # We need to explicitly state that we need all CUDA files in the particle
# # library to be built with -dc as the member functions could be called by
# # other libraries and executables
# set_target_properties( particles
#                        PROPERTIES CUDA_SEPARABLE_COMPILATION ON
#                       )



