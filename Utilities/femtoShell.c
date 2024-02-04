#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define MAX_SIZE (100)
#define COMMAND_SIZE (6)
int main()
{
	char buf[MAX_SIZE], path[MAX_SIZE], *stateBuf;
	char Command[COMMAND_SIZE];
	int iterator = 0;
	while(1)
	{
		iterator = 0;
		int i = 0;
		printf("O2mor ya gameel >> ");
		fgets(buf, MAX_SIZE ,stdin);
		// Clrear the command buffer
		for(i=0; i<COMMAND_SIZE; i++)
		{
			Command[i] = '\0';
		}

		i=0;
		
		// Clear the Path buffer 
                for(i=0; i<MAX_SIZE; i++)
                {
                        path[i] = '\0';
                }

                i=0;

		// deal with case is the user inter a spaces pefore the command
		while(buf[iterator] == ' '){
			iterator++;
		}
		//Starting of reading the command
		while( buf[iterator] != ' ' &&  buf[iterator] != '\n' )
		{
			Command[i] = buf[iterator];
			iterator++;
			i++;
		}

		i=0;
		if (strcmp(Command , "pwd") == 0 )
                {
			 stateBuf = getcwd(buf, MAX_SIZE);
 			 if (stateBuf != NULL)
 			 {
   				 printf (">>%s\n", buf);
			  }
                }
                else if (strcmp(Command , "echo") == 0 )
                {
			while(buf[iterator] != '\0')
			{
				printf("%c",buf[iterator]);
				iterator++;
			}
                }
                else if (strcmp(Command , "cd") == 0 )
                {
                        while(buf[iterator] != '\n')
                        {
                                path[i] = buf[iterator];
                                iterator++;
				i++;
                        }
			
			// adding Null at the end of the path
			path[i] = '\0';
			printf("\n\npath  is %s\n",path);

               		 if ( chdir(path) != 0)
               		 {
                        	printf(">>invalid path\n");
               		 }
		
		 	i=0;	 
                }
		else if (strcmp(Command , "exit") == 0 )
		{
			printf(">>Goodbye\n");
			break;
		}
		else 
		{
			printf(">>Enter a valid Command\n");
		}

	}

}
