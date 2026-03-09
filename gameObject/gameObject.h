#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "gameObjectDefinitions.h"
#include "raylib.h"
#include "enums/enum.h"
#include <stdbool.h>


typedef struct {
	Texture2D sprite;
	int animationSpeed;
	int tick;
	Vector2 position;
	Rectangle renderFrame;
	Orientation orientation;
	bool inMovement;
} GameObjectAnimation;

/*
	Struct to define game objects.
	Animations define how to read .png right for the given path. See Animations Struct for more informations.
	Path gives path from .png spritesheet.
*/
typedef struct {
	char name[50];
	Animations animations;
	char path[50];
	GameObjectAnimation* animation;
	CollisionBox* collisionBox;
	GameObjectType gameObjectType;
	Sound* meeleSound;
	Sound* shootSound;
} GameObject;


typedef struct {

} GameObjectBuild;


void createNewGameObject(Vector2* position, GameObjectDefinition GameObjectDefinition,GameObject *allNonePlayerGameObjects [] );
Vector2 GetPlayerPosition();

#endif