#include <iostream>
#include <log.h>
#include <Box2D/Box2D.h>

using namespace std;

void portal1 ()
{
								good = true;
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
//																Log("pos.y = %.2f\npos.y*M2P = %.2f\nportal_height = %.2f\nonFloor = %.2f\n", pos.y, pos.y*M2P, portal_height, onFloor);
//																Log("pos.y*M2P + portal_height = %.2f, >= onFloor - 50?\n", (pos.y*M2P + portal_height));
																if (contains(ud1, (const char *)"left"))
																{
																		  if (p2)
																		  {
																					 if (pos.y >= bodyb->GetPosition().y && pos.y >= p2->GetPosition().y)
																					 {
																								if (bodyb->GetPosition().y < p2->GetPosition().y)
																								{
																										  if (p2->GetPosition().y + 1.3f*portal_height*P2M > 0.0f)
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
																										  if (bodyb->GetPosition().y + 1.3f*portal_height*P2M > 0.0f)
																										  {
																													 // break out, not enough room to place portal
																													 Log("no room for portal, not placing one\n");
																													 Log("216\n");
																													 good = false;
																										  }
																										  //else dir = 1
																								}
																					 }
																					 else if (pos.y >= bodyb->GetPosition().y && pos.y < p2->GetPosition().y)
																					 {
																								if (p2->GetPosition().y - 1.3f*portal_height*P2M < getHeight(bodyb))
																								{
																										  // break out, not enough space
																										  Log("no room for portal, not placing one\n");
																										  Log("227\n");
																										  good = false;
																								}
																								// else dir = 1
																					 }
																					 else if (pos.y < bodyb->GetPosition().y && pos.y >= p2->GetPosition().y)
																					 {
																								if (bodyb->GetPosition().y + 1.3f*portal_height*P2M > getHeight(bodyb))
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
																								if (bodyb->GetPosition().y > p2->GetPosition().y)
																								{
																										  if (p2->GetPosition().y - 1.3f*portal_height*P2M < getHeight(bodyb))
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
																										  if (bodyb->GetPosition().y - 1.3f*portal_height*P2M < getHeight(bodyb))
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

																					 while (good && (fabs(pos.y*M2P) - portal_height*0.5f) <= (fabs(onFloor)) && fabs(pos.y - p2->GetPosition().y) < 1.3f*portal_height*P2M)
																					 {
																								Log("fixing portal position from y = %.2f", pos.y);
																								pos.y += (float)dir * 0.1f * P2M;
																								Log(" to %.2f\n", pos.y);
//																								Log("\ntest:\t%.2f >= %.2f?\n", (pos.y*M2P + portal_height), (onFloor - 50.0f));
																					 }
																		  }
																		  else
																		  {
																					 if (pos.y >= bodyb->GetPosition().y)
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
																								while (good && (fabs(pos.y*M2P) + portal_height*0.5f) >= (fabs(getHeight(bodyb))))
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
																					 if (pos.y >= bodyb->GetPosition().y && pos.y >= p1->GetPosition().y)
																					 {
																								if (bodyb->GetPosition().y < p1->GetPosition().y)
																								{
																										  if (p1->GetPosition().y + 1.3f*portal_height*P2M > 0.0f)
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
																										  if (bodyb->GetPosition().y + 1.3f*portal_height*P2M > 0.0f)
																										  {
																													 // break out, not enough room to place portal
																													 Log("no room for portal, not placing one\n");
																													 Log("333\n");
																													 good = false;
																										  }
																										  //else dir = 1
																								}
																					 }
																					 else if (pos.y >= bodyb->GetPosition().y && pos.y < p1->GetPosition().y)
																					 {
																								if (p1->GetPosition().y - 1.3f*portal_height*P2M < getHeight(bodyb))
																								{
																										  // break out, not enough space
																										  Log("no room for portal, not placing one\n");
																										  Log("345\n");
																										  good = false;
																								}
																								// else dir = 1
																					 }
																					 else if (pos.y < bodyb->GetPosition().y && pos.y >= p1->GetPosition().y)
																					 {
																								if (bodyb->GetPosition().y + 1.3f*portal_height*P2M > getHeight(bodyb))
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
																								if (bodyb->GetPosition().y > p1->GetPosition().y)
																								{
																										  if (p1->GetPosition().y - 1.3f*portal_height*P2M < getHeight(bodyb))
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
																										  if (bodyb->GetPosition().y - 1.3f*portal_height*P2M < getHeight(bodyb))
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

																					 while (good && (fabs(pos.y*M2P) - portal_height*0.5f) <= (fabs(onFloor)) && fabs(pos.y - p1->GetPosition().y) < 1.3f*portal_height*P2M)
																					 {
																								Log("fixing portal position from y = %.2f", pos.y);
																								pos.y += (float)dir * 0.1f * P2M;
																								Log(" to %.2f\n", pos.y);
																								Log("\ntest:\t%.2f >= %.2f?\n", (pos.y*M2P + portal_height), (onFloor - 50.0f));
																					 }
																		  }
																		  else
																		  {
																					 if (pos.y > bodyb->GetPosition().y)
																					 {
																								dir = -1;
																					 }
																					 // else dir = 1
																					 while (good && (fabs(pos.y*M2P) - portal_height*0.5f) <= (fabs(onFloor)) && fabs(pos.y - bodyb->GetPosition().y) < 1.3f*portal_height*P2M)
																					 {
																								Log("fixing portal position from y = %.2f", pos.y);
																								pos.y += (float)dir * 0.1f * P2M;
																								Log(" to %.2f\n", pos.y);
																								Log("\ntest:\t%.2f >= %.2f?\n", (pos.y*M2P + portal_height), (onFloor - 50.0f));
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
