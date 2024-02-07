# Pico Shell
### This  Pico shell supports:
####      - Built-in echo, pwd and cd, in addition to exit. 
####      - Command line parsing to parse the command line entered by the user, divide it into arguments 
####      -If the user entered any thing other than (echo, pwd, cd, exit) the command will be executed by using fork/exec system calls.
####       - Support executing the programs using their names directly without the need to enter the full patch (check man exec).
#### -Support Dynamic memory allocation for the input

## To use this pico shell run these commands
### `gcc picoShell.c -o picoShell`
### `./picoShell`

## Example of the output:
<img width="717" alt="image" src="https://github.com/MohamedRefat13/ST-Linux_Tranning/assets/93578161/5e74c7b7-ec95-4ab2-aa77-ad88cb48353d">

