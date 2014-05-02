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

#include "log.h"
#include "xwin.h"

using namespace std;

// X Windows variables
int xres = 640;
int yres = 480;
int zres = 1;
const float M2P = 20;
const float P2M = 1/M2P;

//Box2D
b2World* world;

//macros
#define rnd() (((double)rand())/(double)RAND_MAX)
#define random(a) (rand()%a)

//function prototypes
void init_opengl(void);
void check_mouse(XEvent *e);
void check_keys(XEvent *e);
void init();
void physics(void);
void render(void);
void step();
void check_resize();
void camera();

//Setup timers
const double physicsRate = 1.0 / 60.0;
const double oobillion = 1.0 / 1e9;
struct timespec timeStart, timeCurrent;
struct timespec timePause;
double physicsCountdown=0.0;
double timeSpan=0.0;
double timeDiff(struct timespec *start, struct timespec *end) {
		  return (double)(end->tv_sec - start->tv_sec ) +
					 (double)(end->tv_nsec - start->tv_nsec) * oobillion;
}
void timeCopy(struct timespec *dest, struct timespec *source) {
		  memcpy(dest, source, sizeof(struct timespec));
}


bool running = true;

Display *dpy;
Window win;
GLXContext glc;

bool pauseGame = false;

int keys[65536];

b2Body * myPlayer;
b2Body * gameFloor;

enum _moveState {
		  MS_STOP,
		  MS_LEFT,
		  MS_RIGHT,
};

_moveState moveState = MS_STOP;

int main(void)
{
		  logOpen();
		  running = true;
		  pauseGame = false;
		  initXWindows();
		  XEvent e;
		  init_opengl();
		  srand(time(NULL));
		  clock_gettime(CLOCK_REALTIME, &timePause);
		  clock_gettime(CLOCK_REALTIME, &timeStart);

		  XAllowEvents(dpy, AsyncBoth, CurrentTime);
		  XGrabPointer(dpy, win, 1, PointerMotionMask | ButtonPressMask | ButtonReleaseMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);

		  while(running) {
					 if(!pauseGame){
								while(XPending(dpy)) {
										  XEvent e;
										  XNextEvent(dpy, &e);
										  check_mouse(&e);
										  check_keys(&e);
										  //step();
								}
								clock_gettime(CLOCK_REALTIME, &timeCurrent);
								timeSpan = timeDiff(&timeStart, &timeCurrent);
								timeCopy(&timeStart, &timeCurrent);
								physicsCountdown += timeSpan;
								while(physicsCountdown >= physicsRate) {
										  physics();
										  physicsCountdown -= physicsRate;
								}
								render();
								world->Step(1.0/30.0,8,3);
								world->ClearForces();
					 }
					 else if(pauseGame) {
								XEvent e;
								XNextEvent(dpy, &e);
								check_keys(&e);
					 }
		  }
		  cleanupXWindows();
		  logClose();
		  return 0;
}

b2Body* addRect(int x, int y, int w, int h, float f, float d, int dyn, char * udata = NULL)
{
		  //bodydef (pos, type)

		  b2BodyDef bodydef;
		  bodydef.position.Set(x*P2M, y*P2M);
		  if(dyn == 1)
		  {
					 bodydef.type=b2_dynamicBody;
		  }
		  else if (dyn == 2)
		  {
					 bodydef.type=b2_staticBody;
		  }
		  else
		  {
					 bodydef.type=b2_kinematicBody;
		  }
		  bodydef.linearDamping = d;
		  bodydef.fixedRotation = false;
		  b2Body* body = world->CreateBody(&bodydef);
		  b2PolygonShape shape;
		  shape.SetAsBox(P2M*w/2.0, P2M*h/2.0);

		  b2FixtureDef fixturedef;
		  fixturedef.shape = &shape;
		  fixturedef.density = 1.0;
		  fixturedef.friction = f;
		  body->CreateFixture(&fixturedef);
		  if (udata)
		  {
					 body->SetUserData((void*)udata);
					 if (udata == (char *)("platform"))
					 {
								//Log("it is a platform , setting initial velocity\n");
								body->SetLinearVelocity(b2Vec2(5.0f, 0.0f));
					 }
		  }
		  return body;
}

b2Body* addPlayer(int x, int y, int w, int h)
{
		  b2BodyDef bodydef;
		  bodydef.position.Set(x*P2M, y*P2M);
		  bodydef.type = b2_dynamicBody;
		  bodydef.gravityScale = 1.0f;
		  bodydef.fixedRotation = true;
		  b2Body* body = world->CreateBody(&bodydef);
		  b2PolygonShape shape;
		  shape.SetAsBox(P2M*w/2.0,P2M*h/2.0);

		  b2FixtureDef fixturedef;

		  fixturedef.shape = &shape;
		  fixturedef.density = 1.0;
		  body->CreateFixture(&fixturedef);


		  return body;
}

void addFoot(int h)
{
		  b2PolygonShape shape;
		  shape.SetAsBox(P2M*40, P2M*40, b2Vec2(0,(h/2)), 0);

		  b2FixtureDef fixturedef;
		  fixturedef.shape = &shape;
		  fixturedef.density = 0.0f;
		  fixturedef.isSensor = true;
		  b2Fixture* footSensorFixture = myPlayer->CreateFixture(&fixturedef);
}

void addObstacles()
{
		  //top of floor is yres-50-25 = yres-75
		  float onFloor = yres-75;
		  addRect(800, yres-105, 60, 60, 0.02f, 0.2f, 1);//bottomleft of stack
		  addRect(865, yres-105, 60, 60, 0.02f, 0.2f, 1);//bottom right
		  addRect(832.5, yres-170, 60, 60, 0.02f, 0.2f, 1);//top

		  addRect(1200, onFloor-15, 80, 30, 0.7f, 0.2f, 2);// stairs
		  addRect(1280, onFloor-30, 80, 60, 0.7f, 0.2f, 2);
		  addRect(1360, onFloor-45, 80, 90, 0.7f, 0.2f, 2);
		  addRect(1440, onFloor-60, 80, 120, 0.7f, 0.2f, 2);
		  addRect(1520, onFloor-75, 80, 150, 0.7f, 0.2f, 2);
}

void init_opengl(void)
{
		  glMatrixMode( GL_PROJECTION);
		  glOrtho(0, xres, yres, 0, -1, 1);
		  glMatrixMode(GL_MODELVIEW);
		  glClearColor(0,0,0,1);
		  world=new b2World(b2Vec2(0.0,10.0f));
		  gameFloor = addRect(xres*3/2, yres-50, xres*3, 50, 0.7f, 0.2f, 2);
		  addRect(0.0f, yres/4-150, 50, yres*2, 0.0f, 0.2f, 2);//left wall
		  addRect(xres*3, yres/4-150, 50, yres*2, 0.0f, 0.2f, 2);//right wall
		  addRect(0.5f*xres, 0.33f*yres, 250, 30, 100.0f, 0.0f, 3, (char *)"platform"); // platform
		  addObstacles();
		  myPlayer = addPlayer(50, 50, 60, 60);
		  addFoot(60);
}

void check_mouse(XEvent *e)
{
		  //int key = XLookupKeysym(&e->xkey, 0);
		  //Did the mouse move?
		  //Was a mouse button clicked?
		  static int savex = 0;
		  static int savey = 0;
		  //
		  if (e->type == ButtonRelease) {
					 if (e->xbutton.button==1) {
								//Left button is down
								//addRect(e->xbutton.x, e->xbutton.y, 20, 20, true);
					 }
		  }
		  if (e->type == ButtonPress) {
					 if (e->xbutton.button==1) {
								//Left button is down
								//addRect(e->xbutton.x, e->xbutton.y, 20, 20, true);
					 }
					 if (e->xbutton.button==3) {
								//Right button is down
								//addRect(e->xbutton.x, e->xbutton.y, 20, 20, true);
					 }
		  }
		  if (savex != e->xbutton.x || savey != e->xbutton.y) {
					 //Mouse moved
					 savex = e->xbutton.x;
					 savey = e->xbutton.y;
		  }
}

void check_keys(XEvent *e)
{
		  static int shift=0;
		  int key = XLookupKeysym(&e->xkey, 0);
		  if(!pauseGame) {
					 if (e->type == KeyRelease)
					 {
								keys[key]=0;
								if (key == XK_Shift_L || key == XK_Shift_R)
										  shift=0;
					 }
					 if (e->type == KeyPress)
					 {
								if (key == XK_Escape)
								{
										  running = false;
										  return;
								}
								keys[key]=1;
								if (key == XK_Shift_L || key == XK_Shift_R) {
										  shift=1;
										  return;
								}
								if (key == XK_p)
								{
										  if(pauseGame)
													 pauseGame = false;
										  else
													 pauseGame = true;
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
		  else {
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


void physics (void)
{
		  if (pauseGame)
		  {
					 /* do nothing */
		  }
		  else
		  {
					 b2Vec2 vel = myPlayer->GetLinearVelocity();
					 if (keys[XK_Up] == 1 || keys[XK_w])
					 {
								/* rotate gun up */
					 }
					 if (keys[XK_Down] == 1 || keys[XK_s])
					 {
								/* rotate gun down */
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

					 myPlayer->SetLinearVelocity(vel);
		  }
}

void movePlatform (b2Body * p, const float lmax = -243.0f, const float rmax = 338.5f)
{
		  b2Vec2 pos = p->GetWorldCenter();
		  Log("pos.x = %.2f, rmax = %.2f, lmax = %.2f\n", pos.x, rmax, lmax);
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

void step() {
		  b2Vec2 vel = myPlayer->GetLinearVelocity();
		  switch ( moveState )
		  {
					 case MS_LEFT:  vel.x = b2Max( vel.x - 0.01f, -1.0f ); break;
					 case MS_STOP:  vel.x *=  0.98; break;
					 case MS_RIGHT: vel.x = b2Min( vel.x + 0.01f,  1.0f ); break;
		  }
		  myPlayer->SetLinearVelocity( vel );
}

void camera() {
		  glMatrixMode(GL_PROJECTION);
		  glLoadIdentity();
		  float posx = myPlayer->GetWorldCenter().x*M2P;
		  float posy = myPlayer->GetWorldCenter().y*M2P;
		  float adjusty = 250;//The higher this is, the more shifted up the camera
		  float zoomScale = 1.00;//lower scale = zoomed out
		  //glPushMatrix();
		  //glTranslatef(myPlayer->GetWorldCenter().x*M2P, myPlayer->GetWorldCenter().y*M2P, 0);
		  //glPopMatrix();
		  gluOrtho2D(posx-xres/zoomScale, posx+xres/zoomScale, posy+yres/zoomScale-adjusty, posy-yres/zoomScale-adjusty);
		  glMatrixMode(GL_MODELVIEW);
		  glLoadIdentity();
}


void drawSquare(b2Vec2* points, b2Vec2 center, float angle)
{
		  glColor3f(1,1,1);
		  glPushMatrix();
		  glTranslatef(center.x*M2P, center.y*M2P, 0);
		  glRotatef(angle*180.0/M_PI, 0, 0, 1);
		  glBegin(GL_QUADS);
		  for(int i = 0; i < 4; i++)
					 glVertex2f(points[i].x*M2P, points[i].y*M2P);
		  glEnd();
		  glPopMatrix();
}

void drawFoot()
{
		  glColor3f(0,100,0);
		  glPushMatrix();
		  glTranslatef(myPlayer->GetWorldCenter().x*M2P, myPlayer->GetWorldCenter().y*M2P, 0);
		  glRotatef(myPlayer->GetAngle()*180.0/M_PI, 0, 0, 1);
		  b2Vec2 points[4];
		  b2Fixture * tmp = myPlayer->GetFixtureList();
		  tmp = tmp->GetNext();
		  for(int i=0; i < 4; i++)
					 points[i] = ((b2PolygonShape*)tmp->GetShape())->GetVertex(i);
		  glBegin(GL_QUADS);
		  for(int i = 0; i < 4; i++)
					 glVertex2f(points[i].x*M2P, points[i].y*M2P);
		  glEnd();
		  glPopMatrix();
}

void drawPlayer()
{
		  glColor3f(0,1,0);
		  glPushMatrix();
		  glTranslatef(myPlayer->GetWorldCenter().x*M2P, myPlayer->GetWorldCenter().y*M2P, 0);
		  glRotatef(myPlayer->GetAngle()*180.0/M_PI, 0, 0, 1);
		  b2Vec2 points[4];
		  b2Fixture * tmp = myPlayer->GetFixtureList();
		  while (tmp)
		  {
					 for(int i=0; i < 4; i++)
								points[i] = ((b2PolygonShape*)tmp->GetShape())->GetVertex(i);
					 glBegin(GL_QUADS);
					 for(int i = 0; i < 4; i++)
								glVertex2f(points[i].x*M2P, points[i].y*M2P);
					 glEnd();
					 tmp = tmp->GetNext();
		  }
		  glPopMatrix();
}

void render(void)
{
		  glClear(GL_COLOR_BUFFER_BIT);
		  //glPushMatrix();
		  glLoadIdentity();
		  b2Body* tmp = world->GetBodyList();
		  b2Vec2 points[4];
		  while(tmp)
		  {
					 if ((char *)(tmp->GetUserData()) == (char *)("platform"))
					 {
								//Log("found platform\n");
								movePlatform(tmp);
					 }
					 for(int i=0; i < 4; i++)
								points[i] = ((b2PolygonShape*)tmp->GetFixtureList()->GetShape())->GetVertex(i);
					 drawSquare(points, tmp->GetWorldCenter(), tmp->GetAngle());
					 tmp = tmp->GetNext();
		  }
		  camera();
		  drawPlayer();
		  drawFoot();
		  //glPopMatrix();
		  glXSwapBuffers(dpy, win);
}
