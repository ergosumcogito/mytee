#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"

void handle_file_error(TeeOptions *options, const char *filename) {
    fprintf(stderr, "Error writing to %s\n", filename);

    if (options->output_error == 2) {
        exit(1);
    }
}

FILE **open_files(TeeOptions *options) {
    FILE **files = malloc(options->file_count * sizeof(FILE *));
    if (!files) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }

    for (int i = 0; i < options->file_count; i++) {
        files[i] = fopen(options->files[i], options->append ? "a" : "w");
        if (!files[i]) {
            fprintf(stderr, "Error opening %s\n", options->files[i]);

            // Case --output-error=exit
            if (options->output_error == 2) {
                free(files);
                exit(1);
            }
        }
    }
    return files;
}

void close_files(FILE **files, int file_count) {
    for (int i = 0; i < file_count; i++) {
        if (files[i]) fclose(files[i]);
    }
    free(files);
}
