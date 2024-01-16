#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

// Define a structure named Overflow
typedef struct {
    char source[5];   // Source file name with a buffer size of 5
    char canary[8];   // Canary value with a buffer size of 8
} Overflow;

// Function to print help information
void print_help() {
    printf("Usage: cp <src> <dest>\n");
    printf("Copy the contents of the source file to the destination file.\n");
    printf("\nOptions:\n");
    printf("  -i   Prompt before overwriting the destination file. Usage: cp -i <src> <dest>\n");
    printf("  -h, --help   Display this help message. Usage: cp -h or cp --help\n");
}

// Main function
int main(int argc, char *argv[]) {
    // Check if there are enough command-line arguments
    if (argc < 2) {
        printf("Not enough arguments entered! Use '-h' or '--help' for usage information.\n");
        return 1;
    }

    // Declare and initialize an instance of the Overflow structure
    Overflow overflow;
    strcpy(overflow.canary, "CANARY");

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

    // Copy the source file name from the command line arguments to the Overflow structure
    strcpy(overflow.source, argv[1]);

    // Check for overflow by comparing the canary value
    if (strcmp(overflow.canary, "CANARY") != 0) {
        printf("Overflow detected\n");
        printf("Buffer %s", overflow.canary);
        return 0;
    }

    // Open the source file for reading
    int src = open(overflow.source, O_RDONLY);
    if (src == -1) {
        printf("Source error! File doesn't exist\n");
        return 1;
    }

    // Open or create the destination file for writing
    int dest = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0766);
    if (dest == -1) {
        printf("File creation error! Do you have permissions?\n");
        close(src);
        return 1;
    }

    int size = 8192;  // Set the buffer size
    char *buf = malloc(sizeof(char) * size);  // Allocate memory for the buffer
    int amt = 0;

    // Check for interactive mode and ask for confirmation before overwriting
    if (interactive) {
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

    // Read from the source file and write to the destination file until the end of the file is reached
    while ((amt = read(src, buf, size)) > 0) {
        write(dest, buf, amt);
    }

    // Close the source and destination files, and free the allocated memory
    close(src);
    close(dest);
    free(buf);

    return 0;
}
