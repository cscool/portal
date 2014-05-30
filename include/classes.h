#pragma once
#include <log.h>

using namespace std;

class object
{
		  protected:
					 char * obj_name;
					 b2Body * obj_body;
					 b2Vec2 obj_norm;
					 bool p1_contacting;
					 bool p2_contacting;
					 b2Vec2 * prev_3_vel;

		  public:
					 object()
					 {
								obj_name = new char [50];
								obj_body = NULL;
								obj_norm.x = 0.0f;
								obj_norm.y = 0.0f;
								p1_contacting = false;
								p2_contacting = false;
								prev_3_vel = new b2Vec2 [3];
								prev_3_vel[0].x = 0.0f;
								prev_3_vel[0].y = 0.0f;
								prev_3_vel[1].x = 0.0f;
								prev_3_vel[1].y = 0.0f;
								prev_3_vel[2].x = 0.0f;
								prev_3_vel[2].y = 0.0f;
					 }

					 ~object()
					 {
								delete obj_name;
								if (world)
								{
										  b2Body * tmp = world->GetBodyList();
										  while (tmp)
										  {
													 if (tmp == obj_body)
													 {
																world->DestroyBody(obj_body);
																break;
													 }
													 tmp = tmp->GetNext();
										  }
										  tmp = NULL;
								}
								obj_body = NULL;
								obj_norm.x = 0.0f;
								obj_norm.y = 0.0f;
								p1_contacting = false;
								p2_contacting = false;
								delete [] prev_3_vel;
					 }

					 /* mutators */

					 bool setPrevVel (const b2Vec2 & v)
					 {
								prev_3_vel[2] = prev_3_vel[1];
								prev_3_vel[1] = prev_3_vel[0];
								prev_3_vel[0] = v;
					 }

					 bool setP2Contacting (const int & t)
					 {
								if (t != 0)
								{
										  p2_contacting = true;
								}
								else
								{
										  p2_contacting = false;
								}
								return true;
					 }

					 bool setP2Contacting (const bool & t)
					 {
								p2_contacting = t;
								if (p2_contacting == t)
								{
										  return true;
								}
								return false;
					 }

					 bool setP1Contacting (const int & t)
					 {
								if (t != 0)
								{
										  p1_contacting = true;
								}
								else
								{
										  p1_contacting = false;
								}
								return true;
					 }

					 bool setP1Contacting (const bool & t)
					 {
								p1_contacting = t;
								if (p1_contacting == t)
								{
										  return true;
								}
								return false;
					 }

					 bool setNorm(const float & x, const float & y)
					 {
								obj_norm.x = x;
								obj_norm.y = y;
								if (obj_norm.x == x && obj_norm.y == y)
								{
										  return true;
								}
								return false;
					 }

					 bool setNorm(const b2Vec2 & n)
					 {
								obj_norm = n;
								if (obj_norm.x == n.x && obj_norm.y == n.y)
								{
										  return true;
								}
								return false;
					 }

					 bool setBody(const b2Body * b)
					 {
								if (!b)
								{
										  return false;
								}
								obj_body = b;
								if (obj_body == b)
								{
										  return true;
								}
								return false;
					 }

					 bool setName(const char * n)
					 {
								if (!n || strlen(n) < 1)
								{
										  return false;
								}
								obj_name = n;
								if (obj_name == n)
								{
										  return true;
								}
								return false;
					 }

					 /* accessors */

					 b2Vec2 getPrevVel(const int & n = 0)
					 {
								if (n <= 0 || n > 2)
								{
										  return prev_3_vel[0];
								}
								return prev_3_vel[n];
					 }
					 inline char * getName(void)
					 {
								return obj_name;
					 }
					 inline b2Body * getBody(void)
					 {
								return obj_body;
					 }
					 inline b2vec2 getVel(void)
					 {
								return obj_vel;
					 }
					 inline b2vec2 getNorm(void)
					 {
								return obj_norm;
					 }
					 inline bool getP1Contacting(void)
					 {
								return p1_contacting;
					 }
					 inline bool getP2Contacting(void)
					 {
								return p2_contacting;
					 }
					 b2Body * getContactingPortal(void)
					 {
								if (p1_contacting)
								{
										  return p1;
								}
								else if (p2_contacting)
								{
										  return p2;
								}
								return NULL;
					 }
};

class player
