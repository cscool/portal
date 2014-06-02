#ifndef TURRET_H
#define TURRET_H

typedef struct laser_turret {
	b2Body * turret;
	float max_angle;
	float min_angle;
	float angleSpeed;
} Turret;
#endif
