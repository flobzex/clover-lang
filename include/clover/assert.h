#ifndef CLOVER_ASSERT_H_
#define CLOVER_ASSERT_H_

#include <clover/base.h>
#include <clover/log.h>

#define clv_assert(expr,tail)   if (!(expr)) { clv_error ("assertion failed: " CLV_STRING (expr), msg); tail; }

#endif /* CLOVER_ASSERT_H_ */
