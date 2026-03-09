#ifndef ENUM_H
#define ENUM_H
#include "raylib.h"

typedef enum {
	LEFT_ORIENTATION = 0,
	RIGHT_ORIENTATION = 1,
	TOP_ORIENTATION = 2,
	BOTTOM_ORIENTATION = 3,
	NONE_ORIENTATION = 4
} Orientation;


typedef enum {
	PLAYER_TYPE = 0,
	ENEMY_TYPE=1,
	NPC_TYPE=2,
    ITEM_TYPE=3
} GameObjectType;


/*
	Struct defines all animations and how they are interpreted.
	First value can be 0 or 1 for existing.
	Second value defines starting point.
	Thrid value defines end point.
	Fourth value defines not in motion frame
*/
typedef struct {
	int leftAnimation[4];
	int rightAnimation[4];
	int bottomAnimations[4];
	int topAnimations[4];
	int deathAnimations[4];
	int attackAnimations[4];
} Animations;


typedef struct {
	Rectangle collisionRectangle;
	bool isColliding;
} CollisionBox;


#endif