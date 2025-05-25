#include <clover/compiler.h>
#include <clover/source.h>
#include <clover/log.h>

#include <stdlib.h>
#include <stdio.h>


struct clv_unit {
    clv_str file;
};


static bool
compile_unit (clv_str file, struct clv_unit **out_unit) {
    clv_error ("%s: stub", __func__);
    return false;
}


static bool
write_exec (clv_str _manifest, clv_str output) {
    clv_error ("%s: stub", __func__);
    return false;
}


bool
clv_compile (clv_str _manifest, clv_list_t *files, clv_str output, bool debug) {
    clv_list_t *units = clv_list_new ();

    if (units == NULL) {
        return false;
    }

    bool good = true;

    clv_list_iter_t iter = clv_list_get_head (files);

    for (; iter != NULL; iter = clv_list_iter_get_next (iter)) {
        clv_str file = clv_list_iter_get_data (iter);

        struct clv_unit *unit;

        if (compile_unit (file, &unit)) {
            clv_list_push_back (units, CLV_VOIDPTR (unit));
        } else {
            good = false;
            break;
        }
    }

    if (good && !write_exec (_manifest, output)) {
        good = false;
    }

    clv_list_free (units, (clv_list_func_t)free);

    return good;
}
