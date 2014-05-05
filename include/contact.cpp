#include "contact.h"

using namespace std;

void contactListener::BeginContact (b2Contact * contact)
{
		  char * ud = (char *)(contact->GetFixtureA()->GetBody()->GetUserData());
		  if (ud == (char *)"player")
		  {
					 //								Log("Player hit something\n");
		  }
		  if (ud == (char *)"bullet")
		  {
					 Log("bullet hit something\n");
					 toDestroy = (contact->GetFixtureA()->GetBody());
		  }
		  ud = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
		  if (ud == (char *)"player")
		  {
					 //								Log("Player hit something\n");
		  }
		  if (ud == (char *)"bullet")
		  {
					 Log("bullet hit something\n");
					 toDestroy = (contact->GetFixtureB()->GetBody());
		  }
}
void contactListener::EndContact (b2Contact * contact)
{
		  char * ud = (char *)(contact->GetFixtureA()->GetBody()->GetUserData());
		  if (ud == (char *)"player")
		  {
					 //								Log("Player hit something\n");
		  }
		  if (ud == (char *)"bullet")
		  {
					 Log("bullet hit something\n");
					 toDestroy = (contact->GetFixtureA()->GetBody());
		  }
		  ud = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
		  if (ud == (char *)"player")
		  {
					 //								Log("Player hit something\n");
		  }
		  if (ud == (char *)"bullet")
		  {
					 Log("bullet hit something\n");
					 toDestroy = (contact->GetFixtureB()->GetBody());
		  }
}
