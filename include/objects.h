#pragma once
#include "const.h"
#include "log.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecNegate(a)	(a)[0]=(-(a)[0]); (a)[1]=(-(a)[1]); (a)[2]=(-(a)[2]);
#define VecDot(a,b)	((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecLen(a)	((a)[0]*(a)[0]+(a)[1]*(a)[1]+(a)[2]*(a)[2])
#define VecLenSq(a)	sqrtf((a)[0]*(a)[0]+(a)[1]*(a)[1]+(a)[2]*(a)[2])
#define VecCopy(a,b)	(b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2];
#define VecAdd(a,b,c) (c)[0]=(a)[0]+(b)[0]; (c)[1]=(a)[1]+(b)[1]; (c)[2]=(a)[2]+(b)[2]
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; (c)[1]=(a)[1]-(b)[1]; (c)[2]=(a)[2]-(b)[2]
#define VecS(A,a,b) (b)[0]=(A)*(a)[0]; (b)[1]=(A)*(a)[1]; (b)[2]=(A)*(a)[2]
#define VecAddS(A,a,b,c) (c)[0]=(A)*(a)[0]+(b)[0]; (c)[1]=(A)*(a)[1]+(b)[1]; (c)[2]=(A)*(a)[2]+(b)[2]
#define VecCross(a,b,c) (c)[0]=(a)[1]*(b)[2]-(a)[2]*(b)[1]; (c)[1]=(a)[2]*(b)[0]-(a)[0]*(b)[2]; (c)[2]=(a)[0]*(b)[1]-(a)[1]*(b)[0]
#define VecZero(v) (v)[0]=0.0;(v)[1]=0.0;v[2]=0.0
#define ABS(a) (((a)<0)?(-(a)):(a))
#define SGN(a) (((a)<0)?(-1):(1))
#define SGND(a) (((a)<0.0)?(-1.0):(1.0))
#define TOGGLE(a) (a = (a + 1) % 2)

typedef float Vec[3];
static const Vec zero_vec = {0.0, 0.0, 0.0};
static const Vec empty_vec = {-1.0, -1.0, -1.0};

static const int p_width = 3; // half width
static const int p_height = 10; // half height

extern int objcnt;
extern int xres;
extern int yres;

typedef struct _vec_list
{
	 Vec v;
	 _vec_list * next;
} vec_list;

class object
{
	 protected:
		  Vec pos;
		  Vec vel;
		  int portalable;
		  vec_list * head;
		  Vec n; // normal unit vector of object
		  Vec d; // directional unit vector of object. always normal to n
		  int deadly;
		  float edges[4];

	 public:
		  object (const object&);
		  object ();
		  ~object ();
		  vec_list * initNode (void);

		  int isEmpty (void);
		  float * getVert (int);
		  vec_list * getLastVert (void);
		  Vec * getVel (void);
		  void setVel(const float &, const float &, const float &);
		  Vec * getPos (void);
		  Vec * getN (void);
		  Vec * getD (void);
		  float getNormalAngle (void);
		  float getDirectionalAngle (void);
		  int isPortalable (void);
		  int isDeadly (void);
		  float getEdge (const int &);

		  string toString (void);
		  string dumpCsv (void);

		  void addVec (const float &, const float &, const float &);
		  void setPos (void);
		  void setPos (const float &, const float &, const float &);
		  void shiftPos (const float &, const float &, const float &);
		  void setHead (const vec_list *);
		  void setN (const float &, const float &, const float &);
		  void setD (const float &, const float &, const float &);
		  void shiftN (const float &, const float &, const float &);
		  void shiftD (const float &, const float &, const float &);
		  void invertD (void);
		  void invertN (void);
		  void makeUnit (Vec *);
		  void initVectors (void);
		  void setEdges (void);
		  void shiftEdges (const float &, const float &, const float &);
		  void setPortalable (const int &a = -1);
		  void setDeadly (const int &);

		  object& operator = (const object &);
};

class portal : public object
{
	 protected:
		  int is_placed;

		  void drawPortal (void); // a rectangle idiot

	 public:
		  portal ();
		  portal (const portal &);
		  ~portal ();

		  int getIsPlaced (void);
		  int isPlaced (void);
		  string toString (void);
		  string dumpCsv (void);

		  void setIsPlaced (const int &);
		  void setPlaced (const int &);


		  portal& operator = (const portal&);

		  friend bool operator == (const portal &, const portal &);
};
