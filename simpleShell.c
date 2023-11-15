#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64

void execute_command(char *args[]) {
    pid_t pid, wait_pid;
    int status;

    pid = fork();

    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("shell");
    } else {
        // Parent process
        do {
            wait_pid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARG_SIZE];
    int i;

    while (1) {
        // Print shell prompt
        printf("shell> ");

        // Read input
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            perror("shell");
            exit(EXIT_FAILURE);
        }

        // Remove newline character
        input[strcspn(input, "\n")] = '\0';

        // Tokenize input
        char *token = strtok(input, " ");
        i = 0;
        while (token != NULL && i < MAX_ARG_SIZE - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Check for exit command
        if (strcmp(args[0], "exit") == 0) {
            exit(EXIT_SUCCESS);
        }

        // Execute command
        execute_command(args);
    }

    return 0;
}
