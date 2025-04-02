#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT 1024

int execute_builtin(char **args) {
    if (strcmp(args[0], "exit") == 0) {
        printf("Goodbye!\n");
        exit(0);
    } else if (strcmp(args[0], "pwd") == 0) {
        char cwd[MAX_INPUT];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        } else {
            perror("pwd");
        }
        return 1;
    } else if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else if (chdir(args[1]) != 0) {
            perror("cd");
        }
        return 1;
    } else if (strcmp(args[0], "echo") == 0) {
        for (int i = 1; args[i] != NULL; i++) {
            printf("%s ", args[i]);
        }
        printf("\n");
        return 1;
    }
    return 0;
}


void execute_external(char **args) {
    pid_t pid = fork();
    if (pid == 0) { 
        if (execvp(args[0], args) == -1) {
            perror("execvp");
        }
        exit(EXIT_FAILURE);
    } else if (pid > 0) { 
        waitpid(pid, NULL, 0);
    } else {
        perror("fork");
    }
}


char **parse_input(char *input) {
    int bufsize = 64, index = 0;
    char **args = malloc(bufsize * sizeof(char *));
    char *token;

    if (!args) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, " \t\n");
    while (token != NULL) {
        args[index++] = token;

        if (index >= bufsize) {
            bufsize += 64;
            args = realloc(args, bufsize * sizeof(char *));
            if (!args) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\n");
    }
    args[index] = NULL;
    return args;
}

int main() {
    char *input = NULL;
    size_t len = 0;
    ssize_t read;

    while (1) {
        printf("PicoShell > ");
        read = getline(&input, &len, stdin);
        if (read == -1) {
            free(input);
            printf("\nGoodbye!\n");
            exit(0);
        }

        char **args = parse_input(input);
        if (args[0] != NULL) {
            if (!execute_builtin(args)) {
                execute_external(args);
            }
        }
        free(args);
    }

    free(input);
    return 0;
}
