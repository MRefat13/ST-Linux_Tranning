#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define RET_STATUS 0



//int main(int argc, char** argv)
int
main (int argc, char *argv[])
{

  int fd1, fd2, num_read, num_write;
  unsigned char buf[100];

  if (argc != 3)
  {
    printf ("Usage: %s file_name\n", argv[0]);
    return -1;
  }

  fd1 = open (argv[1], O_RDONLY);
  if (fd1 < 0)
  {
    printf (">> Could not open the file\n");
    return -1;
  }
  printf (">> the file opend with fd = %d\n", fd1);

  fd2 = open (argv[2], O_WRONLY | O_CREAT, 0644);
  if (fd2 < 0)
  {
    printf (">> Could not open the file2\n");
    return -1;
  }


  while ((num_read = read (fd1, buf, 100)) != 0)
  {
    if (num_read < 0)
    {
      printf (">> Could not read from the file2\n");
      return -1;
    }
    printf (">> I read %d bytes\n", num_read);

    num_write = write (fd2, buf, num_read);
    if (num_write < 0)
    {
      printf (">> Could not write to stdout\n");
      return -1;
    }
    printf ("\n>> I wrote %d bytes\n", num_write);
  }

  close (fd1);
  close (fd2);

  return RET_STATUS;
}
