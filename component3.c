#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>


int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Not enough arguments entered! The correct way: cp [-i] <src> <dest>\n");
        return 1;
    }

    int interactive = 0; // Flag to indicate interactive mode

    // Check for the interactive option
    if (argc == 4 && strcmp(argv[1], "-i") == 0) {
        interactive = 1;
        argv++; // Skip the -i option
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
