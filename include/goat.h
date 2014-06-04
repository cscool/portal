#ifndef GOAT_H
#define GOAT_H

typedef struct _goat {
    b2Body * goat;
    b2Vec2 max_pos;
    b2Vec2 min_pos;
    b2Vec2 dir;
    float speed;
} Goat;
#endif
