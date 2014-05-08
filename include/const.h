#ifndef _CONST_H
#define _CONST_H

static const float pi = 3.1416;
static const float timeslice = 1.0f;
static const float gravity = -0.5f;
#define ALPHA 1
#define LEFT 0
#define RIGHT 1
#define TOP 2
#define BOTTOM 3
#define LEFT_PORTAL_KEY 46
#define RIGHT_PORTAL_KEY 47
#define PLAYER 0
#define GUN 1

static const float D2R = 180.0f/(pi);
static const float R2D = (pi)/180.0f;

static const float player_width = 15.0f;
static const float player_height = 20.0f;

static const float portal_width = 20.0f;
static const float portal_height = 180.0f;

static const float gun_width = 40.0f;
static const float gun_height = 27.0f;

static const int min_width = 300;
static const int min_height = 200;
static const int max_width = 800;
static const int max_height = 600;

#endif // const.h
