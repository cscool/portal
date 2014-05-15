#include "arenas.h"

using namespace std;

void makeArena(const int n)
{
		  if (n == 0)
		  {
					 gameFloor = addRect(xres * 5.0f, 0.0f, xres*10.0f, 50.0f, 0.7f, 0.2f, 2, (char *)"floor portalable");
					 gameFloor->SetAwake(false);
					 ((b2Body *)(addRect(0.0f, (-1.0f*yres), 50, yres*2, 0.0f, 0.2f, 2, (char *)"left wall portalable")))->SetAwake(false);//left wall
					 ((b2Body *)(addRect(xres*10.0f, (-1.0f*yres), 50, yres*2, 0.0f, 0.2f, 2, (char *)"right wall portalable")))->SetAwake(false);//right wall

//					 platform = addRect(0.5f*xres, -0.33f*yres, 250, 30, 0.7f, 0.9f, 3, (char *)"platform"); // platform
					 mineObject = addRect(1.5f*xres, -0.75f*yres, 150.0f, 150.0f, 0.7f, 0.9f, 3, (char *)"mine deadly"); // mine
					 addObstacles();
		  }
}

void addObstacles(void)
{
		  //top of floor is yres-50-25 = yres-75
		  addRect(xres * 1.0f, onFloor - 15.0f, 60.0f, 60.0f, 0.02f, 0.2f, 1);//bottomleft of stack
		  addRect(xres * 1.0f + 65.0f, onFloor - 15.0f, 60.0f, 60.0f, 0.02f, 0.2f, 1);//bottom right
		  addRect(xres * 1.0f + 32.5f, onFloor - 20.0f, 60.0f, 60.0f, 0.02f, 0.2f, 1);//top

		  addStairs();

		  b2Body * awall;
		  awall = addRect(2500.0f, onFloor - 350.0f, 50.0f, 250.0f, 0.7f, 0.7f, 2, (char *)"angled wall portalable");
		  awall->SetTransform((awall->GetPosition()), -45.0f);
		  awall->SetAwake(false);
}

void addStairs(void)
{
		  addRect(1200.0f, onFloor + 10.0f, 80.0f, 30.0f, 0.7f, 0.2f, 2);// stairs
		  addRect(1280.0f, onFloor, 80.0f, 60.0f, 0.7f, 0.2f, 2);
		  addRect(1360.0f, onFloor-15.0f, 80.0f, 90.0f, 0.7f, 0.2f, 2);
		  addRect(1440.0f, onFloor-30.0f, 80.0f, 120.0f, 0.7f, 0.2f, 2);
		  addRect(1520.0f, onFloor-45.0f, 80.0f, 150.0f, 0.7f, 0.2f, 2);
}
