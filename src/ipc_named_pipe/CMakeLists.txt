add_executable(ipc_named_pipe_sender sender.c common.c)
add_executable(ipc_named_pipe_receiver receiver.c common.c)

target_include_directories(ipc_named_pipe_sender PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ipc_named_pipe_receiver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})