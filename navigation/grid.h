#ifndef GRID_H
#define GRID_H

#include <stdbool.h>
#include "gameObject/gameObject.h"
#include "raylib.h"
#include "dataStruct/priorityQueue.h"


typedef struct {
	Vector2 position;
	int width;
	int height;
	bool walkable;
} Cell;

typedef struct {
	int width;
	int height;
	int cellWidth;
	int cellHeigh;
	bool diplay;
	Cell* cells; // rework
	int cellsLenght; 
} Grid;

typedef struct {
	int cellIndex;
	float gValue;
	float fValue;
	float hValue;
	int parentIndex;
} PathNode;

typedef struct {
	PathNode* pathNode;
	int pathNodeLength;	
} Path;

Cell* GetCell(Grid* grid, Vector2* coordinate);
Grid* InitNavigationGrid(int width, int height, int cellWidth, int cellHeigth, bool display);
void DrawNavigationGrid(Grid* grid);
void LightUpCell(Cell* cell);
int FindNearesCellToPosition(Grid* grid, GameObject* gameObject);
HeapArena* AStarAlgorithm(Grid* grid, int startIndex, int tragetIndex);
HeapArena* BuildPathToPlayer(Grid* grid, GameObject* sourceGameObject);

#endif // GRID_H