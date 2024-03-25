/* Kevin Biju 22332903*/
#ifndef MYSHELL_H
#define MYSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>

// Function prototypes
void shell_loop(FILE *input_stream);
char *read_line(FILE *input_stream);
char **parse_args(char *line);
int execute_command(char **args);
int cd_command(char **args);
int clr_command();
int dir_command(char **args);
int environ_command();
int echo_command(char **args);
int help_command();
int pause_command();
int quit_command();
int execute_external_command(char **args, int background);

#endif
