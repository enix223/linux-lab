add_executable(copy_sys_invoke copy_sys_invoke.cpp)

target_include_directories(copy_sys_invoke
                           PRIVATE 
                           ${CMAKE_SOURCE_DIR}/../exception
                           ${CMAKE_SOURCE_DIR}/../command)