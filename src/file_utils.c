#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"

int handle_file_error(TeeOptions *options, const char *filename) {
    fprintf(stderr, "Error writing to %s\n", filename);
    if (options->output_error == 2) {
        exit(1);
    }
    return 1;
}

int open_files(TeeOptions *options, FILE ***out_files) {
    if (options->file_count == 0) {
        *out_files = NULL;
        return 0;
    }

    FILE **files = malloc(options->file_count * sizeof(FILE *));
    if (!files) {
        fprintf(stderr, "Memory allocation error\n");
        return 2;
    }

    int error_occurred = 0;

    for (int i = 0; i < options->file_count; i++) {
        files[i] = fopen(options->files[i], options->append ? "a" : "w");
        if (!files[i]) {
            fprintf(stderr, "Error opening %s\n", options->files[i]);

            if (options->output_error == 2) { // output-error=exit
                close_files(files, i);
                return 1;
            } else {
                files[i] = NULL; // output-error=warn: continue execution
                error_occurred = 1;
            }
        }
    }

    *out_files = files;
    return error_occurred ? 1 : 0;  // Return 1 if any error occurred
}

void close_files(FILE **files, int file_count) {
    if (files != NULL) {
        for (int i = 0; i < file_count; i++) {
            if (files[i]) {
                fclose(files[i]);
            }
        }
        free(files);
    }
}
