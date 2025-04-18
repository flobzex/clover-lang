#include <clover/log.h>

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


static bool _debug_mode = false;


static const struct log_level {
    clv_zstr level;
    clv_zstr format;
} log_levels[] = {
    { "debug",   "\e[1;3m%s\e[0m: "  },
    { "info",    "\e[1m%s\e[0m: "    },
    { "warning", "\e[1;33m%s\e[0m: " },
    { "error",   "\e[1;31m%s\e[0m: " },
    { "severe",  "\e[1;31m%s\e[0m: " },
    { "???",     "\e[1;40m%s\e[0m: " }
};


void
_clv_log0 (const char *file, int lineno, enum clv_loglevel level, const char *msg, ...) {
    va_list args;
    FILE *out;

    if (level == CLV_LOGLEVEL_DEBUG && !clv_log_get_debug_mode ()) {
        return;
    }

    out = (level >= CLV_LOGLEVEL_ERROR ? stderr : stdout);

    if (!CLV_ENUM_ISVALID (level, __CLV_LOGLEVEL_MAX)) {
        level = __CLV_LOGLEVEL_MAX;
    }

    struct log_level log_level = log_levels[level];

#if defined (CLV_DEBUG) && CLV_DEBUG
    fprintf (out, "[%s:%u] ", file, lineno);
#endif /* CLV_DEBUG */

    fprintf (out, log_level.format, log_level.level);

    va_start (args, msg);
    vfprintf (out, msg, args);
    va_end (args);

    fputc ('\n', out);
}

void
clv_log_set_debug_mode (bool enabled) {
    _debug_mode = enabled;
}

bool
clv_log_get_debug_mode () {
    return _debug_mode;
}
