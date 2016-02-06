#include<stdio.h>
void function1(int arg);
void function2(int arg);

int main(int argc, char** argv)
{
  printf("Main function started\n"); int fArgs = 10;
  function1(fArgs);
  return 0;
}

void function1(int arg)
{
  printf("Function1 arg is %d\n", arg); arg = arg - 1;
  function2(arg);
  return;
}

void function2(int arg)
{
  printf("Function2 arg is %d\n", arg);
  arg = arg + 1;
  return;
}
