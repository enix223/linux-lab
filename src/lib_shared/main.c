#include "algebra.h"
#include <stdio.h>

void usage(const char *exe)
{
  printf("%s <a> <b>\n", exe);
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    usage(argv[0]);
    return -1;
  }
  int a = atoi(argv[1]);
  int b = atoi(argv[2]);
  int c = lb_add(a, b);
  printf("%d + %d = %d\n", a, b, c);
  return 0;
}