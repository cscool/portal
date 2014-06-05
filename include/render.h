#pragma once
#include "Box2D/Box2D.h"
#include "log.h"
#include "ppm.h"
#include "render.h"
#include "physics.h"
#include "const.h"
#include "contains.h"
#include "turret.h"
#include "door.h"
#include "goat.h"
#include "button.h"
#include "mine.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <lens.h>

using namespace std;

extern Display * dpy;
extern Window win;
extern GLXContext glc;
extern const float M2P;
extern const float P2M;
extern bool normalTesting;
extern b2Body * myPlayer;
extern int player_direction;
extern int xres;
extern int yres;
extern b2Body * p1;
extern b2Body * p2;
extern Turret * turrets;
extern int p_isleft;
extern b2Vec2 p_vel;
extern b2Body * p_obj;
extern b2Vec2 p1_dir;
extern b2Vec2 p2_dir;
extern b2Vec2 p_pos;
extern float p_angle;
extern b2Body * gunEnemy1;
extern b2Body * gunEnemy2;
extern Goat * goats;
extern Lens * lens;

extern GLuint silhouetteTexture;

extern Ppmimage * turretEnemyImage;
extern GLuint turretEnemyTexture;
extern Ppmimage * turretEnemyRightImage;
extern GLuint turretEnemyRightTexture;
extern Ppmimage * mirrorImage;
extern GLuint mirrorTexture;
extern Ppmimage * lensImage;
extern GLuint lensTexture;
extern Ppmimage * goatImage;
extern GLuint goatTexture;
extern Ppmimage * mineImage;
extern GLuint mineTexture;
extern Ppmimage * playerLeftImage;
extern GLuint playerLeftTexture;
extern Ppmimage * playerRightImage;
extern GLuint playerRightTexture;
extern Ppmimage * gunLeftImage;
extern GLuint gunLeftTexture;
extern Ppmimage * gunRightImage;
extern GLuint gunRightTexture;
extern Ppmimage * labratImage;
extern GLuint labratTexture;
extern Ppmimage * wall1Image;
extern GLuint wall1Texture;
extern Ppmimage * wall2Image;
extern GLuint wall2Texture;
extern Ppmimage * buttonImage;
extern GLuint buttonTexture;
extern Ppmimage * buttonDepressedImage;
extern GLuint buttonDepressedTexture;
extern Ppmimage * p1Image;
extern GLuint p1Texture;
extern Ppmimage * p2Image;
extern GLuint p2Texture;
extern Ppmimage * pwallImage;
extern GLuint pwallTexture;
extern Ppmimage * npwallImage;
extern GLuint npwallTexture;
extern Ppmimage * spikeImage;
extern GLuint spikeTexture;
extern Ppmimage * pauseMenuImage;
extern GLuint pauseMenuTexture;
extern Ppmimage * mainMenuImage;
extern GLuint mainMenuTexture;
extern Ppmimage * cCubeImage;
extern GLuint cCubeTexture;
extern Ppmimage * goatRightImage;
extern GLuint goatRightTexture;
extern Ppmimage * dMenuImage;
extern GLuint dMenuTexture;
extern Ppmimage * mine2Image;
extern GLuint mine2Texture;

extern int state;

void drawEnemy(b2Body * b);
void drawGoat(b2Body * g);
void drawCompanion(b2Body * b);
void drawMenu();
float getWidth(b2Body *b);
float getHeight(b2Body *b);
void drawWall(b2Body * b, const int & n);
void init_opengl(void);
void init_images(void);
void render(void);
void drawPlayer();
void drawPortal(b2Body * p);
void drawFoot();
void drawButton(Button);
void drawSquare(b2Vec2* points, b2Vec2 center, float angle, int & color);
void camera();
void drawMine(Mine);
unsigned char *buildAlphaData(Ppmimage *img);
void calcLaser(Turret);
void drawLaser(b2Vec2, b2Vec2);
void drawGunLaser();
void drawSpikes(b2Body * b);
void drawGunEnemySight(b2Body *);
void drawExplode(b2Body * b);
