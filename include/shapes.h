#pragma once
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "const.h"
#include "obj.h"
#include "log.h"

//extern double ** oval;
extern int xres;
extern int yres;
extern int zres;
extern int objcnt;
extern int portalcnt;
//extern long int sz;

struct portal ** plist; // ptr to a portal object. 2 max.
int plast; // last created portal - the other is the one to modify
struct obj ** olist;
#ifndef _SHAPES_H
#define _SHAPES_H

void destroyObj (int);
void destroyPortal (int);
void initObj (void);
void initPortal (void);
void drawPortal(struct portal *);
void drawOval(short int ***);

#endif // shapes.h
