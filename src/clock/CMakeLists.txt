add_executable(clock main.cpp clock.cpp)

target_include_directories(clock PRIVATE 
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_CURRENT_SOURCE_DIR}/../logger/)
