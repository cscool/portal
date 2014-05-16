#include "createObjects.h"

using namespace std;

void createPortal (const b2Vec2 &pos, const float &angle, const int &isleft)
{
		  Log("in createPortal, got angle = %.2f\n", angle);
		  if (p1 && isleft == 1)
		  {
					 world->DestroyBody(p1);
		  }
		  if (p2 && isleft != 1)
		  {
					 world->DestroyBody(p2);
		  }
		  if (isleft == 1)
		  {
					 Log("creating left portal\n");
					 p1 = addRect(pos.x, pos.y, portal_width, portal_height, 0.0f, 0.0f, 2, (char *)"isportal left");
					 p1->SetTransform(pos, angle);
		  }
		  else
		  {
					 Log("creating right portal\n");
					 p2 = addRect(pos.x, pos.y, portal_width, portal_height, 0.0f, 0.0f, 2, (char *)"isportal right");
					 p2->SetTransform(pos, angle);
		  }
}

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
					 Log("creating %s\n", udata);
					 if (udata == (char *)("platform"))
					 {
								//Log("it is a platform , setting initial velocity\n");
								body->SetLinearVelocity(b2Vec2(5.0f, 0.0f));
					 }
					 if (contains(udata, (const char *)"bullet"))
					 {
								//Log("it is a bullet, setting initial velocity\n");
								body->SetGravityScale(0);
								float angle = myGun->GetAngle() * R2D;
								/*
								float inverseAngle;
								if( angle <= 180 )
										  inverseAngle = (180 - angle);
								else if( angle <= 270 )
										  inverseAngle = (360 - angle - 180);
								else
										  inverseAngle = 0;
										  */
								b2Vec2 a((float)(cos(myGun->GetAngle())), (float)(sin(myGun->GetAngle())));
								body->SetLinearVelocity(19.0f * a);
								b2Vec2 p((float)(myGun->GetPosition().x + 4 * player_direction), (float)(myGun->GetPosition().y));
								body->SetTransform(p, myGun->GetAngle());
					 }
					 if (contains(udata, (const char *)"gun"))
					 {
								fixturedef.isSensor = true;
								body->SetGravityScale(0);
					 }
					 if (contains(udata, (const char *)"isportal"))
					 {
								Log("setting portal fixtures to be sensors\n");
								fixturedef.isSensor = true;
					 }
					 if (contains(udata, (const char *)"mine"))
					 {
								body->SetLinearVelocity(b2Vec2(0.0f, 5.0f));
					 }
		  }
		  body->CreateFixture(&fixturedef);
		  return body;
}

b2Body* addDoor(float xpos, float ypos)
{
	float width = 100;
	float height = 50;
	b2BodyDef bodydef;
	bodydef.position.Set(xpos*P2M, ypos*P2M);
	bodydef.type = b2_staticBody;
	//bot left
	b2Body* body = world->CreateBody(&bodydef);
	b2PolygonShape shape;
	shape.SetAsBox(P2M*width/2.0, P2M*height/2.0);

	b2FixtureDef fixturedef;
	fixturedef.shape = &shape;
	body->CreateFixture(&fixturedef);

	bodydef.position.Set((xpos+200)*P2M, ypos*P2M);
	//bot right
	b2Body* body2 = world->CreateBody(&bodydef);
	body2->CreateFixture(&fixturedef);

	//top left
	bodydef.position.Set((xpos)*P2M, (-yres+125)*P2M);
	b2Body* body3 = world->CreateBody(&bodydef);
	shape.SetAsBox(P2M*width/2.0, P2M*(height*4)/2.0);
	fixturedef.shape = &shape;
	body3->CreateFixture(&fixturedef);

	//top right
	bodydef.position.Set((xpos+200)*P2M, (-yres+125)*P2M);
	b2Body* body4 = world->CreateBody(&bodydef);
	body4->CreateFixture(&fixturedef);
	
	//door
	bodydef.position.Set((xpos+100)*P2M, (0.0)*P2M);
	bodydef.type = b2_kinematicBody;
	b2Body* body5 = world->CreateBody(&bodydef);
	shape.SetAsBox(P2M*width/2.0, P2M*(2*yres - 50)/2.0);
	fixturedef.shape = &shape;
	body5->CreateFixture(&fixturedef);
	return body5;
}

b2Body* addPlayer(int x, int y, int w, int h, b2World * world, b2Body*& gun)
{
		  b2Body* foot;
		  b2BodyDef bodydef;
		  bodydef.position.Set(x*P2M, y*P2M);
		  bodydef.type = b2_dynamicBody;
		  bodydef.gravityScale = 1.0f;
		  bodydef.fixedRotation = true;
		  b2Body* body = world->CreateBody(&bodydef);
		  gun = world->CreateBody(&bodydef);
		  b2PolygonShape shape; // body
		  b2PolygonShape shape2; // gun
		  b2PolygonShape shape3; // foot
		  shape.SetAsBox(P2M*w/2.0f,P2M*h/1.0f);
		  shape2.SetAsBox(P2M*w/1.3f, P2M*h/4.0f);
		  shape3.SetAsBox(P2M*w/4.0, P2M*h/3.5);

		  b2FixtureDef fixturedef;

		  fixturedef.shape = &shape;
		  fixturedef.density = 1.0;
		  body->CreateFixture(&fixturedef);

		  fixturedef.shape = &shape2;
		  fixturedef.isSensor = true;
		  gun->CreateFixture( &fixturedef );
		  gun->SetUserData((void *)((char *)"gun"));

		  foot = world->CreateBody(&bodydef);
		  fixturedef.shape = &shape3;
		  fixturedef.isSensor = true;
		  foot->CreateFixture( &fixturedef );
		  foot->SetUserData((void *)((char *)"foot"));

		  b2RevoluteJointDef revoluteJointDef2;
		  revoluteJointDef2.bodyA = body;
		  revoluteJointDef2.bodyB = foot;
		  revoluteJointDef2.collideConnected = false;
		  /*
		  revoluteJointDef2.localAnchorB.Set(0.0f, 0.0f);
		  revoluteJointDef2.localAnchorA.Set(0.0f, 0.0f);
		  */
		  revoluteJointDef2.localAnchorA.Set(0.0f, 0.0f);
		  revoluteJointDef2.localAnchorB.Set(0.0f, -1*(P2M*h/1.0f));

		  //b2RevoluteJoint* f_joint = (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef2);
		  world->CreateJoint(&revoluteJointDef2);

		  b2RevoluteJointDef revoluteJointDef;
		  revoluteJointDef.bodyA = body;
		  revoluteJointDef.bodyB = gun;
		  revoluteJointDef.collideConnected = false;
		  revoluteJointDef.localAnchorA.Set(0, 0);
		  revoluteJointDef.localAnchorB.Set(0, 0);

		  //b2RevoluteJoint* m_joint = (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef);
		  world->CreateJoint(&revoluteJointDef);

		  myPlayerFoot = foot;

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
