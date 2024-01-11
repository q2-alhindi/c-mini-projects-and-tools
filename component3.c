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
    if (argc < 3) {
        printf("Not enough arguments entered! Use '-h' or '--help' for usage information.\n");
        return 1;
    }

    int interactive = 0; // Flag to indicate interactive mode

    // Check for the help option
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        }
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

    // Rest of the code remains the same

    return 0;
}
