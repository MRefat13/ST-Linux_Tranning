#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int
main (int argc, char **argv)
{
  int Num_read, Num_write;
  char buf[100];

  if (argc == 2)
  {

    int fd = open (argv[1], O_RDONLY);

    if (fd < 0)
    {
      printf (">>Can not  open file \n");
      return -1;
    }
    while (Num_read = read (fd, buf, 100))
    {
      if (Num_read < 0)
      {
	printf (">>Can not Read file \n");
	return -1;
      }
      Num_write = write (1, buf, Num_read);
      if (Num_write < 0)
      {
	printf (">>Can not write \n");
	return -1;
      }
      //printf (">>I write %d Byte \n", Num_write);

    }


  }
}
