#pragma once
#include <cmath>
#include <Box2D/Box2D.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <const.h>
#include <log.h>
#include <ppm.h>
#include <render.h>

using namespace std;

extern b2World * world;

class object
{
		  protected:
					 b2Body * body;
					 bool active;

		  public:
					 /* constructors */
					 object ();
					 object (b2Body *, bool a = false);
					 object (const object &);
					 ~object ();

					 /* overloaded operators */
					 //	 const friend bool operator == (object &) const;

					 /* accessors */
					 b2Body * getBody (void)
					 {
								return body;
					 }
					 const b2Body * getBody (void) const
					 {
								return body;
					 }
					 bool isActive (void)
					 {
								return active;
					 }

					 /* mutators */
					 bool setBody (b2Body *);
					 bool setActive (const bool &);
};

class moving_object : public object
{
		  protected:
					 b2Vec2 start;
					 b2Vec2 end;
					 b2Vec2 direction;
					 float speed;
					 bool angle_active;
					 float max_angle;
					 float min_angle;
					 float angular_speed;

					 b2Vec2 calcDirection (const b2Vec2 &, const b2Vec2 &);
					 float calcMagnitude (const b2Vec2 &);

		  public:
					 /* constructors */
					 moving_object();
					 moving_object(b2Vec2 &, b2Vec2 &, b2Vec2 &, const float &, const bool & aa = false, const float & maxa = 0.0f, const float & mina = 0.0f, const float & as = 0.0f);
					 moving_object(const moving_object &);

					 /* overloaded operators */

					 /* accessors */
					 b2Vec2 getStart (void);
					 const b2Vec2 getStart (void) const;
					 b2Vec2 getEnd (void);
					 const b2Vec2 getEnd (void) const;
					 b2Vec2 getDirection (void);
					 const b2Vec2 getDirection (void) const;
					 float getSpeed (void);
					 bool getAngleActive (void);
					 float getMaxAngle (void);
					 float getMinAngle (void);
					 float getAngularSpeed (void);

					 /* mutators */
					 bool setStart (b2Vec2 &);
					 bool setEnd (b2Vec2 &);
					 bool setDirection (b2Vec2);
					 void reverseDirection (void);
					 bool setSpeed (const float &);
					 bool setAngleActive (const bool &);
					 bool setMaxAngle (const float &);
					 bool setMinAngle (const float &);
					 bool setAngularSpeed (const float &);
};

class portal_object : public moving_object
{
		  protected:
					 bool portalable;
					 bool deadly;
					 bool p1_contacting;
					 bool p2_contacting;
					 float prev_speed[3];
					 char * image_file;
					 Ppmimage * image;
					 GLuint texture;

					 bool setImage (void);
					 void buildTexture (void);

		  public:
					 /* constructors */
					 portal_object (const char * file = NULL, const bool & p = false, const bool & d = false, const bool & p1 = false, const bool & p2 = false);
					 portal_object (const portal_object &);
					 ~portal_object ();

					 /* overloaded operators */

					 /* accessors */
					 bool getPortalable (void);
					 bool getDeadly (void);
					 bool getP1Contacting (void);
					 bool getP2Contacting (void);
					 float getPrevSpeed (const int & n = 0);
					 char * getImageFile (void);
					 Ppmimage * getImage (void);
					 GLuint getTexture (void);

					 /* mutators */
					 bool setPortalable (const bool &);
					 bool setDeadly (const bool &);
					 bool setP1Contacting (const bool &);
					 bool setP2Contacting (const bool &);
					 bool setImageFile (const char *);
};

