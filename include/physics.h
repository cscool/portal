#pragma once
#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include "log.h"
#include "arenas.h"
#include "const.h"
#include "createObjects.h"
#include "contains.h"
#include "Box2D/Box2D.h"
#include "turret.h"
#include "movingPlatform.h"
#include <lens.h>

using namespace std;

extern b2Body * p1;
extern b2Body * p2;
extern b2World * world;
extern b2Body * toDestroy;
extern int bullet_ct;
extern int p1_contacting;
extern int p2_contacting;
extern b2Body * gunEnemy1;
extern b2Body * myPlayerFoot;
extern b2Body * myPlayer;
extern b2Body * myGun;
extern b2Body * myDoor;
extern b2Body * carry;
extern Turret * turrets;
extern Platform * platforms;
extern int cwait;
extern int current_arena;
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
extern int door_is_active;
extern int button_pressed;
extern char * p1_in_contact;
extern char * p2_in_contact;
extern Lens * lens;

void movePlatform2(Platform &plat);
void resetDestroyVars(void);
void detonate (b2Body * a, b2Body * b = NULL);
void physics (void);
void doPortal(b2Body *);
void moveBullet (b2Body * p, const float lmax = -243.0f, const float rmax = 338.5f);
float getMagnitude (b2Vec2);
void movePlatform (b2Body * p, const float lmax = 80.0f, const float rmax = 220.0f);
void moveMine (Mine & p);
float getLMax (const b2Body * m);
float getRMax (const b2Body * m);
