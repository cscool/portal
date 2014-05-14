#pragma once
#include <Box2D/Box2D.h>
#include "log.h"
#include "const.h"
#include "contains.h"

using namespace std;

extern int xres;
extern int yres;
extern const float M2P;
extern const float P2M;
extern b2World * world;

b2Body* addDoor(float xpos, float ypos);
