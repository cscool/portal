#include "arenas.h"

using namespace std;

contactListener contact_handler;

void makeArena(const int &n)
{
		  Log("makeArena called, building arena %d\n", n);

		  if (n == 0)
		  {
					 myPlayer = addPlayer(350.0f, -350.0f, player_width, player_height, world, myGun);
					 myPlayer->SetUserData((void *)((char *)"player"));

					 gameFloor = addRect(xres * 5.0f, 0.0f, xres*10.0f, 50.0f, 0.7f, 0.2f, 2, (char *)"floor portalable");
					 gameFloor->SetAwake(false);

					 //					 ((b2Body *)(addRect(0.0f, (-1.0f*yres), 50, yres*2, 0.0f, 0.2f, 2, (char *)"left wall portalable")))->SetAwake(false);//left wall

					 addRect(0.0f, -0.500f*yres, 50.0f, 1.0f*yres, 0.0f, 0.2f, 2, (char *)"lower third left wall")->SetAwake(false);
					 addRect(0.0f, -1.50f*yres, 50.0f, 1.5f*yres, 0.0f, 0.2f, 2, (char *)"middle third left wall portalable")->SetAwake(false);
					 addRect(0.0f, -2.5f*yres, 50.0f, 1.5f*yres, 0.0f, 0.2f, 2, (char *)"upper third left wall")->SetAwake(false);
					 ((b2Body *)(addRect(xres*10.0f, (-1.0f*yres), 50, yres*2, 0.0f, 0.2f, 2, (char *)"right wall portalable", 180.0f)))->SetAwake(false);//right wall

					 myButton = addRect(5.5f*xres, -28.0f, 100.0f, 50.0f, 0.7f, 0.7f, 2, (char *)"button 1");
					 turret1 = addTurret(0.0f, -yres, 50.0f, 100.0f, world);
					 turret1->SetUserData((void *)((char *)"turret"));

					 addObstacles();
		  }

		  /* add a bionic goat to frolic through level */
		  if (n == 1)
		  {
					 myPlayer = addPlayer(350.0f, -350.0f, player_width, player_height, world, myGun);
					 myPlayer->SetUserData((void *)((char *)"player"));

					 gameFloor = addRect(xres * 5.0f, 0.0f, xres*10.0f, 50.0f, 0.7f, 0.2f, 2, (char *)"floor portalable");
					 gameFloor->SetAwake(false);

					 ((b2Body *)(addRect(0.0f, (-1.0f*yres), 50, yres*2, 0.0f, 0.2f, 2, (char *)"left wall portalable")))->SetAwake(false);//left wall
					 ((b2Body *)(addRect(xres*10.0f, (-1.0f*yres), 50, yres*2, 0.0f, 0.2f, 2, (char *)"right wall portalable")))->SetAwake(false);//right wall
					 addRect(xres * 1.0f + 65.0f, onFloor - 15.0f, 60.0f, 60.0f, 0.9f, 0.2f, 1);//bottom right
		  }
		  /* add companion cube */
		  if (n == 1)
		  {
					 myPlayer = addPlayer(350.0f, -350.0f, player_width, player_height, world, myGun);
					 myPlayer->SetUserData((void *)((char *)"player"));

					 gameFloor = addRect(xres * 5.0f, 0.0f, xres*10.0f, 50.0f, 0.7f, 0.2f, 2, (char *)"floor portalable");
					 gameFloor->SetAwake(false);

					 ((b2Body *)(addRect(0.0f, (-1.0f*yres), 50, yres*2, 0.0f, 0.2f, 2, (char *)"left wall portalable")))->SetAwake(false);//left wall
					 ((b2Body *)(addRect(xres*10.0f, (-1.0f*yres), 50, yres*2, 0.0f, 0.2f, 2, (char *)"right wall portalable")))->SetAwake(false);//right wall
					 addRect(xres * 1.0f + 65.0f, onFloor - 15.0f, 60.0f, 60.0f, 0.9f, 0.2f, 1);//bottom right
		  }
		  Log("done!\n");
}

void addObstacles(void)
{
		  //top of floor is yres-50-25 = yres-75
		  addRect(xres * 1.0f, onFloor - 15.0f, 60.0f, 60.0f, 0.9f, 0.2f, 1);//bottomleft of stack
		  addRect(xres * 1.0f + 65.0f, onFloor - 15.0f, 60.0f, 60.0f, 0.9f, 0.2f, 1);//bottom right
		  addRect(xres * 1.0f + 32.5f, onFloor - 20.0f, 60.0f, 60.0f, 0.9f, 0.2f, 1);//top

		  addStairs();

		  b2Body * awall;
		  awall = addRect(2500.0f, onFloor - 350.0f, 50.0f, 250.0f, 0.7f, 0.7f, 2, (char *)"angled wall portalable top");
		  awall->SetTransform((awall->GetPosition()), (-45.0f * D2R));
		  awall->SetAwake(false);
		  awall = (addRect(2500.0f, onFloor - 300.0f, 50.0f, 250.0f, 0.7f, 0.7f, 2, (char *)"angled wall portalable bottom"));
		  awall->SetTransform((awall->GetPosition()), (135.0f * D2R));
		  platform = addRect(4.0f*xres, -0.33f*yres, 250, 30, 0.7f, 0.9f, 3, (char *)"platform"); // platform
		  mineObject = addRect(1.5f*xres, -0.75f*yres, 150.0f, 150.0f, 0.7f, 0.9f, 3, (char *)"mine deadly"); // mine

		  myDoor = addDoor(6*xres, yres-75);
}

void firstInit(void)
{
		  Log("initializing world for first game\n");
		  world=new b2World(b2Vec2(0.0,10.0f));
		  world->SetContactListener(&contact_handler);
}

void restart(const int & a)
{
		  Log("restart called, destroying and rebuilding world\n");
		  delete world;
		  world = NULL;
		  myPlayer = NULL;
		  myPlayerFoot = NULL;
		  myGun = NULL;
		  p_dest = NULL;
		  p_obj = NULL;
		  gameFloor = NULL;
		  platform = NULL;
		  p1 = NULL;
		  p2 = NULL;
		  mineObject = NULL;
		  myDoor = NULL;
		  carry = NULL;
		  player_direction = 1;
		  resetDestroyVars();
		  Log("vars resset, rebuilding...\n");
		  world=new b2World(b2Vec2(0.0,10.0f));
		  toDestroy = NULL;
		  world->SetContactListener(&contact_handler);

		  makeArena(a);
}

void addStairs(void)
{
		  addRect(1200.0f, onFloor + 10.0f, 80.0f, 30.0f, 0.7f, 0.2f, 2);// stairs
		  addRect(1280.0f, onFloor, 80.0f, 60.0f, 0.7f, 0.2f, 2);
		  addRect(1360.0f, onFloor-15.0f, 80.0f, 90.0f, 0.7f, 0.2f, 2);
		  addRect(1440.0f, onFloor-30.0f, 80.0f, 120.0f, 0.7f, 0.2f, 2);
		  addRect(1520.0f, onFloor-45.0f, 80.0f, 150.0f, 0.7f, 0.2f, 2);
}
