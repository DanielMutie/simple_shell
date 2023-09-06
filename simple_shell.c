#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 1024

int main() {
    char input[MAX_COMMAND_LENGTH];
    char *command;

    while (1) {
        // Display the shell prompt
        printf("($) ");

        // Read user input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Handle end-of-file (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove newline character
        input[strlen(input) - 1] = '\0';

        // Check for built-in exit command
        if (strcmp(input, "exit") == 0) {
            printf("Exiting the shell.\n");
            break;
        }

        // Execute the command using the system function
        int result = system(input);

        if (result == -1) {
            perror("Command execution error");
        }
    }

    return (0);
}

