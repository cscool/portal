#pragma once
#include "log.h"
#include "arenas.h"
#include "const.h"
#include "createObjects.h"
#include "contains.h"
#include <cstring>
#include "Box2D/Box2D.h"

using namespace std;

extern b2Vec2 p_pos;
extern float p_angle;
extern int p_isleft;
extern b2Vec2 p_vel;
extern b2Vec2 p1_dir;
extern b2Vec2 p2_dir;
extern b2Body * p_obj;
extern char * p_dest;
extern int p1_contacting;
extern int p2_contacting;
extern b2World * world;
extern b2Body * myPlayer;
extern b2Body * gameFloor;
extern b2Body * myDoor;
extern b2Body * platform;
extern b2Body * toDestroy;
extern bool can_jump;
extern int fix_vel;
extern b2Vec2 mod_vel;

class contactListener : public b2ContactListener
{
		  void BeginContact (b2Contact * contact);
		  void EndContact (b2Contact * contact);
};
