#include <stdbool.h>
#include "gameObject/gameObject.h"
#include "raylib.h"





typedef struct {
	int xPosiiton;
	int yPosition;
} Coordinate;

typedef struct {
	int xPos;
	int yPos;
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
	Cell* cells;
	int  cellsLength;
} Path;



Cell* GetCell(Grid* grid, Coordinate* coordinate);
Grid* InitNavigationGrid(int width, int height, int cellWidth, int cellHeigth, bool display);
void DrawNavigationGrid(Grid* grid);
void LightUpCell(Cell* cell);
int FindNearesCellToPosition(Grid* grid, GameObject* gameObject);