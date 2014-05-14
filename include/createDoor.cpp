#include "createDoor.h"

using namespace std;

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
