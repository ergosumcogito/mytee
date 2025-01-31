#include <signal.h>
#include "signal_handler.h"

void setup_signal_handling(TeeOptions *options) {
    if (options->ignore_int) {
        signal(SIGINT, SIG_IGN);
    }
}
