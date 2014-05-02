/* TO DO 
 * overload destroy to take no args to destroy all, one int to destroy one. void on all.
 */

#include "shapes.h"

void destroyPortal (int p)
{
	 Log("start of destroyPortal\n");
	 if (plist[p] == 000)
		  return;
	 //	 int i = 0, j = 0, k = 0;
	 plist[p]->isPortal = 0; // not a portal - yet
	 /*
		 while (i < imgres)
		 {
		 j = 0;
		 while (j < imgres)
		 {
		 k = 0;
		 while (k < 1)
		 {
		 free(plist[p]->img[i][j][k]);
		 k++;
		 }
		 free(plist[p]->img[i][j]);
		 j++;
		 }
		 free(plist[p]->img[i]);
		 i++;
		 }
		 */
	 free(plist[p]->img);
	 //	 plist[p] = 000;
	 Log("end of destroyPortal\n");
	 return;
}

//struct obj * destroyObj (struct obj *o)
void destroyObj (int o)
{
	 Log("start of destroyObj\n");
	 int i = 0, j = 0;
	 olist[o]->isPortal = 0; // not a portal
	 while (i < imgres)
	 {
		  while (j < imgres)
		  {
				free(olist[o]->img[i][j]);
				j++;
		  }
		  i++;
	 }
	 free(olist[o]->img);
	 olist[o] = 000;
	 objcnt--;
	 Log("end of destroyObj\n");
	 return;
}

/* so you have a portal count, starting at 0. if == 0, initialize the portal array; initialize both objects to all zeros for pos arrays; lastportal ++ % 2. if cnt == 0, 1, at beginning. if at 1, portal[0]->isPortal = false. else, if ct == 2, portal[0] and [1] -> isPortal = true.
 * */

void initPortal (void) // easy - only ever two, check if two, then one turns into new portal. need to check age??
{
	 Log("start of initPortal\n");
	 pWidth = (2.0/3.0)*(float)imgres;
	 pHeight = (1.0)*(float)imgres;
	 pDepth = (2.0/3.0)*(float)imgres;
	 if (portalcnt == 0)
	 {
		  plist = (struct portal**)malloc(2*sizeof(struct portal**));
		  plist[0] = (struct portal*)malloc(1*sizeof(struct portal*));
		  plist[1] = (struct portal*)malloc(1*sizeof(struct portal*));
	 }

	 struct portal * p = 000;
	 if (p == 000)
	 {
		  p = (struct portal*)malloc(1*sizeof(struct portal*));
	 }
	 int i = 0;
	 //p->img = (short int *)malloc(sz*sizeof(short int*)); // first imgres elements are the x values, second are y values, third are z values
	 /* access with x = p->img[x], y = p->img[imgres+x], z = p->img[imgres+imgres+x] ? */
	 while (i < 300)
	 {
		  Log("assigning 0 to %d\n", i);
		  p->img[i++] = (short int)0; // maybe negative values for nothing?
	 }

	 /* this sucks - trying single, long array - thanks, chris
		 p->img = (short int ****)malloc(imgres*sizeof(short int ****));
		 int i = 0, j = 0, k = 0;
		 while (i < imgres)
		 {
		 j = 0;
		 p->img[i] = (short int ***)malloc(imgres*sizeof(short int ***));
		 while (j < imgres)
		 {
		 k = 0;
		 p->img[i][j] = (short int **)malloc(imgres*sizeof(short int **));
		 while (k < imgres)
		 {
		 p->img[i][j][k] = (short int *)malloc(1*sizeof(short int*));
		 p->img[i][j][k][0] = 0; // new images will have 0 as empty value
		 Log("p->img[%d][%d][%d][0] = %d\n", i, j, k, p->img[i][j][k][0]);
		 k++;
		 }
		 j++;
		 }
		 i++;
		 }
		 i = j = k = 0;
		 */
	 p->isPortal = 0; // not a portal - yet
	 p->pos[0] = xres/2;
	 p->pos[1] = yres/2;
	 p->pos[2] = zres/2;
//	 Log("passing p, p = %p, to drawPortal, check below if it matches\n", p);
//	 drawPortal(p);
	 if (portalcnt == 0) // first portal created
	 {
		  portalcnt++;
		  plist[0] = p;
		  plast = (plast + 1) % 2; // 0 or 1
	 }
	 else
	 {
		  if (portalcnt != 2)
		  {
				portalcnt = 2;
		  }
		  destroyPortal(plast);
		  plist[plast] = p;
		  plast = (plast + 1) % 2; // 0 or 1
	 }
	 Log("end of initPortal\n");
	 return;
}

void drawPortal(struct portal * p) // instead of taking one, return one
{
	 Log("start drawPortal\n");
	 Log("p = %p\n", p);
	 float x = 0.0, y = 0.0, z = 0.0;
	 float t = 0.0;
	 int i = 0;
	 do
	 {
		  Log("i = %d\n", i);
		  t += ((2*pi)/imgres);
		  x = cos(t);
		  y = sin(t);
		  x += 1;
		  y += 1;
		  x *= pWidth; // scale circle - radius
		  y *= pHeight;
		  p->img[(int)x] = (short int)1;
		  p->img[(int)x + imgres + (int)y] = (short int)1;
		  Log("assigning 1 (turning on) at x = %d, y = %d, z = %d\n", (int)x, (int)y, (int)z);
		  p->img[(int)x + imgres + (int)y + imgres + (int)z] = (short int)1; // turn on the pixel at x,y,z
		  i++;
	 }
	 while (t < 360 && i < imgres); // try t as a counter
	 Log("end drawPortal\n");
}

void initObj (void) // make a new object. check for full/uninitialized list.
{
	 Log("start of initObj\n");
	 int i = 0;
	 if (objcnt == 0) // uninitialized
	 {
		  objcnt += 1;
		  // get more memory
		  olist = (struct obj**)malloc((objcnt)*2*sizeof(struct obj*));
		  objcnt -= 1;
	 }
	 else if (objcnt+1 >= maxobj)
	 {
		  struct obj ** tmp;
		  int c = objcnt;
		  tmp = (struct obj**)malloc((maxobj)*2*sizeof(struct obj*));
		  while (i < c)
		  {
				tmp[i] = olist[i];
				destroyObj(i);
				i++;
		  }
		  olist = tmp;
		  objcnt = c;
		  maxobj *= 2;
	 }
	 struct obj * o = 000;
	 if (o == 000)
	 {
		  o = (struct obj*)malloc(1*sizeof(struct obj*));
	 }
	 int j = 0, k = 0;
	 o->img = (short int ***)malloc(imgres*imgres*sizeof(short int***));
	 while (i < imgres)
	 {
		  o->img[i++] = (short int **)malloc(imgres*sizeof(short int**));
	 }
	 i = 0;
	 while (i < imgres)
	 {
		  while (j < imgres)
		  {
				o->img[i][j] = (short int *)malloc(imgres*sizeof(short int*));
				k = 0;
				while (k < imgres)
				{
					 o->img[i][j][k++] = 0; // new images will have 0 as empty value
				}
				j++;
		  }
		  i++;
	 }
	 o->isPortal = 0; // not a portal
	 o->pos[0] = xres/2; // will lose some accuracy - no half pixels. center of object. default position is center of screen.
	 o->pos[1] = yres/2;
	 o->pos[2] = zres/2;
	 olist[objcnt++] = o;
	 Log("end of initObj\n");
	 //	 return o;
}

void drawOval(short int *** oval) // instead of taking one, return one
{
	 Log("start drawOval\n");
	 Log("&oval = %p\n", &oval);
	 float x = 0.0, y = 0.0, z = 0.0;
	 float t = 0.0;
	 int i = 0;
	 do
	 {
		  Log("i = %d\n", i);
		  t += ((2*pi)/imgres); // 1000 points for the circle
		  x = cos(t);
		  y = sin(t);
		  x += 1;
		  y += 1;
		  x *= pWidth; // scale circle - radius
		  y *= pHeight;
		  Log("assigning 1 to (%f, %f, %f), actually to (%d, %d, %d)\n", x, y, z, (int)x, (int)y, (int)z);
		  Log("&oval[0] = %p\n", &oval[0]);
		  Log("&oval[0][0] = %p\n", &oval[0][0]);
		  Log("oval[0][0][0] = %d\n", oval[0][0][0]);
		  oval[(int)x][(int)y][(int)z] = 1; // will loose some accuracy, could possibly be regained with the p->img being (imgres*imgres) in dimensions and reducing as needed
		  i++;
	 }
	 while (t < 360 && i < imgres); // try t as a counter
	 Log("end drawOval\n");
}
