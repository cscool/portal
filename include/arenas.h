#pragma once
#include "Box2D/Box2D.h"
#include "const.h"
#include "createObjects.h"
#include "log.h"

using namespace std;

extern b2World * world;
extern b2Body * toDestroy;
extern int bullet_ct;
extern b2Body * myPlayerFoot;
extern b2Body * myPlayer;
extern b2Body * myGun;
extern b2Body * gameFloor;
extern b2Body * platform;
extern b2Body * p1;
extern b2Body * p2;
extern b2Body * mineObject;

void makeArena(const int n = 0);
void addObstacles(void);
void addStairs(void);
