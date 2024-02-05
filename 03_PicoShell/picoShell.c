#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define PATH_MAX_SIZE (200)
#define TOKENS_NUMBER (100)
int  getTokenNumber(char* cmd)
{
	int iterator = 0;
	int cnt=0;
	//case user enter a spaces before the command
	while(cmd[iterator] == ' ' && cmd[iterator] != '\0' )
	{
		iterator++;
	}
	
	while( cmd[iterator] != '\0' )
	{
		if ( cmd[iterator] == ' ')
		{
			cnt++;
			iterator++;
       			 while(cmd[iterator] == ' ' && cmd[iterator] != '\0' )
       			 {
                		iterator++;
       			 }
		}
		iterator++;
	}
	return cnt;
}

void
parsing (char *pInput, char *arr_tokens[], int *pTokensNum);


int
main ()
{
  int iterator = 0, tokensNum = 0;
  char *cmd = NULL;
  size_t n = 0;
  while (1)
  {
    char path[PATH_MAX_SIZE];
    iterator = 0;
    printf ("O2mor ya gameel >> ");
    int size = getline(&cmd, &n, stdin);
    cmd[size - 1] = 0;
    int x = getTokenNumber(cmd);
    //printf("NUMBER OF TOKENS IS :%d\n",x);
    if (strlen(cmd) == 0)
    {
	continue;
    }
    //char **name = (char **) malloc(MAX * sizeof(char *));    
    char *arr_tokens[TOKENS_NUMBER];
    parsing (cmd, arr_tokens, &tokensNum);
    if (strcmp (arr_tokens[0], "pwd\0") == 0)
    {

      if (getcwd (path,PATH_MAX_SIZE) != NULL)
      {
	printf (">>%s\n", path);
      }
    }
    else if (strcmp (arr_tokens[0], "echo") == 0)
    {
      iterator = 1;
      while (arr_tokens[iterator] != NULL)
      {
	printf ("%s ", arr_tokens[iterator]);
	iterator++;
      }
      printf ("\n");
    }
    else if (strcmp (arr_tokens[0], "cd") == 0)
    {

      if (chdir (arr_tokens[1]) != 0)
      {
	printf (">>invalid path\n");
      }
    }
    else if (strcmp (arr_tokens[0], "exit") == 0)
    {
      printf (">>Goodbye\n");
      break;
    }
    else
    {
      pid_t returned_pid = fork ();
      if (returned_pid > 0)
      {
	// PARENT
	int wstatus;
	wait (&wstatus);
      }
      else if (returned_pid == 0)
      {
	// CHILD
	arr_tokens[tokensNum - 1] = NULL;
	execvp (arr_tokens[0], arr_tokens);
	printf ("Please Enter a valid Command\n");
      }
    }
  }

}
void
parsing (char *pInput, char *arr_tokens[], int *pTokensNum)
{
  int iterator = 0;
  arr_tokens[iterator] = strtok (pInput, " ");

  while (arr_tokens[iterator++] != NULL)
  {
    arr_tokens[iterator] = strtok (NULL, " ");
  }
  *pTokensNum = iterator;
  // insert a null-terminator(\0) at the end of the last toke
  /*iterator -= 2;
  int token_length = strlen (arr_tokens[iterator]);
  if (arr_tokens[iterator][token_length - 1] == '\n')
  {
    arr_tokens[iterator][token_length - 1] = '\0';
  }*/
}


