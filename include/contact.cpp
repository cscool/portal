#include "contact.h"

using namespace std;

void contactListener::BeginContact (b2Contact * contact)
{
		  char * ud1;
		  char * ud2;
		  b2Vec2 pos;
		  b2Vec2 norm;
		  float angle = 0.0f;
		  b2BodyType dyn = myPlayer->GetType();
		  b2BodyType kin = platform->GetType();
		  //		  b2BodyType stat = gameFloor->GetType();
		  ud1 = (char *)(contact->GetFixtureA()->GetBody()->GetUserData());
		  if (ud1)
		  {
					 if (contains(ud1, (const char *)"foot"))
					 {
								//								Log("foot contacted something ( A ):\n");
								ud2 = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
								if (ud2)
								{
										  //										  Log("\thit %s\n", ud2);
										  if (!(contains(ud2, (const char *)"player")) && !(contains(ud2, (const char *)"gun")))
										  {
													 if (!can_jump)
													 {
																toggle(can_jump);
													 }
										  }
								}
								else
								{
										  if (!can_jump)
										  {
													 toggle(can_jump);
										  }
								}
								/* HERE account for moving objects? */
								if ((b2BodyType)(contact->GetFixtureB()->GetBody()->GetType()) == kin)
								{
										  Log("started standing on a kinematic object\n");
										  fix_vel = 1;
								}
					 }
					 if (contains(ud1, (const char *)"player"))
					 {
								//								Log("Player hit something\n");
					 }
					 else if (contains(ud1, (const char *)"gun"))
					 {
								// do nothing
					 }
					 else if (contains(ud1, (const char *)"bullet"))
					 {
								//								Log("bullet hit something\n");
								//								Log("FixtureA's user data:\n\t%s\n", ((char *)(contact->GetFixtureA()->GetBody()->GetUserData())));
								//								Log("FixtureB's user data:\n\t%s\n", ((char *)(contact->GetFixtureB()->GetBody()->GetUserData())));
								ud2 = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
								if (ud2)
								{
										  if (contains(ud2, (const char *)"portalable"))
										  {
													 //										  Log("you shot a portalable object!\n");
													 pos = (b2Vec2)(contact->GetFixtureA()->GetBody()->GetPosition());
													 norm = (b2Vec2)(contact->GetManifold()->localNormal);
													 if (!contains(ud2, (const char *)"floor"))
													 {
																angle = (float)(contact->GetFixtureB()->GetBody()->GetAngle());
													 }
													 else
													 {
																angle = pi/2.0f;
													 }
													 if (contains(ud1, (const char *)"left"))
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
								else
								{
										  Log("that's not portalable\n");
								}
								toDestroy = (b2Body *)(contact->GetFixtureA()->GetBody());
					 }
					 else if (contains(ud1, (const char *)"isportal") && !p_contacting && p1 && p2)
					 {
								Log("something hit a portal!\n");
								if ((b2BodyType)(contact->GetFixtureB()->GetBody()->GetType()) == dyn)
								{
										  Log("its a dynamic object\n");
										  if (contains (ud1, (const char *)"left"))
										  {
													 p_dest = (char *)"p2";
										  }
										  else if (contains (ud1, (const char *)"right"))
										  {
													 p_dest = (char *)"p1";
										  }
										  p_obj = (b2Body *)(contact->GetFixtureB()->GetBody());
										  p_vel = (b2Vec2)(contact->GetFixtureB()->GetBody()->GetLinearVelocity());
								}
								else
								{
										  Log("not a dynamic object, don't portal\n");
								}
								p_contacting = 1;
					 }
		  }
		  ud1 = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
		  if (ud1)
		  {
					 if (contains(ud1, (const char *)"foot"))
					 {
								Log("foot contacted something ( B ):\n");
								ud2 = (char *)(contact->GetFixtureA()->GetBody()->GetUserData());
								if (ud2)
								{
										  Log("\thit %s\n", ud2);
										  if (!(contains(ud2, (const char *)"player")) && !(contains(ud2, (const char *)"gun")))
										  {
													 if (!can_jump)
													 {
																toggle(can_jump);
													 }
										  }
								}
								else
								{
										  if (!can_jump)
										  {
													 toggle(can_jump);
										  }
								}
								if ((b2BodyType)(contact->GetFixtureA()->GetBody()->GetType()) == kin)
								{
										  Log("started standing on a kinematic object\n");
										  fix_vel = 2;
								}
					 }
					 if (contains(ud1, (const char *)"player"))
					 {
								//								Log("Player hit something\n");
					 }
					 else if (contains(ud1, (const char *)"gun"))
					 {
								// do nothing
					 }
					 else if (contains(ud1, (const char *)"bullet"))
					 {
								//								Log("bullet hit something\n");
								//								Log("FixtureA's user data:\n\t%s\n", ((char *)(contact->GetFixtureA()->GetBody()->GetUserData())));
								//								Log("FixtureB's user data:\n\t%s\n", ((char *)(contact->GetFixtureB()->GetBody()->GetUserData())));
								ud2 = (char *)(contact->GetFixtureA()->GetBody()->GetUserData());
								if (ud2)
								{
										  if (contains(ud2, "portalable"))
										  {
													 //										  Log("you shot a portalable object!\n");
													 pos = (b2Vec2)(contact->GetFixtureB()->GetBody()->GetPosition());
													 norm = (b2Vec2)(contact->GetManifold()->localNormal);
													 if (!contains(ud2, (const char *)"floor"))
													 {
																angle = (float)(contact->GetFixtureA()->GetBody()->GetAngle());
													 }
													 else
													 {
																angle = pi/2.0f;
													 }
													 if (contains(ud1, (const char *)"left"))
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
								else
								{
										  Log("that's not portalable\n");
								}
								toDestroy = (b2Body *)(contact->GetFixtureB()->GetBody());
					 }
					 else if (contains(ud1, (const char *)"isportal") && !p_contacting && p1 && p2)
					 {
								Log("something hit a portal!\n");
								if ((b2BodyType)(contact->GetFixtureA()->GetBody()->GetType()) == dyn)
								{
										  Log("its a dynamic object\n");
										  if (contains (ud1, (const char *)"left"))
										  {
													 p_dest = (char *)"p2";
										  }
										  else if (contains (ud1, (const char *)"right"))
										  {
													 p_dest = (char *)"p1";
										  }
										  p_obj = (b2Body *)(contact->GetFixtureA()->GetBody());
										  p_vel = (b2Vec2)(contact->GetFixtureA()->GetBody()->GetLinearVelocity());

										  p_contacting = 1;
								}
								else
								{
										  Log("not a dynamic object, don't portal\n");
								}
					 }
		  }
		  if (fix_vel == 1)
		  {
					 Log("Fixing player velocity while on platform\n");
					 b2Vec2 v(contact->GetFixtureB()->GetBody()->GetLinearVelocity().x, contact->GetFixtureB()->GetBody()->GetLinearVelocity().y);
					 mod_vel = v;
		  }
		  else if (fix_vel == 2)
		  {
					 Log("Fixing player velocity while on platform\n");
					 b2Vec2 v(contact->GetFixtureA()->GetBody()->GetLinearVelocity().x, contact->GetFixtureA()->GetBody()->GetLinearVelocity().y);
					 mod_vel = v;
		  }
}

void contactListener::EndContact (b2Contact * contact)
{
		  b2BodyType dyn = myPlayer->GetType();
		  b2BodyType kin = platform->GetType();
		  char * ud1;
		  char * ud2;
		  ud1 = (char *)(contact->GetFixtureA()->GetBody()->GetUserData());
		  if (ud1)
		  {
					 if (contains(ud1, (const char *)"player"))
					 {
								//								Log("Player hit something\n");
					 }
					 if (contains(ud1, (const char *)"bullet"))
					 {
								//								Log("bullet hit something\n");
								toDestroy = (b2Body *)(contact->GetFixtureA()->GetBody());
					 }
					 if (contains(ud1, (const char *)"isportal") && p_contacting)
					 {
								if ((b2BodyType)(contact->GetFixtureB()->GetBody()->GetType()) == dyn)
								{
										  p_contacting = 0;
								}
					 }
					 if (contains(ud1, (const char *)"foot"))
					 {
								Log("foot stopped contacting something ( A ):\n");
								ud2 = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
								if (ud2)
								{
										  Log("\tstopped hitting %s\n", ud2);
										  if (!(contains(ud2, (const char *)"player")) && !(contains(ud2, (const char *)"gun")))
										  {
													 if (can_jump)
													 {
																toggle(can_jump);
													 }
										  }
								}
								else
								{
										  if (can_jump)
										  {
													 toggle(can_jump);
										  }
								}
								if ((b2BodyType)(contact->GetFixtureB()->GetBody()->GetType()) == kin)
								{
										  Log("stopped standing on a kinematic object\n");
										  fix_vel = 0;
								}
					 }
		  }
		  ud1 = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
		  if (ud1)
		  {
					 if (contains(ud1, (const char *)"player"))
					 {
								//								Log("Player hit something\n");
					 }
					 if (contains(ud1, (const char *)"bullet"))
					 {
								//								Log("bullet hit something\n");
								toDestroy = (b2Body *)(contact->GetFixtureB()->GetBody());
					 }
					 if (contains(ud1, (const char *)"isportal") && p_contacting)
					 {
								if ((b2BodyType)(contact->GetFixtureA()->GetBody()->GetType()) == dyn)
								{
										  p_contacting = 0;
								}
					 }
					 if (contains(ud1, (const char *)"foot"))
					 {
								Log("foot stopped contacting something ( B ):\n");
								ud2 = (char *)(contact->GetFixtureA()->GetBody()->GetUserData());
								if (ud2)
								{
										  Log("\tstopped hitting %s\n", ud2);
										  if (!(contains(ud2, (const char *)"player")) && !(contains(ud2, (const char *)"gun")))
										  {
													 if (can_jump)
													 {
																toggle(can_jump);
													 }
										  }
								}
								else
								{
										  if (can_jump)
										  {
													 toggle(can_jump);
										  }
								}
								if ((b2BodyType)(contact->GetFixtureA()->GetBody()->GetType()) == kin)
								{
										  Log("stopped standing on a kinematic object\n");
										  fix_vel = 0;
								}
					 }
		  }
}
