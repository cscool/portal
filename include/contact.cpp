#include "contact.h"

using namespace std;

const static float C_THRESHOLD = 5000.0f;
const static b2BodyType dyn = b2_dynamicBody;
const static b2BodyType kin = b2_kinematicBody;
const static b2BodyType stat = b2_staticBody;

void contactListener::BeginContact (b2Contact * contact)
{
		  char * ud1;
		  char * ud2;
		  b2Vec2 pos;
		  b2Vec2 norm;
		  float angle = 0.0f;
		  ud1 = (char *)(contact->GetFixtureA()->GetBody()->GetUserData());
		  ud2 = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
		  b2Body * bodya = (b2Body *)(contact->GetFixtureA()->GetBody());
		  b2Body * bodyb = (b2Body *)(contact->GetFixtureB()->GetBody());
//		  bool good = true;
//		  int dir = 1;
		  if (ud1)
		  {
					 if (contains(ud1, (const char *)"end"))
					 {
								if (contains(ud2, (const char *)"player") || contains(ud2, (const char *)"gun"))
								{
										  level_complete = true;
								}
								if (contains(ud2, (const char *)"bullet"))
								{
										  toDestroy = bodyb;
								}
					 }
					 if (contains(ud1, (const char *)"button"))
					 {
								//			Log("someone hit the button\n");
								if ((b2BodyType)(bodyb->GetType()) == dyn)
								{
										  //					  Log("\tit was a dynamic object\n");
										  for(int i = 0; i < 5; i++)
										  {
													 if (buttons[i].button)
													 {
																if (buttons[i].button == bodya)
																{
																		  buttons[i].pressed = 1;
																		  if (doors[i].door)
																		  {
																					 doors[i].active = 1;
																		  }
																		  i = 5;
																}
													 }
										  }
								}
					 }
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
								if ((b2BodyType)(bodyb->GetType()) == kin)
								{
										  //					  Log("started standing on a kinematic object\n");
										  fix_vel = 2;
								}
					 }
					 if (contains(ud1, (const char *)"deadly"))
					 {
								if (contains(ud1, (const char *)"mine"))
								{
										  //								Log("mine hit something\n");
										  if (bodyb->GetType() == dyn)
										  {
													 if (ud2)
													 {
																if (contains(ud2, (const char *)"foot"))
																{
																		  Log("foot hit mine, ignore\n");
																}
																if (contains(ud2, (const char *)"gun") || contains(ud2, (const char *)"player"))
																{
																		  Log("\tplayer death\n");
																		  detonate(myPlayer, bodya);
																}
																else if (!contains(ud2, (const char *)"bullet"))
																{
																		  detonate(bodya, bodyb);
																}
													 }
													 else
													 {
																detonate(bodya, bodyb);
													 }
										  }
								}
								else
								{
										  if (bodyb->GetType() == dyn)
										  {
													 if (ud2)
													 {
																if (contains(ud2, (const char *)"gun") || contains(ud2, (const char *)"player") || contains(ud2, (const char *)"foot"))
																{
																		  Log("\tplayer death\n");
																		  detonate(myPlayer, bodya);
																}
													 }
										  }
								}
					 }
					 if (contains(ud1, (const char *)"player"))
					 {
								//								Log("player hit something\n");
								if (ud2)
								{
										  if (contains(ud2, (const char *)"mine"))
										  {
													 // do nothing
										  }
										  else
										  {
													 b2ContactEdge * edges = myPlayer->GetContactList();
													 b2Vec2 normals[4];
													 int c_count = 0;
													 char * cdata = NULL;
													 while (edges && c_count < 4)
													 {
																//																Log("contact edge %d, hitting?\n", c_count);
																normals[c_count] = contact->GetManifold()->localNormal;
																cdata = (char *)(bodyb->GetUserData());
																if (cdata)
																{
																		  //																		  Log("\t%s\n", cdata);
																}
																else
																{
																		  //																		  Log("\tNo user data found\n");
																}
																edges = edges->next;
																c_count++;
													 }
										  }
								}
								else
								{
										  b2ContactEdge * edges = myPlayer->GetContactList();
										  b2Vec2 normals[4];
										  int c_count = 0;
										  char * cdata = NULL;
										  while (edges && c_count < 4)
										  {
													 //													 Log("contact edge %d, hitting?\n", c_count);
													 normals[c_count] = contact->GetManifold()->localNormal;
													 cdata = (char *)(bodyb->GetUserData());
													 if (cdata)
													 {
																//																Log("\t%s\n", cdata);
													 }
													 else
													 {
																//																Log("\tNo user data found\n");
													 }
													 edges = edges->next;
													 c_count++;
										  }
								}
					 }
					 if (contains(ud1, (const char *)"bullet"))
					 {
								if (contains(ud1, (const char *)"left") || contains(ud1, (const char *)"right"))
								{
//										  good = true;
										  //								Log("bullet hit something\n");
										  //								Log("FixtureA's user data:\n\t%s\n", ((char *)(contact->GetFixtureA()->GetBody()->GetUserData())));
										  //								Log("FixtureB's user data:\n\t%s\n", ((char *)(contact->GetFixtureB()->GetBody()->GetUserData())));
										  if (ud2)
										  {
													 if (contains(ud2, (const char *)"portalable"))
													 {
//																b2Vec2 body_pos = bodyb->GetPosition();
//																float body_height = getHeight(bodyb);
//																float portal_space = 1.3*portal_height*P2M;
																//										  Log("you shot a portalable object!\n");
																pos = (b2Vec2)(bodya->GetPosition());
																norm = (b2Vec2)(contact->GetManifold()->localNormal);
																if (!contains(ud2, (const char *)"floor") && !contains(ud2, (const char *)"ceiling"))
																{
																		  angle = (float)(bodyb->GetAngle());
																		  //																Log("pos.y = %.2f\npos.y*M2P = %.2f\nportal_height = %.2f\nonFloor = %.2f\n", pos.y, pos.y*M2P, portal_height, onFloor);
																		  //																Log("pos.y*M2P + portal_height = %.2f, >= onFloor - 50?\n", (pos.y*M2P + portal_height));
																}
																else
																{
																		  angle = pi/2.0f;
																}
																if (contains(ud1, (const char *)"left"))
																{
																		  //													 Log("storing left portal data with angle = %.2f\n", angle);
																		  p_isleft = 1;
																		  Log("angle = %.2f\n", angle);
																		  p1_in_contact = ud2;
																}
																else
																{
																		  //													 Log("storing right portal data with angle = %.2f\n", angle);
																		  p_isleft = 0;
																		  Log("angle = %.2f\n", angle);
																		  p2_in_contact = ud2;
																}
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
													 Log("its a dynamic object\nhas velocity <%.2f, %.2f>", bodyb->GetLinearVelocity().x, bodyb->GetLinearVelocity().y);
													 Log("\tp_vel = <%.2f, %.2f>", p_vel.x, p_vel.y);
													 Log("\tp2_vel = <%.2f, %.2f>", p2_vel.x, p2_vel.y);
													 Log("\tp3_vel = <%.2f, %.2f>", p3_vel.x, p3_vel.y);
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
		  }
		  ud1 = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
		  ud2 = (char *)(contact->GetFixtureA()->GetBody()->GetUserData());
		  if (ud1)
		  {
					 if (contains(ud1, (const char *)"end"))
					 {
								if (contains(ud2, (const char *)"player") || contains(ud2, (const char *)"gun"))
								{
										  level_complete = true;
								}
								if (contains(ud2, (const char *)"bullet"))
								{
										  toDestroy = bodya;
								}
					 }
					 if (contains(ud1, (const char *)"button"))
					 {
								Log("someone hit the button\n");
								if ((b2BodyType)(bodya->GetType()) == dyn)
								{
										  for(int i = 0; i < 5; i++)
										  {
													 if (buttons[i].button)
													 {
																if (buttons[i].button == bodyb)
																{
																		  buttons[i].pressed = 1;
																		  if (doors[i].door)
																		  {
																					 doors[i].active = 1;
																		  }
																		  i = 5;
																}
													 }
										  }
										  Log("\tit was a dynamic object\n");
								}
					 }
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
					 if (contains(ud1, (const char *)"deadly"))
					 {
								if (contains(ud1, (const char *)"mine"))
								{
										  Log("mine hit something\n");
										  if (bodya->GetType() == dyn)
										  {
													 if (ud2)
													 {
																if (contains(ud2, (const char *)"foot"))
																{
																		  Log("foot hit mine, ignore\n");
																}
																if (contains(ud2, (const char *)"gun") || contains(ud2, (const char *)"player"))
																{
																		  Log("\tplayer death\n");
																		  detonate(myPlayer, bodyb);
																}
																else if (!contains(ud2, (const char *)"bullet"))
																{
																		  detonate(bodya, bodyb);
																}
													 }
													 else
													 {
																detonate(bodya, bodyb);
													 }
										  }
								}
								else
								{
										  if (ud2)
										  {
													 if (contains(ud2, (const char *)"gun") || contains(ud2, (const char *)"player") || contains(ud2, (const char *)"foot"))
													 {
																Log("\tplayer death\n");
																detonate(myPlayer, bodya);
													 }
										  }
								}
					 }
					 if (contains(ud1, (const char *)"player"))
					 {
								Log("player hit something\n");
								if (ud2)
								{
										  if (contains(ud2, (const char *)"mine"))
										  {
													 // do nothing
										  }
										  else
										  {
													 b2ContactEdge * edges = myPlayer->GetContactList();
													 b2Vec2 normals[4];
													 int c_count = 0;
													 int pt_ct = 0;
													 char * cdata = NULL;
													 while (edges && c_count < 4)
													 {
																normals[c_count] = contact->GetManifold()->localNormal;
																pt_ct = contact->GetManifold()->pointCount;
																Log("this contact has %d points touching\n", pt_ct);
																for (int i = 0; i < pt_ct; i++)
																{
																		  Log("\t%.4f\n", contact->GetManifold()->points[i].normalImpulse);
																}
																Log("contact edge %d, hitting?\n", c_count + 1);
																cdata = (char *)(bodyb->GetUserData());
																if (cdata)
																{
																		  Log("\t%s\n", cdata);
																}
																else
																{
																		  Log("\tNo user data found\n");
																}
																edges = edges->next;
																c_count++;
													 }
										  }
								}
								else
								{
										  b2ContactEdge * edges = myPlayer->GetContactList();
										  b2Vec2 normals[4];
										  int c_count = 0;
										  int pt_ct = 0;
										  char * cdata = NULL;
										  while (edges && c_count < 4)
										  {
													 normals[c_count] = contact->GetManifold()->localNormal;
													 pt_ct = contact->GetManifold()->pointCount;
													 Log("this contact has %d points touching\n", pt_ct);
													 for (int i = 0; i < pt_ct; i++)
													 {
																Log("\t%.4f\n", contact->GetManifold()->points[i].normalImpulse);
													 }
													 Log("contact edge %d, hitting?\n", c_count + 1);
													 cdata = (char *)(bodyb->GetUserData());
													 if (cdata)
													 {
																Log("\t%s\n", cdata);
													 }
													 else
													 {
																Log("\tNo user data found\n");
													 }
													 edges = edges->next;
													 c_count++;
										  }
								}
					 }
					 if (contains(ud1, (const char *)"bullet"))
					 {
								if (contains(ud1, (const char *)"left") || contains(ud1, (const char *)"right"))
								{
//										  good = true;
										  //								Log("bullet hit something\n");
										  //								Log("FixtureA's user data:\n\t%s\n", ((char *)(contact->GetFixtureA()->GetBody()->GetUserData())));
										  //								Log("FixtureB's user data:\n\t%s\n", ((char *)(contact->GetFixtureB()->GetBody()->GetUserData())));
										  if (ud2)
										  {
													 if (contains(ud2, "portalable"))
													 {
																//										  Log("you shot a portalable object!\n");
																pos = (b2Vec2)(bodyb->GetPosition());
																norm = (b2Vec2)(contact->GetManifold()->localNormal);
																if (!contains(ud2, (const char *)"floor") && !contains(ud2, (const char *)"ceiling"))
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
																		  Log("angle = %.2f\n", angle);
																		  p1_in_contact = ud2;
																}
																else
																{
																		  //													 Log("storing right portal data with angle = %.2f\n", angle);
																		  p_isleft = 0;
																		  Log("angle = %.2f\n", angle);
																		  p2_in_contact = ud2;
																}
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
													 Log("its a dynamic object\nhas velocity <%.2f, %.2f>", bodyb->GetLinearVelocity().x, bodyb->GetLinearVelocity().y);
													 Log("\tp_vel = <%.2f, %.2f>", p_vel.x, p_vel.y);
													 Log("\tp2_vel = <%.2f, %.2f>", p2_vel.x, p2_vel.y);
													 Log("\tp3_vel = <%.2f, %.2f>", p3_vel.x, p3_vel.y);
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
		  }
}

void contactListener::EndContact (b2Contact * contact)
{
		  char * ud1;
		  char * ud2;
		  ud1 = (char *)(contact->GetFixtureA()->GetBody()->GetUserData());
		  ud2 = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
		  b2Body * bodya = (b2Body *)(contact->GetFixtureA()->GetBody());
		  b2Body * bodyb = (b2Body *)(contact->GetFixtureB()->GetBody());
		  if (ud1)
		  {
					 if (contains(ud1, (const char *)"button"))
					 {
								Log("something stopped hitting the button\n");
								if ((b2BodyType)(bodyb->GetType()) == dyn)
								{
										  //										  Log("\tit was a dynamic object\n");
										  for(int i = 0; i < 5; i++)
										  {
													 if (buttons[i].button)
													 {
																if (buttons[i].button == bodya)
																{
																		  buttons[i].pressed = 0;
																		  if (doors[i].door)
																		  {
																					 doors[i].active = 0;
																		  }
																		  i = 5;
																}
													 }
										  }
								}
					 }
					 if (contains(ud1, (const char *)"player"))
					 {
								//								Log("Player hit something\n");
					 }
					 if (contains(ud1, (const char *)"bullet"))
					 {
								//								Log("bullet hit something\n");
								if (ud2)
								{
										  if (!contains(ud2, (const char *)"player") && !contains(ud2, (const char *)"gun") && !contains(ud2, (const char *)"foot"))
										  {
													 toDestroy = bodya;
										  }
								}
								else
								{
										  toDestroy = bodya;
								}
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
					 if (contains(ud1, (const char *)"button"))
					 {
								Log("something stopped hitting the button\n");
								if ((b2BodyType)(bodya->GetType()) == dyn)
								{
										  for(int i = 0; i < 5; i++)
										  {
													 if (buttons[i].button)
													 {
																if (buttons[i].button == bodyb)
																{
																		  buttons[i].pressed = 0;
																		  if (doors[i].door)
																		  {
																					 doors[i].active = 0;
																		  }
																		  i = 5;
																}
													 }
										  }
								}
					 }
					 if (contains(ud1, (const char *)"player"))
					 {
								//								Log("Player hit something\n");
					 }
					 if (contains(ud1, (const char *)"bullet"))
					 {
								//								Log("bullet hit something\n");
								if (ud2)
								{
										  if (!contains(ud2, (const char *)"player") && !contains(ud2, (const char *)"gun") && !contains(ud2, (const char *)"foot"))
										  {
													 toDestroy = bodyb;
										  }
								}
								else
								{
										  toDestroy = bodyb;
								}
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

void contactListener::PostSolve(b2Contact* contact/*, const b2ContactImpulse* impulse*/)
{ /* handle post-solve event */ 
		  int pt_ct = contact->GetManifold()->pointCount;
		  //		  Log("\nin post solve\nthis contact has %d points touching\n", pt_ct);
		  b2Body * bodya = contact->GetFixtureA()->GetBody();
		  b2Body * bodyb = contact->GetFixtureB()->GetBody();
		  char * ud1 = (char *)(contact->GetFixtureA()->GetBody()->GetUserData());
		  char * ud2 = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
		  if (ud1 && (contains(ud1, (const char *)"isportal")))
		  {
					 Log("in post solve contact handler, something hit a portal with velocity <%.2f, %.2f>\n", bodya->GetLinearVelocity().x, bodya->GetLinearVelocity().y);
		  }
		  if (ud2 && (contains(ud2, (const char *)"isportal")))
		  {
					 Log("in post solve contact handler, something hit a portal with velocity <%.2f, %.2f>\n", bodyb->GetLinearVelocity().x, bodyb->GetLinearVelocity().y);
		  }
		  for (int i = 0; i < pt_ct; i++)
		  {
					 Log("\t%.4f\n", contact->GetManifold()->points[i].normalImpulse);
					 if (contact->GetManifold()->points[i].normalImpulse > C_THRESHOLD)
					 {
								//								Log("its kill the following thing!\n");
								if (bodya->GetType() == b2_dynamicBody && (bodyb->GetType() == b2_staticBody || bodyb->GetType() == b2_kinematicBody))
								{
										  //										  Log("***default case 1\n");
										  toDestroy = bodya;
								}
								else if (bodyb->GetType() == b2_dynamicBody && (bodya->GetType() == b2_staticBody || bodya->GetType() == b2_kinematicBody))
								{
										  //										  Log("***default case 2\n");
										  toDestroy = bodyb;
								}
								else if (bodya->GetType() == b2_dynamicBody && bodyb->GetType() == b2_dynamicBody)
								{
										  if (ud1 && !ud2)
										  {
													 toDestroy = bodyb;
										  }
										  else if (ud2 && !ud1)
										  {
													 toDestroy = bodya;
										  }
										  else if (contains(ud1, (char *)"box"))
										  {
													 toDestroy = bodya;
										  }
										  else if (contains(ud2, (char *)"box"))
										  {
													 toDestroy = bodyb;
										  }
										  else if (contains(ud1, (char *)"cube"))
										  {
													 toDestroy = bodya;
										  }
										  else if (contains(ud2, (char *)"cube"))
										  {
													 toDestroy = bodyb;
										  }
								}
					 }
		  }
		  if (ud1)
		  {
					 //					 Log("user data for body a: %s\n\n", ud1);
		  }
		  else
		  {
					 //					 Log("no user data for body a\n\n");
		  }
		  if (ud2)
		  {
					 //					 Log("user data for body b: %s\n\n", ud2);
		  }
		  else
		  {
					 //					 Log("no user data for body b\n\n");
		  }
}
