#include <stdio.h>
#include <stdlib.h>
#include "tee.h"
#include "file_utils.h"
#include <unistd.h>
#include "thread_utils.h"

#define BUFFER_SIZE 1024

int tee(TeeOptions *options) {
    FILE **files = NULL;
    int exit_code = open_files(options, &files);

    // If in exit mode and an error occurred, return immediately to avoid using NULL files pointer
    if (exit_code != 0 && options->output_error == 2) {
        return exit_code;
    }

    char buffer[BUFFER_SIZE];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if(write_to_files_and_console(files, options->file_count, buffer) != 0) {
            exit_code = 1;
        }
    }

    if (options->file_count > 0 && files != NULL) {
        close_files(files, options->file_count);
    }

    return exit_code;
}