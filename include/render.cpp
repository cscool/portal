#include "render.h"

using namespace std;

void init_opengl(void)
{
		  glMatrixMode( GL_PROJECTION);
		  glOrtho(0, xres, yres, 0, -1, 1);
		  glMatrixMode(GL_MODELVIEW);
		  glClearColor(0,0,0,1);
		  glColor3f(1.0f,1.0f,1.0f);
}

unsigned char *buildAlphaData(Ppmimage *img)
{
		  //add 4th component to RGB stream...
		  int i;
		  int a,b,c;
		  unsigned char *newdata, *ptr;
		  unsigned char *data = (unsigned char *)img->data;
		  newdata = (unsigned char *)malloc(img->width * img->height * 4);
		  ptr = newdata;
		  for (i=0; i<img->width * img->height * 3; i+=3) {
					 a = *(data+0);
					 b = *(data+1);
					 c = *(data+2);
					 *(ptr+0) = a;
					 *(ptr+1) = b;
					 *(ptr+2) = c;
					 //new code, suggested by Chris Smith, Fall 2013
					 *(ptr+3) = (a|b|c);
					 //
					 ptr += 4;
					 data += 3;
		  }
		  return newdata;
}

void init_images(void)
{
		  labratImage = ppm6GetImage((char *)"./images/labrat.ppm");
		  glGenTextures(1, &labratTexture);
		  glBindTexture(GL_TEXTURE_2D, labratTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		  glTexImage2D(GL_TEXTURE_2D, 0, 3, labratImage->width, labratImage->height, 0, GL_RGB, GL_UNSIGNED_BYTE, labratImage->data);

		  unsigned char * sdata = NULL;

		  buttonDepressedImage = ppm6GetImage((char *)"./images/button1.ppm");
		  glGenTextures(1, &buttonDepressedTexture);
		  glBindTexture(GL_TEXTURE_2D, buttonDepressedTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(buttonDepressedImage);	
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, buttonDepressedImage->width, buttonDepressedImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  buttonImage = ppm6GetImage((char *)"./images/button.ppm");
		  glGenTextures(1, &buttonTexture);
		  glBindTexture(GL_TEXTURE_2D, buttonTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(buttonImage);	
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, buttonImage->width, buttonImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  mineImage = ppm6GetImage((char *)"./images/mine2.ppm");
		  glGenTextures(1, &mineTexture);
		  glBindTexture(GL_TEXTURE_2D, mineTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(mineImage);	
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mineImage->width, mineImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  playerLeftImage = ppm6GetImage((char *)"./images/player_left.ppm");
		  glGenTextures(1, &playerLeftTexture);
		  glBindTexture(GL_TEXTURE_2D, playerLeftTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(playerLeftImage);	
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, playerLeftImage->width, playerLeftImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  playerRightImage = ppm6GetImage((char *)"./images/player_right.ppm");
		  glGenTextures(1, &playerRightTexture);
		  glBindTexture(GL_TEXTURE_2D, playerRightTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(playerRightImage);	
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, playerRightImage->width, playerRightImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  gunLeftImage = ppm6GetImage((char *)"./images/gun_left.ppm");
		  glGenTextures(1, &gunLeftTexture);
		  glBindTexture(GL_TEXTURE_2D, gunLeftTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(gunLeftImage);	
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gunLeftImage->width, gunLeftImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  gunRightImage = ppm6GetImage((char *)"./images/gun_right.ppm");
		  glGenTextures(1, &gunRightTexture);
		  glBindTexture(GL_TEXTURE_2D, gunRightTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(gunRightImage);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gunRightImage->width, gunRightImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  wall1Image = ppm6GetImage((char *)"./images/wall1.ppm");
		  glGenTextures(1, &wall1Texture);
		  glBindTexture(GL_TEXTURE_2D, wall1Texture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(wall1Image);	
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wall1Image->width, wall1Image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  wall2Image = ppm6GetImage((char *)"./images/wall2.ppm");
		  glGenTextures(1, &wall2Texture);
		  glBindTexture(GL_TEXTURE_2D, wall2Texture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(wall2Image);	
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wall2Image->width, wall2Image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);
}

void camera() {
		  glMatrixMode(GL_PROJECTION);
		  glLoadIdentity();
		  float posx = myPlayer->GetPosition().x*M2P;
		  float posy = myPlayer->GetPosition().y*M2P;
		  float adjusty = 250;//The higher this is, the more shifted up the camera
		  float zoomScale = 1.00;//lower scale = zoomed out
		  gluOrtho2D(posx-xres/zoomScale, posx+xres/zoomScale, posy+yres/zoomScale-adjusty, posy-yres/zoomScale-adjusty);
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  glBindTexture(GL_TEXTURE_2D, wall1Texture);
		  glBegin(GL_QUADS);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		  glTexCoord2f(0.0f, 0.0f);
		  glVertex2i(-2.0f * xres, -4.0f * yres);
		  glTexCoord2f(0.0f, 10.0f);
		  glVertex2i(-2.0f * xres, 1.0f * yres);
		  glTexCoord2f(50.0f, 10.0f);
		  glVertex2i(20.0f * xres, 1.0f * yres);
		  glTexCoord2f(50.0f, 0.0f);
		  glVertex2i(20.0f * xres, -4.0f * yres);
		  /*
			  glBindTexture(GL_TEXTURE_2D, labratTexture);
			  glBegin(GL_QUADS);
			  glTexCoord2f(0.0f, 0.0f);
			  glVertex2i(0.0f * xres, -2.0f * yres);
			  glTexCoord2f(0.0f, 1.0f);
			  glVertex2i(0.0f * xres, 0.0f * yres);
			  glTexCoord2f(1.0f, 1.0f);
			  glVertex2i(3.0f * xres, 0.0f * yres);
			  glTexCoord2f(1.0f, 0.0f);
			  glVertex2i(3.0f * xres, -2.0f * yres);
			  */
		  glEnd();
		  glPopMatrix();
		  glDisable(GL_TEXTURE_2D);
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

void drawButton(void)
{
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  b2Vec2 points[4];
		  b2Fixture * tmp;
		  if (button_pressed)
		  {
					 glTranslatef(myButton->GetPosition().x*M2P, myButton->GetPosition().y*M2P, 0);
					 glRotatef(myButton->GetAngle()*180.0/M_PI, 0, 0, 1);
					 glBindTexture(GL_TEXTURE_2D, buttonDepressedTexture);
					 tmp = myButton->GetFixtureList();
		  }
		  else
		  {
					 glTranslatef(myButton->GetPosition().x*M2P, myButton->GetPosition().y*M2P, 0);
					 glRotatef(myButton->GetAngle()*180.0/M_PI, 0, 0, 1);
					 glBindTexture(GL_TEXTURE_2D, buttonTexture);
					 tmp = myButton->GetFixtureList();
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

void drawMine(void)
{
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  glTranslatef(mineObject->GetPosition().x*M2P, mineObject->GetPosition().y*M2P, 0);
		  glRotatef(mineObject->GetAngle()*180.0/M_PI, 0, 0, 1);
		  glBindTexture(GL_TEXTURE_2D, mineTexture);
		  b2Vec2 points[4];
		  b2Fixture * tmp = mineObject->GetFixtureList();
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
		  camera();
		  b2Vec2 points[4];
		  b2Body* tmp = world->GetBodyList();
		  glEnable(GL_ALPHA_TEST);
		  glAlphaFunc(GL_GREATER, 0.0f);
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
								else if (contains(ud, (const char *)("mine")))
								{
										  //Log("found mine\n");
										  moveMine(tmp);
										  drawMine();
										  tmp = tmp->GetNext();
										  continue;
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
								else if (contains(ud, (const char *)"gun"))
								{
										  tmp = tmp->GetNext();
										  continue;
								}
								else if (contains(ud, (const char *)"player"))
								{
										  tmp = tmp->GetNext();
										  continue;
								}
								else if (contains(ud, (const char *)"foot"))
								{
										  tmp = tmp->GetNext();
										  continue;
								}
								else if (contains(ud, (const char *)"button"))
								{
										  drawButton();
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
					 p_dest = NULL;
		  }
		  drawPlayer();
		  glXSwapBuffers(dpy, win);
}
