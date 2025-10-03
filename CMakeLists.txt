cmake_minimum_required(VERSION 3.20.0)
project(linux-lab VERSION 0.1.0 LANGUAGES C CXX)

# Set C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add source subdirectory
add_subdirectory(src/ipc_anonymous_pipe)
add_subdirectory(src/ipc_named_pipe)
add_subdirectory(src/clock)
