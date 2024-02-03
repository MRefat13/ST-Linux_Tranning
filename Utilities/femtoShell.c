#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define MAX_SIZE (100)
#define COMMAND_SIZE (50)
int main()
{
	char buf[MAX_SIZE], path[MAX_SIZE], *stateBuf;
	char Command[COMMAND_SIZE];
	int iterator = 0;
	while(1)
	{
		iterator = 0;
		printf("O2mor ya gameel >> ");
		fgets(buf, MAX_SIZE ,stdin);
		while( buf[iterator] != ' ' )
		{
			Command[iterator] = buf[iterator];
			iterator++;
		}

		if (strcmp(Command , "pwd\n") == 0 )
                {
			 stateBuf = getcwd(buf, MAX_SIZE);
 			 if (stateBuf != NULL)
 			 {
   				 printf (">>%s\n", buf);
			  }
                }
                else if (strcmp(Command , "echo\n") == 0 )
                {
			while(buf[iterator] != '\0')
			{
				printf("%c",buf[iterator]);
				iterator++;
			}
                }
                else if (strcmp(Command , "cd\n") == 0 )
                {
			int i=0;
                        while(buf[iterator] != '\0')
                        {
                                path[i] = buf[iterator];
                                iterator++;
				i++;
                        }
               		 if ( chdir(path) != 0)
               		 {
                        	printf(">>invalid path\n");
               		 }
			
                }
		else if (strcmp(Command , "exit\n") == 0 )
		{
			printf(">>Goodbye\n");
			break;
		}
	}
}
