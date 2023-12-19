#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void create_backup(const char *filename) {
    // Create a backup filename by appending a tilde (~)
    char backup_filename[256];
    snprintf(backup_filename, sizeof(backup_filename), "%s~", filename);

    // Open the original file for reading
    int src = open(filename, O_RDONLY);
    if (src == -1) {
        printf("Source error! File doesn't exist\n");
        return;
    }

    // Open the backup file for writing
    int dest = open(backup_filename, O_CREAT | O_TRUNC | O_WRONLY, 0766);
    if (dest == -1) {
        printf("Backup creation error! Do you have permissions?\n");
        close(src);
        return;
    }

    // Copy the original file to the backup file
    int size = 8192;
    char *buf = malloc(sizeof(char) * size);
    int amt = 0;

    while ((amt = read(src, buf, size)) > 0) {
        write(dest, buf, amt);
    }

    close(src);
    close(dest);
    free(buf);
}


int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Not enough arguments entered! The correct way: cp [-i] [-b] <src> <dest>\n");
        return 1;
    }

    int interactive = 0; // Flag to indicate interactive mode
    int backup = 0;      // Flag to indicate backup mode

    // Check for the interactive and backup options
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            interactive = 1;
        } else if (strcmp(argv[i], "-b") == 0) {
            backup = 1;
        }
    }

    // Adjust the argv pointer based on options
    int arg_offset = interactive + backup;
    argv += arg_offset;
    argc -= arg_offset;

    // Check if there are enough arguments after adjusting for options
    if (argc < 3) {
        printf("Not enough arguments entered! The correct way: cp [-i] [-b] <src> <dest>\n");
        return 1;
    }

    if (backup) {
        // Create a backup of the destination file
        create_backup(argv[2]);
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
