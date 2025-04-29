#include <clover/log.h>

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>


static const struct log_template {
    clv_zstr level;
    clv_zstr format;
} templates[] = {
    { "debug",   "\e[1;35m%s\e[0m: " },
    { "info",    "\e[1m%s\e[0m: "    },
    { "warning", "\e[1;33m%s\e[0m: " },
    { "error",   "\e[1;31m%s\e[0m: " }
};


bool
clv_log_debug () {
    static int debug = -1;

    if (debug < 0) {
        char *debug_env = getenv("DEBUG");

        if (debug_env != NULL) {
            debug = (strcmp (debug_env, "1") == 0);
        } else {
            debug = false;
        }
    }

    return (bool)debug;
}


void
_clv_log0 (const char *file, int lineno, int level, int mode, const char *msg, ...) {
    va_list args;

    if (level == CLV_DEBUG && !clv_log_debug ()) {
        return;
    }

    FILE *out = stdout;
    struct log_template tt = { "???", "\e[1;40m%s\e[0m: " };

    if ((level >= 0 && level <= CLV_ERROR)) {
        tt = templates[level];
        out = (level >= CLV_ERROR ? stderr : stdout);
    }

#if defined (CLV_DEBUG) && CLV_DEBUG
    fprintf (out, "[%s:%u] ", file, lineno);
#endif /* CLV_DEBUG */

    if (mode & CLV_LOG_TEMPLATE) {
        fprintf (out, tt.format, tt.level);
    }

    va_start (args, msg);
    vfprintf (out, msg, args);
    va_end (args);

    if (mode & CLV_LOG_NEWLINE) {
        fputc ('\n', out);
    }
}
