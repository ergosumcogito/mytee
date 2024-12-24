#include <iostream>
#include <string.h>
#define BUFFER_SIZE 1024

int tee(char fileName[]) {
    // open a file
    FILE *file = fopen(fileName, "a");
    if (file == NULL) {
        printf("Error: Failed to open file.\n");
        return 1;                  // not found
    }

    char output[BUFFER_SIZE]; // our string

    // write to file
    printf("Print your lines you want to save (or empty line or Ctrl+D to exit:\n");
    while (fgets(output, BUFFER_SIZE, stdin) != NULL){
        // close if the line empty
        if (strcmp(output, "\n") == 0) {
            break;
        }

        // write to file one line
        if (fputs(output, file) == EOF) {
            printf("Error: Failed to write to file.\n");
            fclose(file);
            return 1;               // Error
        }

        // output the line
        printf("%s", output);
    }

    // close file
    if (fclose(file) == EOF) {
        printf("Error closing file");
        return 1;
    }

    printf("String successfully written to the file.\n");
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <output_file>\n", argv[0]);
        return 1;
    }

    return tee(argv[1]);
}
