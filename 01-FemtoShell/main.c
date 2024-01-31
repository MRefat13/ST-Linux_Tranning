#include <stdio.h>
#include <string.h>
#define MAX_STR (50)
int main()
{
	char strCommand[MAX_STR];
	while(1)
	{
		printf("O2mor ya gameel > ");
		fgets(strCommand, MAX_STR ,stdin);
		if (strcmp(strCommand , "exit\n") != 0 )
		{
			printf("You said: %s\n",strCommand);
			continue;
		}
		printf("ana mashee:( \n");
		break;
	}
}
