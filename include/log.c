#include <stdio.h>
#include <stdarg.h>

static FILE *fpxx;

void logOpen(void)
{
	fpxx = fopen("game.log","w");
}

void logClose(void)
{
	fclose(fpxx);
}

void Log(const char *fmt, ...)
{
	va_list ap;
	if (fmt == NULL) return;
	va_start(ap, fmt);
	vfprintf(fpxx, fmt, ap);
	fflush(fpxx);
	va_end(ap);
}
