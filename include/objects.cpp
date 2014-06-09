#include "objects.h"

using namespace std;

object::object()
{
		  body = NULL;
		  active = false;
}

object::object(b2Body * b, bool a)
{
		  body = b;
		  active = a;
}

object::object(const object & r)
{
		  body = r.body;
		  active = r.active;
}

object::~object()
{
		  if (world)
		  {
					 bool cont = true;
					 for (b2Body * tmp = world->GetBodyList(); tmp && cont; tmp = tmp->GetNext())
					 {
								if (tmp == body)
								{
										  world->DestroyBody(body);
										  cont = false;
								}
					 }
		  }
		  body = NULL;
		  active = false;
}

bool object::setBody (b2Body * b)
{
		  if (!b)
		  {
					 return false;
		  }
		  body = b;
		  if (body == b)
		  {
					 return true;
		  }
		  return false;
}

bool object::setActive (const bool & a)
{
		  active = a;
		  if (active == a)
		  {
					 return true;
		  }
		  return false;
}

/*
	const friend bool operator == (const object & r) const
	{
	if (body == r.getBody && active == r.isActive())
	{
	return true;
	}
	return false;
	}
	*/

moving_object::moving_object ()
{
		  start = b2Vec2(0.0f, 0.0f);
		  end = b2Vec2(0.0f, 0.0f);
		  direction = b2Vec2(0.0f, 0.0f);
		  speed = 0.0f;
		  active = false;
		  max_angle = 0.0f;
		  min_angle = 0.0f;
		  angular_speed = 0.0f;
}

moving_object::moving_object (b2Vec2 & st, b2Vec2 & e, b2Vec2 & d, const float & sp, const bool & aa, const float & maxa, const float & mina, const float & as)
{
		  start = st;
		  end = e;
		  direction = d;
		  speed = sp;
		  active = aa;
		  max_angle = maxa;
		  min_angle = mina;
		  angular_speed = as;
}

moving_object::moving_object (const moving_object & r) : object (r)
{
		  start = r.start;
		  end = r.end;
		  direction = r.direction;
		  speed = r.speed;
		  active = r.angle_active;
		  max_angle = r.max_angle;
		  min_angle = r.min_angle;
		  angular_speed = r.angular_speed;
}

b2Vec2 moving_object::getStart (void)
{
		  return start;
}

const b2Vec2 moving_object::getStart (void) const
{
		  return start;
}

b2Vec2 moving_object::getEnd (void)
{
		  return end;
}

const b2Vec2 moving_object::getEnd (void) const
{
		  return end;
}

b2Vec2 moving_object::getDirection (void)
{
		  return direction;
}

const b2Vec2 moving_object::getDirection (void) const
{
		  return direction;
}

float moving_object::getSpeed (void)
{
		  return speed;
}

bool moving_object::getAngleActive (void)
{
		  return angle_active;
}

float moving_object::getMaxAngle (void)
{
		  return max_angle;
}

float moving_object::getMinAngle (void)
{
		  return min_angle;
}

float moving_object::getAngularSpeed (void)
{
		  return angular_speed;
}

b2Vec2 moving_object::calcDirection (const b2Vec2 & a, const b2Vec2 & b)
{
		  b2Vec2 diff = b2Vec2((b.x - a.x), (b.y - a.y));
		  return (1.0f/calcMagnitude(diff)) * diff;
}

float moving_object::calcMagnitude (const b2Vec2 & v)
{
		  return (float)(sqrt(pow((double)v.x, 2.0) + pow((double)v.y, 2.0)));
}

bool moving_object::setStart (b2Vec2 & v)
{
		  start = v;
		  if (start == v)
		  {
					 if (setDirection (calcDirection(start, end)))
					 {
								return true;
					 }
		  }
		  return false;
}

bool moving_object::setEnd (b2Vec2 & v)
{
		  end = v;
		  if (end == v)
		  {
					 if (setDirection (calcDirection(start, end)))
					 {
								return true;
					 }
		  }
		  return false;
}

/* Do not use this functions unless you're sure about the direction.
 * This class will handle calculating the proper direction, but if you think you know better...
 */
bool moving_object::setDirection (b2Vec2 v)
{
		  direction = v;
		  if (direction == v)
		  {
					 return true;
		  }
		  return false;
}

void moving_object::reverseDirection (void)
{
		  direction *= -1.0f;
}

bool moving_object::setSpeed (const float & f)
{
		  speed = f;
		  if (speed == f)
		  {
					 return true;
		  }
		  return false;
}

bool moving_object::setAngleActive (const bool & b)
{
		  angle_active = b;
		  if (angle_active == b)
		  {
					 return true;
		  }
		  return false;
}

bool moving_object::setMaxAngle (const float & f)
{
		  max_angle = f;
		  if (max_angle == f)
		  {
					 return true;
		  }
		  return false;
}

bool moving_object::setMinAngle (const float & f)
{
		  min_angle = f;
		  if (min_angle == f)
		  {
					 return true;
		  }
		  return false;
}

bool moving_object::setAngularSpeed (const float & f)
{
		  angular_speed = f;
		  if (angular_speed == f)
		  {
					 return true;
		  }
		  return false;
}

portal_object::portal_object (const char * file, const bool & p, const bool & d, const bool & p1, const bool & p2)
{
		  strcpy(image_file, file);
		  portalable = p;
		  deadly = d;
		  p1_contacting = p1;
		  p2_contacting = p2;
		  prev_speed[0] = 0.0f;
		  prev_speed[1] = 0.0f;
		  prev_speed[2] = 0.0f;
}

portal_object::portal_object (const portal_object & r) : moving_object(r)
{
		  portalable = r.portalable;
		  deadly = r.deadly;
		  p1_contacting = r.p1_contacting;
		  p2_contacting = r.p2_contacting;
		  prev_speed[0] = r.prev_speed[0];
		  prev_speed[1] = r.prev_speed[1];
		  prev_speed[2] = r.prev_speed[2];
}

portal_object::~portal_object ()
{
		  portalable = false;
		  deadly = false;
		  p1_contacting = false;
		  p2_contacting = false;
		  prev_speed[0] = 0.0f;
		  prev_speed[1] = 0.0f;
		  prev_speed[2] = 0.0f;
}

bool portal_object::getPortalable (void)
{
		  return portalable;
}

bool portal_object::getDeadly (void)
{
		  return deadly;
}

bool portal_object::getP1Contacting (void)
{
		  return p1_contacting;
}

bool portal_object::getP2Contacting (void)
{
		  return p2_contacting;
}

float portal_object::getPrevSpeed (const int & n)
{
		  if (n > 0 && n < 3)
		  {
					 return prev_speed[n];
		  }
		  return prev_speed[0];
}

char * portal_object::getImageFile (void)
{
		  return image_file;
}

Ppmimage * portal_object::getImage (void)
{
		  return image;
}

GLuint portal_object::getTexture (void)
{
		  return texture;
}

bool portal_object::setPortalable (const bool & b)
{
		  portalable = b;
		  if (portalable == b)
		  {
					 return true;
		  }
		  return false;
}

bool portal_object::setDeadly (const bool & b)
{
		  deadly = b;
		  if (deadly == b)
		  {
					 return true;
		  }
		  return false;
}

bool portal_object::setP1Contacting (const bool & b)
{
		  p1_contacting = b;
		  if (p1_contacting == b)
		  {
					 return true;
		  }
		  return false;
}

bool portal_object::setP2Contacting (const bool & b)
{
		  p2_contacting = b;
		  if (p2_contacting == b)
		  {
					 return true;
		  }
		  return false;
}

bool portal_object::setImageFile (const char * f)
{
		  if (!f)
		  {
					 return false;
		  }
		  strcpy(image_file, f); // direction? HERE
		  if (setImage())
		  {
					 buildTexture();
					 return true;
		  }
		  return false;
}

bool portal_object::setImage (void)
{
		  if (image_file)
		  {
					 Ppmimage * tmp = ppm6GetImage(image_file);
					 if (tmp)
					 {
								image = tmp;
								if (image == tmp)
								{
										  return true;
								}
					 }
		  }
		  return false;
}

void portal_object::buildTexture (void)
{
		  unsigned char * sdata = NULL;

		  glGenTextures(1, &texture);
		  glBindTexture(GL_TEXTURE_2D, texture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(image);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);
}

