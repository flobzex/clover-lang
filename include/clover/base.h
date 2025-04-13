#ifndef CLOVER_BASE_H_
#define CLOVER_BASE_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* Handy macros */

#define CLV_STRINGIFY0(x)           #x
#define CLV_STRINGIFY(x)            CLV_STRINGIFY0(x)

#define CLV_ARR_SIZEOF(x)           (sizeof (x) / sizeof (*x))

#define CLV_MIN(a,b)                (a < b ? a : b)
#define CLV_MAX(a,b)                (a > b ? a : b)
#define CLV_CLAMP(x,mn,mx)          (x < mn ? mn : (x > mx ? mx : x))
#define CLV_ENUM_VALUE(x,mx)        CLV_CLAMP (x, 0, (mx-1))
#define CLV_ENUM_ISVALID(x,mx)      (x >= 0 && x < mx)

#define CLV_GET_OR(test_expr,get_expr,fallback_expr) \
    ((test_expr) ? (get_expr) : (fallback_expr))

#define CLV_ARRAY_GET(arr,i,fallback) \
    (CLV_GET_OR ((i) >= 0 && (i) < CL_ARR_SIZEOF (arr), arr[(i)], (fallback)))

#define CLV_FUNCNAME                __func__

/* Attribute macros */

#define _CLV_NODISCARD              __attribute_warn_unused_result__
#define _CLV_NOTHROW                __THROWNL
#define _CLV_LEAF                   __attribute__ ((__leaf__))
#define _CLV_DEPRECATED             __attribute_deprecated__
#define _CLV_DEPRECATED_MSG(msg)    __attribute_deprecated__(msg)
#define _CLV_ALWAYS_INLINE          __always_inline
/* Type macros */

#define CLV_VOIDPTR(p)              ((void *)(p))

/* Type defs */

typedef const char *clv_zstr;

#endif /* CLOVER_BASE_H_ */
