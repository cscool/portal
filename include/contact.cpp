#include "contact.h"

using namespace std;

void contactListener::BeginContact (b2Contact * contact)
{
		  char * ud;
		  ud = (char *)(contact->GetFixtureA()->GetBody()->GetUserData());
		  if (ud)
		  {
					 if (ud == (char *)"player")
					 {
								//								Log("Player hit something\n");
					 }
					 else if (contains(ud, (const char *)"bullet"))
					 {
								Log("bullet hit something\n");
								toDestroy = (b2Body *)(contact->GetFixtureA()->GetBody());
					 }
		  }
		  ud = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
		  if (ud)
		  {
					 if (ud == (char *)"player")
					 {
								//								Log("Player hit something\n");
					 }
					 if (contains(ud, (const char *)"bullet"))
					 {
								Log("bullet hit something\n");
								toDestroy = (b2Body *)(contact->GetFixtureB()->GetBody());
					 }
		  }
}
void contactListener::EndContact (b2Contact * contact)
{
		  char * ud;
		  ud = (char *)(contact->GetFixtureA()->GetBody()->GetUserData());
		  if (ud)
		  {
					 if (ud == (char *)"player")
					 {
								//								Log("Player hit something\n");
					 }
					 if (contains(ud, (const char *)"bullet"))
					 {
								Log("bullet hit something\n");
								toDestroy = (b2Body *)(contact->GetFixtureA()->GetBody());
					 }
		  }
		  ud = (char *)(contact->GetFixtureB()->GetBody()->GetUserData());
		  if (ud)
		  {
					 if (ud == (char *)"player")
					 {
								//								Log("Player hit something\n");
					 }
					 if (contains(ud, (const char *)"bullet"))
					 {
								Log("bullet hit something\n");
								toDestroy = (b2Body *)(contact->GetFixtureB()->GetBody());
					 }
		  }
}
