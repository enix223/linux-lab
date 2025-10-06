#include <stdio.h>

#include "add.h"
#include "division.h"
#include "multiply.h"
#include "substract.h"

int main(int argv, const char *argc[])
{
  int a = 24, b = 8;
  printf("%d + %d = %d\n", a, b, add(a, b));
  printf("%d - %d = %d\n", a, b, substract(a, b));
  printf("%d * %d = %d\n", a, b, multiply(a, b));
  printf("%d / %d = %d\n", a, b, divide(a, b));
  return 0;
}