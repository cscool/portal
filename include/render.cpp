#include "render.h"

using namespace std;

void drawExplode(b2Body * b)
{
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  glBindTexture(GL_TEXTURE_2D, mine2Texture);
		  glTranslatef(b->GetPosition().x*M2P, b->GetPosition().y*M2P, 0);
		  glRotatef(b->GetAngle()*180.0/M_PI, 0, 0, 1);
		  b2Vec2 points[4];
		  b2Fixture * tmp = b->GetFixtureList();
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
													 glTexCoord2f(0.0f, 0.0f); //glVertex2i(-wid,-wid);
													 break;
										  case 1:
													 glTexCoord2f(1.0f, 0.0f); //glVertex2i(-wid, wid);
													 break;
										  case 2:
													 glTexCoord2f(1.0f, 1.0f); //glVertex2i( wid, wid);
													 break;
										  case 3:
													 glTexCoord2f(0.0f, 1.0f); //glVertex2i( wid,-wid);
													 break;
								}
								glVertex2f(points[i].x*M2P, points[i].y*M2P);
					 }
					 glEnd();
					 tmp = tmp->GetNext();
		  }
		  glDisable(GL_TEXTURE_2D);
		  glPopMatrix();
		  glXSwapBuffers(dpy, win);
}

void drawMenu()
{
		  //		  b2Body * menu = addRect(myPlayer->GetPosition().x + 1.0f * xres, myPlayer->GetPosition().y + -1.3f * yres, 1000, 800, 0, 0, 2);
		  b2Body * menu = addRect(myPlayer->GetPosition().x, myPlayer->GetPosition().y, 1000, 800, 0, 0, 2);
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  glRotatef(menu->GetAngle()*180.0/M_PI, 0, 0, 1);
		  if (state == 2)
		  {
					 glBindTexture(GL_TEXTURE_2D, pauseMenuTexture);
					 glTranslatef(myPlayer->GetPosition().x*M2P, myPlayer->GetPosition().y*M2P - 190, 0);
		  }
		  else if (state == 3)
		  {
					 glBindTexture(GL_TEXTURE_2D, dMenuTexture);
					 glTranslatef(myPlayer->GetPosition().x*M2P, myPlayer->GetPosition().y*M2P - 190, 0);
		  }
		  else
		  {
					 glBindTexture(GL_TEXTURE_2D, mainMenuTexture);
					 glTranslatef(1.5f*xres, -yres, 0);
		  }
		  b2Vec2 points[4];
		  b2Fixture * tmp = menu->GetFixtureList();
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
													 glTexCoord2f(0.0f, 0.0f); //glVertex2i(-wid,-wid);
													 break;
										  case 1:
													 glTexCoord2f(1.0f, 0.0f); //glVertex2i(-wid, wid);
													 break;
										  case 2:
													 glTexCoord2f(1.0f, 1.0f); //glVertex2i( wid, wid);
													 break;
										  case 3:
													 glTexCoord2f(0.0f, 1.0f); //glVertex2i( wid,-wid);
													 break;
								}
								glVertex2f(points[i].x*M2P, points[i].y*M2P);
					 }
					 glEnd();
					 tmp = tmp->GetNext();
		  }
		  glDisable(GL_TEXTURE_2D);
		  glPopMatrix();
		  world -> DestroyBody(menu);
}

void init_opengl(void)
{
		  glMatrixMode( GL_PROJECTION);
		  glOrtho(0, xres, yres, 0, -1, 1);
		  glMatrixMode(GL_MODELVIEW);
		  glClearColor(0,0,0,1);
		  glColor3f(1.0f,1.0f,1.0f);
}

void drawEnemy(b2Body * b)
{
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  if (contains((char *)(b->GetUserData()), (char *)"left"))
		  {
					 glBindTexture(GL_TEXTURE_2D, turretEnemyTexture);
		  }
		  else
		  {
					 glBindTexture(GL_TEXTURE_2D, turretEnemyRightTexture);
		  }
		  glTranslatef(b->GetPosition().x*M2P, b->GetPosition().y*M2P, 0);
		  glRotatef(b->GetAngle()*180.0/M_PI, 0, 0, 1);
		  b2Vec2 points[4];
		  b2Fixture * tmp = b->GetFixtureList();
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
													 glTexCoord2f(0.0f, 0.0f); //glVertex2i(-wid,-wid);
													 break;
										  case 1:
													 glTexCoord2f(1.0f, 0.0f); //glVertex2i(-wid, wid);
													 break;
										  case 2:
													 glTexCoord2f(1.0f, 1.0f); //glVertex2i( wid, wid);
													 break;
										  case 3:
													 glTexCoord2f(0.0f, 1.0f); //glVertex2i( wid,-wid);
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

void drawMirror(b2Body * b)
{
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  glBindTexture(GL_TEXTURE_2D, mirrorTexture);
		  glTranslatef(b->GetPosition().x*M2P, b->GetPosition().y*M2P, 0);
		  glRotatef(b->GetAngle()*180.0/M_PI, 0, 0, 1);
		  b2Vec2 points[4];
		  b2Fixture * tmp = b->GetFixtureList();
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
													 glTexCoord2f(0.0f, 0.0f); //glVertex2i(-wid,-wid);
													 break;
										  case 1:
													 glTexCoord2f(1.0f, 0.0f); //glVertex2i(-wid, wid);
													 break;
										  case 2:
													 glTexCoord2f(1.0f, 1.0f); //glVertex2i( wid, wid);
													 break;
										  case 3:
													 glTexCoord2f(0.0f, 1.0f); //glVertex2i( wid,-wid);
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

void drawLens(b2Body * b)
{
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  glBindTexture(GL_TEXTURE_2D, lensTexture);
		  glTranslatef(b->GetPosition().x*M2P, b->GetPosition().y*M2P, 0);
		  glRotatef(b->GetAngle()*180.0/M_PI, 0, 0, 1);
		  b2Vec2 points[4];
		  b2Fixture * tmp = b->GetFixtureList();
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
													 glTexCoord2f(0.0f, 0.0f); //glVertex2i(-wid,-wid);
													 break;
										  case 1:
													 glTexCoord2f(1.0f, 0.0f); //glVertex2i(-wid, wid);
													 break;
										  case 2:
													 glTexCoord2f(1.0f, 1.0f); //glVertex2i( wid, wid);
													 break;
										  case 3:
													 glTexCoord2f(0.0f, 1.0f); //glVertex2i( wid,-wid);
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

void drawCake(b2Body * b)
{
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  glBindTexture(GL_TEXTURE_2D, cakeTexture);
		  glTranslatef(b->GetPosition().x*M2P, b->GetPosition().y*M2P, 0);
		  glRotatef(b->GetAngle()*180.0/M_PI, 0, 0, 1);
		  b2Vec2 points[4];
		  b2Fixture * tmp = b->GetFixtureList();
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
													 glTexCoord2f(0.0f, 0.0f); //glVertex2i(-wid,-wid);
													 break;
										  case 1:
													 glTexCoord2f(1.0f, 0.0f); //glVertex2i(-wid, wid);
													 break;
										  case 2:
													 glTexCoord2f(1.0f, 1.0f); //glVertex2i( wid, wid);
													 break;
										  case 3:
													 glTexCoord2f(0.0f, 1.0f); //glVertex2i( wid,-wid);
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

void drawElevator(b2Body * b)
{
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  glBindTexture(GL_TEXTURE_2D, elevatorTexture);
		  glTranslatef(b->GetPosition().x*M2P, b->GetPosition().y*M2P, 0);
		  glRotatef(b->GetAngle()*180.0/M_PI, 0, 0, 1);
		  b2Vec2 points[4];
		  b2Fixture * tmp = b->GetFixtureList();
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
													 glTexCoord2f(0.0f, 0.0f); //glVertex2i(-wid,-wid);
													 break;
										  case 1:
													 glTexCoord2f(1.0f, 0.0f); //glVertex2i(-wid, wid);
													 break;
										  case 2:
													 glTexCoord2f(1.0f, 1.0f); //glVertex2i( wid, wid);
													 break;
										  case 3:
													 glTexCoord2f(0.0f, 1.0f); //glVertex2i( wid,-wid);
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



void init_images(void)
{
		  labratImage = ppm6GetImage((char *)"./images/labrat.ppm");
		  glGenTextures(1, &labratTexture);
		  glBindTexture(GL_TEXTURE_2D, labratTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		  glTexImage2D(GL_TEXTURE_2D, 0, 3, labratImage->width, labratImage->height, 0, GL_RGB, GL_UNSIGNED_BYTE, labratImage->data);

		  unsigned char * sdata = NULL;

		  mine2Image = ppm6GetImage((char *)"./images/mineBlown.ppm");
		  glGenTextures(1, &mine2Texture);
		  glBindTexture(GL_TEXTURE_2D, mine2Texture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(mine2Image);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mine2Image->width, mine2Image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  dMenuImage = ppm6GetImage((char *)"./images/goMenu.ppm");
		  glGenTextures(1, &dMenuTexture);
		  glBindTexture(GL_TEXTURE_2D, dMenuTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(dMenuImage);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, dMenuImage->width, dMenuImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  cakeImage = ppm6GetImage((char *)"./images/cake.ppm");
		  glGenTextures(1, &cakeTexture);
		  glBindTexture(GL_TEXTURE_2D, cakeTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(cakeImage);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cakeImage->width, cakeImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  elevatorImage = ppm6GetImage((char *)"./images/elevator.ppm");
		  glGenTextures(1, &elevatorTexture);
		  glBindTexture(GL_TEXTURE_2D, elevatorTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(elevatorImage);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, elevatorImage->width, elevatorImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  mirrorImage = ppm6GetImage((char *)"./images/mirror.ppm");
		  glGenTextures(1, &mirrorTexture);
		  glBindTexture(GL_TEXTURE_2D, mirrorTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(mirrorImage);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mirrorImage->width, mirrorImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  lensImage = ppm6GetImage((char *)"./images/lens.ppm");
		  glGenTextures(1, &lensTexture);
		  glBindTexture(GL_TEXTURE_2D, lensTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(lensImage);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, lensImage->width, lensImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  turretEnemyImage = ppm6GetImage((char *)"./images/TurretEnemy.ppm");
		  glGenTextures(1, &turretEnemyTexture);
		  glBindTexture(GL_TEXTURE_2D, turretEnemyTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(turretEnemyImage);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, turretEnemyImage->width, turretEnemyImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  turretEnemyRightImage = ppm6GetImage((char *)"./images/TurretEnemyRight.ppm");
		  glGenTextures(1, &turretEnemyRightTexture);
		  glBindTexture(GL_TEXTURE_2D, turretEnemyRightTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(turretEnemyRightImage);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, turretEnemyRightImage->width, turretEnemyRightImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  goatRightImage = ppm6GetImage((char *)"./images/goatleft.ppm");
		  glGenTextures(1, &goatRightTexture);
		  glBindTexture(GL_TEXTURE_2D, goatRightTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(goatRightImage);	
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, goatRightImage->width, goatRightImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  goatImage = ppm6GetImage((char *)"./images/goat.ppm");
		  glGenTextures(1, &goatTexture);
		  glBindTexture(GL_TEXTURE_2D, goatTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(goatImage);	
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, goatImage->width, goatImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  cCubeImage = ppm6GetImage((char *)"./images/ccube.ppm");
		  glGenTextures(1, &cCubeTexture);
		  glBindTexture(GL_TEXTURE_2D, cCubeTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(cCubeImage);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cCubeImage->width, cCubeImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  mainMenuImage = ppm6GetImage((char *)"./images/mMenu.ppm");
		  glGenTextures(1, &mainMenuTexture);
		  glBindTexture(GL_TEXTURE_2D, mainMenuTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(mainMenuImage);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mainMenuImage->width, mainMenuImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  spikeImage = ppm6GetImage((char *)"./images/spikes.ppm");
		  glGenTextures(1, &spikeTexture);
		  glBindTexture(GL_TEXTURE_2D, spikeTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(spikeImage);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spikeImage->width, spikeImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  pwallImage = ppm6GetImage((char *)"./images/portalable.ppm");
		  glGenTextures(1, &pwallTexture);
		  glBindTexture(GL_TEXTURE_2D, pwallTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(pwallImage);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pwallImage->width, pwallImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  npwallImage = ppm6GetImage((char *)"./images/nonportalable.ppm");
		  glGenTextures(1, &npwallTexture);
		  glBindTexture(GL_TEXTURE_2D, npwallTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(npwallImage);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, npwallImage->width, npwallImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  p1Image = ppm6GetImage((char *)"./images/p1.ppm");
		  glGenTextures(1, &p1Texture);
		  glBindTexture(GL_TEXTURE_2D, p1Texture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(p1Image);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, p1Image->width, p1Image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

		  p2Image = ppm6GetImage((char *)"./images/p2.ppm");
		  glGenTextures(1, &p2Texture);
		  glBindTexture(GL_TEXTURE_2D, p2Texture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(p2Image);	
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, p2Image->width, p2Image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
		  free(sdata);

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

		  pauseMenuImage = ppm6GetImage((char *)"./images/pMenu.ppm");
		  glGenTextures(1, &pauseMenuTexture);
		  glBindTexture(GL_TEXTURE_2D, pauseMenuTexture);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		  sdata = buildAlphaData(pauseMenuImage);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pauseMenuImage->width, pauseMenuImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sdata);
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
		  glVertex2i(-5.0f * xres, -8.0f * yres);
		  glTexCoord2f(0.0f, 10.0f);
		  glVertex2i(-5.0f * xres, 3.0f * yres);
		  glTexCoord2f(50.0f, 10.0f);
		  glVertex2i(25.0f * xres, 3.0f * yres);
		  glTexCoord2f(50.0f, 0.0f);
		  glVertex2i(25.0f * xres, -8.0f * yres);
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

void drawGoat(Goat & g)
{
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  glTranslatef(g.goat->GetPosition().x*M2P, g.goat->GetPosition().y*M2P, 0);
		  glRotatef(g.goat->GetAngle()*0/M_PI, 0, 0, 1);
		  if (g.dir.x == 1.0f)
		  {
					 glBindTexture(GL_TEXTURE_2D, goatRightTexture);
		  }
		  else
		  {
					 glBindTexture(GL_TEXTURE_2D, goatTexture);
		  }
		  b2Vec2 points[4];
		  b2Fixture * tmp = g.goat->GetFixtureList();
		  while (tmp)
		  {
					 for(int i=0; i < 4; i++)
					 {
								points[i] = ((b2PolygonShape*)tmp->GetShape())->GetVertex(i);
					 }
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
		  else if (color == 3)
		  {
					 glColor3f(0, 255, 0);
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
		  /*
			  if (contains((char *)(p->GetUserData()), (char *)"left"))
			  {
			  glColor3f(0,0,1);
			  }
			  else
			  {
			  glColor3f(1,0,0);
			  }
			  */
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  if (contains((char *)(p->GetUserData()), (char *)"left"))
		  {
					 glBindTexture(GL_TEXTURE_2D, p1Texture);
		  }
		  else
		  {
					 glBindTexture(GL_TEXTURE_2D, p2Texture);
		  }
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
		  glPopMatrix();
		  glDisable(GL_TEXTURE_2D);
}

void drawButton(Button b)
{
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  b2Vec2 points[4];
		  b2Fixture * tmp;
		  if (b.pressed)
		  {
					 glTranslatef(b.button->GetPosition().x*M2P, b.button->GetPosition().y*M2P, 0);
					 glRotatef(b.button->GetAngle()*180.0/M_PI, 0, 0, 1);
					 glBindTexture(GL_TEXTURE_2D, buttonDepressedTexture);
					 tmp = b.button->GetFixtureList();
		  }
		  else
		  {
					 glTranslatef(b.button->GetPosition().x*M2P, b.button->GetPosition().y*M2P, 0);
					 glRotatef(b.button->GetAngle()*180.0/M_PI, 0, 0, 1);
					 glBindTexture(GL_TEXTURE_2D, buttonTexture);
					 tmp = b.button->GetFixtureList();
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

void drawSpikes(b2Body * b)
{
		  //		  Log("drawing spikes\n");
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  glTranslatef(b->GetPosition().x*M2P, b->GetPosition().y*M2P, 0);
		  glRotatef(b->GetAngle()*180.0/M_PI, 0, 0, 1);
		  glBindTexture(GL_TEXTURE_2D, spikeTexture);
		  b2Vec2 points[4];
		  b2Fixture * tmp = b->GetFixtureList();
		  while (tmp)
		  {
					 for(int i=0; i < 4; i++)
								points[i] = ((b2PolygonShape*)tmp->GetShape())->GetVertex(i);
					 glBegin(GL_QUADS);
					 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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

void drawMine(Mine m)
{
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  glTranslatef(m.mine->GetPosition().x*M2P, m.mine->GetPosition().y*M2P, 0);
		  glRotatef(m.mine->GetAngle()*180.0/M_PI, 0, 0, 1);
		  glBindTexture(GL_TEXTURE_2D, mineTexture);
		  b2Vec2 points[4];
		  b2Fixture * tmp = m.mine->GetFixtureList();
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

float getWidth(b2Body *b)
{
		  float y1 = ((b2PolygonShape*)b->GetFixtureList()->GetShape())->GetVertex(2).y;
		  float y2 = ((b2PolygonShape*)b->GetFixtureList()->GetShape())->GetVertex(1).y;
		  return (fabs(y2-y1));
}

float getHeight(b2Body *b)
{
		  float x1 = ((b2PolygonShape*)b->GetFixtureList()->GetShape())->GetVertex(0).x;
		  float x2 = ((b2PolygonShape*)b->GetFixtureList()->GetShape())->GetVertex(1).x;
		  return (fabs(x2-x1));
}

void drawCompanion(b2Body * b)
{
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  glTranslatef(b->GetPosition().x*M2P, b->GetPosition().y*M2P, 0);
		  glRotatef(b->GetAngle()*180.0/M_PI, 0, 0, 1);
		  glBindTexture(GL_TEXTURE_2D, cCubeTexture);
		  b2Vec2 points[4];
		  b2Fixture * tmp = b->GetFixtureList();
		  //		  float wid = getWidth(b);
		  //		  float hei = getHeight(b);
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
													 glTexCoord2f(0.0f, 0.0f);
													 break;
										  case 1:
													 glTexCoord2f(1.0f, 0.0f);
													 break;
										  case 2:
													 glTexCoord2f(1.0f, 1.0f);
													 break;
										  case 3:
													 glTexCoord2f(0.0f, 1.0f);
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

void drawWall(b2Body * b, const int & n)
{
		  glColor3f(1.0f,1.0f,1.0f);
		  glEnable(GL_TEXTURE_2D);
		  glPushMatrix();
		  glTranslatef(b->GetPosition().x*M2P, b->GetPosition().y*M2P, 0);
		  glRotatef(b->GetAngle()*180.0/M_PI, 0, 0, 1);
		  if (n == 1)
		  {
					 glBindTexture(GL_TEXTURE_2D, pwallTexture);
		  }
		  else
		  {
					 glBindTexture(GL_TEXTURE_2D, npwallTexture);
		  }
		  b2Vec2 points[4];
		  b2Fixture * tmp = b->GetFixtureList();
		  /*
			  glTexCoord2f(0.0f, 0.0f);
			  glVertex2i(-2.0f * xres, -4.0f * yres);
			  glTexCoord2f(0.0f, 10.0f);
			  glVertex2i(-2.0f * xres, 1.0f * yres);
			  glTexCoord2f(50.0f, 10.0f);
			  glVertex2i(20.0f * xres, 1.0f * yres);
			  glTexCoord2f(50.0f, 0.0f);
			  glVertex2i(20.0f * xres, -4.0f * yres);
			  */
		  float wid = getWidth(b);
		  float hei = getHeight(b);
		  while (tmp)
		  {
					 for(int i=0; i < 4; i++)
								points[i] = ((b2PolygonShape*)tmp->GetShape())->GetVertex(i);
					 glBegin(GL_QUADS);
					 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
					 for(int i = 0; i < 4; i++)
					 {
								switch (i)
								{
										  case 0:
													 glTexCoord2f(0.0f, 0.1f*hei);
													 break;
										  case 1:
													 glTexCoord2f(0.0f, 0.0f);
													 break;
										  case 2:
													 glTexCoord2f(0.1f*wid, 0.0f);
													 break;
										  case 3:
													 glTexCoord2f(0.1f*wid, 0.1f*hei);
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

void calcLaser(Turret turret1)
{
		  //b2Joint * joint = turret1.turret->GetJointList()->joint;
		  //b2RevoluteJoint * revJoint = static_cast<b2RevoluteJoint*>(joint);
		  //float currentRayAngle = revJoint->GetJointAngle();
		  float currentRayAngle = turret1.turret->GetAngle();
		  float rayLength = turret1.length;
		  Log("length = %.2f\n", rayLength);
		  b2Vec2 p1 = turret1.turret->GetPosition();
		  //b2Vec2 p2 = p1 + rayLength * b2Vec2( sinf(currentRayAngle), -cosf(currentRayAngle) + 45*D2R );
		  b2Vec2 p2 = p1 + rayLength * b2Vec2( sinf(currentRayAngle), -cosf(currentRayAngle) );

		  drawLaser( p1, p2);
}


void drawLaser(b2Vec2 point1, b2Vec2 point2)
{
		  bool isMirror = false;
		  bool isLportal = false;
		  bool isRportal = false;
		  b2RayCastInput input;
		  input.p1 = point1;
		  input.p2 = point2;
		  input.maxFraction = 1;

		  //check every fixture of every body to find closest
		  float closestFraction = 1; //start with end of line as p2
		  b2Vec2 intersectionNormal(0,0);
		  for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
					 for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {

								b2RayCastOutput output;
								if ( ! f->RayCast( &output, input, 0 ) )
										  continue;
								if ( output.fraction < closestFraction ) {
										  if (b->GetUserData())
										  {
													 //													 Log("laser hitting:\n\t%s\n", (char *)(b->GetUserData()));
													 if (contains((char *)(b->GetUserData()), (const char *)"player") || (contains((char *)(b->GetUserData()), (const char *)"gun")))
													 {
																//																Log("kill player with laser\n");
																detonate(myPlayer, myPlayerFoot);
																isMirror = false;
																isLportal = false;
																isRportal = false;
																if (current_arena == 2)
																{
																		  doors[0].active = false;
																}
													 }
													 else if (contains((char *)(b->GetUserData()), (const char *)"lens"))
													 {
																if (current_arena == 2)
																{
																		  doors[0].active = true;
																}
													 }
													 else if (contains((char *)(b->GetUserData()), (const char *)"mirror"))
													 {
																isMirror = true;
																isLportal = false;
																isRportal = false;
																if (current_arena == 2)
																{
																		  doors[0].active = false;
																}
													 }
													 else if (contains((char *)(b->GetUserData()), (const char *)"isportal left"))
													 {
																if(p2)
																		  isLportal = true;
																isMirror = false;
																isRportal = false;
																if (current_arena == 2)
																{
																		  doors[0].active = false;
																}
													 }
													 else if (contains((char *)(b->GetUserData()), (const char *)"isportal right"))
													 {
																if(p1)
																		  isRportal = true;
																isMirror = false;
																isLportal = false;
																if (current_arena == 2)
																{
																		  doors[0].active = false;
																}
													 }
													 else
													 {
																if (current_arena == 2)
																{
																		  doors[0].active = false;
																}
													 }
										  }
										  closestFraction = output.fraction;
										  intersectionNormal = output.normal;
								}            
					 }
		  }

		  b2Vec2 intersectionPoint = point1 + closestFraction * (point2 - point1);

		  //draw a line
		  glColor3f(1,0,0); //white
		  glBegin(GL_LINES);
		  glVertex2f( point1.x*M2P, point1.y*M2P );
		  glVertex2f( intersectionPoint.x*M2P, intersectionPoint.y*M2P );
		  glEnd();

		  //draw a point at the intersection point
		  glPointSize(5);
		  glBegin(GL_POINTS);
		  glVertex2f( intersectionPoint.x*M2P, intersectionPoint.y*M2P );
		  glEnd();

		  if(isMirror) {
					 if ( closestFraction == 1 )
								return; //ray hit nothing so we can finish here
					 if ( closestFraction == 0 )
								return;

					 //still some ray left to reflect
					 b2Vec2 remainingRay = (point2 - intersectionPoint);
					 b2Vec2 projectedOntoNormal = b2Dot(remainingRay, intersectionNormal) * intersectionNormal;
					 b2Vec2 nextp2 = point2 - 2 * projectedOntoNormal;

					 //recurse
					 drawLaser(intersectionPoint, nextp2);
		  }

		  else if(isLportal || isRportal) {
					 b2Vec2 portal1 = p1->GetPosition();
					 b2Vec2 portal2 = p2->GetPosition();
					 if ( closestFraction == 1 )
								return; //ray hit nothing so we can finish here
					 if ( closestFraction == 0 )
								return;

					 //still some ray left to reflect
					 b2Vec2 remainingRay = (point2 - intersectionPoint);
					 b2Vec2 projectedOntoNormal = b2Dot(remainingRay, intersectionNormal) * intersectionNormal;
					 b2Vec2 nextp2 = point2 - 2 * projectedOntoNormal;

					 //recurse
					 if(isLportal)
								drawLaser(portal2 - (portal1 - intersectionPoint), nextp2);
					 else if(isRportal)
								drawLaser(portal1 - (portal2 - intersectionPoint), nextp2);
		  }
}

void drawGunLaser()
{
		  float currentRayAngle = myGun->GetAngle() + 90.0f*D2R;
		  float rayLength = 15.0f * M2P;
		  b2Vec2 p1 = myGun->GetPosition();
		  b2Vec2 p2 = p1 + rayLength * b2Vec2( sinf(currentRayAngle), -cosf(currentRayAngle));
		  b2RayCastInput input;
		  input.p1 = p1;
		  input.p2 = p2;
		  input.maxFraction = 1;

		  float closestFraction = 1; //start with end of line as p2
		  b2Vec2 intersectionNormal(0,0);
		  for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
					 for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {

								b2RayCastOutput output;
								if ( ! f->RayCast( &output, input, 0 ) )
										  continue;
								if ( output.fraction < closestFraction ) {
										  closestFraction = output.fraction;
										  intersectionNormal = output.normal;
								}            
					 }
		  }

		  b2Vec2 intersectionPoint = p1 + closestFraction * (p2 - p1);

		  //draw a line
		  glColor3f(1,0,1);
		  glBegin(GL_LINES);
		  glVertex2f( p1.x*M2P, p1.y*M2P );
		  glVertex2f( intersectionPoint.x*M2P, intersectionPoint.y*M2P );
		  glEnd();

		  //draw a point at the intersection point
		  glPointSize(5);
		  glBegin(GL_POINTS);
		  glVertex2f( intersectionPoint.x*M2P, intersectionPoint.y*M2P );
		  glEnd();

		  //draw intersection normal
		  b2Vec2 normalEnd = intersectionPoint + 3*intersectionNormal;
		  glColor3f(1,0,1);
		  glBegin(GL_LINES);
		  glVertex2f( intersectionPoint.x*M2P, intersectionPoint.y*M2P );
		  glVertex2f( normalEnd.x*M2P, normalEnd.y*M2P );
		  glEnd();
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
		  //		  glClear(GL_COLOR_BUFFER_BIT);
		  glLoadIdentity();
		  b2Vec2 points[4];
		  b2Body* tmp = world->GetBodyList();
		  glEnable(GL_ALPHA_TEST);
		  glAlphaFunc(GL_GREATER, 0.0f);
		  char * ud;
		  int color = 0;
		  switch(state)
		  {
					 case 0:
					 case 1:
								camera();
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
																if (platform)
																{
																		  //Log("found platform\n");
																		  movePlatform(tmp);
																		  drawWall(tmp, 0);
																}
																tmp = tmp->GetNext();
																continue;
													 }
													 else if (contains(ud, (const char *)("mirror")))
													 {
																drawMirror(tmp);
																tmp = tmp->GetNext();
																continue;
													 }
													 else if (contains(ud, (const char *)("companion")))
													 {
																drawCompanion(tmp);
																tmp = tmp->GetNext();
																continue;
													 }
													 else if (contains(ud, (const char *)("mine")))
													 {
																tmp = tmp->GetNext();
																continue;
													 }
													 else if (contains(ud, (const char *)"enemy"))
													 {
																drawEnemy(tmp);
																tmp = tmp->GetNext();
																continue;
													 }
													 else if (contains(ud, (const char *)"bullet"))
													 {
																if(contains(ud, (const char *)"deadly"))
																{
//																		  cout << "deadly bullet\n" << flush;
																		  color = 2;
																		  drawSquare(points, tmp->GetPosition(), tmp->GetAngle(), color);
																		  tmp = tmp->GetNext();
																		  continue;
																}
																else if (contains (ud, (const char *)"left"))
																{
																		  //					 Log("left bullet\n");
																		  color = 1;
																		  drawSquare(points, tmp->GetPosition(), tmp->GetAngle(), color);
																		  tmp = tmp->GetNext();
																		  continue;
																}
																else if (contains (ud, (const char *)"right"))
																{
																		  //					 Log("right bullet\n");
																		  color = 2;
																		  drawSquare(points, tmp->GetPosition(), tmp->GetAngle(), color);
																		  tmp = tmp->GetNext();
																		  continue;
																}
													 }
													 else if (contains(ud, (const char *)"wall") || contains(ud, (const char *)"floor") || contains(ud, (const char *)"ceiling"))
													 {
																if (contains(ud, (const char *)"portalable"))
																{
																		  drawWall(tmp, 1);
																}
																else
																{
																		  drawWall(tmp, 0);
																}
																tmp = tmp->GetNext();
																continue;
													 }
													 else if (contains(ud, (const char *)"spike"))
													 {
																//										  Log("found spikes, calling draw\n");
																drawSpikes(tmp);
																tmp = tmp->GetNext();
																continue;
													 }
													 else if (contains(ud, (const char *)("goat")))
													 {
																tmp = tmp->GetNext();
																continue;
													 }
													 else if (contains(ud, (const char *)"lens"))
													 {
																tmp = tmp->GetNext();
																continue;
													 }
													 else if (contains(ud, (const char *)"elevator"))
													 {
																drawElevator(tmp);
																tmp = tmp->GetNext();
																continue;
													 }
													 else if (contains(ud, (const char *)"cake"))
													 {
																drawCake(tmp);
																tmp = tmp->GetNext();
																continue;
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
													 else if (contains(ud, (const char *)"isportal"))
													 {
																tmp = tmp->GetNext();
																continue;
													 }
													 else if (contains(ud, (const char *)"button"))
													 {
																tmp = tmp->GetNext();
																continue;
													 }
													 else
													 {
																drawWall(tmp, 0);
																tmp = tmp->GetNext();
																continue;
													 }
										  }
										  //					 drawSquare(points, tmp->GetPosition(), tmp->GetAngle(), color);
										  drawWall(tmp, 0);
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
								for(int i = 0; i < 10; i++)
								{
										  if (turrets[i].turret)
										  {
													 calcLaser(turrets[i]);
										  }
										  if (mines[i].mine)
										  {
													 moveMine(mines[i]);
													 drawMine(mines[i]);
										  }
										  if (buttons[i].button)
										  {
													 drawButton(buttons[i]);
										  }
										  if (lens[i].lens)
										  {
													 drawLens(lens[i].lens);
										  }
										  if (goats[i].goat)
										  {
													 drawGoat(goats[i]);
										  }
								}
								if (gunEnemy1)
								{
										  drawGunEnemySight(gunEnemy1);
								}
								if (gunEnemy2)
								{
										  drawGunEnemySight(gunEnemy2);
								}
								if (normalTesting)
								{
										  drawGunLaser();
								}
								if (state == 0)
								{
										  drawMenu();
								}
								break;
					 case 2:
					 case 3:
								drawMenu();
								break;
		  }
		  glXSwapBuffers(dpy, win);
}

void drawGunEnemySight(b2Body * enem)
{
		  static int btime = 0;
		  float currentRayAngle = enem->GetAngle() + 90.0f*D2R;
		  float rayLength = 1.5*M2P;
		  b2Vec2 p1 = enem->GetPosition();
		  b2Vec2 p2 = p1 + rayLength * b2Vec2( sinf(currentRayAngle), -cosf(currentRayAngle) );
		  b2RayCastInput input;
		  input.p1 = p1;
		  input.p2 = p2;
		  input.maxFraction = 1;

		  //check every fixture of every body to find closest
		  float closestFraction = 1; //start with end of line as p2
		  b2Vec2 intersectionNormal(0,0);
		  for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
					 for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {

								b2RayCastOutput output;
								if ( ! f->RayCast( &output, input, 0 ) )
										  continue;
								if ( output.fraction < closestFraction ) {
										  if (b->GetUserData())
										  {
													 if (contains((char *)(b->GetUserData()), (const char *)"player") || contains((char *)(b->GetUserData()), (const char *)"gun"))
													 {
																if (btime <= 0)
																{
																		  Log("shooting at player\nenem->GetAngle = %.2f\nenemy addr = %p\n", enem->GetAngle(), enem);
																		  if (contains((char *)(enem->GetUserData()), (const char *)"left"))
																		  {
																					 addRect(enem->GetPosition().x, enem->GetPosition().y, 12, 12, 0.0f, 0.0f, 1, (char *)"bullet deadly", enem->GetAngle()+(180.0f*D2R), enem); // make a bullet
																		  }
																		  else
																		  {
																					 addRect(enem->GetPosition().x, enem->GetPosition().y, 12, 12, 0.0f, 0.0f, 1, (char *)"bullet deadly", enem->GetAngle(), enem); // make a bullet
																		  }
																		  btime = 10;
																}
																if (btime > 0)
																{
																		  btime--;
																}
													 }
										  }
										  closestFraction = output.fraction;
										  intersectionNormal = output.normal;
								}            
					 }
		  }

		  b2Vec2 intersectionPoint = p1 + closestFraction * (p2 - p1);

		  if (normalTesting)
		  {
					 //draw a line
					 glColor3f(0,0,1); //blue
					 glBegin(GL_LINES);
					 glVertex2f( p1.x*M2P, p1.y*M2P );
					 glVertex2f( intersectionPoint.x*M2P, intersectionPoint.y*M2P );
					 glEnd();

					 //draw a point at the intersection point
					 glPointSize(5);
					 glBegin(GL_POINTS);
					 glVertex2f( intersectionPoint.x*M2P, intersectionPoint.y*M2P );
					 glEnd();
		  }
}
