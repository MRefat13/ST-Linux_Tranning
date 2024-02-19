#include <stdio.h>
#include <unistd.h>
#define MAX_SIZE (100)
int
main (int argc, char **argv)
{
  char buf[MAX_SIZE], *stateBuf;
  stateBuf = getcwd (buf, MAX_SIZE);
  if (stateBuf != NULL)
  {
    printf (">> %s\n", buf);
  }

}
