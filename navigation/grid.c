#include "grid.h"
#include "enums/enum.h"
#include "gameObject/gameObject.h"
#include "globals.h"
#include "raylib.h"
#include <cstddef>
#include <iterator>
#define RAYMATH_IMPLEMENTATION
#include "raymath.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/*TODO: Create Pathfinding over calculationg every weight for every cell on the map based on the player position*/

/*Creats an cartesian coord sytem saved in Column Major Order array*/
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
				{currentPositionX, currentPositionY}, cellWidth, cellHeigth
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
            cell.position.x + cell.width / 2.0f,
            cell.position.y + cell.height / 2.0f
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
	size_t index = coordinate -> x + (grid->width / grid->cellWidth) * coordinate ->y; //index = x + NX *y Column Major Order
	return grid -> cells+index;
}


void LightUpCell(Cell* cell){
	//printf("draw grid cell pos x %d, cell pos y  %d \n", cell ->xPos,  cell -> yPos);
	DrawRectangle(cell ->position.x, cell ->position.y, cell ->height, cell ->width, RED);
}

float CalculateManhattanDistance(Vector2 start, Vector2 end){
	return fabs(start.x - end.x) + fabs(start.y - end.y);
}

/*uses a* algorithm to calculate path to object given Vector2, works with manhattan distance and only dinstance lower 200*/
Path* AStarAlgorithm(Grid* grid, int startIndex, int endIndex, int relativPositions [4]){
	Cell endCell = grid->cells[endIndex];
	Path* path = malloc(sizeof(Path));

	PathNode proceededCells [100];
	int currentIndex = startIndex;
	int currentGValue=100;
	int currentFValue=0;
	int currentHValue=100;
	proceededCells[0] = (PathNode){
		startIndex,
		currentGValue,
		currentFValue,
		currentHValue}; 
	int finishedCellsLength = 1;

	PathNode* cheapestPathNodes = malloc(sizeof(PathNode)*grid->cellsLenght);
	int cheapestPathLength = 0;


	while(true){
		if (currentIndex == endIndex) {
			break;
		}

		currentGValue++;
		int tempLowestHValue;
		int tempLowestCurrentIndex = currentIndex;

		for (int i=0; i<4; i++){ // iterates all relativPositions for caluclating values
			int currentRelativIndex = relativPositions[i] + currentIndex;

			for(int i =0; i<finishedCellsLength;i++){ // checks if index was already processed if yes, continue to next index.
				if(currentRelativIndex == proceededCells[i].cellIndex){
					continue;
				}
			}

			currentHValue = CalculateManhattanDistance( // calculates h value
				grid->cells[currentRelativIndex].position,
			 	endCell.position);



			if (tempLowestHValue+currentGValue>currentHValue + currentGValue){ // if checks if temp_h is bigger, if yes sets new tempCurrentIndex and tempLowestHValue to find cheapest path
				tempLowestCurrentIndex = currentRelativIndex;
				tempLowestHValue = currentHValue;
				currentFValue = currentHValue+currentGValue;
			}

			proceededCells[finishedCellsLength] = (PathNode){startIndex,currentGValue,currentFValue,currentHValue};
		}
		cheapestPathNodes[cheapestPathLength] = (PathNode){tempLowestHValue,currentGValue,currentHValue, currentFValue};
		cheapestPathLength++;

	}

	path = &(Path){cheapestPathNodes,cheapestPathLength};
	return path;
}


Path* BuildPathToPlayer(Grid* grid, GameObject* sourceGameObject){
	Path* path = malloc(sizeof(Path));
	GameObject* player = playerGlobalpt;
	int sourceCellIndex = FindNearesCellToPosition(grid,sourceGameObject);
	int sinkCellIndex = FindNearesCellToPosition(grid,player);
	
	int rowLength = grid ->width / grid ->cellWidth;
	int relativeTopBottom = grid ->width/grid->cellWidth; // to get in a Column Major Order the Element right in top of cartesian coordination system we ne to move the index 1 full row element count.

	int relativPositions [4] = {1,-1,relativeTopBottom,-relativeTopBottom};
	

	return AStarAlgorithm(grid,sourceCellIndex,sinkCellIndex, relativPositions);
}








