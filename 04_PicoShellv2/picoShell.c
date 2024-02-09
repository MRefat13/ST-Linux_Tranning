#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

/* Delimiter for tokenizing input on spaces */
#define SPACE_DELIMETER (" ") 

/* Delimiter for tokenizing input within double quotes */
#define DQOTES_DELIMETER ("\"")

/*  Maximum length of a file path */
#define PATH_MAX (200)     

/* Position of the output redirection symbol (>) */
int arrow_poss = 0;

/**
 * @brief Function is used to parse the input into tokens
 * 
 * @param pInput  string of the input line by the user 
 * @param myargv  array of tokens to store the tokens in it
 * @return int    number of tokens argc 
 * @note  the return from the function (argc) my be diff from the return from getTokenNumber
 *          because the parsing function doesn't count special characters [ " and > ] 
 */
int parsing(char *pInput, char *myargv[]);

/**
 * @brief Function to count the number of tokens in the input
 * 
 * @param cmd string of the input line by the user
 * @return int number of tokens(arguments) argc
 */
int getTokenNumber(char *cmd);

int main()
{
  int iterator = 0, myargc = 0;
  char *cmd = NULL;
  size_t n = 0;
  while (1)
  {
    iterator = 0;

    /* Read the Input from the user */
    printf("O2mor ya gameel >> ");
    int size = getline(&cmd, &n, stdin);

    /* inset a '\0' at the and of the input */
    cmd[size - 1] = 0;

    /* get Number of tokens[argument] --> argc */
    int myargc = getTokenNumber(cmd); // number of tokens
    if (myargc == 0)
    {
      continue;
    }

    /* increment  myargc to add a null at the end of the tokens
     *  for the exec function
     * */
    myargc++;

    /* Allocate a memory for the array of the argument */
    char **myargv;
    myargv = (char **)malloc((myargc) * sizeof(char *));

    /*parse the input line */
    int myargc_new = parsing(cmd, myargv);

    /*Check for the O/P redirection > */
    int fd;
    char RedirFile_Flag = 0;
    int Output_Fd = 1; // STDOUT

    /*Handel O/P Redirection */
    if (arrow_poss != 0)
    {

      fd = open(myargv[arrow_poss],
                O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if (fd > 0)
      {
        RedirFile_Flag = 1;
      }
      else
      {
        printf("Can not open of creat the redirection file\n");
      }
      arrow_poss = 0;
    }
    if (RedirFile_Flag == 1)
    {
      Output_Fd = fd;
    }

    if (strcmp(myargv[0], "pwd\0") == 0)
    {
      char path[PATH_MAX];
      size_t size = PATH_MAX;
      if (getcwd(path, size) != NULL)
      {
        dprintf(Output_Fd, ">>%s\n", path);
      }
    }
    else if (strcmp(myargv[0], "echo") == 0)
    {
      iterator = 1;
      for (iterator = 1; iterator < myargc_new - 1; iterator++)
      {
        dprintf(Output_Fd, "%s ", myargv[iterator]);
      }
      dprintf(Output_Fd, "\n");
    }
    else if (strcmp(myargv[0], "cd") == 0)
    {

      if (chdir(myargv[1]) != 0)
      {
        dprintf(1, ">>invalid path\n");
      }
    }
    else if (strcmp(myargv[0], "exit") == 0)
    {
      dprintf(1, ">>Goodbye\n");
      break;
    }
    else
    {
      pid_t returned_pid = fork();
      if (returned_pid > 0)
      {
        // PARENT
        int wstatus;
        wait(&wstatus);
      }
      else if (returned_pid == 0)
      {
        // CHILD
        myargv[myargc_new] = NULL;
        if (RedirFile_Flag == 1)
        {
          int fd2 = dup2(fd, 1);
          if (fd2 < 0)
          {
            dprintf(1, "Failed to redirect the output\n");
          }
          else
          {

            char *new_envp[] = {NULL};
            execvp(myargv[0], new_envp);
            dprintf(1, "Please Enter a valid Command\n");
          }
        }
        else
        {

          execvp(myargv[0], myargv);
          dprintf(1, "Please Enter a valid Command\n");
        }

        return 0;
      }
    }

    if (RedirFile_Flag == 1)
    {
      close(fd);
    }

    /* free the array of the input arguments --> argv */
    for (iterator = 0; iterator < myargc; iterator++)
    {

      free(myargv[iterator]);
      myargv[iterator] = NULL;
    }

    /* free the array of  the argument it self */
    free(myargv);
    myargv = NULL;

    /* Free the CMD */
    free(cmd);
    cmd = NULL;
    n = 0;
  }
}

int parsing(char *pInput, char *myargv[])
{
  int iterator = 0;
  char *pTemp = 0;
  char delimeter[] = SPACE_DELIMETER;
  char openFlag = 0;
  char *token = strtok(pInput, " ");
  while (token != NULL)
  {
    /* if the token is a [ " or > ] do not store it in myargv */
    if ((strcmp(token, "\"") != 0) &&
        (strcmp(token, ">") != 0))
    {
      myargv[iterator] = strdup(token);
      iterator++;
    }
    if ((strcmp(token, ">") == 0))
    {
      arrow_poss = iterator;
    }

    if (openFlag == 1 || (strcmp(token, "\"") == 0))
    {

      if (openFlag == 0)
      {
        openFlag = 1;
        strcpy(delimeter, DQOTES_DELIMETER);
      }
      else if (openFlag == 1)
      {
        openFlag = 0;
        strcpy(delimeter, SPACE_DELIMETER);
      }
    }
    token = strtok(NULL, delimeter);
  }
  // return number of argument
  return iterator;
}

int getTokenNumber(char *cmd)
{
  int iterator1 = 0;
  int cnt = 0;
  char arg_flag = 0;
  while (cmd[iterator1] != '\0')
  {
    // Skip leading spaces before any token
    while (cmd[iterator1] == ' ' && cmd[iterator1] != '\0')
    {
      iterator1++;
    }

    // Skip the token and increment cnt by one
    while (cmd[iterator1] != ' ' && cmd[iterator1] != '\0')
    {
      iterator1++;
      if (arg_flag == 0)
      {
        arg_flag = 1;
      }
    }
    if (arg_flag == 1)
    {
      arg_flag = 0;
      cnt++;
    }
    iterator1++;
  }
  // return number of arguments
  return cnt;
}
