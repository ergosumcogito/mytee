#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    int append;        // -a / --append
    int ignore_int;    // -i / --ignore-interrupts
    int output_error;  // --output-error=[warn|exit]
    int file_count;    // Number of output files
    char *files[10];   // File names
} TeeOptions;

#endif //STRUCTS_H
