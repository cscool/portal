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
					 turrets[0].turret = addTurret(b2Vec2(0.0f, -yres), b2Vec2(50.0f, 100.0f), false, 45.0f, 90.0f, world);
					 turrets[0].turret->SetUserData((void *)((char *)"turret"));
					 turrets[0].max_angle = 135.0f;
					 turrets[0].min_angle = 45.0f;
					 turrets[0].angleSpeed = 0.10f;
					 gunEnemy1 = addGunEnemy(b2Vec2(xres*8.0f, -64.0f), b2Vec2(75, 125), 0, world);
					 gunEnemy2 = addGunEnemy(b2Vec2(xres*9.0f, -64.0f), b2Vec2(75, 125), 1, world);
					 addMirror(b2Vec2(2.0f*xres, -0.75f*yres), b2Vec2(40.0f, 150.0f), 0.0f, world);

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
		  if (n == 2)
		  {
					 myPlayer = addPlayer(350.0f, -350.0f, player_width, player_height, world, myGun);
					 myPlayer->SetUserData((void *)((char *)"player"));

					 gameFloor = addRect(xres * 5.0f, 0.0f, xres*10.0f, 50.0f, 0.7f, 0.2f, 2, (char *)"floor portalable");
					 gameFloor->SetAwake(false);

					 ((b2Body *)(addRect(0.0f, (-1.0f*yres), 50, yres*2, 0.0f, 0.2f, 2, (char *)"left wall portalable")))->SetAwake(false);//left wall
					 ((b2Body *)(addRect(xres*10.0f, (-1.0f*yres), 50, yres*2, 0.0f, 0.2f, 2, (char *)"right wall portalable")))->SetAwake(false);//right wall
					 addRect(xres * 1.0f + 65.0f, onFloor - 15.0f, 60.0f, 60.0f, 0.9f, 0.2f, 1);//bottom right
		  }
		  /* spikes */
		  if (n == 3)
		  {
					 myPlayer = addPlayer(310.0f, -1.87f * yres, player_width, player_height, world, myGun);
					 myPlayer->SetUserData((void *)((char *)"player"));

					 gameFloor = addRect(xres * 5.0f + 400.0f, 0.0f, xres*10.0f, 50.0f, 0.7f, 0.2f, 2, (char *)"main floor 2 portalable");
					 gameFloor->SetAwake(false);

					 ((b2Body *)(addRect(425.0f, (-2.45f*yres), 50.0f, yres*0.8f, 0.0f, 0.2f, 2, (char *)"left wall 3 portalable")))->SetAwake(false);// left wall 3
					 ((b2Body *)(addRect(425.0f, (-0.7f*yres), 50.0f, yres*1.3f, 0.0f, 0.2f, 2, (char *)"left wall 2 portalable")))->SetAwake(false);// left wall 2
					 ((b2Body *)(addRect(25.0f, (-1.70f*yres), 50.0f, yres*0.5f, 0.0f, 0.2f, 2, (char *)"left wall 1 portalable")))->SetAwake(false);// left wall 1
					 ((b2Body *)(addRect(225.0f, (-1.4f*yres), 450.0f, 50.0f, 0.0f, 0.2f, 2, (char *)"left floor 1 portalable")))->SetAwake(false);// left floor 1
					 ((b2Body *)(addRect(225.0f, (-2.0f*yres), 450.0f, 50.0f, 0.0f, 0.2f, 2, (char *)"ceiling 0 portalable")))->SetAwake(false);// ceiling 0
					 ((b2Body *)(addRect(725.0f, (-2.8f*yres), 600.0f, 50.0f, 0.0f, 0.2f, 2, (char *)"ceiling 1 portalable")))->SetAwake(false);// ceiling 1
					 ((b2Body *)(addRect(2100.0f, (-2.8f*yres), 2400.0f, 50.0f, 0.0f, 0.2f, 2, (char *)"ceiling 2")))->SetAwake(false);// ceiling 2
					 ((b2Body *)(addRect(1100.0f, (-1.1f*yres), 50.0f, yres*2.2f, 0.0f, 0.2f, 2, (char *)"wall 4 portalable")))->SetAwake(false);// wall 4
					 ((b2Body *)(addRect(1375.0f, (-50.0f), 550.0f, 50.0f, 0.0f, 0.2f, 2, (char *)"spike 1")))->SetAwake(false);// spike floor 1
					 ((b2Body *)(addRect(2225.0f, (-50.0f), 550.0f, 50.0f, 0.0f, 0.2f, 2, (char *)"spike 2")))->SetAwake(false);// spike floor 2

					 ((b2Body *)(addRect(2500.0f, (-1.1f*yres), 50.0f, yres*2.2f, 0.0f, 0.2f, 2, (char *)"wall 5 portalable")))->SetAwake(false);// wall 5
					 ((b2Body *)(addRect(3475.0f, (-1.8f*yres), 300.0f, 50.0f, 0.0f, 0.2f, 2, (char *)"floor 3")))->SetAwake(false);// floor 3
					 ((b2Body *)(addRect(3600.0f, (-2.1f*yres), 50.0f, yres*1.25f, 0.0f, 0.2f, 2, (char *)"wall 6 portalable")))->SetAwake(false);// wall 6
					 turrets[0].turret = addTurret(b2Vec2(2500.0f, -0.4 * yres), b2Vec2(50.0f, 100.0f), false, 45.0f, 90.0f, world);
					 turrets[0].turret->SetUserData((void *)((char *)"turret"));
					 ((b2Body *)(addRect(4750.0f, (-2.8f*yres), 2900.0f, 50.0f, 0.0f, 0.2f, 2, (char *)"ceiling 3 portalable")))->SetAwake(false);// ceiling 3
					 ((b2Body *)(addRect(4900.0f, (-1.6f*yres), 900.0f, 50.0f, 0.0f, 0.2f, 2, (char *)"right floor 3 portalable")))->SetAwake(false);// right floor 3
					 mineObject = addRect(4300, -2.2f*yres, 150.0f, 150.0f, 0.7f, 0.9f, 3, (char *)"mine deadly"); // mine
					 MINE_LMAX = -32.2f;
					 MINE_RMAX = -32.0f;

					 ((b2Body *)(addRect(xres*8.3f, (-1.4f*yres), 50, yres*2.8f, 0.0f, 0.2f, 2, (char *)"right wall portalable")))->SetAwake(false);//right wall
					 addRect(xres * 8.1f + 65.0f, onFloor - 25.0f, 60.0f, 60.0f, 0.9f, 0.2f, 1);// a block
					 addRect(xres * 8.1f, onFloor - 25.0f, 60.0f, 60.0f, 0.9f, 0.2f, 1);// another block
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
