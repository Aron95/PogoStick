#include "raylib.h"
#include "stdio.h"
#include "animation/animations.h"
#include <time.h>





void currentTime(char* occasionName) {
	time_t rawtime;
    
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    printf("Current local time and date: %s, %s", asctime(timeinfo),occasionName);
} 

void DrawAnimationsInList(GameObject* toAnimateArry [], int toAnimationSize) {
	for (int i =0; i<=toAnimationSize; i++){
		// Rectangle frameRec = toAnimateArry[i] -> collisionBox -> collisionRectangle;
		// DrawRectangleLines(frameRec.x,
		// 				  	frameRec.y, 
		// 				   (int)frameRec.width, (int)frameRec.height, 
		// 				   RED);
		DrawTextureRec(toAnimateArry[i]->animation->sprite, 
					   toAnimateArry[i]->animation-> renderFrame,
					   toAnimateArry[i]->animation ->position, 
					   WHITE);
	}
}

/*
gets all the nessesary data from GameObjectAnimation to move the Rectangle on the given sprite sheet in correct order for given orientation
*/
void UpdateAnimationRectangle(GameObject* gameObject) {
	int* animationDefinition = NULL;
	Animations frameInformation = gameObject -> animations;

	if (gameObject -> animation -> orientation == RIGHT_ORIENTATION) animationDefinition = frameInformation.rightAnimation;
    if (gameObject -> animation -> orientation == BOTTOM_ORIENTATION) animationDefinition = frameInformation.bottomAnimations;
    if (gameObject -> animation -> orientation== LEFT_ORIENTATION) animationDefinition = frameInformation.leftAnimation;
    if (gameObject -> animation -> orientation == TOP_ORIENTATION) animationDefinition = frameInformation.topAnimations;
    if (gameObject -> animation -> orientation==0) animationDefinition = frameInformation.rightAnimation; //todo: better error message


    if (animationDefinition == NULL){
    	return;
    }

	if (gameObject -> animation  -> inMovement) {
		gameObject -> animation ->tick++;
	} else {
		gameObject -> animation  -> tick = animationDefinition[3];
	}

   	if (gameObject -> animation ->tick>animationDefinition[2]) gameObject -> animation ->tick = animationDefinition[1]; 
    
    gameObject -> animation ->renderFrame.x = (float)gameObject -> animation ->tick*(float)gameObject -> animation ->sprite.width/20;
}



