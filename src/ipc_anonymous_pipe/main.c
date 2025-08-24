#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    // 0 - read; 1 - write
    int fd[2];
    pid_t pid;
    char buf[100];

    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        // child process
        printf("[child] send message\n");
        close(fd[0]);
        char *msg = "Hello world";
        write(fd[1], msg, strlen(msg) + 1);
        close(fd[1]);
    }
    else
    {
        // parent process
        close(fd[1]);
        read(fd[0], buf, sizeof(buf));
        printf("[parent] msg from child: %s\n", buf);
        close(fd[0]);
    }
    return 0;
}