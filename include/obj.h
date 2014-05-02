#ifndef _OBJ_H
#define _OBJ_H

static const int pWidth = 100;
static const int pHeight = 150;
static int maxobj = 0;

struct obj
{
	 float *** pos;
	 float halfWidth;
	 float halfHeight;
	 float halfDepth;
	 int isPortal; // not a portal. needed???
};

struct portal
{
	 float *** pos;
	 float halfWidth;
	 float halfHeight;
	 float halfDepth;
	 int isPortal; // not a portal until there are 2 portals
};

#endif /* obj.h */
