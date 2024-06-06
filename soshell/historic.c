// historic.c

#include "shell.h"

#define HISTORY_FILE "history.txt"

void add_to_history(const char *command) {
    FILE *file = fopen(HISTORY_FILE, "a");
    if (file == NULL) {
        perror("Failed to open history file");
        return;
    }
    fprintf(file, "%s\n", command);
    fclose(file);
}

void print_history() {
    char line[1024];
    FILE *file = fopen(HISTORY_FILE, "r");
    if (file == NULL) {
        perror("Failed to open history file");
        return;
    }
    int index = 1;
    while (fgets(line, sizeof(line), file)) {
        printf("%d %s", index++, line);
    }
    fclose(file);
}

void execute_command_from_history(int n) {
    char line[1024];
    FILE *file = fopen(HISTORY_FILE, "r");
    if (file == NULL) {
        perror("Failed to open history file");
        return;
    }
    int index = 1;
    while (fgets(line, sizeof(line), file)) {
        if (index == n) {
            line[strcspn(line, "\n")] = '\0'; // remover o null char
            process_command(line);
            break;
        }
        index++;
    }
    fclose(file);
}

void process_command(char *command) {
    char *args[64];
    int numargs = parse(command, args);
    if (!builtin(args)) {
        execute(numargs, args);
    }
}
