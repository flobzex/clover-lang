#include <clover.h>
#include <clover/list.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


struct clv_buildopt {
    // runtime mode
    bool rt_nojit;              // JIT compiler
    bool rt_nohost;             // host-bound optimizations
    clv_zstr rt_clx_file;       // clover executable file
    struct clv_list *rt_args;   // cmdline args

    // build mode
    bool cp_compile_mode;
    bool cp_debug_symbols;
    clv_zstr cp_manifest_file;
    clv_zstr cp_output_file;
};


_CLV_ALWAYS_INLINE static bool
strequal (clv_zstr a, clv_zstr b) {
    return strcmp (a, b) == 0;
}


_CLV_ALWAYS_INLINE static bool
is_option (clv_zstr x) {
    if (x == NULL || strlen (x) < 2) {
        return false;
    }

    return x[0] == '-';
}


_CLV_ALWAYS_INLINE static void
check_arity (int arity, int i, int argc, const char **argv) {
    if (i + arity >= argc) {
        clv_error ("missing argument for option '%s'", argv[i]);
        exit (1);
    }
}


_CLV_ALWAYS_INLINE static void
show_help () {
    printf ((
        "Usage:\n"
        "\tclover [options...] <file> [args...]\n"
        "\tclover -c <manifest> [-d] [-o <output>]\n\n"
        "Run options:\n"
        "  --nojit                      Disable Just-in-Time compiler\n"
        "  --nohost                     Disable host-bound optimizations\n\n"
        "Compile options:\n"
        "  -c MANIFEST                  Compile program\n"
        "  -d  --debug-symbols          Enable debug symbols\n"
        "  -o FILE  --output FILE       Set output file name\n"
        "General options:\n"
        "  -h  --help                   Displays this message and exits\n"
        "  -v  --version                Displays program version and exits\n"
    ));
}


static void
show_version () {
    printf ((
        "clover " CLOVER_VERSION " - built with " CLOVER_BUILDINFO " \n"
        "Copyright (C) 2025 Thaynan M. Silva\n"
        "\n"
        "This is free software, and you are welcome to redistribute it\n"
        "under the terms of the GNU Lesser General Public License 3.0.\n"
        "This program comes with ABSOLUTELY NO WARRANTY!\n"
        "\n"
        "License: <https://www.gnu.org/licenses/lgpl-3.0.html>\n"
    ));
}


static void
parse_options (struct clv_buildopt *options, int argc, const char **argv) {
    bool end_options = false;

    for  (int i = 1; i < argc; i++) {
        const clv_zstr curr = argv[i];

        if (!end_options && is_option (curr)) {
            if (strequal (curr, "-h") || strequal (curr, "--help")) {
                show_help ();
                exit (0);
            } else if (strequal (curr, "-v") || strequal (curr, "--version")) {
                show_version ();
                exit (0);
            } else if (strequal (curr, "-c")) {
                check_arity (1, i, argc, argv);
                options->cp_compile_mode = true;
                options->cp_manifest_file = argv[++i];
            } else if (strequal (curr, "-d") || strequal (curr, "--debug-symbols")) {
                options->cp_debug_symbols = true;
            } else if (strequal (curr, "--nojit")) {
                options->rt_nojit = true;
            } else if (strequal (curr, "--nohost")) {
                options->rt_nohost = true;
            } else if (strequal (curr, "-o") || strequal (curr, "--output")) {
                check_arity (1, i, argc, argv);
                options->cp_output_file = argv[++i];
            } else if (strequal (argv[i], "--")) {
                end_options = true;
            } else {
                clv_error ("invalid option: '%s'. use -h to get help", argv[i]);
                exit (1);
            }
        } else {
            clv_list_push (&options->rt_args, (void *)argv[i]);
        }
    }

    if (options->cp_compile_mode && options->rt_args != NULL) {
        clv_error ("invalid number of arguments. use -h to get help");
        exit (1);
    }
}

int
main (int argc, const char **argv) {
    if (argc < 2) {
        show_help ();
        return 1;
    }

    struct clv_buildopt options = {0};

    parse_options (&options, argc, argv);

    clv_list_clear (&options.rt_args, NULL);
}
