#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int total_char=0;
int total_words=0;
int total_lines=0;
void count_wc(const char *filename, int count_chars, int count_lines, int count_words) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int char_count = 0;
    int line_count = 0;
    int word_count = 0;
    int in_word = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        char_count++;

        if (count_lines && ch == '\n') {
            line_count++;
        }

        if (count_words) {
            if (ch == ' ' || ch == '\t' || ch == '\n') {
                if (in_word) {
                    word_count++;
                    in_word = 0;
                }
            } else {
                in_word = 1;
            }
        }
    }

    if (count_words && in_word) {
        word_count++;
    }
    fclose(file);

    if (count_chars){
        total_char+=char_count; 
        printf("Characters in %s: %d\n", filename, char_count);
    }
    if (count_lines) {
        total_lines+=count_lines;
        printf("Lines in %s: %d\n", filename, line_count);
    }
    if (count_words) {
	total_words+=count_words;
        printf("Words in %s: %d\n", filename, word_count);
    }
}

int main(int argc, char *argv[]) {
    int count_chars = 0;
    int count_lines = 0;
    int count_words = 0;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-c] [-l] [-w] <file1> [<file2> ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            count_chars = 1;
        } else if (strcmp(argv[i], "-l") == 0) {
            count_lines = 1;
        } else if (strcmp(argv[i], "-w") == 0) {
            count_words = 1;
        } else {
            count_wc(argv[i],1,1,1);
        }
    }
    printf("\n total char :- %d\n",total_char);
    printf("total lines :- %d\n",total_lines);
    printf("total words :- %d\n",total_words);
    return 0;
}
