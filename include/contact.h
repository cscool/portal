#pragma once
#include "log.h"
#include "const.h"
#include "createObjects.h"
#include "contains.h"
#include <cstring>
#include "Box2D/Box2D.h"

using namespace std;

extern b2Vec2 p_pos;
extern float p_angle;
extern int p_isleft;
extern b2World * world;
extern b2Body * myPlayer;
extern b2Body * gameFloor;
extern b2Body * platform;
extern b2Body * toDestroy;

class contactListener : public b2ContactListener
{
		  void BeginContact (b2Contact * contact);
		  void EndContact (b2Contact * contact);
};
