#include "render.h"

using namespace std;

void init_opengl(void)
{
		  glMatrixMode( GL_PROJECTION);
		  glOrtho(0, xres, yres, 0, -1, 1);
		  glMatrixMode(GL_MODELVIEW);
		  glClearColor(0,0,0,1);
		  /*
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  glBindTexture(GL_TEXTURE_2D, labratTexture);
		  glBegin(GL_QUADS);
		  glTexCoord2f(0.0f, 1.0f); //glVertex2i(-wid,-wid);
		  glTexCoord2f(0.0f, 0.0f); //glVertex2i(-wid, wid);
		  glTexCoord2f(1.0f, 0.0f); //glVertex2i( wid, wid);
		  glTexCoord2f(1.0f, 1.0f); //glVertex2i( wid,-wid);
		  glEnd();
		  glPopMatrix();
		  glDisable(GL_TEXTURE_2D);
		  */
}

void init_images(void)
{
		  mineImage = ppm6GetImage((char *)"./images/mine2.ppm");
		  glGenTextures(1, &mineTexture);
		  glBindTexture(GL_TEXTURE_2D, mineTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		  glTexImage2D(GL_TEXTURE_2D, 0, 3, mineImage->width, mineImage->height, 0, GL_RGB, GL_UNSIGNED_BYTE, mineImage->data);

		  playerLeftImage = ppm6GetImage((char *)"./images/player_left.ppm");
		  glGenTextures(1, &playerLeftTexture);
		  glBindTexture(GL_TEXTURE_2D, playerLeftTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		  glTexImage2D(GL_TEXTURE_2D, 0, 3, playerLeftImage->width, playerLeftImage->height, 0, GL_RGB, GL_UNSIGNED_BYTE, playerLeftImage->data);

		  playerRightImage = ppm6GetImage((char *)"./images/player_right.ppm");
		  glGenTextures(1, &playerRightTexture);
		  glBindTexture(GL_TEXTURE_2D, playerRightTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		  glTexImage2D(GL_TEXTURE_2D, 0, 3, playerRightImage->width, playerRightImage->height, 0, GL_RGB, GL_UNSIGNED_BYTE, playerRightImage->data);

		  gunLeftImage = ppm6GetImage((char *)"./images/gun_left.ppm");
		  glGenTextures(1, &gunLeftTexture);
		  glBindTexture(GL_TEXTURE_2D, gunLeftTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		  glTexImage2D(GL_TEXTURE_2D, 0, 3, gunLeftImage->width, gunLeftImage->height, 0, GL_RGB, GL_UNSIGNED_BYTE, gunLeftImage->data);

		  gunRightImage = ppm6GetImage((char *)"./images/gun_right.ppm");
		  glGenTextures(1, &gunRightTexture);
		  glBindTexture(GL_TEXTURE_2D, gunRightTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		  glTexImage2D(GL_TEXTURE_2D, 0, 3, gunRightImage->width, gunRightImage->height, 0, GL_RGB, GL_UNSIGNED_BYTE, gunRightImage->data);

		  labratImage = ppm6GetImage((char *)"./images/labrat.ppm");
		  glGenTextures(1, &labratTexture);
		  glBindTexture(GL_TEXTURE_2D, labratTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		  glTexImage2D(GL_TEXTURE_2D, 0, 3, labratImage->width, labratImage->height, 0, GL_RGB, GL_UNSIGNED_BYTE, labratImage->data);
}

void camera() {
		  glMatrixMode(GL_PROJECTION);
		  glLoadIdentity();
		  float posx = myPlayer->GetPosition().x*M2P;
		  float posy = myPlayer->GetPosition().y*M2P;
		  float adjusty = 250;//The higher this is, the more shifted up the camera
		  float zoomScale = 1.00;//lower scale = zoomed out
		  //glPushMatrix();
		  //glTranslatef(myPlayer->GetPosition().x*M2P, myPlayer->GetPosition().y*M2P, 0);
		  //glPopMatrix();
		  gluOrtho2D(posx-xres/zoomScale, posx+xres/zoomScale, posy+yres/zoomScale-adjusty, posy-yres/zoomScale-adjusty);
		  glMatrixMode(GL_MODELVIEW);
		  glLoadIdentity();
}

void drawSquare(b2Vec2* points, b2Vec2 center, float angle, int & color)
{
		  //		  Log("color = %d\n", color);
		  if (color == 0)
		  {
					 glColor3f(1,1,1);
		  }
		  else if (color == 1)
		  {
					 glColor3f(0, 0, 1);
		  }
		  else if (color == 2)
		  {
					 glColor3f(1, 0, 0);
		  }
		  else
		  {
					 glColor3f(0, 1, 0);
		  }
		  glPushMatrix();
		  glTranslatef(center.x*M2P, center.y*M2P, 0);
		  glRotatef(angle*180.0/M_PI, 0, 0, 1);
		  glBegin(GL_QUADS);
		  for(int i = 0; i < 4; i++)
					 glVertex2f(points[i].x*M2P, points[i].y*M2P);
		  glEnd();
		  glPopMatrix();
}

void drawPortal(b2Body * p)
{
		  if (contains((char *)(p->GetUserData()), (char *)"left"))
		  {
					 glColor3f(0,0,1);
		  }
		  else
		  {
					 glColor3f(1,0,0);
		  }
		  glPushMatrix();
		  glTranslatef(p->GetPosition().x*M2P, p->GetPosition().y*M2P, 0.0f);
		  //		  Log("in drawPortal, angle = %.2f\n", p->GetAngle());
		  glRotatef((p->GetAngle())*R2D, 0.0f, 0.0f, 1.0f);
		  b2Vec2 points[4];
		  b2Fixture * tmp = p->GetFixtureList();
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

void drawPlayer(void)
{
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  glTranslatef(myPlayer->GetPosition().x*M2P, myPlayer->GetPosition().y*M2P, 0);
		  glRotatef(myPlayer->GetAngle()*180.0/M_PI, 0, 0, 1);
		  if (player_direction == 1)
		  {
					 glBindTexture(GL_TEXTURE_2D, playerRightTexture);
		  }
		  else
		  {
					 glBindTexture(GL_TEXTURE_2D, playerLeftTexture);
		  }
		  b2Vec2 points[4];
		  b2Fixture * tmp = myPlayer->GetFixtureList();
		  while (tmp)
		  {
					 for(int i=0; i < 4; i++)
								points[i] = ((b2PolygonShape*)tmp->GetShape())->GetVertex(i);
					 glBegin(GL_QUADS);
					 for(int i = 0; i < 4; i++)
					 {
								switch (i)
								{
										  case 0:
													 glTexCoord2f(0.0f, 1.0f); //glVertex2i(-wid,-wid);
													 break;
										  case 1:
													 glTexCoord2f(0.0f, 0.0f); //glVertex2i(-wid, wid);
													 break;
										  case 2:
													 glTexCoord2f(1.0f, 0.0f); //glVertex2i( wid, wid);
													 break;
										  case 3:
													 glTexCoord2f(1.0f, 1.0f); //glVertex2i( wid,-wid);
													 break;
								}
								glVertex2f(points[i].x*M2P, points[i].y*M2P);
					 }
					 glEnd();
					 tmp = tmp->GetNext();
		  }
		  glDisable(GL_TEXTURE_2D);
		  glEnable(GL_TEXTURE_2D);
		  tmp = myGun->GetFixtureList();
		  glRotatef(myGun->GetAngle()*R2D, 0, 0, 1);
		  if (player_direction == 1)
		  {
					 glBindTexture(GL_TEXTURE_2D, gunRightTexture);
		  }
		  else
		  {
					 glBindTexture(GL_TEXTURE_2D, gunLeftTexture);
		  }
		  while (tmp)
		  {
					 for(int i=0; i < 4; i++)
								points[i] = ((b2PolygonShape*)tmp->GetShape())->GetVertex(i);
					 glBegin(GL_QUADS);
					 for(int i = 0; i < 4; i++)
					 {
								switch (i)
								{
										  case 0:
													 glTexCoord2f(0.0f, 1.0f); //glVertex2i(-wid,-wid);
													 break;
										  case 1:
													 glTexCoord2f(0.0f, 0.0f); //glVertex2i(-wid, wid);
													 break;
										  case 2:
													 glTexCoord2f(1.0f, 0.0f); //glVertex2i( wid, wid);
													 break;
										  case 3:
													 glTexCoord2f(1.0f, 1.0f); //glVertex2i( wid,-wid);
													 break;
								}
								glVertex2f(points[i].x*M2P, points[i].y*M2P);
					 }
					 glEnd();
					 tmp = tmp->GetNext();
		  }
		  glDisable(GL_TEXTURE_2D);
		  glPopMatrix();
}

void render(void)
{
		  //		  Log("in render\n");
		  glClear(GL_COLOR_BUFFER_BIT);
		  glLoadIdentity();
		  b2Vec2 points[4];
		  b2Body* tmp = world->GetBodyList();
		  char * ud;
		  int color = 0;
		  while(tmp)
		  {
					 //					 Log("in while loop\n");
					 for(int i=0; i < 4; i++)
					 {
								points[i] = ((b2PolygonShape*)tmp->GetFixtureList()->GetShape())->GetVertex(i);
					 }
					 ud = (char *)(tmp->GetUserData());
					 color = 0;
					 if (ud)
					 {
								if (contains(ud, (const char *)("platform")))
								{
										  //Log("found platform\n");
										  movePlatform(tmp);
								}
								else if (contains(ud, (const char *)"bullet left"))
								{
										  //					 Log("left bullet\n");
										  color = 1;
								}
								else if (contains(ud, (const char *)"bullet right"))
								{
										  //					 Log("right bullet\n");
										  color = 2;
								}
								else if (contains(ud, (const char *)"wall") || contains(ud, (const char *)"floor") || contains(ud, (const char *)"ceiling"))
								{
										  color = 0;
								}
								else if (contains(ud, (const char *)"foot"))
								{
										  tmp = tmp->GetNext();
										  continue;
								}
								else
								{
										  color = 3;
								}
					 }
					 drawSquare(points, tmp->GetPosition(), tmp->GetAngle(), color);
					 tmp = tmp->GetNext();
		  }
		  //drawFoot();
		  if (p_isleft >= 0)
		  {
					 createPortal(p_pos, p_angle, p_isleft);
					 p_isleft = -1;
		  }
		  if (p1)
		  {
					 //					 Log("drawing left portal\n");
					 drawPortal(p1);
		  }
		  if (p2)
		  {
					 //					 Log("drawing right portal\n");
					 drawPortal(p2);
		  }
		  if (p_dest)
		  {
					 doPortal(p_obj);
					 p_dest = (char *)"";
		  }
		  drawPlayer();
		  camera();
		  glXSwapBuffers(dpy, win);
}
