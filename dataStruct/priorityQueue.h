#include <stddef.h>


typedef struct {
	int *buffer;
	int currendNodeCount;
	int maxNodes;
} HeapArena;


HeapArena* CreateHeapArena(size_t arenaSize);
int InsertHeapArena(HeapArena* heap, int insertValue);
int PopHeapArena(HeapArena* heap);