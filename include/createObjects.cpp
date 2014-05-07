#include "createObjects.h"

using namespace std;

b2Body* addRect(int x, int y, int w, int h, float f, float d, int dyn, char * udata)
{
		  //bodydef (pos, type)

		  b2BodyDef bodydef;
		  bodydef.position.Set(x*P2M, y*P2M);
		  if(dyn == 1)
		  {
					 bodydef.type=b2_dynamicBody;
		  }
		  else if (dyn == 2)
		  {
					 bodydef.type=b2_staticBody;
		  }
		  else
		  {
					 bodydef.type=b2_kinematicBody;
		  }
		  bodydef.linearDamping = d;
		  bodydef.fixedRotation = false;
		  b2Body* body = world->CreateBody(&bodydef);
		  b2PolygonShape shape;
		  shape.SetAsBox(P2M*w/2.0, P2M*h/2.0);

		  b2FixtureDef fixturedef;
		  fixturedef.shape = &shape;
		  fixturedef.density = 1.0;
		  fixturedef.friction = f;
		  if (udata)
		  {
					 body->SetUserData((void*)udata);
					 if (udata == (char *)("platform"))
					 {
								//Log("it is a platform , setting initial velocity\n");
								body->SetLinearVelocity(b2Vec2(5.0f, 0.0f));
					 }
					 if (contains(udata, (const char *)"bullet"))
					 {
								//Log("it is a platform , setting initial velocity\n");
								body->SetGravityScale(0);
								body->SetLinearVelocity(b2Vec2((float)player_direction * 19.0f, 0.0f));
					 }
		  }
		  body->CreateFixture(&fixturedef);
		  return body;
}

b2Body* addPlayer(int x, int y, int w, int h)
{
		  b2BodyDef bodydef;
		  bodydef.position.Set(x*P2M, y*P2M);
		  bodydef.type = b2_dynamicBody;
		  bodydef.gravityScale = 1.0f;
		  bodydef.fixedRotation = true;
		  b2Body* body = world->CreateBody(&bodydef);
		  b2PolygonShape shape;
		  shape.SetAsBox(P2M*w/2.0,P2M*h/2.0);

		  b2FixtureDef fixturedef;

		  fixturedef.shape = &shape;
		  fixturedef.density = 1.0;
		  body->CreateFixture(&fixturedef);


		  return body;
}

void addFoot(int h)
{
		  b2PolygonShape shape;
		  shape.SetAsBox(P2M*40, P2M*40, b2Vec2(0,(h/2)), 0);

		  b2FixtureDef fixturedef;
		  fixturedef.shape = &shape;
		  fixturedef.density = 0.0f;
		  fixturedef.isSensor = true;
		  myPlayer->CreateFixture(&fixturedef);
}

void addObstacles()
{
		  //top of floor is yres-50-25 = yres-75
		  float onFloor = yres-75;
		  addRect(800, yres-105, 60, 60, 0.02f, 0.2f, 1);//bottomleft of stack
		  addRect(865, yres-105, 60, 60, 0.02f, 0.2f, 1);//bottom right
		  addRect(832.5, yres-170, 60, 60, 0.02f, 0.2f, 1);//top

		  addRect(1200, onFloor-15, 80, 30, 0.7f, 0.2f, 2);// stairs
		  addRect(1280, onFloor-30, 80, 60, 0.7f, 0.2f, 2);
		  addRect(1360, onFloor-45, 80, 90, 0.7f, 0.2f, 2);
		  addRect(1440, onFloor-60, 80, 120, 0.7f, 0.2f, 2);
		  addRect(1520, onFloor-75, 80, 150, 0.7f, 0.2f, 2);
}
