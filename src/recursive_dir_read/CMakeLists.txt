add_executable(recursive_dir_read recursive_dir_read.cpp)

target_include_directories(recursive_dir_read
                           PRIVATE 
                           "${CMAKE_SOURCE_DIR}/src/logger"
                           "${CMAKE_SOURCE_DIR}/src/command"
                           "${CMAKE_SOURCE_DIR}/src/exception")
