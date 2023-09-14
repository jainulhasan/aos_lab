#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_ps(const char *options) {
    char command[256];
    snprintf(command, sizeof(command), "ps %s", options);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("Error executing ps command");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    pclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-a] [-ae] [-u <username>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-a") == 0) {
        execute_ps("a");
    } else if (strcmp(argv[1], "-ae") == 0) {
        execute_ps("ae");
    } else if (strcmp(argv[1], "-u") == 0 && argc >= 3) {
        if (strlen(argv[2]) > 0) {
            char options[256];
            snprintf(options, sizeof(options), "u %s", argv[2]);
            execute_ps(options);
        } else {
            fprintf(stderr, "Invalid username argument\n");
            exit(EXIT_FAILURE);
        }
    } else {
        execute_ps("");
    }

    return 0;
}
