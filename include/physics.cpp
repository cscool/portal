#include "physics.h"

using namespace std;

void moveBullet (b2Body * p, const float lmax, const float rmax)
{
		  b2Vec2 pos = p->GetPosition();
		  if (pos.x+5.0f >= rmax)
		  {
					 b2Vec2 vel = p->GetLinearVelocity();
					 vel.x = (0.0f);
					 p->SetLinearVelocity(vel);
		  }
		  else if (pos.x-5.0f <= lmax)
		  {
					 b2Vec2 vel = p->GetLinearVelocity();
					 vel.x = (0.0f);
					 p->SetLinearVelocity(vel);
		  }
		  return;
}

void doPortal(b2Body * o)
{
		  Log("pos of p1:\n\t(%.2f, %.2f)\n", p1->GetPosition().x, p1->GetPosition().y);
		  Log("pos of p2:\n\t(%.2f, %.2f)\n", p2->GetPosition().x, p2->GetPosition().y);
		  Log("destination: %s\n", p_dest);
		  if (contains(p_dest, (char *)"p1"))
		  {
//					 b2Vec2 v((p1_dir.x * o->GetLinearVelocity().x), (p1_dir.y * o->GetLinearVelocity().y));
//					 o->SetLinearVelocity((1.0f/getMagnitude(p1_dir)) * v);
					 o->SetTransform((p1->GetPosition())/* + (50.0f * o->GetLinearVelocity()))*/, 0.0f);
		  }
		  else
		  {
//					 b2Vec2 v((p2_dir.x * o->GetLinearVelocity().x), (p2_dir.y * o->GetLinearVelocity().y));
//					 o->SetLinearVelocity((1.0f/getMagnitude(p2_dir)) * v);
					 o->SetTransform((p2->GetPosition())/* + (50.0f * o->GetLinearVelocity()))*/, 0.0f);
		  }
}

void physics (void)
{
		  static b2Body * b1 = NULL;
		  static b2Body * b2 = NULL;
		  static b2Vec2 vel_old;
		  float angle = myGun->GetAngle() * R2D;
		  float inverseAngle;
		  //cout << angle << endl;
		  if( angle <= 180 )
					 inverseAngle = (180 - angle);
		  else if( angle <= 270 )
					 inverseAngle = (360 - angle - 180);
		  else
					 inverseAngle = 0;
		  static int timer = 0;
		  static int jcatch = 0;
		  if (pauseGame)
		  {
					 /* do nothing */
		  }
		  else
		  {
					 if (toDestroy)
					 {
								if (toDestroy->GetUserData())
								{
										  if (contains(((const char *)(toDestroy->GetUserData())), (const char *)"bullet"))
										  {
													 bullet_ct --;
													 if (toDestroy == b1)
													 {
																world->DestroyBody(b1);
																toDestroy = NULL;
																b1 = NULL;
													 }
													 else
													 {
																world->DestroyBody(b2);
																toDestroy = NULL;
																b2 = NULL;
													 }
										  }
										  else
										  {
													 world->DestroyBody(toDestroy);
													 toDestroy = NULL;
										  }
								}
								else
								{
										  world->DestroyBody(toDestroy);
										  toDestroy = NULL;
								}
					 }
					 b2Vec2 vel;
					 if (fix_vel)
					 {
								vel = vel_old;
					 }
					 else
					 {
								vel = myPlayer->GetLinearVelocity();
					 }
					 if (keys[XK_Up] == 1 || keys[XK_w])
					 {
								/* rotate gun up */
								if(angle < 90.0f && angle > -87.0f)
								{
										  myGun->SetTransform(myGun->GetPosition(), myGun->GetAngle() - 3.0f*D2R);
								}
								else if(angle > 90.0f && angle < 267.0f)
								{
										  myGun->SetTransform(myGun->GetPosition(), myGun->GetAngle() + 3.0f*D2R);
								}
					 }
					 if (keys[XK_Down] == 1 || keys[XK_s])
					 {
								/* rotate gun down */
								if(angle < 87.0f && angle > -90.0f)
								{
										  myGun->SetTransform(myGun->GetPosition(), myGun->GetAngle() + 3.0f*D2R);
								}
								else if(angle > 93.0f && angle < 270.0f)
								{
										  myGun->SetTransform(myGun->GetPosition(), myGun->GetAngle() - 3.0f*D2R);
								}
					 }
					 if (keys[XK_Left] == 1 || keys[XK_a])
					 {
								if (angle > -90.0f && angle < 90.0f)
								{
										  myGun->SetTransform(myGun->GetPosition(), inverseAngle*D2R);
								}
								if (vel.y == 0.0f)
								{
										  if (vel.x > -15.0f)
										  {
													 vel.x += -2.5f;
										  }
										  //myPlayer->SetLinearVelocity( vel );
								}
								else
								{
										  if (vel.x > -15.0f)
										  {
													 vel.x += -1.0f;
										  }
								}
								player_direction = -1;
					 }
					 if (keys[XK_Right] == 1 || keys[XK_d])
					 {
								if (angle > 90.0f && angle < 270.0f)
								{
										  myGun->SetTransform(myGun->GetPosition(), inverseAngle*D2R);
								}
								if (vel.y == 0.0f)
								{
										  if (vel.x < 15.0f)
										  {
													 vel.x += 2.5f;
										  }
								}
								else
								{
										  if (vel.x < 15.0f)
										  {
													 vel.x += 1.0f;
										  }
								}
								player_direction = 1;
					 }
					 if (keys[XK_space] == 1)
					 {
								if (can_jump)
								{
										  float impulse = myPlayer->GetMass() * 8.0f;
										  myPlayer->ApplyLinearImpulse(b2Vec2(0,-impulse), myPlayer->GetPosition(),true);
										  vel = myPlayer->GetLinearVelocity();
										  jcatch = 0;
								}
								else
								{
										  if (myPlayer->GetLinearVelocity().y == 0.0f)
										  {
													 jcatch++;
										  }
										  else
										  {
													 jcatch = 0;
										  }
								}
								if (jcatch >= 4)
								{
										  jcatch = 0;
										  toggle(can_jump);
								}
					 }
					 if(keys[XK_Left] == 0 && keys[XK_Right]==0 && keys[XK_a] ==0 && keys[XK_d] == 0)
					 {
								vel.x *= 0.75f;
					 }
					 if (keys[XK_x] || keys[XK_slash] || keys[XK_z] || keys[XK_period] || keys[XK_e] || keys[XK_q])
					 {
								Log("portal key pressed\n");
								if (timer < 1)
								{
										  /*
										  int i = 0;
										  bullet_ct ++;
										  if (bullet_ct > 2)
										  {
													 b2Body* tmp = world->GetBodyList();
													 char * ud;
													 while(tmp)
													 {
																ud = (char *)(tmp->GetUserData());
																if (ud)
																{
																		  if (contains(ud, (const char *)"bullet"))
																		  {
																					 if (i == 0)
																					 {
																								tmp = tmp->GetNext();
																								i++;
																								continue;
																					 }
																					 else
																					 {
																								world->DestroyBody(tmp);
																								tmp = NULL;
																								break;
																								bullet_ct--;
																					 }
																		  }
																		  else
																		  {
																					 tmp = tmp->GetNext();
																		  }
																}
																else
																{
																		  tmp = tmp->GetNext();
																}
													 }
										  }
										  */
										  /* create new body and small square fixture */
										  if (keys[XK_z] || keys[XK_period] || keys[XK_q])
										  {
													 //													 Log("left portal\n");
													 Log("&b1 = %p\n", b1);
													 if (b1)
													 {
																world->DestroyBody(b1);
																b1 = NULL;
																Log("&b1 = %p\n", b1);
													 }
													 b1 = (b2Body *)(addRect(M2P*myGun->GetPosition().x, M2P*myGun->GetPosition().y, 5, 5, 0.0f, 0.0f, 1, (char *)"bullet left")); // make a bullet
													 Log("&b1 = %p\n", b1);
										  }
										  else
										  {
													 Log("&b2 = %p\n", b2);
													 //													 Log("right portal\n");
													 if (b2)
													 {
																world->DestroyBody(b2);
																b2 = NULL;
																Log("&b2 = %p\n", b2);
													 }
													 b2 = (b2Body *)(addRect(M2P*myGun->GetPosition().x, M2P*myGun->GetPosition().y, 5, 5, 0.0f, 0.0f, 1, (char *)"bullet right")); // make a bullet
													 Log("&b2 = %p\n", b2);
										  }
										  //										  Log("done making portal\n");
										  timer = 10; // delay next shot
								}
								if (timer > 0)
								{
										  timer--;
								}
					 }
					 /*
					 if (fix_vel)
					 {
								Log("in physics fixing player velocity\n");
//								Log("\tmod_vel.x = %.2f\tmod_vel.y = %.2f\n\tvel.x = %.2f\tvel.y = %.2f\n", mod_vel.x, mod_vel.y, vel.x, vel.y);
								b2Vec2 vel2(mod_vel.x + vel.x, mod_vel.y + vel.y);
//								Log("applying vel2.x = %.2f, vel2.y = %.2f\n", vel2.x, vel2.y);
								myPlayer->SetLinearVelocity(vel2);
								vel_old = vel;
					 }
					 else
					 */
					 {
//								Log("applying vel.x = %.2f, vel.y = %.2f\n", vel.x, vel.y);
								myPlayer->SetLinearVelocity(vel);
					 }
					 //					 Log("player velocity set\n");
		  }
}

void movePlatform (b2Body * p, const float lmax, const float rmax)
{
		  b2Vec2 pos = p->GetPosition();
		  //		  Log("pos.x = %.2f, rmax = %.2f, lmax = %.2f\n", pos.x, rmax, lmax);
		  if (pos.x+250.0f >= rmax)
		  {
					 b2Vec2 vel = p->GetLinearVelocity();
					 vel.x *= (-1.0f);
					 p->SetLinearVelocity(vel);
		  }
		  else if (pos.x-250.0f <= lmax)
		  {
					 b2Vec2 vel = p->GetLinearVelocity();
					 vel.x *= (-1.0f);
					 p->SetLinearVelocity(vel);
		  }
		  return;
}

float getMagnitude (b2Vec2 v)
{
		  return (sqrt(pow(v.x, 2.0f) + pow(v.y, 2.0f)));
}
