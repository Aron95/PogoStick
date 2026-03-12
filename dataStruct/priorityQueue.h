typedef struct {
	int *buffer;
	int currendNodeCount;
	int maxNodes;
} HeapArena;



void InsertHeapArena(HeapArena* heap, int insertValue);
int PopHeapArena(HeapArena* heap);