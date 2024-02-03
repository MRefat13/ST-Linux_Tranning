#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc > 1) {
	int iterator = 1;
	do {
	    printf("%s ", argv[iterator]);
	    iterator++;

	}
	while (iterator < argc);
	//printf("\nNumber of argument is %d \n",argc);

    }
    printf("\n");

}
