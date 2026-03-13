#include <stddef.h>
#include "navigation/grid.h"

typedef struct {
	PathNode *buffer;
	int currendNodeCount;
	int maxNodes;
} HeapArena;


HeapArena* CreateHeapArena(size_t arenaSize);
int InsertHeapArena(HeapArena* heap, PathNode insertValue);
PathNode PopHeapArena(HeapArena* heap); 
void LogHeap(HeapArena* arena);