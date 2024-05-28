#include <stdio.h>
#include <stdlib.h>

void read_fasta(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[256];
    int is_sequence = 0;

    while (fgets(line, sizeof(line), file)) {
        // Check if the line starts with '>'
        if (line[0] == '>') {
            // Skip the description line
            is_sequence = 1;
            continue;
        }

        // If it is a sequence line, print it
        if (is_sequence) {
            printf("%s", line);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    const char *filename = argv[1];
    read_fasta(filename);

    return 0;
}
