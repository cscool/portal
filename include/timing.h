#pragma once
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern const double physicsRate;
extern const double oobillion;
extern struct timespec timeStart;
extern struct timespec timeCurrent;
extern struct timespec timePause;
extern double physicsCountdown;
extern double timeSpan;
//extern unsigned int upause;

#ifndef TIMING_H
#define TIMING_H

double timeDiff(struct timespec *, struct timespec *);
void timeCopy(struct timespec *, struct timespec *);

#endif /* timing.h */
