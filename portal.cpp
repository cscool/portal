#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Box2D/Box2D.h"
#include "ppm.h"
#include "render.h"
#include "physics.h"
#include "render.h"
#include "log.h"
#include "xwin.h"
#include <const.h>
#include "contact.h"
#include "arenas.h"
#include <timing.h>

using namespace std;

//PPM Images
GLuint silhouetteTexture;
Ppmimage * mineImage = NULL;
GLuint mineTexture;
Ppmimage * playerLeftImage = NULL;
GLuint playerLeftTexture;
Ppmimage * playerRightImage = NULL;
GLuint playerRightTexture;
Ppmimage * gunLeftImage = NULL;
GLuint gunLeftTexture;
Ppmimage * gunRightImage = NULL;
GLuint gunRightTexture;
Ppmimage * labratImage = NULL;
GLuint labratTexture;
Ppmimage * wallImage = NULL;
GLuint wallTexture;

// portaling vars
b2Vec2 p_pos;
float p_angle = 0.0f;
int p_isleft = -1;
b2Vec2 p_vel;
b2Body * p_obj;
b2Vec2 p1_dir;
b2Vec2 p2_dir;
char * p_dest;
int p_contacting = 0;

// X Windows variables
Display * dpy;
Window win;
GLXContext glc;
int xres = 640;
int yres = 480;
int zres = 1;
const float M2P = 20;
const float P2M = 1/M2P;

//Box2D
b2World * world;
b2Body * toDestroy;
contactListener contact_handler;
int bullet_ct = 0;
b2Fixture * myPlayerFoot;
b2Body * myPlayer;
b2Body * myGun;
b2Body * gameFloor;
b2Body * platform;
b2Body * p1;
b2Body * p2;
b2Body * mineObject;
b2Body * myDoor;
b2Body * carry;
int cwait = 0;

//Setup timers
const double physicsRate = 1.0 / 60.0;
const double oobillion = 1.0 / 1e9;
struct timespec timeStart, timeCurrent;
struct timespec timePause;
double physicsCountdown=0.0;
double timeSpan=0.0;
double t_limit = 1.0/60.0;

// other globals
int keys[65536];
bool running = true;
bool pauseGame = false;
int player_direction = 1; // right
bool can_jump = false;
int fix_vel = 0;
b2Vec2 mod_vel;

//macros
#define rnd() (((double)rand())/(double)RAND_MAX)
#define random(a) (rand()%a)

//function prototypes
void check_mouse(XEvent *);
void check_keys(XEvent *);
void init(void);
void step(void);
void check_resize(void);
void init_b2d(void);
void cleanup(void);

enum _moveState
{
		  MS_STOP,
		  MS_LEFT,
		  MS_RIGHT,
};
_moveState moveState = MS_STOP;

int main(void)
{
		  init();
		  XEvent e;

		  /* game loop */
		  while(running)
		  {
					 if(!pauseGame)
					 {
								clock_gettime(CLOCK_REALTIME, &timeCurrent);
								if (timeDiff(&timeStart, &timeCurrent) >= t_limit)
								{
										  while(XPending(dpy))
										  {
													 XNextEvent(dpy, &e);
													 check_mouse(&e);
													 check_keys(&e);
										  }
										  physics();
										  render();
										  world->Step(1.0/30.0,8,3);
										  world->ClearForces();
										  timeCopy(&timeStart, &timeCurrent);
										  Log("carry = %p\n", carry);
//										  Log("current player position:\n\t(%.2f, %.2f)\n", myPlayer->GetPosition().x, myPlayer->GetPosition().y);
//										  Log("p_contacting = %d\n", p_contacting);
								}
					 }
					 else if(pauseGame)
					 {
								XNextEvent(dpy, &e);
								check_keys(&e);
								check_mouse(&e);
					 }
		  }

		  cleanup();
		  return 0;
}

void cleanup(void)
{
		  cleanupXWindows();
		  logClose();
}

void init(void)
{
		  logOpen();
		  running = true;
		  pauseGame = false;
		  initXWindows();
		  init_images();
		  init_opengl();
		  srand(time(NULL));
		  clock_gettime(CLOCK_REALTIME, &timePause);
		  clock_gettime(CLOCK_REALTIME, &timeStart);
		  timeCopy(&timeStart, &timeCurrent);
		  XAllowEvents(dpy, AsyncBoth, CurrentTime);
		  XGrabPointer(dpy, win, 1, PointerMotionMask | ButtonPressMask | ButtonReleaseMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
		  init_b2d();
		  makeArena(0);
}

void check_mouse(XEvent *e)
{
		  //int key = XLookupKeysym(&e->xkey, 0);
		  //Did the mouse move?
		  //Was a mouse button clicked?
		  static int savex = 0;
		  static int savey = 0;
		  //
		  if (e->type == ButtonRelease)
		  {
					 if (e->xbutton.button==1)
					 {
								//Left button is down
								//addRect(e->xbutton.x, e->xbutton.y, 20, 20, true);
					 }
		  }
		  if (e->type == ButtonPress)
		  {
					 if (e->xbutton.button==1)
					 {
								//Left button is down
								//addRect(e->xbutton.x, e->xbutton.y, 20, 20, true);
					 }
					 if (e->xbutton.button==3)
					 {
								//Right button is down
								//addRect(e->xbutton.x, e->xbutton.y, 20, 20, true);
					 }
		  }
		  if (savex != e->xbutton.x || savey != e->xbutton.y)
		  {
					 //Mouse moved
					 savex = e->xbutton.x;
					 savey = e->xbutton.y;
		  }
}

void check_keys(XEvent * e)
{
		  static int shift=0;
		  int key = XLookupKeysym(&e->xkey, 0);
		  if(!pauseGame)
		  {
					 if (e->type == KeyRelease)
					 {
								keys[key]=0;
								if (key == XK_Shift_L || key == XK_Shift_R)
								{
										  shift=0;
								}
					 }
					 if (e->type == KeyPress)
					 {
								if (key == XK_Escape)
								{
										  running = false;
										  return;
								}

								keys[key] = 1;

								if (key == XK_Shift_L || key == XK_Shift_R)
								{
										  shift=1;
										  return;
								}
								if (key == XK_p)
								{
										  if(pauseGame)
										  {
													 pauseGame = false;
										  }
										  else
										  {
													 pauseGame = true;
										  }
										  return;
								}
					 }
					 else
					 {
								return;
					 }
					 if (shift)
					 {
								// run?
					 }
		  }
		  else
		  {
					 if (e->type == KeyPress)
					 {
								if (key == XK_p)
								{
										  pauseGame = false;
										  return;
								}
					 }
		  }
}

void init_b2d(void)
{
		  world=new b2World(b2Vec2(0.0,10.0f));
		  toDestroy = NULL;
		  world->SetContactListener(&contact_handler);
		  myDoor = addDoor(6*xres, yres-75);
		  myPlayer = addPlayer(350.0f, -350.0f, player_width, player_height, world, myGun);
}

void step(void)
{
		  b2Vec2 vel = myPlayer->GetLinearVelocity();
		  switch (moveState)
		  {
					 case MS_LEFT:
								vel.x = b2Max( vel.x - 0.01f, -1.0f );
								break;
					 case MS_STOP:
								vel.x *=  0.98;
								break;
					 case MS_RIGHT:
								vel.x = b2Min( vel.x + 0.01f,  1.0f );
								break;
		  }
		  myPlayer->SetLinearVelocity( vel );
}
