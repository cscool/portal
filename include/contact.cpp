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
		  b2BodyType stat = gameFloor->GetType();
		  ud1 = (char *)(contact->GetFixtureA()->GetBody()->GetUserData());
		  ud2 = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
		  b2Body * bodya = (b2Body *)(contact->GetFixtureA()->GetBody());
		  b2Body * bodyb = (b2Body *)(contact->GetFixtureB()->GetBody());
		  if (ud1)
		  {
					 if (contains(ud1, (const char *)"foot"))
					 {
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
					 if (contains(ud1, (const char *)"mine"))
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
					 if (contains(ud1, (const char *)"player"))
					 {
								Log("player hit something\n");
								b2ContactEdge * contact = myPlayer->GetContactList();
								b2BodyType t;
								int c_count = 0;
								int kin_count = 0;
								int stat_count = 0;
								int dyn_count = 0;
								char * cdata = NULL;
								while (contact)
								{
										  t = contact->other->GetType();
										  if (t == dyn)
										  {
													 dyn_count++;
										  }
										  else if (t == stat)
										  {
													 stat_count++;
										  }
										  else if (t == kin)
										  {
													 kin_count++;
										  }
										  c_count++;
										  Log("contact edge %d, hitting?\n", c_count);
										  cdata = (char *)(contact->other->GetUserData());
										  if (cdata)
										  {
													 Log("\t%s\n", cdata);
										  }
										  else
										  {
													 Log("\tNo user data found\n");
										  }
										  contact = contact->next;
								}
								Log("static object count: %d\n", stat_count);
								Log("dynamic object count: %d\n", dyn_count);
								Log("kinematic object count: %d\n", kin_count);
								if (c_count > 1)
								{
										  Log("contact edge count = %d\n", c_count);
								}
					 }
					 if (contains(ud1, (const char *)"gun"))
					 {
								// do nothing
					 }
					 if (contains(ud1, (const char *)"bullet"))
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
					 if (contains(ud1, (const char *)"isportal") && !p1_contacting && !p2_contacting)
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
																p1_contacting = 1;
													 }
													 else if (contains (ud1, (const char *)"right"))
													 {
																p_dest = (char *)"p1";
																p2_contacting = 1;
													 }
													 p_obj = bodyb;
													 p_vel = (b2Vec2)(bodyb->GetLinearVelocity());
										  }
										  else
										  {
													 Log("not a dynamic object, don't portal\n");
										  }
								}
					 }
					 if (contains(ud1, (const char *)"mine"))
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
					 if (contains(ud1, (const char *)"player"))
					 {
								Log("player hit something\n");
								b2ContactEdge * contact = myPlayer->GetContactList();
								b2Body * c1;
								b2Body * c2;
								b2Body * c3;
								b2Body * c4;
								b2Body * d1;
								b2Body * d2;
								b2Body * d3;
								b2Body * d4;
								b2Body * s1;
								b2Body * s2;
								b2Body * s3;
								b2Body * s4;
								b2Body * k1;
								b2Body * k2;
								b2Body * k3;
								b2Body * k4;
								int c_count = 0;
								int kin_count = 0;
								int stat_count = 0;
								int dyn_count = 0;
								char * cdata = NULL;
								b2BodyType t;
								while (contact)
								{
										  c_count++;
										  Log("contact edge %d, hitting?\n", c_count);
										  switch (c_count)
										  {
													 case 1:
																c1 = contact->other;
																t = c1->GetType();
																if (t == dyn)
																{
																		  dyn_count++;
																		  switch (dyn_count)
																		  {
																					 case 1:
																								d1 = c1;
																								break;
																					 case 2:
																								d2 = c1;
																								break;
																					 case 3:
																								d3 = c1;
																								break;
																					 case 4:
																								d4 = c1;
																								break;
																		  }
																}
																else if (t == stat)
																{
																		  stat_count++;
																		  switch (stat_count)
																		  {
																					 case 1:
																								s1 = c1;
																								break;
																					 case 2:
																								s2 = c1;
																								break;
																					 case 3:
																								s3 = c1;
																								break;
																					 case 4:
																								s4 = c1;
																								break;
																		  }
																}
																else if (t == kin)
																{
																		  kin_count++;
																		  switch (kin_count)
																		  {
																					 case 1:
																								k1 = c1;
																								break;
																					 case 2:
																								k2 = c1;
																								break;
																					 case 3:
																								k3 = c1;
																								break;
																					 case 4:
																								k4 = c1;
																								break;
																		  }
																}
																break;
													 case 2:
																c2 = contact->other;
																t = c2->GetType();
																if (t == dyn)
																{
																		  dyn_count++;
																		  switch (dyn_count)
																		  {
																					 case 1:
																								d1 = c2;
																								break;
																					 case 2:
																								d2 = c2;
																								break;
																					 case 3:
																								d3 = c2;
																								break;
																					 case 4:
																								d4 = c2;
																								break;
																		  }
																}
																else if (t == stat)
																{
																		  stat_count++;
																		  switch (stat_count)
																		  {
																					 case 1:
																								s1 = c2;
																								break;
																					 case 2:
																								s2 = c2;
																								break;
																					 case 3:
																								s3 = c2;
																								break;
																					 case 4:
																								s4 = c2;
																								break;
																		  }
																}
																else if (t == kin)
																{
																		  kin_count++;
																		  switch (kin_count)
																		  {
																					 case 1:
																								k1 = c2;
																								break;
																					 case 2:
																								k2 = c2;
																								break;
																					 case 3:
																								k3 = c2;
																								break;
																					 case 4:
																								k4 = c2;
																								break;
																		  }
																}
																break;
													 case 3:
																c3 = contact->other;
																t = c3->GetType();
																if (t == dyn)
																{
																		  dyn_count++;
																		  switch (dyn_count)
																		  {
																					 case 1:
																								d1 = c3;
																								break;
																					 case 2:
																								d2 = c3;
																								break;
																					 case 3:
																								d3 = c3;
																								break;
																					 case 4:
																								d4 = c3;
																								break;
																		  }
																}
																else if (t == stat)
																{
																		  stat_count++;
																		  switch (stat_count)
																		  {
																					 case 1:
																								s1 = c3;
																								break;
																					 case 2:
																								s2 = c3;
																								break;
																					 case 3:
																								s3 = c3;
																								break;
																					 case 4:
																								s4 = c3;
																								break;
																		  }
																}
																else if (t == kin)
																{
																		  kin_count++;
																		  switch (kin_count)
																		  {
																					 case 1:
																								k1 = c3;
																								break;
																					 case 2:
																								k2 = c3;
																								break;
																					 case 3:
																								k3 = c3;
																								break;
																					 case 4:
																								k4 = c3;
																								break;
																		  }
																}
																break;
													 case 4:
																c4 = contact->other;
																t = c4->GetType();
																if (t == dyn)
																{
																		  dyn_count++;
																		  switch (dyn_count)
																		  {
																					 case 1:
																								d1 = c4;
																								break;
																					 case 2:
																								d2 = c4;
																								break;
																					 case 3:
																								d3 = c4;
																								break;
																					 case 4:
																								d4 = c4;
																								break;
																		  }
																}
																else if (t == stat)
																{
																		  stat_count++;
																		  switch (stat_count)
																		  {
																					 case 1:
																								s1 = c4;
																								break;
																					 case 2:
																								s2 = c4;
																								break;
																					 case 3:
																								s3 = c4;
																								break;
																					 case 4:
																								s4 = c4;
																								break;
																		  }
																}
																else if (t == kin)
																{
																		  kin_count++;
																		  switch (kin_count)
																		  {
																					 case 1:
																								k1 = c4;
																								break;
																					 case 2:
																								k2 = c4;
																								break;
																					 case 3:
																								k3 = c4;
																								break;
																					 case 4:
																								k4 = c4;
																								break;
																		  }
																}
																break;
										  }
										  cdata = (char *)(contact->other->GetUserData());
										  if (cdata)
										  {
													 Log("\t%s\n", cdata);
										  }
										  else
										  {
													 Log("\tNo user data found\n");
										  }
										  contact = contact->next;
								}
								Log("static object count: %d\n", stat_count);
								Log("dynamic object count: %d\n", dyn_count);
								Log("kinematic object count: %d\n", kin_count);
								if (c_count > 1 && kin_count > 0)
								{
										  Log("contact edge count = %d\n", c_count);
										  if (kin_count > 2)
										  {
													 Log("definitely dead\n");
													 toDestroy = myPlayer;
													 return; // special case
										  }
										  if (kin_count > 1 && stat_count > 1)
										  {
										  }
								}
					 }
					 if (contains(ud1, (const char *)"mine"))
					 {
								Log("mine hit something\n");
								if (bodyb->GetType() == dyn)
								{
										  world->DestroyBody(bodya);
										  world->DestroyBody(bodyb);
								}
					 }
					 if (contains(ud1, (const char *)"gun"))
					 {
								// do nothing
					 }
					 if (contains(ud1, (const char *)"bullet"))
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
					 if (contains(ud1, (const char *)"isportal") && !p1_contacting && !p2_contacting)
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
																p1_contacting = 1;
													 }
													 else if (contains (ud1, (const char *)"right"))
													 {
																p_dest = (char *)"p1";
																p2_contacting = 1;
													 }
													 p_obj = bodya;
													 p_vel = (b2Vec2)(bodya->GetLinearVelocity());
										  }
										  else
										  {
													 Log("not a dynamic object, don't portal\n");
										  }
								}
					 }
					 if (contains(ud1, (const char *)"mine"))
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
		  b2BodyType stat = gameFloor->GetType();
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
					 if (contains(ud1, (const char *)"isportal"))
					 {
								Log("something stopped hitting a portal\n");
								if (contains(ud1, (const char *)"left"))
								{
										  Log("something stopped hitting p1\n");
										  if (p2_contacting == 1)
										  {
													 p2_contacting = 0;
										  }
								}
								if (contains(ud1, (const char *)"right"))
								{
										  Log("something stopped hitting p2\n");
										  if (p1_contacting == 1)
										  {
													 p1_contacting = 0;
										  }
								}
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
					 if (contains(ud1, (const char *)"isportal"))
					 {
								Log("something stopped hitting a portal\n");
								if (contains(ud1, (const char *)"left"))
								{
										  Log("something stopped hitting p1\n");
										  if (p2_contacting == 1)
										  {
													 p2_contacting = 0;
										  }
								}
								if (contains(ud1, (const char *)"right"))
								{
										  Log("something stopped hitting p2\n");
										  if (p1_contacting == 1)
										  {
													 p1_contacting = 0;
										  }
								}
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
