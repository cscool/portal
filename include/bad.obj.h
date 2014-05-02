#pragma once
#include "const.h"

#ifndef _OBJ_H
#define _OBJ_H

static float pWidth;
static float pHeight;
static float pDepth;
static int maxobj = 0;

/* only reasoning behind storing "half" width, is that division is one of the worst operations to perform with a CPU - 
 * if you need the width, *2.
 */

struct obj
{
	 int pos [3]; // center of obj
	 short int *** img; // basically boolean: at (0,0,0), is there a point? (1 or 0)
	 int isPortal; // not a portal. needed???
};

struct portal
{
	 int pos [3]; // center of obj
	 int img[300];
	 int isPortal; // not a portal until there are 2 portals
};

#endif /* obj.h */
