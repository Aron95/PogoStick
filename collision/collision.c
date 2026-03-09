
#include "gameObject/gameObject.h"
#include "globals.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>
#include "enums/enum.h"


void collisionDetection(GameObject * gameObjectsPTArry[], int size) {
	 bool collisonFound = true;
	 Rectangle playerBox = playerGlobalpt ->collisionBox ->collisionRectangle;
	 for(int i =0; i < size;i++){
	 	GameObject gameObject = *gameObjectsPTArry[i];
	 	Rectangle collisonBox = gameObject.collisionBox ->collisionRectangle;


	 	if (CheckCollisionRecs(playerBox,collisonBox)) {
	 		collisonFound = false;
	 	}else {
	 		collisonFound = true;
	 	}

	 }
	 playerGlobalpt ->collisionBox ->isColliding = collisonFound;
}