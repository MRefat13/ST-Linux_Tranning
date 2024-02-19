# Shell Program Readme
#### This shell program reads the user's input in a loop, prompting the user with "O2mor ya gameel >>", and takes the input using getline. The program provides a basic shell-like environment where users can enter commands and execute them.

## Input Parsing
The program counts the number of tokens (arguments) in the input using the getTokenNumber function. If there are no tokens, it skips the current iteration of the loop.

The shell also supports escape characters, allowing you to include special characters within double quotes or single quotes without their usual interpretation. For example you can creat a file with name (file 1 ) 

Memory is allocated for the myargv array to store the parsed tokens. The input is then parsed into tokens using the parsing function. The program tokenizes the input based on spaces, as well as within double quotes and single quotes.

## Output Redirection
The program checks for output redirection using the > symbol. If the symbol is present, it opens the specified file for writing.

## Command Execution
The shell has built-in commands that can be executed directly:

* echo : Prints the arguments following the command.
* pwd: Prints the current working directory.
* cd: Changes the current directory to the specified path.
* exit: Terminates the shell program.


If the command entered by the user is not a built-in command, the program forks a child process to execute the command. The child process executes the command using execvp to search for the program in the directories specified in PATH. The parent process waits for the child process to complete using wait.

## Memory Management
After executing the command, the program closes the redirection file (if any) and frees the allocated memory for the command and arguments.

## Termination
The loop continues until the user enters the "exit" command, at which point the program prints "Goodbye" and terminates.

## To use this pico shell run these commands
### `gcc picoShell.c -o picoShell`
### `./picoShell`

## Example of the output:
file:///home/mohamedrefat/Pictures/Screenshots/Screenshot%20from%202024-02-19%2022-46-33.png![image](https://github.com/MohamedRefat13/ST-Linux_Tranning/assets/93578161/a7aa35bf-34c7-46ea-aa1e-14b4fae1bf6f)

