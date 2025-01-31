#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"

void parse_args(int argc, char *argv[], TeeOptions *options) {
    int opt;
    static struct option long_options[] = {
        {"append", no_argument, 0, 'a'},
        {"ignore-interrupts", no_argument, 0, 'i'},
        {"output-error", required_argument, 0, 'o'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "aio:h", long_options, NULL)) != -1) {
        switch (opt) {
            case 'a': options->append = 1; break;
            case 'i': options->ignore_int = 1; break;
            case 'o':
                if (strcmp(optarg, "warn") == 0)
                    options->output_error = 1;
                else if (strcmp(optarg, "exit") == 0)
                    options->output_error = 2;
                else {
                    fprintf(stderr, "Invalid --output-error value. Use 'warn' or 'exit'.\n");
                    exit(1);
                }
            break;
            case 'h':
                printf("Usage: tee [OPTION]... [FILE]...\n");
            exit(0);
            default:
                exit(1);
        }
    }

    // Collect remaining args as file names
    for (int i = optind; i < argc; i++) {
        options->files[options->file_count++] = argv[i];
    }
}