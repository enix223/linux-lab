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

  int fd = open(FIFO_FILE_PATH, O_RDONLY);
  if (fd == -1)
  {
    printf("fifo file not found: %s\n", FIFO_FILE_PATH);
    return -1;
  }
  char buf[100];
  read(fd, buf, sizeof(buf));
  printf("[RECEIVER] received message: %s\n", buf);
  close(fd);
  return 0;
}