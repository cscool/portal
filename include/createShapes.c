#include "createShapes.h"

void createOval(void)
{
	 float x = 0.0, y = 0.0;
	 float t = 0.0;
	 int i = 0;
	 do
	 {
		  t += ((2*pi)/1000.0); // 1000 points for the circle
		  x = cos(t);
		  y = sin(t);
		  x += 1;
		  y += 1;
		  x *= 100; // scale circle - radius
		  y *= 150;
		  oval[i][0] = x;
		  oval[i][1] = y;
		  i++;
	 }
	 while (t < 360 && i < 1000); // try t as a counter
}
