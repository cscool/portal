#include "objects.h"

using namespace std;

object::object (const object& r)
{
	 Log("in object copy constructor\n");
	 pos[0] = r.pos[0];
	 pos[1] = r.pos[1];
	 pos[2] = r.pos[2];
	 portalable = r.portalable;
	 n[0] = r.n[0];
	 n[1] = r.n[1];
	 n[2] = r.n[2];
	 head = r.head;
	 d[0] = r.n[0];
	 d[1] = r.n[1];
	 d[2] = r.n[2];
	 deadly = r.deadly;
	 objcnt++;
	 edges[LEFT] = r.edges[LEFT];
	 edges[RIGHT] = r.edges[RIGHT];
	 edges[TOP] = r.edges[TOP];
	 edges[BOTTOM] = r.edges[BOTTOM];
	 vel[0] = r.vel[0];
	 vel[1] = r.vel[1];
	 vel[2] = r.vel[2];
	 Log("end of object copy constructor, objcnt now = %d\n", objcnt);
}

object::object ()
{
	 Log("in default object constructor\n");
	 pos[0] = empty_vec[0];
	 pos[1] = empty_vec[1];
	 pos[2] = empty_vec[2];
	 portalable = 0;
	 head = initNode();
	 /* both zero vectors - this will serve as a sentinel value when we check to see if we need to set these */
	 n[0] = 0.0;
	 n[1] = 0.0;
	 n[2] = 0.0;
	 d[0] = 0.0;
	 d[1] = 0.0;
	 d[2] = 0.0;
	 setDeadly(0);
	 objcnt++;
	 edges[LEFT] = 0.0;
	 edges[RIGHT] = 0.0;
	 edges[TOP] = 0.0;
	 edges[BOTTOM] = 0.0;
	 vel[0] = zero_vec[0];
	 vel[1] = zero_vec[1];
	 vel[2] = zero_vec[2];
	 Log("end of object constructor, objcnt now = %d\n", objcnt);
}

/* could remove most of this for an optimization if need be */
object::~object()
{
	 Log("in object destructor\n");
	 pos[0] = empty_vec[0];
	 pos[1] = empty_vec[1];
	 pos[2] = empty_vec[2];
	 portalable = 0;
	 n[0] = 0.0;
	 n[1] = 0.0;
	 n[2] = 0.0;
	 d[0] = 0.0;
	 d[1] = 0.0;
	 d[2] = 0.0;
	 head = initNode();
	 setDeadly(0);
	 objcnt--;
	 edges[LEFT] = 0.0;
	 edges[RIGHT] = 0.0;
	 edges[TOP] = 0.0;
	 edges[BOTTOM] = 0.0;
	 vel[0] = zero_vec[0];
	 vel[1] = zero_vec[1];
	 vel[2] = zero_vec[2];
	 Log("end of object destructor, objcnt now = %d\n", objcnt);
}

vec_list * object::initNode(void)
{
	 vec_list * a = (vec_list *)malloc(1*sizeof(vec_list));
	 a->v[0] = empty_vec[0];
	 a->v[1] = empty_vec[1];
	 a->v[2] = empty_vec[2];
	 a->next = 0;
	 return a;
}

// accessors
Vec * object::getPos (void)
{
	 return &pos;
}

Vec * object::getVel (void)
{
	 return &vel;
}

void object::setEdges(void)
{
	 Log("in setEdges()\n");
	 vec_list * l = head;
	 float x_max = pos[0], y_max = pos[1];
	 float x_min = pos[0], y_min = pos[1];
	 while (l)
	 {
		  if (l->v[0] > x_max)
		  {
				x_max = l->v[0];
		  }
		  if (l->v[0] < x_min)
		  {
				x_min = l->v[0];
		  }
		  if (l->v[1] > y_max)
		  {
				y_max = l->v[1];
		  }
		  if (l->v[1] < y_min)
		  {
				y_min = l->v[1];
		  }
		  l = l->next;
	 }
	 edges[LEFT] = x_min;
	 edges[RIGHT] = x_max;
	 edges[TOP] = y_max;
	 edges[BOTTOM] = y_min;
	 Log("l, r, t, b:\n%.2f, %.2f, %.2f, %.2f\n", x_min, x_max, y_max, y_min);
	 Log("e[l], e[r], e[t], e[b]:\n%.2f, %.2f, %.2f, %.2f\n", edges[LEFT], edges[RIGHT], edges[TOP], edges[BOTTOM]);
}

float object::getNormalAngle(void)
{
	 return (atan(n[1]/n[0]));
}

float object::getDirectionalAngle(void)
{
	 return (atan(d[1]/d[0]));
}

float object::getEdge(const int &n)
{
	 return (edges[n]);
}

void object::shiftEdges(const float &x, const float &y, const float &z)
{
	 edges[LEFT] += x;
	 edges[RIGHT] += x;
	 edges[TOP] += y;
	 edges[BOTTOM] += y;
}

void object::setD (const float &a, const float &b, const float &c)
{
	 d[0] = a;
	 d[1] = b;
	 d[2] = c;
}

void object::setN (const float &a, const float &b, const float &c)
{
	 n[0] = a;
	 n[1] = b;
	 n[2] = c;
}

Vec * object::getD(void)
{
	 return &d;
}

Vec * object::getN(void)
{
	 return &n;
}

int object::isPortalable (void)
{
	 return portalable;
}

float * object::getVert (int i = 0)
{
	 if (i == 0)
	 {
		  return (head->v);
	 }
	 vec_list *t = head;
	 while (i > 0)
	 {
		  t = t->next;
		  if (t == 0)
		  {
				return 0;
		  }
		  i--;
	 }
	 return (t->v);
}

vec_list * object::getLastVert (void)
{
	 vec_list *t = head;
	 while (t->next != 0)
	 {
		  t = t->next;
	 }
	 return t;
}

void object::setVel(const float &x, const float &y, const float &z)
{
	 vel[0] = x;
	 vel[1] = y;
	 vel[2] = z;
}

void object::makeUnit(Vec * v)
{
	 double l = (pow((double)(v[0][0]), 2.0) + pow((double)(v[0][1]), 2.0) + pow((double)(v[0][2]), 2.0));
	 if (l != 0.0)
	 {
		  l = sqrt(l);
	 }
	 else
	 {
		  l = 1;
	 }
	 l = 1/l;
	 v[0][0] = (v[0][0])*l;
	 v[0][1] = (v[0][1])*l;
	 v[0][2] = (v[0][2])*l;
}

string object::toString(void)
{
	 ostringstream oss;
	 oss << "Object pos: (" << pos[0] << ", " << pos[1] << ", " << pos[2] << ")" << endl;
	 oss << "Object portalable? ";
	 if (isPortalable())
	 {
		  oss << "True\n";
	 }
	 else
	 {
		  oss << "False\n";
	 }
	 oss << "Object Veriticies:\n";
	 vec_list * t = head;
	 while (t != 0)
	 {
		  oss << "\t(" << t->v[0] << ", " << t->v[1] << ", " << t->v[2] << ")\n";
		  t = t->next;
	 }
	 oss << "Normal vector:\n";
	 oss << "\t<" << n[0] << ", " << n[1] << ", " << n[2] << ">";
	 oss << endl;
	 oss << "Directional vector:\n";
	 oss << "\t<" << d[0] << ", " << d[1] << ", " << d[2] << ">";
	 oss << endl;
	 oss << "Object is deadly?\n";
	 if (isDeadly())
	 {
		  oss << "True\n";
	 }
	 else
	 {
		  oss << "False\n";
	 }
	 oss << "Object edges:\n(0 - Left, 1 - Right, 2 - Top, 3 - Bottom)\n";
	 for (int i = 0; i < 4; i++)
	 {
		  oss << "\tEdge " << i << ": " << edges[i] << endl;
	 }
	 oss << "Object velocity:\n";
	 oss << "\t<" << vel[0] << ", " << vel[1] << ", " << vel[2] << ">\n";
	 return oss.str();
}

// position vector, isPortalable, verticies, normal vector, directional vector, isDeadly, edges
string object::dumpCsv(void)
{
	 ostringstream oss;
	 oss << pos[0] << "," << pos[1] << "," << pos[2] << "," << isPortalable() << ",";
	 vec_list * t = head;
	 while (t != 0)
	 {
		  oss << t->v[0] << "," << t->v[1] << "," << t->v[2] << ",";
		  t = t->next;
	 }
	 oss << n[0] << "," << n[1] << "," << n[2] << ",";
	 oss << d[0] << "," << d[1] << "," << d[2] << ",";
	 oss << isDeadly();
	 for (int i = 0; i < 4; i++)
	 {
		  oss << "," << edges[i];
	 }
	 oss << "," << vel[0] << "," << vel[1] << "," << vel[2];
	 oss << endl;
	 return oss.str();
}

void object::setPos (void)
{
	 pos[0] = xres/2.0;
	 pos[1] = yres/2.0;
	 pos[2] = 1.0;
}

void object::setPos (const float &x, const float &y, const float &z)
{
	 shiftEdges(x, y, z);
	 if (x < 0.0)
	 {
		  pos[0] = 0.0;
	 }
	 else
	 {
		  pos[0] = x;
	 }
	 if (y < 0.0)
	 {
		  pos[1] = 0.0;
	 }
	 else
	 {
		  pos[1] = y;
	 }
	 if (z < 0.0)
	 {
		  pos[2] = 0.0;
	 }
	 else
	 {
		  pos[2] = z;
	 }
}

void object::setPortalable (const int &a)
{
	 if (a != 1 && a != 0)
	 {
		  TOGGLE(portalable);
	 }
	 else
	 {
		  portalable = a;
	 }
}

void object::setHead (const vec_list * p = 0)
{
	 if (p == 0)
	 {
		  return;
	 }
	 head = (vec_list *)p;
}

int object::isEmpty(void)
{
	 if (head == 0)
	 {
		  return 1;
	 }
	 if (head->v[0] == empty_vec[0] && head->v[1] == empty_vec[1] && head->v[2] == empty_vec[2])
	 {
		  return 2;
	 }
	 return 0;
}

int object::isDeadly(void)
{
	 return deadly;
}

void object::setDeadly(const int &a = 1)
{
	 deadly = a;
}

void object::addVec (const float &x = 0.0, const float &y = 0.0, const float &z = 0.0)
{
	 if (isEmpty()) // no verticies added yet (heads is empty)
	 {
		  head->v[0] = x;
		  head->v[1] = y;
		  head->v[2] = z;
		  return;
	 }
	 vec_list * a = (vec_list *)malloc(1*sizeof(vec_list));
	 a->v[0] = x;
	 a->v[1] = y;
	 a->v[2] = z;
	 getLastVert()->next = a;
	 a->next = 0;
	 return;
}

void object::shiftD (const float &x, const float &y, const float &z)
{
	 d[0] += x;
	 d[1] += y;
	 d[2] += z;
}

void object::shiftN (const float &x, const float &y, const float &z)
{
	 Log("In setN, n[1] = %2.f, y = %.2f\n", n[1], y);
	 n[0] += x;
	 n[1] += y;
	 n[2] += z;
	 Log("done adding y to n, n[1] = %.2f\n", n[1]);
}

void object::shiftPos (const float &x, const float &y, const float &z)
{
	 shiftEdges(x, y, z);
	 pos[0] += x;
	 pos[1] += y;
	 pos[2] += z;
}

void object::invertD(void)
{
	 d[0] *= (-1.0);
	 d[1] *= (-1.0);
	 d[2] *= (-1.0);
}

void object::invertN(void)
{
	 n[0] *= (-1.0);
	 n[1] *= (-1.0);
	 n[2] *= (-1.0);
}

void object::initVectors(void)
{
	 Log("in initVectors\n");
	 Vec a, b, c;
	 a[0] = getVert(0)[0];
	 a[1] = getVert(0)[1];
	 a[2] = getVert(0)[2];
	 b[0] = getVert(1)[0];
	 b[1] = getVert(1)[1];
	 b[2] = getVert(1)[2];
	 c[0] = getVert(2)[0];
	 c[1] = getVert(2)[1];
	 c[2] = getVert(2)[2];
	 VecSub(a, b, d); // directional vector, not unit
	 VecSub(b, c, n); // normal vector, not unit
	 makeUnit(&d);
	 makeUnit(&n);
}

object & object::operator = (const object &r)
{
	 pos[0] = r.pos[0];
	 pos[1] = r.pos[1];
	 pos[2] = r.pos[2];
	 portalable = r.portalable;
	 head = r.head;
	 return (*this);
}

portal::portal()
{
	 objcnt--;
	 setIsPlaced(0);
	 drawPortal();
	 setDeadly(0);
}

portal::portal(const portal &r) : object(r)
{
	 objcnt--;
	 is_placed = r.is_placed;
	 setDeadly(0);
}

portal::~portal()
{
	 objcnt++;
	 is_placed = 0;
	 setDeadly(0);
}

int portal::isPlaced(void)
{
	 return is_placed;
}

int portal::getIsPlaced(void)
{
	 return is_placed;
}

string portal::toString(void)
{
	 ostringstream oss;
	 oss << object::toString();
	 oss << "Is placed?\n\t";
	 if (isPlaced())
	 {
		  oss << "Yes\n";
	 }
	 else
	 {
		  oss << "No\n";
	 }
	 oss << endl;
	 return oss.str();
}

string portal::dumpCsv(void)
{
	 ostringstream oss;
	 oss << object::dumpCsv();
	 oss << isPlaced() << ",";
	 return oss.str();
}

void portal::setIsPlaced(const int &a = -1)
{
	 if (a != 1 && a != 0)
	 {
		  TOGGLE(is_placed);
	 }
	 else
	 {
		  is_placed = a;
	 }
}

void portal::setPlaced(const int &a = -1)
{
	 if (a != 1 && a != 0)
	 {
		  TOGGLE(is_placed);
	 }
	 else
	 {
		  is_placed = a;
	 }
}

void portal::drawPortal(void)
{
	 int x = 0, y = 0, z = 0;
	 x = p_width;
	 y = p_height;
	 Vec a, b, c;
	 a[0] = -1*x;
	 a[1] = -1*y;
	 a[2] = 0;
	 b[0] = -1*x;
	 b[1] = 1*y;
	 b[2] = 0;
	 c[0] = 1*x;
	 c[1] = 1*y;
	 c[2] = 0;
	 addVec(-1*x, -1*y, z); // draw a basic portal
	 addVec(-1*x, 1*y, z);
	 addVec(1*x, 1*y, z);
	 addVec(1*x, -1*y, z);
	 Log("in drawPortal, creating vectors:\n");
	 Log("\td = <%f,%f,%f>\n\tn = <%f,%f,%f>\n", d[0], d[1], d[2], n[0], n[1], n[2]);
	 VecSub(a, b, d); // directional vector, not unit
	 VecSub(b, c, n); // normal vector, not unit
	 Log("\td = <%f,%f,%f>\n\tn = <%f,%f,%f>\n", d[0], d[1], d[2], n[0], n[1], n[2]);
	 Log("making magnitude 1...\n");
	 makeUnit(&d);
	 makeUnit(&n);
	 Log("\td = <%f,%f,%f>\n\tn = <%f,%f,%f>\n", d[0], d[1], d[2], n[0], n[1], n[2]);
}

portal & portal::operator = (const portal &r)
{
	 object::operator=(r);
	 is_placed = r.is_placed;
	 return (*this);
}

bool operator == (const portal &l, const portal &r)
{
	 return (l.pos == r.pos);
}
