#ifndef MOVINGPLATFORM_H
#define MOVINGPLATFORM_H

typedef struct moving_platform {
    b2Body * platform;
    b2Vec2 start;
    b2Vec2 end;
    b2Vec2 direction;
    float speed;
    bool active = false;
    bool angleActive = false;
    float maxAngle;
    float minAngle;
    float angleSpeed;
} Platform;
#endif
