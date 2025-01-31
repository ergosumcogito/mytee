#include <stdio.h>
#include "structs.h"
#include "args.h"
#include "tee.h"
#include "signal_handler.h"

int main(int argc, char *argv[]) {
    TeeOptions options = {0};

    parse_args(argc, argv, &options);
    setup_signal_handling(&options);

    if (options.file_count == 0) {
        fprintf(stderr, "Usage: %s [-a] [-i] [--output-error=MODE] [file...]\n", argv[0]);
        return 1;
    }

    tee(&options);
    return 0;
}
