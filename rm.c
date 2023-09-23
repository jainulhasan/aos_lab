#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [<file2> ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++){
        if (remove(argv[i]) == 0) {
            printf("Removed file: %s\n", argv[i]);
        } else {
            perror("Error deleting file");
        }
    }

    return 0;
}
