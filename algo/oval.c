#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


void createOval(void)
{
	 int oval [1000][2];
	 int i = 0;
	 do
	 {
		  /* stuff */
		  t += ((2*pi)/1000.0); // 100 points for the circle
		  x = cos(t);
		  y = sin(t);
		  x += 1;
		  y += 1;
		  x *= 100; // scale circle - radius
		  y *= 150;
		  oval[i][0] = x;
		  oval[i][1] = y;
	 }
	 while (t < 360); // try t as a counter
}
