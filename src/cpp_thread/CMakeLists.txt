add_executable(cpp_thread_join join.cpp)
add_executable(cpp_thread_detach detach.cpp)

target_compile_options(cpp_thread_detach PRIVATE "-g")

target_include_directories(cpp_thread_join PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../logger/)
target_include_directories(cpp_thread_detach PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../logger/)