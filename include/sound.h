#pragma once
#include "fmod.h"
#include "log.h"
#include "fmod_errors.h"
#include "wincompat.h"
#include <stdio.h>
#include <math.h>

void musicHandler (void);
void playMusic(const int &);
void ERRCHECK(FMOD_RESULT result);
void stopMusic (void);
void initMusic(void);
