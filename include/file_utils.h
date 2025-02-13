#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include "structs.h"

int open_files(TeeOptions *options, FILE ***out_files);
void close_files(FILE **files, int file_count);
int handle_file_error(TeeOptions *options, const char *filename);

#endif //FILE_UTILS_H
