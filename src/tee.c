#include <stdio.h>
#include <stdlib.h>
#include "tee.h"
#include "file_utils.h"
#include <unistd.h>

#define BUFFER_SIZE 1024

void tee(TeeOptions *options) {
    FILE **files = open_files(options);
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        for (int i = 0; i < options->file_count; i++) {
            if (files[i] && fputs(buffer, files[i]) == EOF) {
                handle_file_error(options, options->files[i]);
            }
        }

        printf("%s", buffer);
        fflush(stdout);
    }

    close_files(files, options->file_count);
}
