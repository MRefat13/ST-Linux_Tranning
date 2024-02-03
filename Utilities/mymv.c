#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define RETURN (0)
#define BUF_MAX_SIZE (100)
int main(int argc, char **argv)
{
    int fd1, fd2, maxMul = 1;
    int numRead, numWrite;	// Number of bytes
    char buf[BUF_MAX_SIZE], flag = 0;

    if (argc == 3) {
	// open first file
	fd1 = open(argv[1], O_RDONLY);
	// open or creat(if not exist ) file2
	fd2 = open(argv[2], O_RDWR | O_CREAT, 0644);
	if (fd1 < 0) {
	    printf(">> Could not open the %s \n", argv[1]);
	}
	if (fd2 < 0) {
	    printf(">> Could not open or Creat the %s \n", argv[2]);
	}
	// Read the content of the first file.
	while ((numRead = read(fd1, buf, BUF_MAX_SIZE)) != 0) {
	    if (numRead < 0) {
		printf(">> Could not read from the file1\n");
		return -1;
	    }

	    if (flag != 0) {
		/* Set the ofssit to the last byte in file2 to continue
		 * the writing operation from the last byte
		 *
		 * note: this flage is to dont execute this operation at
		 *       the first of writing in the file 
		 */

		lseek(fd2, BUF_MAX_SIZE * maxMul, SEEK_SET);
		maxMul++;	//increment the Multiplication factor of the ofssit
	    }

	    printf(">> I read %d bytes\n", numRead);
	    numWrite = write(fd2, buf, numRead);
	    if (numWrite < 0) {
		printf(">> Could not write on the targeted file\n");
		return -1;
	    }

	    printf(">> I write %d bytes\n", numWrite);
	    flag = 1;
	}

	// remove file1
	remove(argv[1]);
    } else {
	printf(">>Parameter error \n");
    }
    close(fd2);
    return RETURN;
}
