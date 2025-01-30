#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

int tee(const char *fileName) {
    FILE *file = fopen(fileName, "w"); // Skip argv[0] (program name)
    if (file == NULL) {
        printf("Error: Failed to open file.\n");
        return 1;                  // not found
    }

    char output[BUFFER_SIZE]; // our string

    while (fgets(output, BUFFER_SIZE, stdin) != NULL){
        // Part1: print to stdout
        printf("%s", output);
        fflush(stdout);

        // Part2: write to file
        if (fputs(output, file) == EOF) {
            printf("Error: Failed to write to file.\n");
            fclose(file);
            return 1;
        }
    }

    // close file
    if (fclose(file) == EOF) {
        printf("Error closing file");
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <output_file>\n", argv[0]);
        return 1;
    }

    return tee(argv[1]);
}
