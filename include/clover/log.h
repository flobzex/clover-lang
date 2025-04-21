#ifndef CLOVER_LOG_H_
#define CLOVER_LOG_H_

#include <clover/base.h>

enum clv_loglevel
{
    CLV_LOGLEVEL_DEBUG,
    CLV_LOGLEVEL_INFO,
    CLV_LOGLEVEL_WARNING,
    CLV_LOGLEVEL_ERROR,
    CLV_LOGLEVEL_SEVERE,
    __CLV_LOGLEVEL_MAX
};

#define clv_log(level,msg,args...)  _clv_log0 (__FILE__, __LINE__, level, msg, ## args)
#define clv_debug(msg,args...)      clv_log (CLV_LOGLEVEL_DEBUG, msg, ## args)
#define clv_info(msg,args...)       clv_log (CLV_LOGLEVEL_INFO, msg, ## args)
#define clv_warning(msg,args...)    clv_log (CLV_LOGLEVEL_WARNING, msg, ## args)
#define clv_error(msg,args...)      clv_log (CLV_LOGLEVEL_ERROR, msg, ## args)
#define clv_severe(msg,args...)     clv_log (CLV_LOGLEVEL_SEVERE, msg, ## args)

void _clv_log0 (const char *file, int lineno, enum clv_loglevel level, const char *msg, ...);

#endif /* CLOVER_LOG_H_ */
