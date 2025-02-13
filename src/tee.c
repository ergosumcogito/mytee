#include <stdio.h>
#include <stdlib.h>
#include "tee.h"
#include "file_utils.h"
#include <unistd.h>
#include "thread_utils.h"

#define BUFFER_SIZE 1024

void tee(TeeOptions *options) {
    FILE **files = open_files(options);
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        write_to_files_and_console(files, options->file_count, buffer);
    }

    if (options->file_count > 0 && files != NULL) {
        close_files(files, options->file_count);
    }
}