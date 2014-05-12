#pragma once
#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include "log.h"
#include "const.h"
#include "createObjects.h"
#include "contains.h"
#include "Box2D/Box2D.h"

using namespace std;

extern b2Body * p1;
extern b2Body * p2;
extern b2World * world;
extern b2Body * toDestroy;
extern int bullet_ct;
extern b2Fixture * myPlayerFoot;
extern b2Body * myPlayer;
extern b2Body * myGun;
extern const float M2P;
extern const float P2M;
extern int keys[];
extern b2Vec2 p1_dir;
extern b2Vec2 p2_dir;
extern int player_direction;
extern bool pauseGame;
extern char * p_dest;
extern bool can_jump;
extern int fix_vel;
extern b2Vec2 mod_vel;

void physics (void);
void doPortal(b2Body *);
void moveBullet (b2Body * p, const float lmax = -243.0f, const float rmax = 338.5f);
float getMagnitude (b2Vec2);
void movePlatform (b2Body * p, const float lmax = -243.0f, const float rmax = 338.5f);
