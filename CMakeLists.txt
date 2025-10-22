cmake_minimum_required(VERSION 3.20.0)
project(linux-lab VERSION 0.1.0 LANGUAGES C CXX)

# Set C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set CXX standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source subdirectory
add_subdirectory(src/ipc_anonymous_pipe)
add_subdirectory(src/ipc_named_pipe)
add_subdirectory(src/clock)
add_subdirectory(src/cpp_thread)
add_subdirectory(src/fileio)
add_subdirectory(src/recursive_dir_read)
