#include "enums/enum.h"
#include "gameObjectDefinitions.h"
#include "globals.h"
#include "raylib.h"
#include "gameObject.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


bool isCollisionBoxConfigured(const float* collisonBoxConfig) {
	for(int i=0; i< 3; i++){ // collisonBoxConfig size is 4
		if(collisonBoxConfig[i]!=0) return true;
	}
	return false;
}

Vector2 GetPlayerPosition(){
	GameObject* player = playerGlobalpt;
	Vector2 position = player -> animation ->position;
	position.x += 50;
	position.y += 76;
	return position;
}

void createNewGameObject(Vector2* position, 
						 GameObjectDefinition gameObjectDefinition,
						 GameObject *allNonePlayerGameObjects [] )
{
	printf("Start \n");
	GameObjectAnimation* animationConfig = malloc(sizeof(GameObjectAnimation));
	GameObject* gameObject = malloc(sizeof(GameObject));
	CollisionBox* collisionBox = malloc(sizeof(CollisionBox));
	Rectangle* collisionRectangle = malloc(sizeof(Rectangle));
	Texture2D gameObjectTexture = LoadTexture(gameObjectDefinition.spritePath);



	Rectangle frameRec = { position ->x, position -> y, 
						  (float)gameObjectTexture.width/gameObjectDefinition.spriteSheetLength, 
						  (float)gameObjectTexture.height};

	if (isCollisionBoxConfigured(gameObjectDefinition.collisonBoxConfig)) {
		collisionRectangle -> x = position ->x + gameObjectDefinition.collisonBoxConfig[0];
		collisionRectangle -> y = position ->y + gameObjectDefinition.collisonBoxConfig[1];
		collisionRectangle -> width = gameObjectDefinition.collisonBoxConfig[2];
		collisionRectangle -> height = gameObjectDefinition.collisonBoxConfig[3];
				
	}else {
		collisionRectangle -> x = position ->x;
		collisionRectangle -> y = position ->y;
		collisionRectangle -> width = (float)gameObjectTexture.width/gameObjectDefinition.spriteSheetLength;
		collisionRectangle -> height = (float)gameObjectTexture.height;
	}


	animationConfig ->sprite =gameObjectTexture;
	animationConfig ->animationSpeed = 0;
	animationConfig ->tick =0;
	animationConfig ->position = *position;
	animationConfig ->renderFrame = frameRec;
	animationConfig -> orientation = gameObjectDefinition.orientation;
	animationConfig -> inMovement = false;


	collisionBox ->collisionRectangle = *collisionRectangle; //Create Collision box for GameObject
	collisionBox -> isColliding = false;

	memcpy(gameObject->name,  gameObjectDefinition.name, 49);
	memcpy(gameObject ->path, gameObjectDefinition.spritePath, 49);
	gameObject->name[49] = '\0';
	gameObject->path[49] = '\0';

	gameObject -> animations = *gameObjectDefinition.animationDescription;
	
	gameObject -> animation = animationConfig;
	gameObject -> collisionBox = collisionBox;

	if (gameObjectDefinition.gameObjectType == PLAYER_TYPE) {
    	gameObject->meeleSound = malloc(sizeof(Sound));
    	gameObject->shootSound = malloc(sizeof(Sound));

    	
    	Sound meeleSound = LoadSound(gameObjectDefinition.attackSoundPath);
    	Sound shootSound = LoadSound(gameObjectDefinition.shootSoundPath);

    	if (meeleSound.frameCount == 0) {
    		printf("sound with path: %s could not loaded \n",gameObjectDefinition.attackSoundPath);
    	}

    	if (shootSound.frameCount == 0) {
    		printf("sound with path: %s could not loaded \n",gameObjectDefinition.shootSoundPath);
    	}

    	// Load directly into the allocated memory
    	*(gameObject->meeleSound) = LoadSound(gameObjectDefinition.attackSoundPath);
    	*(gameObject->shootSound) = LoadSound(gameObjectDefinition.shootSoundPath);
	}


	if (gameObjectDefinition.gameObjectType == PLAYER_TYPE){
		playerGlobalpt = gameObject;
	}
	else {
		allNonePlayerGameObjects[0] = gameObject;
	}
	
}


bool hasSounds(GameObject* gameObject) {
	//todo implement
	return false;
}
