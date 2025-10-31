add_executable(copy_sys_invoke copy_sys_invoke.cpp)
add_executable(copy_with_stdlib copy_with_stdlib.cpp)
add_executable(file_link file_link.cpp)
add_executable(dup_file dup_file.cpp)

target_include_directories(copy_sys_invoke
                           PRIVATE 
                           "${CMAKE_SOURCE_DIR}/src/logger"
                           "${CMAKE_SOURCE_DIR}/src/command"
                           "${CMAKE_SOURCE_DIR}/src/exception")

target_include_directories(copy_with_stdlib
                           PRIVATE 
                           "${CMAKE_SOURCE_DIR}/src/logger"
                           "${CMAKE_SOURCE_DIR}/src/command"
                           "${CMAKE_SOURCE_DIR}/src/exception")

target_include_directories(file_link
                           PRIVATE 
                           "${CMAKE_SOURCE_DIR}/src/logger"
                           "${CMAKE_SOURCE_DIR}/src/command"
                           "${CMAKE_SOURCE_DIR}/src/exception")

target_include_directories(dup_file
                           PRIVATE 
                           "${CMAKE_SOURCE_DIR}/src/logger"
                           "${CMAKE_SOURCE_DIR}/src/command"
                           "${CMAKE_SOURCE_DIR}/src/exception")