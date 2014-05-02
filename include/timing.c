#include "timing.h"

double timeDiff(struct timespec *start, struct timespec *end)
{
	 return (double)(end->tv_sec - start->tv_sec ) +
		  (double)(end->tv_nsec - start->tv_nsec) * oobillion;
}

void timeCopy(struct timespec *dest, struct timespec *source)
{
	 memcpy(dest, source, sizeof(struct timespec));
}

