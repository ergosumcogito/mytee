#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include "structs.h"

FILE **open_files(TeeOptions *options);
void close_files(FILE **files, int file_count);

#endif //FILE_UTILS_H
