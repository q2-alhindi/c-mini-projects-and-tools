#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

// Function called when the help flag is used
void print_help() {
    printf("Usage: cp <src> <dest>\n");
    printf("Copy the contents of the source file to the destination file.\n");
    printf("\nOptions:\n");
    printf("  -i   Prompt before overwriting the destination file. Usage: cp -i <src> <dest>\n");
    printf("  -n   Display line numbers in the output. Usage: cp -n <src> <dest>\n");
    printf("  -h, --help   Display this help message. Usage: cp -h or cp --help\n");
}

int main(int argc, char *argv[]) {
    // Check if the number of command-line arguments is less than 2
    if (argc < 2) {
        // Print an error message indicating insufficient arguments
        printf("Not enough arguments entered! Use '-h' or '--help' for usage information.\n");

        // Return a non-zero value to indicate an error condition
        return 1;
    }

    int interactive = 0; // Flag to indicate interactive mode
    int numbered_lines = 0; // Flag to indicate numbered lines

    // Check for the help option
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        print_help();
        return 0;
    }

    // Check for the interactive and numbered lines options
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            interactive = 1;
        } else if (strcmp(argv[i], "-n") == 0) {
            numbered_lines = 1;
        }
    }

    // Adjust the argv pointer based on options
    int arg_offset = interactive + numbered_lines;
    argv += arg_offset;
    argc -= arg_offset;

    // Check if there are enough arguments after adjusting for options
    if (argc < 2) {
        printf("Not enough arguments entered! Use '-h' or '--help' for usage information.\n");
        return 1;
    }

    // Attempt to open the source file specified in the first command-line argument for reading
    int src = open(argv[1], O_RDONLY);

    // Check if the file opening operation was unsuccessful (indicated by src == -1)
    if (src == -1) {
        printf("Source error! File doesn't exist\n");
        return 1;
    }

    // Attempt to open or create the destination file specified in the second command-line argument
    int dest = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0766);

    // Check if the file opening or creation operation for the destination file was unsuccessful
    if (dest == -1) {
        printf("File creation error! Do you have permissions?\n");
        close(src);
        return 1;
    }

    int size = 8192;
    char *buf = malloc(sizeof(char) * size);
    int amt = 0;
    int line_number = 1;

    if (interactive) {
        // Ask for confirmation before overwriting
        printf("Do you want to overwrite '%s'? (y/n): ", argv[2]);
        char response;
        scanf(" %c", &response);

        if (response != 'y') {
            printf("File not copied.\n");
            close(src);
            close(dest);
            free(buf);
            return 0;
        }
    }

    while ((amt = read(src, buf, size)) > 0) {
        // Display line numbers if the -n flag is specified
        if (numbered_lines) {
            char *line_start = buf;
            char *line_end = buf;

            while (line_end < buf + amt) {
                if (*line_end == '\n') {
                    printf("%d: ", line_number++);
                    write(dest, line_start, line_end - line_start + 1);
                    line_start = line_end + 1;
                }
                line_end++;
            }

            // Write the remaining part of the buffer
            write(dest, line_start, line_end - line_start);
        } else {
            // Write the entire buffer without line numbers
            write(dest, buf, amt);
        }
    }

    close(src);
    close(dest);
    free(buf);

    return 0;
}
