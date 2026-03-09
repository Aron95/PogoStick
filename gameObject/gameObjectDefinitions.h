#ifndef GAMEOBJECTDEFINITIONS_H
#define GAMEOBJECTDEFINITIONS_H
#include "enums/enum.h"
#include "raylib.h"

typedef struct {
	const char* spritePath ;
	const int spriteSheetLength; // how much animation frames are on the actual image. Used to divide for animation frame size rect.
	const char* name ;
	const Orientation orientation;
	const GameObjectType gameObjectType;
	const Animations* animationDescription;
	const float  collisonBoxConfig [4];	// tricky value, it defines where the actual sprit starts at its canvas and how long it is from there from leff top Corner.
										// 42,42,32,12 means it starts 0+42 for x and 0+42 for y and form there the actual movement is 32 and 12 pixel long.
										// {0,0,0,0}means not configured
	const char* attackSoundPath;
	const char* shootSoundPath;
} GameObjectDefinition;


extern const GameObjectDefinition PLAYER_DEF;	
extern const GameObjectDefinition KRUG_DEF;
#endif