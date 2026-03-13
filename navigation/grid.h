#ifndef GRID_H
#define GRID_H

#include <stdbool.h>
#include "gameObject/gameObject.h"
#include "raylib.h"



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
	float g_value;
	float f_value;
	float h_value;
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

#endif // GRID_H