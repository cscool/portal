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
bool pauseGame = false;

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
	 initXWindows();
	 XEvent e;
	 init_opengl();
	 srand(time(NULL));
	 clock_gettime(CLOCK_REALTIME, &timePause);
	 clock_gettime(CLOCK_REALTIME, &timeStart);

	 XAllowEvents(dpy, AsyncBoth, CurrentTime);
	 XGrabPointer(dpy, win, 1, PointerMotionMask | ButtonPressMask | ButtonReleaseMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);

	 while(running) {
		  while(XPending(dpy)) {
				XNextEvent(dpy, &e);
				check_mouse(&e);
				check_keys(&e);
				step();
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
	 }
	 cleanupXWindows();
	 logClose();
	 return 0;
}

b2Body* addRect(int x, int y, int w, int h, int f, bool dyn)
{
	 b2BodyDef bodydef;
	 bodydef.position.Set(x*P2M, y*P2M);
	 if(dyn)
		  bodydef.type=b2_dynamicBody;
	 else
		  bodydef.type=b2_staticBody;
	 b2Body* body = world->CreateBody(&bodydef);
	 b2PolygonShape shape;
	 shape.SetAsBox(P2M*w/2.0, P2M*h/2.0);

	 b2FixtureDef fixturedef;
	 fixturedef.shape = &shape;
	 fixturedef.density = 1.0;
	 fixturedef.friction = f;
	 body->CreateFixture(&fixturedef);
	 return body;
}

b2Body* addPlayer(int x, int y, int w, int h)
{
	 b2BodyDef bodydef;
	 bodydef.position.Set(x*P2M, y*P2M);
	 bodydef.type = b2_dynamicBody;
	 bodydef.gravityScale = 5.0f;
	 b2Body* body = world->CreateBody(&bodydef);
	 b2PolygonShape shape;
	 shape.SetAsBox(P2M*w/2.0,P2M*h/2.0);

	 b2FixtureDef fixturedef;
	 fixturedef.shape = &shape;
	 fixturedef.density = 1.0;
	 body->CreateFixture(&fixturedef);
	 return body;
}


void init_opengl(void)
{
	 glMatrixMode( GL_PROJECTION);
	 glOrtho(0, xres, yres, 0, -1, 1);
	 glMatrixMode(GL_MODELVIEW);
	 glClearColor(0,0,0,1);
	 world=new b2World(b2Vec2(0.0f,10.0f));
	 gameFloor = addRect(xres/2, yres-50, xres, 30, 0.05, false);
	 myPlayer = addPlayer(50, 50, 40, 40);
	addRect(xres/2, yres-70, 20, 20, 0.5f, false);
	addRect(xres/2 - 20, yres-70, 20, 20, 0.5f, false);
	addRect(xres/2, yres-90, 20, 20, 0.5f, false);
	addRect(xres/2 - 20, yres-90, 20, 20, 0.5f, false);
}

void check_mouse(XEvent *e)
{
	 Log("in check_mouse\ne->xbutton.button = %d\ne->type = %d\n", e->xbutton.button, e->type);
	 //Did the mouse move?
	 //Was a mouse button clicked?
	 static int savex = 0;
	 static int savey = 0;
//	 b2Body * companion_cube;
	 if (e->type == ButtonRelease) {
		  if (e->xbutton.button==0) {
				//Left button is down
				Log("got button release on left button\n");
//				companion_cube = addRect(e->xbutton.x, e->xbutton.y, 20, 20, true);
		  }
	 }
	 if (e->type == ButtonPress) {
		  if (e->xbutton.button==0) {
				//Left button is down
				Log("got button press on left button\n");
//				companion_cube = addRect(e->xbutton.x, e->xbutton.y, 20, 20, true);
		  }
		  if (e->xbutton.button==2) {
				//Right button is down
				Log("got button press on right button\n");
//				companion_cube = addRect(e->xbutton.x, e->xbutton.y, 20, 20, true);
		  }
	 }
	 if (savex != e->xbutton.x || savey != e->xbutton.y) {
		  //Mouse moved
		  savex = e->xbutton.x;
		  savey = e->xbutton.y;
		  Log("got mouse move, pos = %d, %d\n",savex, savey);
	 }
}

void check_keys(XEvent *e)
{
	 Log("in check_keys\ne->type = %d\ne->xbutton.button = %d\n", e->type, e->xbutton.button);
	 static int shift=0;
	 int key = XLookupKeysym(&e->xkey, 0);
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
		  if (keys[XK_space] == 1) // doesn't help
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

void drawPlayer()
{
	 glColor3f(0,1,0);
	 glPushMatrix();
	 glTranslatef(myPlayer->GetWorldCenter().x*M2P, myPlayer->GetWorldCenter().y*M2P, 0);
	 glRotatef(myPlayer->GetAngle()*180.0/M_PI, 0, 0, 1);
	 b2Vec2 points[4];
	 for(int i=0; i < 4; i++)
		  points[i] = ((b2PolygonShape*)myPlayer->GetFixtureList()->GetShape())->GetVertex(i);
	 glBegin(GL_QUADS);
	 for(int i = 0; i < 4; i++)
		  glVertex2f(points[i].x*M2P, points[i].y*M2P);
	 glEnd();
	 glPopMatrix();
}

void render(void)
{
	 glClear(GL_COLOR_BUFFER_BIT);
	 glLoadIdentity();
	 b2Body* tmp = world->GetBodyList();
	 b2Vec2 points[4];
	 while(tmp)
	 {
		  for(int i=0; i < 4; i++)
				points[i] = ((b2PolygonShape*)tmp->GetFixtureList()->GetShape())->GetVertex(i);
		  drawSquare(points, tmp->GetWorldCenter(), tmp->GetAngle());
		  tmp = tmp->GetNext();
	 }
	 drawPlayer();
	 glXSwapBuffers(dpy, win);
}
