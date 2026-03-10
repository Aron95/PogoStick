#include "enums/enum.h"
#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include "gameObject/gameObject.h"





void playerMotionInput(GameObject* gameObject){


    //printf("is %s colliding : %d\n",gameObject->name ,gameObject -> collisionBox ->isColliding);


    if(!gameObject -> collisionBox ->isColliding){
        if(gameObject->animation->orientation == RIGHT_ORIENTATION){
            gameObject->animation->inMovement = true;
            gameObject->animation->position.x -= 0.7f;
            gameObject->collisionBox->collisionRectangle.x -= 0.7f;
        }  
        if(gameObject->animation->orientation == LEFT_ORIENTATION){
            gameObject->animation->inMovement = true;
            gameObject->animation->position.x += 0.7f;
            gameObject->collisionBox->collisionRectangle.x += 0.7f;

        }    
        if(gameObject->animation->orientation == TOP_ORIENTATION){
            gameObject->animation->inMovement = true;
            gameObject->animation->position.y += 0.7f;
            gameObject->collisionBox->collisionRectangle.y += 0.7f;

        }    
        if(gameObject->animation->orientation == BOTTOM_ORIENTATION){
            gameObject->animation->inMovement = true;
            gameObject->animation->position.y -= 0.7f;
            gameObject->collisionBox->collisionRectangle.y -= 0.7f;

        }
    }
    if (IsKeyPressed(KEY_D)) {
        printf("Test sound melee attack \n");
        PlaySound(*gameObject -> meeleSound);      // Play WAV sound
    }
    
    if (IsKeyPressed(KEY_S)) {
        printf("Test sound shoot attack \n");
        PlaySound(*gameObject -> shootSound); // Play WAV sound

    }


    if (IsKeyDown(KEY_RIGHT)) {
        
             gameObject->animation->inMovement = true;
             gameObject->animation->position.x += 0.7f;
             gameObject->animation->orientation = RIGHT_ORIENTATION;
             gameObject->collisionBox->collisionRectangle.x += 0.7f;

    } else if (IsKeyDown(KEY_LEFT)) {
        
             gameObject->animation->inMovement = true;
             gameObject->animation->position.x -= 0.7f;
             gameObject->collisionBox->collisionRectangle.x -= 0.7f;
             gameObject->animation->orientation = LEFT_ORIENTATION;
        
    } else if (IsKeyDown(KEY_UP)) {
            gameObject->animation->inMovement = true;
            gameObject->animation->position.y -= 0.7f;
            gameObject->collisionBox->collisionRectangle.y -= 0.7f;
            gameObject->animation->orientation = TOP_ORIENTATION;
        
    } else if (IsKeyDown(KEY_DOWN)) {
            gameObject->animation->inMovement = true;
            gameObject->animation->position.y += 0.7f;
            gameObject->collisionBox->collisionRectangle.y += 0.7f;
            gameObject->animation->orientation = BOTTOM_ORIENTATION;
    } else {
        gameObject->animation->inMovement = false;
    }
}


void cameraControllInput(Camera2D* camera) {
    camera->zoom = expf(logf(camera -> zoom) + ((float)GetMouseWheelMove()*0.1f));

}


void evaluateKeyStrokes(GameObject* gameObject, Camera2D* camera) {
    playerMotionInput(gameObject);
    cameraControllInput(camera);

}
