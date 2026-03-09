#include "collision/collision.h"
#include "raylib.h"
#include "input.h"
#include "animations.h"
#include "gameObject/gameObject.h"
#include "gameObject/gameObjectDefinitions.h"
#include "navigation/grid.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"

/*
	-1 on first position means that there is no

*/
GameObject* playerGlobalpt = NULL;

GameObject* OtherGameObjects [1];

Camera2D createCamera(GameObject* player,int screenWidth,int screenHeight){
	printf("test camera player \n");

	Camera2D camera = { 0 };
    camera.target = (Vector2){ player ->animation -> position.x + 20.0f, player->animation-> position.y + 20.0f };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    printf("test camera player \n");

    return camera;
}


int main () {
	GameObject* toAnimateArry [64];
	const int screenWidth = 1024;
	const int screenHeight = 764;
	InitWindow(screenWidth, screenHeight, "Test Window");
    InitAudioDevice();
    Grid* grid =InitNavigationGrid(screenWidth, screenHeight, 32, 32, 0);

    Music music = LoadMusicStream("resource/music/HintergrundMusik.mp3");
    music.looping = true;
   
    PlayMusicStream(music);

    Vector2 startPositionPlayer = { 0.0f, 0.0f };
    Vector2 positionKrug = { 300.0f, 10.0f};

	createNewGameObject(&startPositionPlayer, PLAYER_DEF, OtherGameObjects);
    createNewGameObject(&positionKrug, KRUG_DEF, OtherGameObjects);

	

	GameObject* player = playerGlobalpt;
	toAnimateArry[0] = player;
	toAnimateArry[1] = OtherGameObjects[0];
	Camera2D camera = createCamera(player, screenWidth, screenHeight);


    SetTargetFPS(60); 
    int framesCounter = 0;
    int framesSpeed = 10; 
    if (music.stream.buffer == NULL) {
        TraceLog(LOG_WARNING, "FILE NOT FOUND: Check your path!");
        return -1;
    }

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {   

        //UpdateMusicStream(music); 


        int cellIndex = FindNearesCellToPosition(grid,player);

        collisionDetection(OtherGameObjects,1);
    	evaluateKeyStrokes(player, &camera);
    	framesCounter++;
        if (framesCounter >= (60/framesSpeed)){
        	framesCounter = 0;
        	for (int i =0; i <1; i++) {
        		

        		UpdateAnimationRectangle(toAnimateArry[i]);
     	   }
    	}
        BeginDrawing();
        	

        	ClearBackground(RAYWHITE);

        	BeginMode2D(camera);
                LightUpCell(&grid ->cells[cellIndex]);
                DrawNavigationGrid(grid);
                DrawAnimationsInList(toAnimateArry, 1);
            EndMode2D();

            DrawFPS(700, 15);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;

}