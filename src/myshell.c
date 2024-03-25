/* Kevin Biju : 22332903 */
#include <stdio.h>
#include <stdlib.h>
extern char **environ;
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64
#define DELIMS " \t\r\n\a"

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

int main(int argc, char **argv) {
    FILE *input_stream = stdin; // Default to stdin

    // Check if batch mode is enabled
    if (argc > 1) {
        input_stream = fopen(argv[1], "r");
        if (input_stream == NULL) {
            perror("Failed to open batch file");
            exit(EXIT_FAILURE);
        }
    }

    // Start shell loop
    shell_loop(input_stream);

    // Close batch file if opened
    if (input_stream != stdin)
        fclose(input_stream);

    return EXIT_SUCCESS;
}

void shell_loop(FILE *input_stream) {
    char *line;
    char **args;
    int status;
    do {
        printf("%s$ ", getenv("PWD"));
        line = read_line(input_stream);
        args = parse_args(line);
        status = execute_command(args);
        free(line);
        free(args);
    } while (status);
}

char *read_line(FILE *input_stream) {
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, input_stream);
    return line;
}

char **parse_args(char *line) {
    int bufsize = MAX_ARGS, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    token = strtok(line, DELIMS);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += MAX_ARGS;
            tokens = realloc(tokens, bufsize * sizeof(char*));
        }

        token = strtok(NULL, DELIMS);
    }
    tokens[position] = NULL;
    return tokens;
}

int execute_command(char **args) {
    if (args[0] == NULL)
        return 1;

    // Check for internal commands
    if (strcmp(args[0], "cd") == 0)
        return cd_command(args);
    else if (strcmp(args[0], "clr") == 0)
        return clr_command();
    else if (strcmp(args[0], "dir") == 0)
        return dir_command(args);
    else if (strcmp(args[0], "environ") == 0)
        return environ_command();
    else if (strcmp(args[0], "echo") == 0)
        return echo_command(args);
    else if (strcmp(args[0], "help") == 0)
        return help_command();
    else if (strcmp(args[0], "pause") == 0)
        return pause_command();
    else if (strcmp(args[0], "quit") == 0)
        return quit_command();
    else
        return execute_external_command(args, 0); // External command
}

int cd_command(char **args) {
    if (args[1] == NULL) {
        chdir(getenv("HOME"));
        setenv("PWD", getenv("HOME"), 1);
    } else {
        if (chdir(args[1]) != 0) {
            perror("cd");
        } else {
            setenv("PWD", args[1], 1);
        }
    }
    return 1;
}

int clr_command() {
    printf("\033[2J\033[H"); // ANSI escape sequence to clear screen
    return 1;
}

int dir_command(char **args) {
    // Implementation for dir command (ls -al <directory>)
    // You need to write this according to your requirements
    return 1;
}

int environ_command() {
    char **env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
    return 1;
}

int echo_command(char **args) {
    int i = 1;
    while (args[i] != NULL) {
        printf("%s ", args[i]);
        i++;
    }
    printf("\n");
    return 1;
}

int help_command() {
    FILE *help_file = fopen("help.txt", "r");
    if (help_file == NULL) {
        perror("help");
        return 1;
    }
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, help_file) != -1) {
        printf("%s", line);
    }
    fclose(help_file);
    if (line)
        free(line);
    return 1;
}

int pause_command() {
    printf("Press Enter to continue...");
    getchar(); // Wait for Enter key
    return 1;
}

int quit_command() {
    return 0;
}

int execute_external_command(char **args, int background) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) { // Child process
        // Set parent environment variable
        char *parent_env = malloc(MAX_CMD_LEN * sizeof(char));
        snprintf(parent_env, MAX_CMD_LEN, "parent=%s", getenv("PWD"));
        putenv(parent_env);

        if (execvp(args[0], args) == -1) {
            perror("execvp");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork");
    } else {
        if (!background) {
            do {
                wpid = waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        } else {
            printf("Background process started with PID %d\n", pid);
        }
    }
    return 1;
}
