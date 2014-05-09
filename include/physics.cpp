#include "physics.h"

using namespace std;

void moveBullet (b2Body * p, const float lmax, const float rmax)
{
		  b2Vec2 pos = p->GetWorldCenter();
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
		  if (contains(p_dest, (char *)"p1"))
		  {
					 o->SetLinearVelocity((getMagnitude(((b2Vec2)(o->GetLinearVelocity()))) * (1.0f/getMagnitude(o->GetLinearVelocity()))) * p1_dir);
					 o->SetTransform(p1->GetWorldCenter() + (0.5f * o->GetLinearVelocity()), 0.0f);
		  }
		  else
		  {
					 o->SetLinearVelocity((getMagnitude(((b2Vec2)(o->GetLinearVelocity()))) * (1.0f/getMagnitude(o->GetLinearVelocity()))) * p2_dir);
					 o->SetTransform(p2->GetWorldCenter() + (0.5f * o->GetLinearVelocity()), 0.0f);
		  }
}

void physics (void)
{
		  float angle = myGun->GetAngle() * R2D;
		  static int timer = 0;
		  if (pauseGame)
		  {
					 /* do nothing */
		  }
		  else
		  {
					 if (toDestroy)
					 {
								world->DestroyBody(toDestroy);
								toDestroy = NULL;
								bullet_ct --;
					 }
					 b2Vec2 vel = myPlayer->GetLinearVelocity();
					 if (keys[XK_Up] == 1 || keys[XK_w])
					 {
								/* rotate gun up */
								if(angle < 90.0f && angle > -87.0f)
								{
										  myGun->SetTransform(myGun->GetPosition(), myGun->GetAngle() - 3*D2R);
								}
								else if(angle > 90.0f && angle < 267.0f)
								{
										  myGun->SetTransform(myGun->GetPosition(), myGun->GetAngle() + 3*D2R);
								}
					 }
					 if (keys[XK_Down] == 1 || keys[XK_s])
					 {
								/* rotate gun down */
								if(angle < 87.0f && angle > -90.0f)
								{
										  myGun->SetTransform(myGun->GetPosition(), myGun->GetAngle() + 3*D2R);
								}
								else if(angle > 93.0f && angle < 270.0f)
								{
										  myGun->SetTransform(myGun->GetPosition(), myGun->GetAngle() - 3*D2R);
								}
					 }
					 if (keys[XK_Left] == 1 || keys[XK_a])
					 {
								//if(vel.x <= 50)
								//myPlayer->ApplyForce( b2Vec2(-5,0), myPlayer->GetWorldCenter(),true);
								//moveState = MS_LEFT;
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
								//if(vel.x > -50)
								//myPlayer->ApplyForce( b2Vec2(5,0), myPlayer->GetWorldCenter(),true);
								//moveState = MS_RIGHT;
								if (vel.y == 0.0f)
								{
										  if (vel.x < 15.0f)
										  {
													 vel.x += 2.5f;
										  }
										  //myPlayer->SetLinearVelocity( vel );
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
								//addRect(e->xbutton.x, e->xbutton.y, 20, 20, true);

								if ((myPlayer->GetLinearVelocity()).y == 0.0f)
								{

										  float impulse = myPlayer->GetMass() * 25.0f;
										  myPlayer->ApplyLinearImpulse(b2Vec2(0,-impulse), myPlayer->GetWorldCenter(),true);
										  vel = myPlayer->GetLinearVelocity();
								}
					 }
					 if(keys[XK_Left] == 0 && keys[XK_Right]==0 && keys[XK_a] ==0 && keys[XK_d] == 0){
								vel.x *= 0.75f;
					 }
					 if (keys[XK_x] || keys[XK_slash] || keys[XK_z] || keys[XK_period])
					 {
								Log("portal key pressed\n");
								if (timer < 1)
								{
										  bullet_ct ++;
										  int i = 0;
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
										  /* create new body and small square fixture */
										  if (keys[XK_z] || keys[XK_period])
										  {
													 //													 Log("left portal\n");
													 addRect(M2P*myPlayer->GetWorldCenter().x + player_direction * 61, M2P*myPlayer->GetWorldCenter().y, 5, 5, 0.0f, 0.0f, 1, (char *)"bullet left"); // make a bullet
													 //										  moveBullet(p);
										  }
										  else
										  {
													 //													 Log("right portal\n");
													 addRect(M2P*myPlayer->GetWorldCenter().x + player_direction * 61, M2P*myPlayer->GetWorldCenter().y, 5, 5, 0.0f, 0.0f, 1, (char *)"bullet right"); // make a bullet
										  }
										  //										  Log("done making portal\n");
										  timer = 10; // delay next shot
								}
								if (timer > 0)
								{
										  timer--;
								}
					 }
					 myPlayer->SetLinearVelocity(vel);
					 //					 Log("player velocity set\n");
		  }
}

void movePlatform (b2Body * p, const float lmax, const float rmax)
{
		  b2Vec2 pos = p->GetWorldCenter();
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
