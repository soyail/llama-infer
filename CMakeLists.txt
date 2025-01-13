cmake_minimum_required(VERSION 3.16)
project(llama_infer)

set(CMAKE_CXX_STANDARD 20)
find_package(glog REQUIRED)
find_package(CUDA REQUIRED)
set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}; -gencode arch=compute_89, code=sm_89)

aux_source_directory(llama-infer/source/base DIR_BASE)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
find_package(GTest REQUIRED)
add_library(llama SHARED ${DIR_BASE})
target_link_libraries(llama sentencepiece glog::glog gtest gtest_main pthread ${CUDA_LIBRARIES})
target_include_directories(llama PUBLIC ${glog_INCLUDE_DIR})
target_include_directories(llama PUBLIC ${PROJECT_SOURCE_DIR}/llama-infer/include)
target_include_directories(llama PUBLIC /usr/local/cuda/include)

add_subdirectory(test)