#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void print_help() {
    printf("Usage: cp [-i] <src> <dest>\n");
    printf("Copy the contents of the source file to the destination file.\n");
    printf("\nOptions:\n");
    printf("  -i   Prompt before overwriting the destination file.\n");
    printf("  -h, --help   Display this help message.\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Not enough arguments entered! Use '-h' or '--help' for usage information.\n");
        return 1;
    }

    int interactive = 0; // Flag to indicate interactive mode

    
    // Check for the help option
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        print_help();
        return 0;
    }


    // Check for the interactive option
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            interactive = 1;
        }
    }

    // Adjust the argv pointer based on options
    int arg_offset = interactive;
    argv += arg_offset;
    argc -= arg_offset;

    // Check if there are enough arguments after adjusting for options
    if (argc < 2) {
        printf("Not enough arguments entered! Use '-h' or '--help' for usage information.\n");
        return 1;
    }

    int src = open(argv[1], O_RDONLY);
    if (src == -1) {
        printf("Source error! File doesn't exist\n");
        return 1;
    }

    int dest = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0766);
    if (dest == -1) {
        printf("File creation error! Do you have permissions?\n");
        close(src);
        return 1;
    }

    int size = 8192;
    char *buf = malloc(sizeof(char) * size);
    int amt = 0;

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
        write(dest, buf, amt);
    }

    close(src);
    close(dest);
    free(buf);

    return 0;
}
