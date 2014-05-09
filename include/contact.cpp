#include "contact.h"

using namespace std;

void contactListener::BeginContact (b2Contact * contact)
{
		  char * ud;
		  b2Vec2 pos;
		  b2Vec2 norm;
		  float angle = 0.0f;
		  b2BodyType dyn = myPlayer->GetType();
		  //		  b2BodyType stat = gameFloor->GetType();
		  //		  b2BodyType kin = platform->GetType();
		  ud = (char *)(contact->GetFixtureA()->GetBody()->GetUserData());
		  if (ud)
		  {
					 if (ud == (char *)"player")
					 {
								//								Log("Player hit something\n");
					 }
					 else if (contains(ud, (const char *)"bullet"))
					 {
								//								Log("bullet hit something\n");
								//								Log("FixtureA's user data:\n\t%s\n", ((char *)(contact->GetFixtureA()->GetBody()->GetUserData())));
								//								Log("FixtureB's user data:\n\t%s\n", ((char *)(contact->GetFixtureB()->GetBody()->GetUserData())));
								if (contains(((char *)(contact->GetFixtureB()->GetBody()->GetUserData())), "portalable"))
								{
										  //										  Log("you shot a portalable object!\n");
										  pos = (b2Vec2)(contact->GetFixtureA()->GetBody()->GetWorldCenter());
										  norm = (b2Vec2)(contact->GetManifold()->localNormal);
										  angle = (float)(contact->GetFixtureB()->GetBody()->GetAngle());
										  if (contains(ud, (const char *)"left"))
										  {
													 //													 Log("storing left portal data with angle = %.2f\n", angle);
													 p_isleft = 1;
													 p1_dir = norm;
										  }
										  else
										  {
													 //													 Log("storing right portal data with angle = %.2f\n", angle);
													 p_isleft = 0;
													 p2_dir = norm;
										  }
										  p_pos = pos;
										  p_angle = angle;
								}
								else
								{
										  Log("that's not portalable\n");
								}
								toDestroy = (b2Body *)(contact->GetFixtureA()->GetBody());
					 }
					 else if (contains(ud, (const char *)"isportal") && !p_contacting)
					 {
								Log("something hit a portal!\n");
								if ((b2BodyType)(contact->GetFixtureB()->GetBody()->GetType()) == dyn)
								{
										  Log("its a dynamic object\n");
//										  if (contains (ud, (const char *)"left") && p2)
										  if (contains (ud, (const char *)"left"))
										  {
													 p_dest = (char *)"p2";
													 p_obj = (b2Body *)(contact->GetFixtureA()->GetBody());
													 p_vel = (b2Vec2)(contact->GetFixtureA()->GetBody()->GetLinearVelocity());
										  }
//										  else if (contains (ud, (const char *)"right") && p1)
										  else if (contains (ud, (const char *)"right"))
										  {
													 p_dest = (char *)"p1";
													 p_obj = (b2Body *)(contact->GetFixtureA()->GetBody());
													 p_vel = (b2Vec2)(contact->GetFixtureA()->GetBody()->GetLinearVelocity());
										  }
								}
								else
								{
										  Log("not a dynamic object, don't portal\n");
								}
								p_contacting = 1;
					 }
		  }
		  ud = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
		  if (ud)
		  {
					 if (ud == (char *)"player")
					 {
								//								Log("Player hit something\n");
					 }
					 if (contains(ud, (const char *)"bullet"))
					 {
								//								Log("bullet hit something\n");
								//								Log("FixtureA's user data:\n\t%s\n", ((char *)(contact->GetFixtureA()->GetBody()->GetUserData())));
								//								Log("FixtureB's user data:\n\t%s\n", ((char *)(contact->GetFixtureB()->GetBody()->GetUserData())));
								if (contains(((char *)(contact->GetFixtureA()->GetBody()->GetUserData())), "portalable"))
								{
										  //										  Log("you shot a portalable object!\n");
										  pos = (b2Vec2)(contact->GetFixtureB()->GetBody()->GetWorldCenter());
										  norm = (b2Vec2)(contact->GetManifold()->localNormal);
										  angle = (float)(contact->GetFixtureA()->GetBody()->GetAngle());
										  if (contains(ud, (const char *)"left"))
										  {
													 //													 Log("storing left portal data with angle = %.2f\n", angle);
													 p_isleft = 1;
													 p1_dir = norm;
										  }
										  else
										  {
													 //													 Log("storing right portal data with angle = %.2f\n", angle);
													 p_isleft = 0;
													 p2_dir = norm;
										  }
										  p_pos = pos;
										  p_angle = angle;
								}
								else
								{
										  Log("that's not portalable\n");
								}
								toDestroy = (b2Body *)(contact->GetFixtureB()->GetBody());
					 }
					 else if (contains(ud, (const char *)"isportal") && !p_contacting)
					 {
								Log("something hit a portal!\n");
								if ((b2BodyType)(contact->GetFixtureA()->GetBody()->GetType()) == dyn)
								{
										  Log("its a dynamic object\n");
//										  if (contains (ud, (const char *)"left") && p2)
										  if (contains (ud, (const char *)"left"))
										  {
													 p_dest = (char *)"p2";
													 p_obj = (b2Body *)(contact->GetFixtureB()->GetBody());
													 p_vel = (b2Vec2)(contact->GetFixtureB()->GetBody()->GetLinearVelocity());
										  }
//										  else if (contains (ud, (const char *)"right") && p1)
										  else if (contains (ud, (const char *)"right"))
										  {
													 p_dest = (char *)"p1";
													 p_obj = (b2Body *)(contact->GetFixtureB()->GetBody());
													 p_vel = (b2Vec2)(contact->GetFixtureB()->GetBody()->GetLinearVelocity());
										  }
								}
								else
								{
										  Log("not a dynamic object, don't portal\n");
								}
								p_contacting = 1;
					 }
		  }
}

void contactListener::EndContact (b2Contact * contact)
{
		  char * ud;
		  ud = (char *)(contact->GetFixtureA()->GetBody()->GetUserData());
		  if (ud)
		  {
					 if (ud == (char *)"player")
					 {
								//								Log("Player hit something\n");
					 }
					 if (contains(ud, (const char *)"bullet"))
					 {
								//								Log("bullet hit something\n");
								toDestroy = (b2Body *)(contact->GetFixtureA()->GetBody());
					 }
					 if (contains(ud, (const char *)"isportal") && p_contacting)
					 {
								p_contacting = 0;
					 }
		  }
		  ud = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
		  if (ud)
		  {
					 if (ud == (char *)"player")
					 {
								//								Log("Player hit something\n");
					 }
					 if (contains(ud, (const char *)"bullet"))
					 {
								//								Log("bullet hit something\n");
								toDestroy = (b2Body *)(contact->GetFixtureB()->GetBody());
					 }
					 if (contains(ud, (const char *)"isportal") && p_contacting)
					 {
								p_contacting = 0;
					 }
		  }
}
