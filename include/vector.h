#pragma once
#include <iostream>

using namespace std;

float getAngle(Vec &p)
{
	 return (arctan(p[1]/p[0]));
}
