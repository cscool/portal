#ifndef DOOR_H
#define DOOR_H

typedef struct _door {
	b2Body * door;
	b2Vec2 max_pos;
	b2Vec2 min_pos;
	float speed;
	int active;
} Door;
#endif
