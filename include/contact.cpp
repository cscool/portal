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
		  bool good = true;
		  int dir = 1;
		  if (ud1)
		  {
					 if (contains(ud1, (const char *)"button"))
					 {
								//			Log("someone hit the button\n");
								if ((b2BodyType)(bodyb->GetType()) == dyn)
								{
										  //					  Log("\tit was a dynamic object\n");
										  door_is_active = 1;
										  button_pressed = 1;
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
													 float impulses[4];
													 int c_count = 0;
													 char * cdata = NULL;
													 while (edges && c_count < 4)
													 {
																//																Log("contact edge %d, hitting?\n", c_count);
																normals[c_count] = contact->GetManifold()->localNormal;
																impulses[c_count] = contact->GetManifold()->points[0].normalImpulse;
																//																Log("recording impulse for contact %d:\n\t%.4f\n", c_count+1, impulses[c_count]);
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
													 for (int i = 1; i < c_count; i++)
													 {
																// if (fabs(n1) == fabs(n2))
																// 	if (body1->GetInertia()/magnitude(inertia) == -1.0f * body2->GetInertia()/magnitdue(inertia))
																// 	OR
																// 	if (contact->GetFixtureA()->GetManifold()->normalImpulse < 1.0f && the other
																// 		toDestroy = myPlayer;
																// 		endGame = 1; // death
													 }
										  }
								}
								else
								{
										  b2ContactEdge * edges = myPlayer->GetContactList();
										  b2Vec2 normals[4];
										  float impulses[4];
										  int c_count = 0;
										  char * cdata = NULL;
										  while (edges && c_count < 4)
										  {
													 //													 Log("contact edge %d, hitting?\n", c_count);
													 normals[c_count] = contact->GetManifold()->localNormal;
													 impulses[c_count] = contact->GetManifold()->points[0].normalImpulse;
													 //													 Log("recording impulse for contact %d:\n\t%.4f\n", c_count+1, impulses[c_count]);
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
										  for (int i = 1; i < c_count; i++)
										  {
													 // if (fabs(n1) == fabs(n2))
													 // 	if (body1->GetInertia()/magnitude(inertia) == -1.0f * body2->GetInertia()/magnitdue(inertia))
													 // 	OR
													 // 	if (contact->GetFixtureA()->GetManifold()->normalImpulse < 1.0f && the other
													 // 		toDestroy = myPlayer;
													 // 		endGame = 1; // death
										  }
								}
					 }
					 if (contains(ud1, (const char *)"gun"))
					 {
								// do nothing
					 }
					 if (contains(ud1, (const char *)"bullet"))
					 {
								good = true;
								//								Log("bullet hit something\n");
								//								Log("FixtureA's user data:\n\t%s\n", ((char *)(contact->GetFixtureA()->GetBody()->GetUserData())));
								//								Log("FixtureB's user data:\n\t%s\n", ((char *)(contact->GetFixtureB()->GetBody()->GetUserData())));
								if (ud2)
								{
										  if (contains(ud2, (const char *)"portalable"))
										  {
													 b2Vec2 body_pos = bodyb->GetPosition();
													 float body_height = getHeight(bodyb);
													 float portal_space = 1.3*portal_height*P2M;
													 //										  Log("you shot a portalable object!\n");
													 pos = (b2Vec2)(bodya->GetPosition());
													 norm = (b2Vec2)(contact->GetManifold()->localNormal);
													 if (!contains(ud2, (const char *)"floor"))
													 {
																angle = (float)(bodyb->GetAngle());
																//																Log("pos.y = %.2f\npos.y*M2P = %.2f\nportal_height = %.2f\nonFloor = %.2f\n", pos.y, pos.y*M2P, portal_height, onFloor);
																//																Log("pos.y*M2P + portal_height = %.2f, >= onFloor - 50?\n", (pos.y*M2P + portal_height));
																if (contains(ud1, (const char *)"left"))
																{
																		  if (p2)
																		  {
																					 b2Vec2 p2_pos = p2->GetPosition();
																					 if (pos.y >= body_pos.y && pos.y >= p2_pos.y)
																					 {
																								if (body_pos.y < p2_pos.y)
																								{
																										  if (p2_pos.y + portal_space > 0.0f)
																										  {
																													 // break out, not enough room to place portal
																													 Log("no room for portal, not placing one\n");
																													 Log("205\n");
																													 good = false;
																										  }
																										  //else dir = 1
																								}
																								else
																								{
																										  if (body_pos.y + portal_space > 0.0f)
																										  {
																													 // break out, not enough room to place portal
																													 Log("no room for portal, not placing one\n");
																													 Log("216\n");
																													 good = false;
																										  }
																										  //else dir = 1
																								}
																					 }
																					 else if (pos.y >= body_pos.y && pos.y < p2_pos.y)
																					 {
																								if (p2_pos.y - portal_space < body_height)
																								{
																										  // break out, not enough space
																										  Log("no room for portal, not placing one\n");
																										  Log("227\n");
																										  good = false;
																								}
																								// else dir = 1
																					 }
																					 else if (pos.y < body_pos.y && pos.y >= p2_pos.y)
																					 {
																								if (body_pos.y + portal_space > body_height)
																								{
																										  // break out, not enough space
																										  Log("no room for portal, not placing one\n");
																										  Log("238\n");
																										  good = false;
																								}
																								else
																								{
																										  dir = -1;
																								}
																					 }
																					 else
																					 {
																								if (body_pos.y > p2_pos.y)
																								{
																										  if (p2_pos.y - portal_space < body_height)
																										  {
																													 // break out, not enough room to place portal
																													 Log("no room for portal, not placing one\n");
																													 Log("254\n");
																													 good = false;
																										  }
																										  else
																										  {
																													 dir = -1;
																										  }
																								}
																								else
																								{
																										  if (body_pos.y - portal_space < body_height)
																										  {
																													 // break out, not enough room to place portal
																													 Log("no room for portal, not placing one\n");
																													 Log("268\n");
																													 good = false;
																										  }
																										  else
																										  {
																													 dir = -1;
																										  }
																								}
																					 }

																					 /* HERE */
																					 while (good && (fabs(pos.y*M2P) - portal_height*0.5f) <= (fabs(onFloor)) && fabs(pos.y - p2_pos.y) < portal_space)
																					 {
																								Log("fixing portal position from y = %.2f", pos.y);
																								pos.y += (float)dir * 0.1f * P2M;
																								Log(" to %.2f\n", pos.y);
																								//																								Log("\ntest:\t%.2f >= %.2f?\n", (pos.y*M2P + portal_height), (onFloor - 50.0f));
																					 }
																		  }
																		  else
																		  {
																					 if (pos.y >= body_pos.y)
																					 {
																								while (good && (fabs(pos.y*M2P) - portal_height*0.5f) <= (fabs(onFloor)))
																								{
																										  Log("fixing portal position from y = %.2f", pos.y);
																										  pos.y -= 0.1f * P2M;
																										  Log(" to %.2f\n", pos.y);
																										  //																										  Log("\ntest:\t%.2f >= %.2f?\n", (pos.y*M2P + portal_height), (onFloor - 50.0f));
																								}
																					 }
																					 else
																					 {
																								while (good && (fabs(pos.y*M2P) + portal_height*0.5f) >= (fabs(body_height)))
																								{
																										  Log("fixing portal position from y = %.2f", pos.y);
																										  pos.y += 0.1f * P2M;
																										  Log(" to %.2f\n", pos.y);
																										  //																										  Log("\ntest:\t%.2f >= %.2f?\n", (pos.y*M2P + portal_height), (onFloor - 50.0f));
																								}
																					 }
																		  }
																}
																else if (contains(ud1, (const char *)"right"))
																{
																		  if (p1)
																		  {
																					 b2Vec2 p1_pos = p1->GetPosition();
																					 if (pos.y >= body_pos.y && pos.y >= p1_pos.y)
																					 {
																								if (body_pos.y < p1_pos.y)
																								{
																										  if (p1_pos.y + portal_space > 0.0f)
																										  {
																													 // break out, not enough room to place portal
																													 Log("no room for portal, not placing one\n");
																													 Log("322\n");
																													 good = false;
																										  }
																										  //else dir = 1
																								}
																								else
																								{
																										  if (body_pos.y + portal_space > 0.0f)
																										  {
																													 // break out, not enough room to place portal
																													 Log("no room for portal, not placing one\n");
																													 Log("333\n");
																													 good = false;
																										  }
																										  //else dir = 1
																								}
																					 }
																					 else if (pos.y >= body_pos.y && pos.y < p1_pos.y)
																					 {
																								if (p1_pos.y - portal_space < body_height)
																								{
																										  // break out, not enough space
																										  Log("no room for portal, not placing one\n");
																										  Log("345\n");
																										  good = false;
																								}
																								// else dir = 1
																					 }
																					 else if (pos.y < body_pos.y && pos.y >= p1_pos.y)
																					 {
																								if (body_pos.y + portal_space > body_height)
																								{
																										  // break out, not enough space
																										  Log("no room for portal, not placing one\n");
																										  Log("356\n");
																										  good = false;
																								}
																								else
																								{
																										  dir = -1;
																								}
																					 }
																					 else
																					 {
																								if (body_pos.y > p1_pos.y)
																								{
																										  if (p1_pos.y - portal_space < body_height)
																										  {
																													 // break out, not enough room to place portal
																													 Log("no room for portal, not placing one\n");
																													 Log("372\n");
																													 good = false;
																										  }
																										  else
																										  {
																													 dir = -1;
																										  }
																								}
																								else
																								{
																										  if (body_pos.y - portal_space < body_height)
																										  {
																													 // break out, not enough room to place portal
																													 Log("no room for portal, not placing one\n");
																													 Log("386\n");
																													 good = false;
																										  }
																										  else
																										  {
																													 dir = -1;
																										  }
																								}
																					 }

																					 while (good && (fabs(pos.y*M2P) - portal_height*0.5f) <= (fabs(onFloor)) && fabs(pos.y - p1_pos.y) < portal_space)
																					 {
																								Log("fixing portal position from y = %.2f", pos.y);
																								pos.y += (float)dir * 0.1f * P2M;
																								Log(" to %.2f\n", pos.y);
																								//																								Log("\ntest:\t%.2f >= %.2f?\n", (pos.y*M2P + portal_height), (onFloor - 50.0f));
																					 }
																		  }
																		  else
																		  {
																					 if (pos.y > body_pos.y)
																					 {
																								dir = -1;
																					 }
																					 // else dir = 1
																					 while (good && (fabs(pos.y*M2P) - portal_height*0.5f) <= (fabs(onFloor)) && fabs(pos.y - body_pos.y) < portal_space)
																					 {
																								Log("fixing portal position from y = %.2f", pos.y);
																								pos.y += (float)dir * 0.1f * P2M;
																								Log(" to %.2f\n", pos.y);
																								//																								Log("\ntest:\t%.2f >= %.2f?\n", (pos.y*M2P + portal_height), (onFloor - 50.0f));
																					 }
																		  }
																}
													 }

													 else
													 {
																Log("pos.y = %.2f\npos.y*M2P = %.2f\n", pos.y, pos.y*M2P);
																while (pos.x*M2P - portal_width*0.5f <= 130.0f)
																{
																		  Log("fixing portal position\n");
																		  pos.x += 0.1f * P2M;
																}
																while (pos.x*M2P + portal_width*0.5f >= xres*10.0f - 130.0f)
																{
																		  Log("fixing portal position\n");
																		  pos.x -= 0.1f * P2M;
																}
																angle = pi/2.0f;
													 }
													 if (good)
													 {
																if (contains(ud1, (const char *)"left"))
																{
																		  //													 Log("storing left portal data with angle = %.2f\n", angle);
																		  p_isleft = 1;
																		  /*
																		  if (contains(ud1, (const char *)"top"))
																		  {
																					 p1_dir.x = sinf((angle - 180.0f) * D2R);
																					 p1_dir.y = cosf((angle - 180.0f) * D2R);
																		  }
																		  else
																		  {
																					 p1_dir.x = sinf((angle + 180.0f) * D2R);
																					 p1_dir.y = cosf((angle + 180.0f) * D2R);
																		  }
																		  */
																		  Log("angle = %.2f\n", angle);
																}
																else
																{
																		  //													 Log("storing right portal data with angle = %.2f\n", angle);
																		  p_isleft = 0;
																		  /*
																		  if (contains(ud1, (const char *)"top"))
																		  {
																					 p2_dir.x = sinf((angle - 180.0f) * D2R);
																					 p2_dir.y = cosf((angle - 180.0f) * D2R);
																		  }
																		  else
																		  {
																					 p2_dir.x = sinf((angle + 180.0f) * D2R);
																					 p2_dir.y = cosf((angle + 180.0f) * D2R);
																		  }
																		  */
																		  Log("angle = %.2f\n", angle);
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
					 if (contains(ud1, (const char *)"button"))
					 {
								Log("someone hit the button\n");
								if ((b2BodyType)(bodya->GetType()) == dyn)
								{
										  Log("\tit was a dynamic object\n");
										  door_is_active = 1;
										  button_pressed = 1;
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
													 float impulses[4];
													 int c_count = 0;
													 int pt_ct = 0;
													 char * cdata = NULL;
													 while (edges && c_count < 4)
													 {
																normals[c_count] = contact->GetManifold()->localNormal;
																pt_ct = contact->GetManifold()->pointCount;
																Log("impulses for contact %d:\n", c_count + 1);
																Log("this contact has %d points touching\n", pt_ct);
																for (int i = 0; i < pt_ct; i++)
																{
																		  Log("\t%.4f\n", contact->GetManifold()->points[i].normalImpulse);
																}
																//										  impulses[c_count] = contact->GetManifold()->points[1].normalImpulse;
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
													 for (int i = 1; i < c_count; i++)
													 {
																// if (fabs(n1) == fabs(n2))
																// 	if (body1->GetInertia()/magnitude(inertia) == -1.0f * body2->GetInertia()/magnitdue(inertia))
																// 	OR
																// 	if (contact->GetFixtureA()->GetManifold()->normalImpulse < 1.0f && the other
																// 		toDestroy = myPlayer;
																// 		endGame = 1; // death
													 }
										  }
								}
								else
								{
										  b2ContactEdge * edges = myPlayer->GetContactList();
										  b2Vec2 normals[4];
										  float impulses[4];
										  int c_count = 0;
										  int pt_ct = 0;
										  char * cdata = NULL;
										  while (edges && c_count < 4)
										  {
													 normals[c_count] = contact->GetManifold()->localNormal;
													 pt_ct = contact->GetManifold()->pointCount;
													 Log("impulses for contact %d:\n", c_count + 1);
													 Log("this contact has %d points touching\n", pt_ct);
													 for (int i = 0; i < pt_ct; i++)
													 {
																Log("\t%.4f\n", contact->GetManifold()->points[i].normalImpulse);
													 }
													 //										  impulses[c_count] = contact->GetManifold()->points[1].normalImpulse;
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
										  for (int i = 1; i < c_count; i++)
										  {
													 // if (fabs(n1) == fabs(n2))
													 // 	if (body1->GetInertia()/magnitude(inertia) == -1.0f * body2->GetInertia()/magnitdue(inertia))
													 // 	OR
													 // 	if (contact->GetFixtureA()->GetManifold()->normalImpulse < 1.0f && the other
													 // 		toDestroy = myPlayer;
													 // 		endGame = 1; // death
										  }
								}
					 }
					 if (contains(ud1, (const char *)"gun"))
					 {
								// do nothing
					 }
					 if (contains(ud1, (const char *)"bullet"))
					 {
								good = true;
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
													 if (!contains(ud2, (const char *)"floor"))
													 {
																angle = (float)(bodya->GetAngle());
																if (contains(ud1, (const char *)"left"))
																{
																		  if (p2)
																		  {
																					 if (pos.y >= bodya->GetPosition().y && pos.y >= p2->GetPosition().y)
																					 {
																								if (bodya->GetPosition().y < p2->GetPosition().y)
																								{
																										  if (p2->GetPosition().y + 1.3f*portal_height*P2M < 0.0f)
																										  {
																													 // break out, not enough room to place portal
																													 Log("no room for portal, not placing one\n");
																													 Log("698\n");
																													 good = false;
																										  }
																										  else
																										  {
																													 dir = -1;
																										  }
																										  //else dir = 1
																								}
																								else
																								{
																										  if (bodya->GetPosition().y + 1.3f*portal_height*P2M > 0.0f)
																										  {
																													 // break out, not enough room to place portal
																													 Log("no room for portal, not placing one\n");
																													 Log("709\n");
																													 good = false;
																										  }
																										  else
																										  {
																													 dir = -1;
																										  }
																										  //else dir = 1
																								}
																					 }
																					 else if (pos.y >= bodya->GetPosition().y && pos.y < p2->GetPosition().y)
																					 {
																								if (p2->GetPosition().y - 1.3f*portal_height*P2M > getHeight(bodya))
																								{
																										  // break out, not enough space
																										  Log("no room for portal, not placing one\n");
																										  Log("721\n");
																										  good = false;
																								}
																								else
																								{
																										  dir = -1;
																								}
																								// else dir = 1
																					 }
																					 else if (pos.y < bodya->GetPosition().y && pos.y >= p2->GetPosition().y)
																					 {
																								if (bodya->GetPosition().y + 1.3f*portal_height*P2M < getHeight(bodya))
																								{
																										  // break out, not enough space
																										  Log("no room for portal, not placing one\n");
																										  Log("732\n");
																										  good = false;
																								}
																								else
																								{
																										  dir = 1;
																								}
																					 }
																					 else
																					 {
																								if (bodya->GetPosition().y > p2->GetPosition().y)
																								{
																										  if (p2->GetPosition().y - 1.3f*portal_height*P2M > getHeight(bodya))
																										  {
																													 // break out, not enough room to place portal
																													 Log("no room for portal, not placing one\n");
																													 Log("748\n");
																													 good = false;
																										  }
																										  else
																										  {
																													 dir = 1;
																										  }
																								}
																								else
																								{
																										  if (bodya->GetPosition().y - 1.3f*portal_height*P2M > getHeight(bodya))
																										  {
																													 // break out, not enough room to place portal
																													 Log("no room for portal, not placing one\n");
																													 Log("762\n");
																													 good = false;
																										  }
																										  else
																										  {
																													 dir = 1;
																										  }
																								}
																					 }

																					 
																					 //while (good && fabs(p2->GetPosition().y - pos.y) < 1.1*portal_height*P2M)/*(fabs(pos.y*M2P) - portal_height*0.5f) <= (fabs(onFloor)) && fabs(pos.y - p2->GetPosition().y) < 2.0f*portal_height*P2M)*/
																					 /*
																					 {
																								Log("fixing portal position from y = %.2f", pos.y);
																								pos.y += (float)dir * 0.1f * P2M;
																								Log(" to %.2f\n", pos.y);
																								Log("\ntest:\t%.2f >= %.2f?\n", (pos.y*M2P + portal_height), (onFloor - 50.0f));
																					 }
																					 */
																		  }
																		  else
																		  {
																								/*
																					 if (pos.y >= bodya->GetPosition().y)
																					 {
																								while (good && (fabs(pos.y*M2P) - portal_height*0.5f) <= (fabs(onFloor)))
																								{
																										  Log("fixing portal position from y = %.2f", pos.y);
																										  pos.y -= 0.1f * P2M;
																										  Log(" to %.2f\n", pos.y);
																										  Log("\ntest:\t%.2f >= %.2f?\n", (pos.y*M2P + portal_height), (onFloor - 50.0f));
																								}
																					 }
																					 else
																					 {
																								while (good && (fabs(pos.y*M2P) + portal_height*0.5f) >= (fabs(getHeight(bodya))))
																								{
																										  Log("fixing portal position from y = %.2f", pos.y);
																										  pos.y += 0.1f * P2M;
																										  Log(" to %.2f\n", pos.y);
																										  Log("\ntest:\t%.2f >= %.2f?\n", (pos.y*M2P + portal_height), (onFloor - 50.0f));
																								}
																					 }
																					 */
																		  }
																}
																else if (contains(ud1, (const char *)"right"))
																{
																		  if (p1)
																		  {
																					 if (pos.y >= bodya->GetPosition().y && pos.y >= p1->GetPosition().y)
																					 {
																								if (bodya->GetPosition().y < p1->GetPosition().y)
																								{
																										  if (p1->GetPosition().y + 1.3f*portal_height*P2M < 0.0f)
																										  {
																													 // break out, not enough room to place portal
																													 Log("no room for portal, not placing one\n");
																													 Log("816\n");
																													 good = false;
																										  }
																										  else
																										  {
																													 dir = -1;
																										  }
																										  //else dir = 1
																								}
																								else
																								{
																										  if (bodya->GetPosition().y + 1.3f*portal_height*P2M < 0.0f)
																										  {
																													 // break out, not enough room to place portal
																													 Log("no room for portal, not placing one\n");
																													 Log("827\n");
																													 good = false;
																										  }
																										  else
																										  {
																													 dir = -1;
																										  }
																										  //else dir = 1
																								}
																					 }
																					 else if (pos.y >= bodya->GetPosition().y && pos.y < p1->GetPosition().y)
																					 {
																								/* had to switch from less than to greater than signs here */
																								if (p1->GetPosition().y - 1.3f*portal_height*P2M > getHeight(bodya))
																								{
																										  // break out, not enough space
																										  Log("no room for portal, not placing one\n");
																										  Log("839\n\n");
																										  Log("(p1->GetPosition() = %.2f) - (1.1*portal_height*P2M = %.2f) = %.2f < (getHeight(bodya) = %.2f)? - FALSE\n\n", p1->GetPosition().y, (1.3f*portal_height*P2M), (p1->GetPosition().y - 1.3f*portal_height*P2M), getHeight(bodya));
																										  good = false;
																								}
																								/* also switching dir */
																								// else dir = 1
																								else
																								{
																										  dir = -1;
																								}
																					 }
																					 else if (pos.y < bodya->GetPosition().y && pos.y >= p1->GetPosition().y)
																					 {
																								if (bodya->GetPosition().y + 1.3f*portal_height*P2M < getHeight(bodya))
																								{
																										  // break out, not enough space
																										  Log("no room for portal, not placing one\n");
																										  Log("850\n");
																										  good = false;
																								}
																								else
																								{
																										  dir = 1;
																								}
																					 }
																					 else
																					 {
																								if (bodya->GetPosition().y > p1->GetPosition().y)
																								{
																										  if (p1->GetPosition().y - 1.3f*portal_height*P2M > getHeight(bodya))
																										  {
																													 // break out, not enough room to place portal
																													 Log("no room for portal, not placing one\n");
																													 Log("866\n");
																													 good = false;
																										  }
																										  else
																										  {
																													 dir = 1;
																										  }
																								}
																								else
																								{
																										  if (bodya->GetPosition().y - 1.3f*portal_height*P2M > getHeight(bodya))
																										  {
																													 // break out, not enough room to place portal
																													 Log("no room for portal, not placing one\n");
																													 Log("880\n");
																													 good = false;
																										  }
																										  else
																										  {
																													 dir = 1;
																										  }
																								}
																					 }

																					 /* removed position tests, only test to see that distance between portal and pos is 1.5*portal_height */
																					 //while (good && fabs((p1->GetPosition().y) - pos.y) < 1.3f*portal_height*P2M)/*(fabs(pos.y*M2P) - portal_height*0.5f) <= (fabs(onFloor)) && fabs(pos.y - p1->GetPosition().y) < 2.0f*portal_height*P2M)*/
																					 /*
																					 {
																								Log("fixing portal position from y = %.2f", pos.y);
																								pos.y += (float)dir * 0.1f * P2M;
																								Log(" to %.2f\n", pos.y);
																								Log("\ntest:\t%.2f >= %.2f?\n", (pos.y*M2P + portal_height), (onFloor - 50.0f));
																					 }
																					 */
																		  }
																		  else
																		  {
																					 if (pos.y > bodya->GetPosition().y)
																					 {
																								dir = -1;
																					 }
																					 // else dir = 1
																					 /*
																					 while (good && (fabs(pos.y*M2P) - portal_height*0.5f) <= (fabs(onFloor)) && fabs(pos.y - bodya->GetPosition().y) < 1.3f*portal_height*P2M)
																					 {
																								Log("fixing portal position from y = %.2f", pos.y);
																								pos.y += (float)dir * 0.1f * P2M;
																								Log(" to %.2f\n", pos.y);
																								//																								Log("\ntest:\t%.2f >= %.2f?\n", (pos.y*M2P + portal_height), (onFloor - 50.0f));
																					 }
																					 */
																		  }
																}
													 }
													 else
													 {
																/*
																while (pos.x*M2P - portal_width*0.5f <= 130.0f)
																{
																		  Log("fixing portal position\n");
																		  pos.x += 0.1f;
																}
																while (pos.x*M2P + portal_width*0.5f >= xres*10.0f - 130.0f)
																{
																		  Log("fixing portal position\n");
																		  pos.x -= 0.1f;
																}
																*/
																angle = pi/2.0f;
													 }
													 if (good)
													 {
																if (contains(ud1, (const char *)"left"))
																{
																		  //													 Log("storing left portal data with angle = %.2f\n", angle);
																		  p_isleft = 1;
																		  /*
																		  if (contains(ud1, (const char *)"top"))
																		  {
																					 p1_dir.x = sinf((angle - 180.0f) * D2R);
																					 p1_dir.y = cosf((angle - 180.0f) * D2R);
																		  }
																		  else
																		  {
																					 p1_dir.x = sinf((angle + 180.0f) * D2R);
																					 p1_dir.y = cosf((angle + 180.0f) * D2R);
																		  }
																		  */
																		  Log("angle = %.2f\n", angle);
																}
																else
																{
																		  //													 Log("storing right portal data with angle = %.2f\n", angle);
																		  p_isleft = 0;
																		  /*
																		  if (contains(ud1, (const char *)"top"))
																		  {
																					 p2_dir.x = sinf((angle - 180.0f) * D2R);
																					 p2_dir.y = cosf((angle - 180.0f) * D2R);
																		  }
																		  else
																		  {
																					 p2_dir.x = sinf((angle + 180.0f) * D2R);
																					 p2_dir.y = cosf((angle + 180.0f) * D2R);
																		  }
																		  */
																		  Log("angle = %.2f\n", angle);
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
		  /*
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
			  */
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
										  Log("\tit was a dynamic object\n");
										  door_is_active = 0;
										  button_pressed = 0;
								}
					 }
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
					 if (contains(ud1, (const char *)"button"))
					 {
								Log("something stopped hitting the button\n");
								if ((b2BodyType)(bodya->GetType()) == dyn)
								{
										  Log("\tit was a dynamic object\n");
										  door_is_active = 0;
										  button_pressed = 0;
								}
					 }
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



void contactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{ /* handle pre-solve event */ 
		  b2Body * bodya = contact->GetFixtureA()->GetBody();
		  b2Body * bodyb = contact->GetFixtureB()->GetBody();
		  char * ud1 = (char *)(bodya->GetUserData());
		  char * ud2 = (char *)(bodyb->GetUserData());
		  if (ud1 && (contains(ud1, (const char *)"isportal")))
		  {
					 Log("in pre solve contact handler, something hit a portal with velocity <%.2f, %.2f>\n", bodya->GetLinearVelocity().x, bodya->GetLinearVelocity().y);
		  }
		  if (ud2 && (contains(ud2, (const char *)"isportal")))
		  {
					 Log("in pre solve contact handler, something hit a portal with velocity <%.2f, %.2f>\n", bodyb->GetLinearVelocity().x, bodyb->GetLinearVelocity().y);
		  }
}



void contactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)

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
										  else if (contains(ud1, (char *)"gun"))
										  {
													 //detonate(myPlayer);
										  }
										  else if (contains(ud2, (char *)"gun"))
										  {
													 //detonate(myPlayer);
										  }
										  else if (contains(ud1, (char *)"foot"))
										  {
													 //detonate(myPlayer);
										  }
										  else if (contains(ud2, (char *)"foot"))
										  {
													 //detonate(myPlayer);
										  }
										  else if (contains(ud1, (char *)"player"))
										  {
													 //detonate(myPlayer);
										  }
										  else if (contains(ud2, (char *)"player"))
										  {
													 //detonate(myPlayer);
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
