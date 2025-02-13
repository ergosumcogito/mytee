#include "structs.h"
#include "args.h"
#include "tee.h"
#include "signal_handler.h"

int main(int argc, char *argv[]) {
    TeeOptions options = {0};

    parse_args(argc, argv, &options);
    setup_signal_handling(&options);

    tee(&options);
    return 0;
}
