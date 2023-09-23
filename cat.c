#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
     if (argc == 1) {
        // No file specified, read from standard input and display
         char c;
         while ((c = getchar()) != EOF) {
             putchar(c);
         }
     }
//    if (argc < 2) {
//        fprintf(stderr, "Usage: %s <file1> [<file2> ...]\n", argv[0]);
//        exit(EXIT_FAILURE);
//    }
else{
    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            perror("Error opening file");
            continue;
        }

        char ch;
        while ((ch = fgetc(file)) != EOF) {
           if(ch==' ')
            break;

            putchar(ch);
        }

        fclose(file);
    }
}
    return 0;
}
