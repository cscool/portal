#ifndef MINE_H
#define MINE_H

typedef struct _mine {
	b2Body * mine;
	b2Vec2 max_pos;
	b2Vec2 min_pos;
	b2Vec2 dir;
	float speed;
} Mine;
#endif
