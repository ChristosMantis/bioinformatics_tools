#include <stdio.h>

int count_lines(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    int lines = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    fclose(file);
    return lines;
}

int main( int argc, char *argv[] ) {
    const char *filename = argv[1];
    int lines = count_lines(filename);

    if (lines != -1) {
        printf("The file '%s' has %d lines.\n", filename, lines);
    } else {
        printf("Failed to count lines in the file '%s'.\n", filename);
    }

    return 0;
}
