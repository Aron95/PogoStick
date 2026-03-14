#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "priorityQueue.h"



void LogHeap(HeapArena* arena){
	printf("Heap  max nodes %d, Heap current nodes %d",arena ->maxNodes, arena ->currendNodeCount);
}

//TODO: Make it generic to work for every kind of data

/* Creates a Heap Arena based on gridsize*/
HeapArena* CreateHeapArena(size_t arenaSize){
	HeapArena* arena = (HeapArena*)malloc(sizeof(HeapArena));
	if (arena == NULL) {
		printf("Failed to allocate HeapArena\n");
		return NULL;
	}
	arena->buffer = (PathNode*)malloc(sizeof(PathNode) * arenaSize);
	if (arena->buffer == NULL) {
		printf("Failed to allocate buffer for HeapArena \n");
		free(arena); 
		return NULL;
	}
	arena->maxNodes = arenaSize;
	arena->currendNodeCount = 0;
	return arena;
}


/*at the moment minheap because only used for astar algorithm*/
int InsertHeapArena(HeapArena* heap, PathNode insertValue){
	if (heap->currendNodeCount >= heap->maxNodes) return -1; // heap full

	
	//enquere value onto the heap
	int currentIndex = heap ->currendNodeCount;
	heap -> buffer[currentIndex] = insertValue;
	heap->currendNodeCount ++;


	while(currentIndex > 0){
		int parentIndex = (currentIndex -1)/2;

		//printf("Parent value %d, Parent Index %d \n", heap -> buffer[parentIndex], parentIndex);
		//printf("Current Value %d, Current Index %d \n", heap -> buffer[currentIndex], currentIndex);

		if (heap ->buffer[parentIndex].fValue > heap ->buffer[currentIndex].fValue)
		{
			// printf(" swap \n");

			PathNode temp = heap->buffer[parentIndex];
            heap->buffer[parentIndex] = heap->buffer[currentIndex];
            heap->buffer[currentIndex] = temp;

            currentIndex = parentIndex;
		}  else {
			// printf(" no swap \n");
            // is in right order
            break;
        }
	}
	return 1;
}


/*pops fist element out of the Heap Arena only minheap at the moment*/
PathNode PopHeapArena(HeapArena* heap) {
	if (heap->currendNodeCount == 0) { //heap is empty
        PathNode emptyNode = {-1, 0.0f, 0.0f, 0.0f}; // Return a default invalid node
        return emptyNode;
    }

	PathNode returnValue = heap->buffer[0]; // gets first element

	heap->buffer[0] = heap->buffer[heap->currendNodeCount - 1];
	heap->currendNodeCount--;

	int currentIndex = 0;
	while(currentIndex < heap->currendNodeCount){ // bubble down
		int leftChildIndex = 2 * currentIndex +1;    
		int rightChildIndex =  2 * currentIndex + 2; 
		int smallest = currentIndex;
		
        if (leftChildIndex < heap->currendNodeCount &&     //check if left is smaller and if bottom reached
            heap->buffer[leftChildIndex].fValue < heap->buffer[smallest].fValue) {
            smallest = leftChildIndex;
        }

        if (rightChildIndex < heap->currendNodeCount &&   //check if right is smaller and if bottem reached
            heap->buffer[rightChildIndex].fValue < heap->buffer[smallest].fValue) {
            smallest = rightChildIndex;
        }

        if (smallest == currentIndex) break; // if no change we reached bottom

       	PathNode temp = heap->buffer[currentIndex]; //swap 
        heap->buffer[currentIndex] = heap->buffer[smallest];
        heap->buffer[smallest] = temp;

        currentIndex = smallest;
    }
	return returnValue;
}

