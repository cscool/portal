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
		  ud2 = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
		  b2Body * bodya = (b2Body *)(contact->GetFixtureA()->GetBody());
		  b2Body * bodyb = (b2Body *)(contact->GetFixtureB()->GetBody());
		  if (ud1)
		  {
					 if (contains(ud1, (const char *)"foot"))
					 {
								if (p_contacting)
								{
										  return;
								}
								//								Log("foot contacted something ( A ):\n");
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
								if ((b2BodyType)(contact->GetFixtureB()->GetBody()->GetType()) == kin)
								{
										  Log("started standing on a kinematic object\n");
										  fix_vel = 1;
								}
					 }
					 else if (contains(ud1, (const char *)"mine"))
					 {
								//								Log("mine hit something\n");
								if (ud2)
								{
										  if (bodyb->GetType() == dyn)
										  {
													 world->DestroyBody(bodya);
													 world->DestroyBody(bodyb);
										  }
								}
					 }
					 else if (contains(ud1, (const char *)"player"))
					 {
								if (p_contacting)
								{
										  return;
								}
								//								Log("Player hit something\n");
					 }
					 else if (contains(ud1, (const char *)"gun"))
					 {
								if (p_contacting)
								{
										  return;
								}
								// do nothing
					 }
					 else if (contains(ud1, (const char *)"bullet"))
					 {
								//								Log("bullet hit something\n");
								//								Log("FixtureA's user data:\n\t%s\n", ((char *)(contact->GetFixtureA()->GetBody()->GetUserData())));
								//								Log("FixtureB's user data:\n\t%s\n", ((char *)(contact->GetFixtureB()->GetBody()->GetUserData())));
								if (ud2)
								{
										  if (contains(ud2, (const char *)"portalable"))
										  {
													 //										  Log("you shot a portalable object!\n");
													 pos = (b2Vec2)(bodya->GetPosition());
													 norm = (b2Vec2)(contact->GetManifold()->localNormal);
													 if (!contains(ud2, (const char *)"floor"))
													 {
																angle = (float)(bodyb->GetAngle());
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
													 Log("creating portal\npos.y = %.2f\n", pos.y);
													 /*
													 if (fabs(pos.y) < (portal_height * P2M))
													 {
																Log("too low\npos.y = %.2f, portal_height * P2M = %.2f\n", pos.y, (portal_height * P2M));
																pos.y = pos.y - ((portal_height * P2M) - fabs(pos.y));
													 }
													 */
													 p_pos = pos;
													 p_angle = angle;
										  }
										  else
										  {
													 Log("that's not portalable\n");
										  }
								}
								else
								{
										  Log("that's not portalable\n");
								}
								toDestroy = bodya;
					 }
					 else if (contains(ud1, (const char *)"isportal") && !p_contacting)
					 {
								Log("something hit a portal!\n");
								if (p1 && p2)
								{
										  if ((b2BodyType)(bodyb->GetType()) == dyn)
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
													 p_obj = bodyb;
													 p_vel = (b2Vec2)(bodyb->GetLinearVelocity());
													 p_contacting = 1;
										  }
										  else
										  {
													 Log("not a dynamic object, don't portal\n");
										  }
								}
					 }
					 else if (contains(ud1, (const char *)"mine"))
					 {
								/* This collision should 'kill' the player, perhaps an explosion animation then destroy player, followed eventually by a splash screen? */
					 }
		  }
		  ud1 = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
		  ud2 = (char *)(contact->GetFixtureA()->GetBody()->GetUserData());
		  if (ud1)
		  {
					 if (contains(ud1, (const char *)"foot"))
					 {
								if (p_contacting)
								{
										  return;
								}
								Log("foot contacted something ( B ):\n");
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
								if ((b2BodyType)(bodya->GetType()) == kin)
								{
										  //										  Log("started standing on a kinematic object\n");
										  fix_vel = 2;
								}
					 }
					 else if (contains(ud1, (const char *)"player"))
					 {
								if (p_contacting)
								{
										  return;
								}
								//								Log("Player hit something\n");
					 }
					 else if (contains(ud1, (const char *)"mine"))
					 {
								if (p_contacting)
								{
										  return;
								}
								//								Log("mine hit something\n");
								if (ud2)
								{
										  if (bodyb->GetType() == dyn)
										  {
													 world->DestroyBody(bodya);
													 world->DestroyBody(bodyb);
										  }
								}
					 }
					 else if (contains(ud1, (const char *)"gun"))
					 {
								if (p_contacting)
								{
										  return;
								}
								// do nothing
					 }
					 else if (contains(ud1, (const char *)"bullet"))
					 {
								//								Log("bullet hit something\n");
								//								Log("FixtureA's user data:\n\t%s\n", ((char *)(contact->GetFixtureA()->GetBody()->GetUserData())));
								//								Log("FixtureB's user data:\n\t%s\n", ((char *)(contact->GetFixtureB()->GetBody()->GetUserData())));
								if (ud2)
								{
										  if (contains(ud2, "portalable"))
										  {
													 //										  Log("you shot a portalable object!\n");
													 pos = (b2Vec2)(bodyb->GetPosition());
													 Log("creating portal\npos.y = %.2f\n", pos.y);
													 norm = (b2Vec2)(contact->GetManifold()->localNormal);
													 if (!contains(ud2, (const char *)"floor"))
													 {
																angle = (float)(bodya->GetAngle());
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
													 /*
													 if (fabs(pos.y) < (portal_height * P2M))
													 {
																Log("too low\npos.y = %.2f, portal_height * P2M = %.2f\n", pos.y, (portal_height * P2M));
																pos.y = pos.y - ((portal_height * P2M) - fabs(pos.y));
													 }
													 */
													 p_pos = pos;
													 p_angle = angle;
										  }
										  else
										  {
													 Log("that's not portalable\n");
										  }
								}
								else
								{
										  Log("that's not portalable\n");
								}
								toDestroy = bodyb;
					 }
					 else if (contains(ud1, (const char *)"isportal") && !p_contacting)
					 {
								Log("something hit a portal!\n");
								if (p1 && p2)
								{
										  if ((b2BodyType)(bodya->GetType()) == dyn)
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
													 p_obj = bodya;
													 p_vel = (b2Vec2)(bodya->GetLinearVelocity());
													 p_contacting = 1;
										  }
										  else
										  {
													 Log("not a dynamic object, don't portal\n");
										  }
								}
					 }
					 else if (contains(ud1, (const char *)"mine"))
					 {
								/* This collision should 'kill' the player, perhaps an explosion animation then destroy player, followed eventually by a splash screen? */
					 }
		  }
		  if (fix_vel == 1)
		  {
					 Log("Fixing player velocity while on platform\n");
					 b2Vec2 v(bodyb->GetLinearVelocity().x, bodyb->GetLinearVelocity().y);
					 mod_vel = v;
		  }
		  else if (fix_vel == 2)
		  {
					 Log("Fixing player velocity while on platform\n");
					 b2Vec2 v(bodya->GetLinearVelocity().x, bodya->GetLinearVelocity().y);
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
		  ud2 = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
		  b2Body * bodya = (b2Body *)(contact->GetFixtureA()->GetBody());
		  b2Body * bodyb = (b2Body *)(contact->GetFixtureB()->GetBody());
		  if (ud1)
		  {
					 if (contains(ud1, (const char *)"player"))
					 {
								//								Log("Player hit something\n");
					 }
					 if (contains(ud1, (const char *)"bullet"))
					 {
								//								Log("bullet hit something\n");
								toDestroy = bodya;
					 }
					 if (contains(ud1, (const char *)"isportal") && p_contacting == 1)
					 {
								Log("something stopped hitting a portal\n");
								//								if (p_dest == (char *)"p1")
								//								{
								if (bodya == p1)
								{
										  if ((b2BodyType)(bodyb->GetType()) == dyn)
										  {
													 p_contacting = 0;
										  }
								}
								//								}
								//								else if (p_dest == (char *)"p2")
								//								{
								if (bodya == p2)
								{
										  if ((b2BodyType)(bodyb->GetType()) == dyn)
										  {
													 p_contacting = 0;
										  }
								}
								//								}
					 }
					 if (contains(ud1, (const char *)"foot"))
					 {
								Log("foot stopped contacting something ( A ):\n");
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
								if ((b2BodyType)(bodyb->GetType()) == kin)
								{
										  Log("stopped standing on a kinematic object\n");
										  fix_vel = 0;
								}
					 }
		  }
		  ud1 = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
		  ud2 = (char *)(contact->GetFixtureA()->GetBody()->GetUserData());
		  if (ud1)
		  {
					 if (contains(ud1, (const char *)"player"))
					 {
								//								Log("Player hit something\n");
					 }
					 if (contains(ud1, (const char *)"bullet"))
					 {
								//								Log("bullet hit something\n");
								toDestroy = bodyb;
					 }
					 if (contains(ud1, (const char *)"isportal") && p_contacting == 1)
					 {
								Log("something stopped hitting a portal\n");
								//								if (p_dest == (char *)"p1")
								//								{
								if (bodyb == p1)
								{
										  if ((b2BodyType)(bodya->GetType()) == dyn)
										  {
													 p_contacting = 0;
										  }
								}
								//								}
								//								else if (p_dest == (char *)"p2")
								//								{
								if (bodyb == p2)
								{
										  if ((b2BodyType)(bodya->GetType()) == dyn)
										  {
													 p_contacting = 0;
										  }
								}
								//								}
					 }
					 if (contains(ud1, (const char *)"foot"))
					 {
								Log("foot stopped contacting something ( B ):\n");
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
								if ((b2BodyType)(bodya->GetType()) == kin)
								{
										  Log("stopped standing on a kinematic object\n");
										  fix_vel = 0;
								}
					 }
		  }
}
