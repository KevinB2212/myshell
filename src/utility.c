#include "utility.h"

int handle_redirection(char **args, char *input_file, char *output_file) {
    int fd_in, fd_out;

    // Open input file if provided
    if (input_file != NULL) {
        fd_in = open(input_file, O_RDONLY);
        if (fd_in == -1) {
            perror("open");
            return 0; // Failed to open input file
        }
        dup2(fd_in, STDIN_FILENO); // Redirect stdin
        close(fd_in);
    }

    // Open output file if provided
    if (output_file != NULL) {
        fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1) {
            perror("open");
            return 0; // Failed to open output file
        }
        dup2(fd_out, STDOUT_FILENO); // Redirect stdout
        close(fd_out);
    }

    // Execute command with redirection
    return execute_command(args);
}
