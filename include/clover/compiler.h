#ifndef CLOVER_COMPILER_H_
#define CLOVER_COMPILER_H_

#include <clover/base.h>
#include <clover/list.h>

#include <stdio.h>

bool clv_compile (FILE *err_fd, clv_str _manifest, clv_list_t *files, clv_str output, bool debug);

#endif /* CLOVER_COMPILER_H_ */
