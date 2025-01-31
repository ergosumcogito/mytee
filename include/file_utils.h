#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include "structs.h"

FILE **open_files(TeeOptions *options);
void close_files(FILE **files, int file_count);
void handle_file_error(TeeOptions *options, const char *filename);

#endif //FILE_UTILS_H
