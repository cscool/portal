#pragma once
#include "log.h"
#include <cstring>
#include "Box2D/Box2D.h"

using namespace std;

extern b2World * world;
extern b2Body * toDestroy;

class contactListener : public b2ContactListener
{
		  void BeginContact (b2Contact * contact);
		  void EndContact (b2Contact * contact);
};
