#pragma once
#include <Box2D/Box2D.h>
#include "log.h"
#include "const.h"
#include "contains.h"

using namespace std;

extern int player_direction;
extern int xres;
extern int yres;
extern int zres;
extern const float M2P;
extern const float P2M;
extern b2World * world;
extern b2Body * toDestroy;
extern b2Body * myPlayer;
extern b2Body * myPlayerFoot;
extern b2Body * myGun;
extern b2Body * gameFloor;
extern b2Body * platform;
extern b2Body * p1;
extern b2Body * p2;
extern b2Body * turret1;
extern b2Body * gunEnemy1;

b2Body* addTurret(b2Vec2, b2Vec2, bool, b2World *);
void init_b2d(void);
void addFoot(int);
b2Body* addPlayer(int, int, int, int, b2World *, b2Body *&);
b2Body* addRect(int, int, int, int, float, float, int, char * udata = NULL, float angle = 0.0f);
b2Body* addMirror(b2Vec2, b2Vec2, float, b2World* world);
void createPortal (const b2Vec2 &pos, const float &angle, const int &isleft);
b2Body* addDoor(float xpos, float ypos);
b2Body* addGunEnemy(b2Vec2 position, b2Vec2 area, int left, b2World * world);
