#include "common.h"
#include "stdio.h"
#include <sys/stat.h>

const char *FIFO_FILE_PATH = "/tmp/ipc_named_pipe_fifo";

ipc_pipe_err_t create_fifo()
{
  struct stat fstat;
  if (stat(FIFO_FILE_PATH, &fstat) == 0)
  {
    if (S_ISFIFO(fstat.st_mode))
    {
      return ERR_OK;
    }
    else
    {
      return ERR_NOT_A_FIFO;
    }
  }

  // create fifo
  if (mkfifo(FIFO_FILE_PATH, 0666) == 0)
  {
    return ERR_OK;
  }
  else
  {
    return ERR_CREATE_FAILED;
  }
}

void print_error(ipc_pipe_err_t err)
{
  switch (err)
  {
  case ERR_NOT_A_FIFO:
    printf("file is not a fifo\n");
    return;
  case ERR_CREATE_FAILED:
    printf("fifo file create failed\n");
    return;
  }
}
