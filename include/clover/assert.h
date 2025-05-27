#ifndef CLOVER_ASSERT_H_
#define CLOVER_ASSERT_H_

#include <clover/base.h>
#include <clover/log.h>

#define clv_assert(expr,_tail) \
    do { \
        if (!(expr)) { \
            clv_error ("assertion failed: " #expr); \
            _tail; \
        } \
    } while (0)

#endif /* CLOVER_ASSERT_H_ */
