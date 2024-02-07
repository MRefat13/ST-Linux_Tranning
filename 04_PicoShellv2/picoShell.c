#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#define PATH_MAX (200)
void parsing(char *pInput, char *arr_tokens[]);
int getTokenNumber(char *cmd);
void freeAllocatedMem(int myargc,char **myargv);

int main()
{
    int iterator = 0, tokensNum = 0;
    char *cmd = NULL;
    size_t n = 0;
    while (1) {
	iterator = 0;

	/* Read the Input from the user */
	printf("O2mor ya gameel >> ");
	int size = getline(&cmd, &n, stdin);

	/* inset a '\0' at the eand of the input */
	cmd[size - 1] = 0;

	/* get Number of tokens[argument] --> argc */
	int tokensNum = getTokenNumber(cmd);	// number of takens
	if (tokensNum == 0) {
	    continue;
	}

	/* increment the tokensNum to add a null at the end of the tokens
	 *  for the exec function
	 * */
	tokensNum++;

	/* Allocate a memory for the array of the argument */
	char **arr_tokens;
	arr_tokens = (char **) malloc( (tokensNum) * sizeof(char *));

	/*parse the input line */
	parsing(cmd, arr_tokens);

	if (strcmp(arr_tokens[0], "pwd\0") == 0) {
	  




	    char path[PATH_MAX];
	    size_t size = PATH_MAX;
	    if (getcwd(path, size) != NULL) {
		printf(">>%s\n", path);
	    }

	} else if (strcmp(arr_tokens[0], "echo") == 0) {
	    iterator = 1;
	    while (arr_tokens[iterator] != NULL) {
		printf("%s ", arr_tokens[iterator]);
		iterator++;
	    }
	    printf("\n");
	} else if (strcmp(arr_tokens[0], "cd") == 0) {

	    if (chdir(arr_tokens[1]) != 0) {
		printf(">>invalid path\n");
	    }
	} else if (strcmp(arr_tokens[0], "exit") == 0) {
	    printf(">>Goodbye\n");
	    break;
	} else {
	    pid_t returned_pid = fork();
	    if (returned_pid > 0) {
		// PARENT
		int wstatus;
		//printf("PARENT: %d\n",getpid());
		wait(&wstatus);
	    } else if (returned_pid == 0) {
		// CHILD

		arr_tokens[tokensNum ] = NULL;
		execvp(arr_tokens[0], arr_tokens);
		printf("Please Enter a valid Command\n");
		return 0;
	    }
	}


	freeAllocatedMem(tokensNum,arr_tokens);
	free(cmd);
	cmd = NULL;
	n = 0;
    }

}

void parsing(char *pInput, char *arr_tokens[])
{
    int iterator = 0;
    char* token = strtok(pInput, " ");
    while( token != NULL )
    {
    	arr_tokens[iterator] = strdup(token);

    	iterator++;
    	token = strtok(NULL, " ");
    }
	
}


int getTokenNumber(char *cmd)
{
    int iterator1 = 0;
    int cnt = 0;
    char arg_flag = 0;
    while (cmd[iterator1] != '\0') {
	// Skip leading spaces before any token
	while (cmd[iterator1] == ' ' && cmd[iterator1] != '\0') {
	    iterator1++;
	}

	while (cmd[iterator1] != ' ' && cmd[iterator1] != '\0') {
	    iterator1++;
	    if (arg_flag == 0) {
		arg_flag = 1;
	    }
	}
	if (arg_flag == 1) {
	    arg_flag = 0;
	    cnt++;
	}
	iterator1++;

    }
    return cnt;
}

void freeAllocatedMem(int myargc,char **myargv)
{
	/* free the array of the input arguments --> argv */
        for (int i = 0; i < myargc; i++) {
            free(myargv[i]);
            (myargv)[i] = NULL;
        }
        /* free the array os the argument it self */
        free(myargv);
	myargv = NULL;
}
