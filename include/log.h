

#ifndef PIP
#define PIP "File: %s; Line:%s\n", __FILE__ , __LINE__
#endif

#ifndef _LOG_H
#define _LOG_H

extern void logOpen(void);
extern void logClose(void);
extern void Log(const char *fmt, ...);

#endif
