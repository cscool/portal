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
#include <Box2D/Box2D.h>

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
	running = true;
	initXWindows();
	init_opengl();
	while(running) {
		while(XPending(dpy)) {
			XEvent e;
			XNextEvent(dpy, &e);
			check_mouse(&e);
			check_keys(&e);
			step();
		}
		render();
		world->Step(1.0/30.0,8,3);
	}
	cleanupXWindows();
	return 0;
}

b2Body* addRect(int x, int y, int w, int h, int f, bool dyn=true)
{
	//bodydef (pos, type)

	b2BodyDef bodydef;
	bodydef.position.Set(x*P2M, y*P2M);
	if(dyn)
		bodydef.type=b2_dynamicBody;
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

b2Body* addPlayer(int x, int y, int w, int h, bool dyn = true)
{
	b2BodyDef bodydef;
	bodydef.position.Set(x*P2M, y*P2M);
	bodydef.type = b2_dynamicBody;
	bodydef.gravityScale = 1.0f;
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
	world=new b2World(b2Vec2(0.0,1));
	gameFloor = addRect(xres/2, yres-50, xres, 30, 0.05, false);
	myPlayer = addPlayer(50, 50, 40, 40, true);
}

void check_mouse(XEvent *e)
{
	//Did the mouse move?
	//Was a mouse button clicked?
	static int savex = 0;
	static int savey = 0;
	//
	if (e->type == ButtonRelease) {
		//if (e->xbutton.button==1) {
		//Left button is down
		addRect(e->xbutton.x, e->xbutton.y, 20, 20, true);
		//}
	}
	if (e->type == ButtonPress) {
		//if (e->xbutton.button==1) {
		//Left button is down
		addRect(e->xbutton.x, e->xbutton.y, 20, 20, true);
		//}
		if (e->xbutton.button==3) {
			//Right button is down
			addRect(e->xbutton.x, e->xbutton.y, 20, 20, true);
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
	b2Vec2 vel = myPlayer->GetLinearVelocity();
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
		if (key == XK_Left)
		{
			//if(vel.x <= 50)
			//myPlayer->ApplyForce( b2Vec2(-5,0), myPlayer->GetWorldCenter(),true);
			//moveState = MS_LEFT;
			vel.x = -1;
			//myPlayer->SetLinearVelocity( vel );
		}
		if (key == XK_Right)
		{
			//if(vel.x > -50)
			//myPlayer->ApplyForce( b2Vec2(5,0), myPlayer->GetWorldCenter(),true);
			//moveState = MS_RIGHT;
			vel.x = 1;
			//myPlayer->SetLinearVelocity( vel );
		}
		if (key == XK_space) // doesn't help
		{
			//addRect(e->xbutton.x, e->xbutton.y, 20, 20, true);
			
			float impulse = myPlayer->GetMass() * 3.5f;
			myPlayer->ApplyLinearImpulse(b2Vec2(0,-impulse), myPlayer->GetWorldCenter(),true);
			vel = myPlayer->GetLinearVelocity();			
			//myPlayer->SetLinearVelocity( vel );
			return;
		}
		if (key == XK_a)
		{
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
	myPlayer->SetLinearVelocity( vel );
	

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
