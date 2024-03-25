#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "myshell.h" // Include the header file containing execute_command prototype

// Utility function prototypes
int handle_redirection(char **args, char *input_file, char *output_file);

#endif
