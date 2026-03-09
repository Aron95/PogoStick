#include "grid.h"
#include "gameObject/gameObject.h"
#include "globals.h"
#include "raylib.h"
#define RAYMATH_IMPLEMENTATION
#include "raymath.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>



Grid* InitNavigationGrid(int width, int height, int cellWidth, int cellHeigth, bool display){
	Grid* grid = malloc(sizeof(Grid));

	size_t cellCountXAxe= width / cellWidth;
	size_t cellCountYAxe= height / cellHeigth;
	size_t ammoutOfCells = cellCountXAxe*cellCountYAxe;

	Cell* cellArry = malloc(ammoutOfCells * sizeof(Cell));
	if (cellArry == NULL) {
		free(grid);
		return NULL;
	}

	int currentPositionX = 0;
	int currentPositionY = 0;
	int arrayIndex = 0;
	for (int y = 0; y < cellCountYAxe; y++) {
		currentPositionX = 0; // Reset X position for each new row
		for (int x = 0; x < cellCountXAxe; x++) {
			cellArry[arrayIndex] = (Cell){
				currentPositionX, currentPositionY, cellWidth, cellHeigth
			};
			currentPositionX += cellWidth;
			arrayIndex++;
		}
		currentPositionY += cellHeigth;
	}
	grid->width = width;
	grid->height = height;
	grid->cellWidth = cellWidth;
	grid->cellHeigh = cellHeigth;
	grid->diplay = display;
	grid->cells = cellArry;
	grid->cellsLenght = ammoutOfCells;

	return grid;
}

void DrawNavigationGrid(Grid* grid){

	if (1) {

		int stepsWidth = grid ->width /grid ->cellWidth;
		int stepsHeight = grid ->height /grid ->cellHeigh;
	
		int lineCurrentX = 0;
		int lineCurrentY = 0;
		
		//printf("grid width: %d, grid height: %d, grid cellwidth %d, grid cell height %d", grid ->width ,grid ->height,grid ->cellWidth,grid ->cellHeigh);
		//printf("build line with steps width: %d and steps heights %d", stepsWidth,stepsHeight);

		for (int i = 0; i < stepsHeight; i ++){ //drawing horizontal lines
			//printf("draw lines from 0 %d to %d %d \n", lineCurrentY,grid->width, lineCurrentY);
			DrawLine(0, lineCurrentY, grid->width, lineCurrentY, RED);
			lineCurrentY += grid ->cellHeigh;
		}
	
		for (int i = 0; i < stepsWidth; i ++){ //drawing vertical lines
			//printf("draw lines from  %d, 0 to %d %d \n", lineCurrentX,lineCurrentX, grid -> height);
			DrawLine(lineCurrentX, 0, lineCurrentX, grid->height, RED);
			lineCurrentX += grid ->cellWidth;
		}
	}else {
		printf("did not draw grid because display off \n");
	}
}

int FindNearesCellToPosition(Grid* grid, GameObject* gameObject) {
	Vector2 position = gameObject -> animation ->position;
	position.x += 50;
	position.y += 76; // make this generic

    int nearestCellIndex = -1;
    float minDistance = -1.0f;

    for (int i = 0; i < grid->cellsLenght; i++) {
        Cell cell = grid->cells[i];
        Vector2 cellCenter = {
            cell.xPos + cell.width / 2.0f,
            cell.yPos + cell.height / 2.0f
        };

        float distance = Vector2Distance(position, cellCenter);

        if (nearestCellIndex == -1 || distance < minDistance) {
            minDistance = distance;
            nearestCellIndex = i;
        }
    }
    return nearestCellIndex;
}


Cell* GetCell(Grid* grid, Vector2* coordinate){
	size_t index = coordinate -> x + (grid->width / grid->cellWidth) * coordinate ->y; //index = x + NX *y
	return grid -> cells+index;
}


void LightUpCell(Cell* cell){
	//printf("draw grid cell pos x %d, cell pos y  %d \n", cell ->xPos,  cell -> yPos);
	DrawRectangle(cell ->xPos, cell ->yPos, cell ->height, cell ->width, RED);
}


Path* BuildPathToPlayer(Grid* grid, GameObject* sourceGameObject){
	Path* path = malloc(sizeof(Path));
	GameObject* player = playerGlobalpt;
	int sourceCellIndex = FindNearesCellToPosition(grid,sourceGameObject);
	int sinkCellIndex = FindNearesCellToPosition(grid,player);
	



	Cell sourceCell = grid -> cells[sourceCellIndex];
	Cell sinkCell = grid -> cells[sinkCellIndex];



	
	
	


	return path;
}


