#include "common.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
  ipc_pipe_err_t err;

  // create fifo if not exist
  if ((err = create_fifo()) < 0)
  {
    print_error(err);
    return -1;
  }

  int fd = open(FIFO_FILE_PATH, O_WRONLY);
  if (fd == -1)
  {
    printf("fifo file not found: %s\n", FIFO_FILE_PATH);
    return -1;
  }
  char *msg = "Hello world";
  write(fd, msg, strlen(msg) + 1);
  printf("[SENDER] send message: %s\n", msg);
  close(fd);
  return 0;
}