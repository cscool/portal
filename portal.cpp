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
#include <timing.h>

using namespace std;

//PPM Images
Ppmimage * mineImage = NULL;
GLuint mineTexture;
GLuint silhouetteTexture;

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

//Setup timers
const double physicsRate = 1.0 / 60.0;
const double oobillion = 1.0 / 1e9;
struct timespec timeStart, timeCurrent;
struct timespec timePause;
double physicsCountdown=0.0;
double timeSpan=0.0;

// other globals
int keys[65536];
bool running = true;
bool pauseGame = false;
int player_direction = 1; // right

//macros
#define rnd() (((double)rand())/(double)RAND_MAX)
#define random(a) (rand()%a)

//function prototypes
void init_opengl(void);
void check_mouse(XEvent *);
void check_keys(XEvent *);
void init(void);
void step(void);
void check_resize(void);
void init_images(void);
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
								while(XPending(dpy))
								{
										  XNextEvent(dpy, &e);
										  check_mouse(&e);
										  check_keys(&e);
								}
								clock_gettime(CLOCK_REALTIME, &timeCurrent);
								timeSpan = timeDiff(&timeStart, &timeCurrent);
								timeCopy(&timeStart, &timeCurrent);
								physicsCountdown += timeSpan;
								while(physicsCountdown >= physicsRate)
								{
										  physics();
										  physicsCountdown -= physicsRate;
								}
								render();
								world->Step(1.0/30.0,8,3);
								world->ClearForces();
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
		  init_opengl();
		  srand(time(NULL));
		  clock_gettime(CLOCK_REALTIME, &timePause);
		  clock_gettime(CLOCK_REALTIME, &timeStart);
		  XAllowEvents(dpy, AsyncBoth, CurrentTime);
		  XGrabPointer(dpy, win, 1, PointerMotionMask | ButtonPressMask | ButtonReleaseMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
		  init_images();
		  init_b2d();
}

void init_images(void)
{
		  mineImage = ppm6GetImage((char *)"./images/mine2.ppm");
		  glGenTextures(1, &mineTexture);
		  glBindTexture(GL_TEXTURE_2D, mineTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		  glTexImage2D(GL_TEXTURE_2D, 0, 3, mineImage->width, mineImage->height, 0, GL_RGB, GL_UNSIGNED_BYTE, mineImage->data);
}

void init_b2d(void)
{
		  world=new b2World(b2Vec2(0.0,10.0f));
		  toDestroy = NULL;
		  world->SetContactListener(&contact_handler);
		  gameFloor = addRect(xres*5, yres-50, xres*10, 50, 0.7f, 0.2f, 2, (char *)"floor portalable");
		  addRect(0.0f, yres/4-150, 50, yres*2, 0.0f, 0.2f, 2, (char *)"left wall portalable");//left wall
		  addRect(xres*10, yres/4-150, 50, yres*2, 0.0f, 0.2f, 2, (char *)"right wall portalable");//right wall
		  platform = addRect(0.5f*xres, 0.33f*yres, 250, 30, 100.0f, 0.0f, 3, (char *)"platform"); // platform
		  addObstacles();
		  myPlayer = addPlayer(50, 50, 60, 60, world, myGun);
		  addFoot(60);
}

void init_opengl(void)
{
		  glMatrixMode( GL_PROJECTION);
		  glOrtho(0, xres, yres, 0, -1, 1);
		  glMatrixMode(GL_MODELVIEW);
		  glClearColor(0,0,0,1);
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
