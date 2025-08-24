#pragma once

extern const char *FIFO_FILE_PATH;

typedef enum
{
  ERR_OK = 0,
  ERR_NOT_A_FIFO = -1,
  ERR_CREATE_FAILED = -2,
} ipc_pipe_err_t;

/**
 * Create fifo file
 *
 * @return error num
 */
ipc_pipe_err_t create_fifo();

void print_error(ipc_pipe_err_t err);