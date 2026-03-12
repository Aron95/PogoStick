#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "priorityQueue.h"

//TODO: Make it generic to work for every kind of data

/* Creates a Heap Arena based on gridsize*/
HeapArena* CreateHeapArena(int width, int height){
	size_t arenaSize = width*height* sizeof(HeapArena);
	HeapArena* arena = malloc(sizeof(arenaSize));
	return arena;
}


/*acs compare, if a > b return 1, a < b return -1, equallity returns 0*/
int compare_acs(const void *a, const void *b){
	int arg1 = *(const int*)a;
	int arg2 = *(const int*)b;


	if (arg1<arg2) return -1;
	if (arg1>arg2) return 1;
	return 0;
}

/*at the moment minheap because only used for astar algorithm*/
void InsertHeapArena(HeapArena* heap, int insertValue){
	if (heap->currendNodeCount >= heap->maxNodes) return; // heap full

	
	//enquere value onto the heap
	int currentIndex = heap ->currendNodeCount;
	heap -> buffer[currentIndex] = insertValue;
	heap->currendNodeCount ++;

	while(currentIndex > 0){
		int parentIndex = (currentIndex -1)/2;
		if (compare_acs(&heap ->buffer[parentIndex], &heap ->buffer[currentIndex]))
		{
			int temp = heap->buffer[parentIndex];
            heap->buffer[parentIndex] = heap->buffer[currentIndex];
            heap->buffer[currentIndex] = temp;

            currentIndex = parentIndex;
		}  else {
            // is in right order
            break;
        }
	}
}


/*pops fist element out of the Heap Arena only minheap at the moment*/
int PopHeapArena(HeapArena* heap) {
	if (heap->currendNodeCount ==0) return -1; //heap is empty

	int returnValue = heap->buffer[0]; // gets first element

	heap->buffer[0] = heap->buffer[heap->currendNodeCount - 1];
	heap->currendNodeCount--;

	int currentIndex = 0;
	while(currentIndex < heap->currendNodeCount){ // bubble down
		int leftChildIndex = 2 * currentIndex +1;    
		int rightChildIndex =  2 * currentIndex + 2; 
		int smallest = currentIndex;
		
        if (leftChildIndex < heap->currendNodeCount &&     //check if left is smaller and if bottom reached
            heap->buffer[leftChildIndex] < heap->buffer[smallest]) {
            smallest = leftChildIndex;
        }

        if (rightChildIndex < heap->currendNodeCount &&   //check if right is smaller and if bottem reached
            heap->buffer[rightChildIndex] < heap->buffer[smallest]) {
            smallest = rightChildIndex;
        }

        if (smallest == currentIndex) break; // if no change we reached bottom

        int temp = heap->buffer[currentIndex]; //swap 
        heap->buffer[currentIndex] = heap->buffer[smallest];
        heap->buffer[smallest] = temp;

        currentIndex = smallest;
    }
	return returnValue;
}

