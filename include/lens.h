#ifndef LENS_H
#define LENS_H

#include "door.h"

typedef struct lens_button {
	b2Body * lens;
	Door door;
	bool active;
} Lens;
#endif
