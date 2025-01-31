#include <stdio.h>
#include <stdlib.h>
#include "tee.h"
#include "file_utils.h"
#include <unistd.h>

#define BUFFER_SIZE 1024

void tee(TeeOptions *options) {
    FILE **files = open_files(options);
    char buffer[BUFFER_SIZE];
    int write_error = 0; // flag to track --output-error=warn case

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (options->file_count > 0 && files != NULL) {
            for (int i = 0; i < options->file_count; i++) {
                if (files[i]) {
                    if (fputs(buffer, files[i]) == EOF) {
                        handle_file_error(options, options->files[i]);
                    } else {
                        fflush(files[i]); // Flush buffer after successful write
                    }
                } else {
                    if (options->output_error == 1) {
                        fprintf(stderr, "Error writing to %s\n", options->files[i]);
                    }
                    write_error = 1;
                }
            }
        }

        printf("%s", buffer);
        fflush(stdout);
    }

    if (options->file_count > 0 && files != NULL) {
        close_files(files, options->file_count);
    }

    if (write_error) {
        exit(1);
    }
}
