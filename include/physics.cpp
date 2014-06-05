#include "physics.h"

using namespace std;

static b2Body * det_a = NULL;
static b2Body * det_b = NULL;

void resetDestroyVars(void)
{
		  det_a = NULL;
		  det_b = NULL;
		  toDestroy = NULL;
}

float getRMax (const b2Body * m)
{
		  Log("in getRMax\n");
		  char * ud = (char *)(m->GetUserData());
		  int i = 0;
		  if (ud)
		  {
					 if (contains(ud, (const char *)"rmax="))
					 {
								while (*ud != 'r' && *(ud + 1) != 'm' && *(ud + 2) != 'a')
								{
										  Log("ud addr = %p\n", &ud);
										  i++;
										  ud = ((char *)(m->GetUserData()) + i);
								}
								while (*ud != '=')
								{
										  Log("ud addr = %p\n", &ud);
										  i++;
										  ud = ((char *)(m->GetUserData()) + i);
								}
								i++;
								ud = ((char *)(m->GetUserData()) + i);
								Log("final ud addr = %p\nud = %s\n", &ud, ud);
								return (atof(ud));
					 }
		  }
		  return 0.0f;
}

float getLMax (const b2Body * m)
{
		  Log("in getLMax\n");
		  char * ud = (char *)(m->GetUserData());
		  int i = 0;
		  if (ud)
		  {
					 if (contains(ud, (const char *)"lmax="))
					 {
								while (*ud != 'l' && *(ud + 1) != 'm' && *(ud + 2) != 'a')
								{
										  Log("ud addr = %p\n", &ud);
										  i++;
										  ud = ((char *)(m->GetUserData()) + i);
								}
								while (*ud != '=')
								{
										  Log("ud addr = %p\n", &ud);
										  i++;
										  ud = ((char *)(m->GetUserData()) + i);
								}
								i++;
								ud = ((char *)(m->GetUserData()) + i);
								Log("final ud addr = %p\nud = %s\n", &ud, ud);
								return (atof(ud));
					 }
		  }
		  return 0.0f;
}

void detonate (b2Body * a, b2Body * b)
{
		  det_a = a;
		  det_b = b;
}

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
		  if (o != myPlayer && o != myGun && o != myPlayerFoot)
		  {
					 Log("doing normal portal operation\n");
					 b2Fixture * fix = o->GetFixtureList();
					 while (fix)
					 {
								fix->SetSensor(true);
								fix = fix->GetNext();
					 }
					 //					 o->SetType(b2_staticBody);
					 //					 o->SetActive(false);
					 if (contains(p_dest, (char *)"p1"))
					 {
								b2Vec2 v((p1_dir.x * getMagnitude(o->GetLinearVelocity())), (p1_dir.y * getMagnitude(o->GetLinearVelocity())));
								b2Vec2 p(((p1->GetPosition().x) + (/*player_width/ */2.0f * P2M)), (p1->GetPosition().y - (/*player_height/ */2.0f * P2M)));
								o->SetTransform((p/* + (0.1f * o->GetLinearVelocity())*/), 0.0f);
								o->SetLinearVelocity(4.5f * v);
					 }
					 else
					 {
								b2Vec2 v((p2_dir.x * getMagnitude(o->GetLinearVelocity())), (p2_dir.y * getMagnitude(o->GetLinearVelocity())));
								b2Vec2 p(((p2->GetPosition().x) + (/*player_width/ */2.0f * P2M)), (p2->GetPosition().y - (/*player_height/ */2.0f * P2M)));
								o->SetTransform((p/* + (0.1f * o->GetLinearVelocity())*/), 0.0f);
								o->SetLinearVelocity(4.5f * v);
					 }
					 fix = o->GetFixtureList();
					 while (fix)
					 {
								fix->SetSensor(false);
								fix = fix->GetNext();
					 }
					 //					 o->SetType(b2_dynamicBody);
					 //					 o->SetActive(true);
		  }
		  else
		  {
					 Log("player/gun/foot portal operation\n");
					 b2Fixture * fix = myPlayer->GetFixtureList();
					 while (fix)
					 {
								fix->SetSensor(true);
								fix = fix->GetNext();
					 }
					 fix = myGun->GetFixtureList();
					 while (fix)
					 {
								fix->SetSensor(true);
								fix = fix->GetNext();
					 }
					 fix = myPlayerFoot->GetFixtureList();
					 while (fix)
					 {
								fix->SetSensor(true);
								fix = fix->GetNext();
					 }
					 //					 myPlayer->SetType(b2_staticBody);
					 myGun->SetType(b2_staticBody);
					 myPlayerFoot->SetType(b2_staticBody);
					 //					 myPlayer->SetActive(false);
					 b2Vec2 v1;
					 if (contains(p_dest, (char *)"p1"))
					 {
								b2Vec2 p;
								if (contains(p1_in_contact, (const char *)"floor"))
								{
										  Log("portaling to the floor\n");
										  p.x = p1->GetPosition().x;
										  p.y = (p1->GetPosition().y - (2.0f));
								}
								else if (contains(p1_in_contact, (const char *)"ceiling"))
								{
										  Log("portaling to the ceiling\n");
										  p.x = p1->GetPosition().x;
										  p.y = (p1->GetPosition().y + (2.0f));
								}
								else
								{
										  Log("portaling to unidentified wall\n");
										  p.x = p1->GetPosition().x;
										  p.y = p1->GetPosition().y;
								}
								v1 = getMagnitude(myPlayer->GetLinearVelocity()) * p1_dir;
								myPlayer->SetTransform((p/* + (0.1f * o->GetLinearVelocity())*/), 0.0f);
								myGun->SetTransform((p/* + (0.1f * o->GetLinearVelocity())*/), myGun->GetAngle());
								myPlayerFoot->SetTransform((p/* + (0.1f * o->GetLinearVelocity())*/), 0.0f);
								myPlayer->SetLinearVelocity(4.5f * v1);
								myGun->SetLinearVelocity(4.5f * v1);
								myPlayerFoot->SetLinearVelocity(4.5f * v1);
								//								Log("player velocity after: <%.2f, %.2f>\n", myPlayer->GetLinearVelocity().x, myPlayer->GetLinearVelocity().y);
					 }
					 else
					 {
								b2Vec2 p;
								if (contains(p2_in_contact, (const char *)"floor"))
								{
										  Log("portaling to the floor\n");
										  p.x = p2->GetPosition().x;
										  p.y = (p2->GetPosition().y - (2.0f));
								}
								else if (contains(p2_in_contact, (const char *)"ceiling"))
								{
										  Log("portaling to the ceiling\n");
										  p.x = p2->GetPosition().x;
										  p.y = (p2->GetPosition().y + (2.0f));
								}
								else
								{
										  Log("portaling to unidentified wall\n");
										  p.x = p2->GetPosition().x;
										  p.y = p2->GetPosition().y;
								}
								v1 = getMagnitude(myPlayer->GetLinearVelocity()) * p2_dir;
								myPlayer->SetTransform((p/* + (0.1f * o->GetLinearVelocity())*/), 0.0f);
								myGun->SetTransform((p/* + (0.1f * o->GetLinearVelocity())*/), myGun->GetAngle());
								myPlayerFoot->SetTransform((p/* + (0.1f * o->GetLinearVelocity())*/), 0.0f);
								myPlayer->SetLinearVelocity(4.5f * v1);
								myGun->SetLinearVelocity(4.5f * v1);
								myPlayerFoot->SetLinearVelocity(4.5f * v1);
								//								Log("player velocity after: <%.2f, %.2f>\n", myPlayer->GetLinearVelocity().x, myPlayer->GetLinearVelocity().y);
					 }
					 fix = myPlayer->GetFixtureList();
					 while (fix)
					 {
								fix->SetSensor(false);
								fix = fix->GetNext();
					 }
					 //					 myPlayer->SetType(b2_dynamicBody);
					 myGun->SetType(b2_dynamicBody);
					 myPlayerFoot->SetType(b2_dynamicBody);
					 //					 myPlayer->SetActive(true);
		  }
}

void clear_keys(void)
{
		  for (int i = 0; i < 65536; i++)
		  {
					 keys[i] &= 0;
		  }
}

void physics (void)
{
		  static b2Body * b1 = NULL;
		  static b2Body * b2 = NULL;
		  static b2Vec2 vel_old;
		  static int timer = 0;
		  static int jcatch = 0;
		  float angle = myGun->GetAngle() * R2D;
		  float inverseAngle;
		  if( angle <= 180 )
					 inverseAngle = (180 - angle);
		  else if( angle <= 270 )
					 inverseAngle = (360 - angle - 180);
		  else
					 inverseAngle = 0;
		  if (pauseGame)
		  {
					 /* do nothing */
		  }
		  else
		  {
					 for (int i = 0; i < 5; i++)
					 {
								if (doors[i].door)
								{
										  //					 Log("game not paused, perform physics\n");
										  if (doors[i].active)
										  {
													 float distance;
													 b2Vec2 temp;
													 distance = sqrt(pow((doors[i].door->GetPosition().x - doors[i].max_pos.x),2) + pow((doors[i].door->GetPosition().y - doors[i].max_pos.y),2));
													 Log("door ACTIVE\ndoors[%d].door->GetPosition() = <%.2f, %.2f>\nGetLinearVelocity() = <%.2f, %.2f>\ndistance: %.2f\n", i, doors[i].door->GetPosition().x, doors[i].door->GetPosition().y, doors[i].door->GetLinearVelocity().x, doors[i].door->GetLinearVelocity().y, distance);
													 //    cout << "Distance: " << distance << endl;
													 if(distance < 5.02) {
																/*
																	plat.direction = -plat.direction;
																	temp = plat.start;
																	plat.start = plat.end;
																	plat.end = temp;
																	*/
																doors[i].door->SetLinearVelocity(ZERO_VEC);
																doors[i].door->SetTransform(b2Vec2(doors[i].max_pos.x+(100.0f*P2M), doors[i].max_pos.y), doors[i].door->GetAngle());
													 }
													 else
													 {
																//																Log("setting velocity in active\n");
																doors[i].door->SetLinearVelocity(1.0f * doors[i].speed * doors[i].dir);
													 }
										  }
										  else
										  {
													 //													 Log("door INACTIVE\ndoors[%d].door->GetPosition() = <%.2f, %.2f>\nGetLinearVelocity() = <%.2f, %.2f>\n", i, doors[i].door->GetPosition().x, doors[i].door->GetPosition().y, doors[i].door->GetLinearVelocity().x, doors[i].door->GetLinearVelocity().y);
													 float distance;
													 b2Vec2 temp;
													 distance = sqrt(pow((doors[i].door->GetPosition().x - doors[i].min_pos.x),2) + pow((doors[i].door->GetPosition().y - doors[i].min_pos.y),2));
													 Log("door INACTIVE\ndoors[%d].door->GetPosition() = <%.2f, %.2f>\nGetLinearVelocity() = <%.2f, %.2f>\ndistance: %.2f\n", i, doors[i].door->GetPosition().x, doors[i].door->GetPosition().y, doors[i].door->GetLinearVelocity().x, doors[i].door->GetLinearVelocity().y, distance);
													 //    cout << "Distance: " << distance << endl;
													 if(distance < 5.02) {
																/*
																	plat.direction = -plat.direction;
																	temp = plat.start;
																	plat.start = plat.end;
																	plat.end = temp;
																	*/
																doors[i].door->SetLinearVelocity(ZERO_VEC);
																doors[i].door->SetTransform(b2Vec2(doors[i].min_pos.x+(100.0f*P2M), doors[i].min_pos.y), doors[i].door->GetAngle());
													 }
													 else
													 {
																//																Log("setting velocity in inactive\n");
																doors[i].door->SetLinearVelocity(-1.0f * doors[i].speed * doors[i].dir);
													 }
										  }
								}
					 }
					 //					 Log("checking for objects to destroy\n");
					 //Platforms
					 for(int i = 0; i < 10; i++)
					 {
								if( platforms[i].platform )
								{
										  movePlatform2( platforms[i] );
								}
					 }
					 if (det_a)
					 {
								if (det_a == carry)
								{
										  carry = NULL;
								}
								//								Log("det_a exists!\n");
								char * adata = (char *)(det_a->GetUserData());
								char * bdata = NULL;
								if (det_b)
								{
										  //										  Log("det_b exists!\n");
										  bdata = (char *)(det_b->GetUserData());
										  if (det_b == carry)
										  {
													 carry = NULL;
										  }
								}
								if (adata)
								{
										  //										  Log("det_a has user data\n");
										  if (contains(adata, (const char *)"player") || contains(adata, (const char *)"gun") || contains(adata, (const char *)"foot"))
										  {
													 clear_keys();
													 state = 3;
//													 restart(current_arena);
													 return;
										  }
								}
								if (bdata)
								{
										  //										  Log("det_b has user data\n");
										  if (contains(bdata, (const char *)"player") || contains(bdata, (const char *)"gun") || contains(bdata, (const char *)"foot"))
										  {
													 clear_keys();
													 state = 3;
//													 restart(current_arena);
													 return;
										  }
								}
								world->DestroyBody(det_b);
								world->DestroyBody(det_a);
								det_a = NULL;
								det_b = NULL;
					 }
					 if (toDestroy)
					 {
								//								Log("toDestroy exists!\n");
								char * ddata = (char *)(toDestroy->GetUserData());
								if (toDestroy == carry)
								{
										  carry = NULL;
								}
								if (ddata)
								{
										  //										  Log("toDestroy has user data\n");
										  if (contains(ddata, (const char *)"player") || contains(ddata, (const char *)"gun") || contains(ddata, (const char *)"foot"))
										  {
													 //													 Log("\nCALLING RESTART WITH TODESTROY\n\n");
													 clear_keys();
													 state = 3;
//													 restart(current_arena);
													 return;
										  }
										  if (contains(ddata, (const char *)"bullet"))
										  {
													 if (!contains(ddata, (const char *)"deadly"))
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
								else
								{
										  world->DestroyBody(toDestroy);
										  toDestroy = NULL;
								}
					 }
					 resetDestroyVars();
					 if (carry)
					 {
								b2Vec2 p(myGun->GetPosition().x + player_direction * 2.0f * player_width * P2M, myGun->GetPosition().y + 4.0f * sin(myGun->GetAngle()));
								carry->SetTransform(p, 0.0f);
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
								if (vel.x > -20.0f)
								{
										  vel.x += -2.5f;
								}
								player_direction = -1;
					 }
					 if (keys[XK_Right] == 1 || keys[XK_d])
					 {
								if (angle > 90.0f && angle < 270.0f)
								{
										  myGun->SetTransform(myGun->GetPosition(), inverseAngle*D2R);
								}

								if (vel.x < 20.0f)
								{
										  vel.x += 2.5f;
								}
								player_direction = 1;
					 }
					 if (keys[XK_space] == 1)
					 {
								if (can_jump)
								{
										  float impulse = myPlayerFoot->GetMass() * 3.5f;
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
										  /* do raycast, get norm of dest, save for future reference */
										  float currentRayAngle = myGun->GetAngle() + 90.0f*D2R;
										  float rayLength = 15.0f * M2P;
										  b2Vec2 p1 = myGun->GetPosition();
										  b2Vec2 p2 = p1 + rayLength * b2Vec2( sinf(currentRayAngle), -cosf(currentRayAngle));
										  b2RayCastInput input;
										  input.p1 = p1;
										  input.p2 = p2;
										  input.maxFraction = 1;

										  float closestFraction = 1; //start with end of line as p2
										  b2Vec2 intersectionNormal(0,0);
										  b2RayCastOutput output;
										  bool cont = true;
										  for (b2Body* b = world->GetBodyList(); b && cont; b = b->GetNext())
										  {
													 for (b2Fixture* f = b->GetFixtureList(); f && cont; f = f->GetNext())
													 {

																if ( ! f->RayCast( &output, input, 0 ) )
																{
																		  continue;
																}
																if ( output.fraction < closestFraction )
																{
																		  closestFraction = output.fraction;
																		  intersectionNormal = output.normal;
																		  cont = false;
																}            
													 }
										  }
										  if (keys[XK_z] || keys[XK_period] || keys[XK_q])
										  {
													 if (b1)
													 {
																world->DestroyBody(b1);
																b1 = NULL;
													 }
													 b1 = (b2Body *)(addRect(M2P*myGun->GetPosition().x, M2P*myGun->GetPosition().y, 5, 5, 0.0f, 0.0f, 1, (char *)"bullet left")); // make a bullet
													 p1_dir = output.normal;
										  }
										  else
										  {
													 if (b2)
													 {
																world->DestroyBody(b2);
																b2 = NULL;
													 }
													 b2 = (b2Body *)(addRect(M2P*myGun->GetPosition().x, M2P*myGun->GetPosition().y, 5, 5, 0.0f, 0.0f, 1, (char *)"bullet right")); // make a bullet
													 p2_dir = output.normal;
										  }
										  timer = 8; // delay next shot
								}
								if (timer > 0)
								{
										  timer--;
								}
					 }
					 if (keys[XK_f])
					 {
								cwait = 1;
					 }
					 else if (!(keys[XK_f]) && cwait)
					 {
								if (carry)
								{
										  /* drop */
										  Log("dropped an object\n");
										  carry->SetGravityScale(1);
										  b2Vec2 v(myPlayer->GetLinearVelocity().x, myPlayer->GetLinearVelocity().y - 0.1f);
										  carry->SetLinearVelocity(v);
										  carry = NULL;
								}
								else
								{
										  b2Body * tmp = world->GetBodyList();
										  b2BodyType dyn = myPlayer->GetType();
										  char * data = NULL;
										  while (tmp && !carry)
										  {
													 data = (char *)(tmp->GetUserData());
													 if (tmp == myPlayer)
													 {
																// do nada
													 }
													 else if (tmp == myGun)
													 {
																// do nada
													 }
													 else if (tmp == b1 || tmp == b2)
													 {
																// no grabbing bullets out of the air
													 }
													 else if (tmp->GetType() == dyn)
													 {
																if (data)
																{
																		  if (contains(data, (const char *)"foot"))
																		  {
																					 // do nada
																		  }
																		  else if (contains(data, (const char *)"turret"))
																		  {
																					 // do nada
																		  }
																		  else if (fabs(b2Distance(myGun->GetPosition(), tmp->GetPosition())) < 6.5f)
																		  {
																					 carry = tmp;
																					 carry->SetGravityScale(0);
																		  }
																}
																else if (fabs(b2Distance(myGun->GetPosition(), tmp->GetPosition())) < 6.5f)
																{
																		  carry = tmp;
																		  carry->SetGravityScale(0);
																}
													 }
													 tmp = tmp->GetNext();
										  }
								}
								cwait = 0;
					 }
					 myPlayer->SetLinearVelocity(vel);
					 for(int i = 0; i < 10; i++)
					 {
								if (turrets[i].turret)
								{
										  b2Joint * joint = turrets[i].turret->GetJointList()->joint;
										  b2RevoluteJoint * revJoint = static_cast<b2RevoluteJoint*>(joint);
										  if(revJoint->GetJointAngle()*R2D >= turrets[i].max_angle)
										  {
													 turrets[i].turret->SetAngularVelocity(-turrets[i].angleSpeed);
										  }
										  if(revJoint->GetJointAngle()*R2D <= turrets[i].min_angle)
										  {
													 turrets[i].turret->SetAngularVelocity(turrets[i].angleSpeed);
										  }
								}
					 }
		  }
}

void moveMine (Mine & p)
{
		  float distance;
		  Log("in move mine\n");
		  b2Vec2 temp;
		  distance = sqrt(pow((p.mine->GetPosition().x - p.min_pos.x),2) + pow((p.mine->GetPosition().y - p.min_pos.y),2));
		  if(distance < 5.02)
		  {
					 Log("switching direction\n");
					 temp = p.max_pos;
					 p.max_pos = p.min_pos;
					 p.min_pos = temp;
					 p.dir *= -1.0f;
					 p.mine->SetLinearVelocity(p.speed * p.dir);
		  }
		  else
		  {
					 Log("not switching direction\n");
					 p.mine->SetLinearVelocity(1.0f * p.speed * p.dir);
		  }
		  return;
}

void movePlatform2(Platform &plat)
{
		  if(plat.active) {
					 float distance;
					 b2Vec2 temp;
					 distance = sqrt(pow((plat.platform->GetPosition().x - plat.end.x),2) + pow((plat.platform->GetPosition().y - plat.end.y),2));
					 if(distance < 5.0) {
								plat.direction = -plat.direction;
								temp = plat.start;
								plat.start = plat.end;
								plat.end = temp;
					 }
					 plat.platform->SetLinearVelocity(plat.speed * plat.direction);
					 if(plat.angleActive) {
								if(plat.platform->GetAngle()*R2D >= plat.maxAngle)
										  plat.platform->SetAngularVelocity(-plat.angleSpeed);
								else if(plat.platform->GetAngle()*R2D <= plat.minAngle)
										  plat.platform->SetAngularVelocity(plat.angleSpeed);
					 }
		  }
}

void movePlatform (b2Body * p, const float lmax, const float rmax)
{
		  b2Vec2 pos = p->GetPosition();
		  //		  Log("pos.x = %.2f, rmax = %.2f, lmax = %.2f\n", pos.x, rmax, lmax);
		  if (pos.x+(250.0f*P2M) >= rmax)
		  {
					 b2Vec2 vel = p->GetLinearVelocity();
					 vel.x *= (-1.0f);
					 p->SetLinearVelocity(vel);
		  }
		  else if (pos.x-(250.0f*P2M) <= lmax)
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
