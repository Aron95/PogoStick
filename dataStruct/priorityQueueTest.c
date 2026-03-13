#include "priorityQueue.h"
#include <assert.h>
#include <stdio.h>
#include "navigation/grid.h"

#define TEST_ARRAY_HEAP { \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 1.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 2.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 3.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 5.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 6.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 8.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 9.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 10.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 13.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 32.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 43.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 45.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 46.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 47.0f, .h_value = 0.0f}  \
}
#define TEST_ARRAY_HEAP_BUBBLE_DOWN { \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 1.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 4.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 6.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 5.0f, .h_value = 0.0f}  \
}
#define TEST_ARRAY_HEAP_NO_BUBBLE_DOWN { \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 1.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 4.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 6.0f, .h_value = 0.0f}, \
    (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 5.0f, .h_value = 0.0f}  \
}

void PrintTestProtocol(char* functionName) {
	printf("_______________ Test Protocoll: %s _______________ \n",functionName);
}

void PrintSucess(){
	printf("_______________ Test SUCCESS_______________\n");
	printf("\n");
	printf("\n");
}


void PrintNotImplemented(){
	printf("_______________ Test Not Implemented_______________\n");
	printf("\n");
	printf("\n");
}

/*________________________________________ Create unit tests__________________________________________*/

void TestCreateHeapArena() {
	PrintTestProtocol("TestCreateHeapArena");
	HeapArena* arena = CreateHeapArena(100);

	assert(arena ->currendNodeCount == 0);
	assert(arena -> maxNodes == 100);

	PrintSucess();
}

/*________________________________________ Insert unit tests__________________________________________*/

void AddFirstValueToHeapArena(PathNode insertValue) {
	PrintTestProtocol("AddFirstValueToHeapArena");

	HeapArena* arena = CreateHeapArena(100);

	int return_value = InsertHeapArena(arena,insertValue);

	assert(return_value == 1);
	assert(arena ->buffer[0].f_value == 3.0f);
	assert(arena ->currendNodeCount == 1);

	PrintSucess();
}

void AddOneMoreThanMax() {
	PrintTestProtocol("AddOneMoreThanMax");
	HeapArena* arena = CreateHeapArena(1);
	
	int return_value = InsertHeapArena(arena, (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 1.0f, .h_value = 0.0f});
	return_value = InsertHeapArena(arena, (PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 1.0f, .h_value = 0.0f});
	
	assert(return_value== -1);
	PrintSucess();
}

void AddValueCheckStructureNoBubbleUp(){// biggest number in whole heap
	PrintTestProtocol("AddValueCheckStructureNoBubbleUp");
	
	HeapArena* arena = CreateHeapArena(100);

	PathNode testValues [] = TEST_ARRAY_HEAP;
	for (int i = 0; i<14;i++) {
		InsertHeapArena(arena, testValues[i]);
	}

	InsertHeapArena(arena,(PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 48.0f, .h_value = 0.0f});

	assert(arena ->buffer[14].f_value == 48.0f); // because in current Heap Parent is 9 no bubble up

	PrintSucess();
}

void AddValueCheckStructureNoBubbleUp2(){// relativly small number but parent is s
	PrintTestProtocol("AddValueCheckStructureNoBubbleUp2");
	
	HeapArena* arena = CreateHeapArena(100);

	PathNode testValues [] = TEST_ARRAY_HEAP;
	for (int i = 0; i<14;i++) {
		InsertHeapArena(arena, testValues[i]);
	}

	InsertHeapArena(arena,(PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 14.0f, .h_value = 0.0f});	

	assert(arena ->buffer[14].f_value == 14.0f); // because in current Heap Parent is 9 no bubble up

	PrintSucess();
}

void AddValueCheckStructureNoBubbleUp3(){ // euqality
	PrintTestProtocol("AddValueCheckStructureNoBubbleUp3");
	
	HeapArena* arena = CreateHeapArena(100);

	PathNode testValues [] = TEST_ARRAY_HEAP;
	for (int i = 0; i<14;i++) {
		InsertHeapArena(arena, testValues[i]);
	}

	InsertHeapArena(arena,(PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 9.0f, .h_value = 0.0f});	

	assert(arena ->buffer[14].f_value == 9.0f); //equal no move

	PrintSucess();
}

void AddValueCheckStructureBubbleUp(){ // one swap
	PrintTestProtocol("AddValueCheckStructureBubbleUp");
	HeapArena* arena = CreateHeapArena(100);

	PathNode testValues [] = TEST_ARRAY_HEAP;
	for (int i = 0; i<14;i++) {
		InsertHeapArena(arena, testValues[i]);
	}

	InsertHeapArena(arena,(PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 8.0f, .h_value = 0.0f});

	assert(arena ->buffer[6].f_value == 8.0f); //swap
	assert(arena ->buffer[14].f_value == 9.0f); //swap

	PrintSucess();
}



void AddValueCheckStructureBubbleUp2(){ // swapp to the top
	PrintTestProtocol("AddValueCheckStructureBubbleUp");
	HeapArena* arena = CreateHeapArena(100);

	PathNode testValues [] = TEST_ARRAY_HEAP;
	for (int i = 0; i<14;i++) {
		InsertHeapArena(arena, testValues[i]);
	}

	InsertHeapArena(arena,(PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 0.0f, .h_value = 0.0f});

	assert(arena ->buffer[0].f_value == 0.0f); //swap to top 

	PrintSucess();
}

/*________________________________________ Pop unit tests__________________________________________*/

void PopFirstValueToHeapArenaOneElement(){
	PrintTestProtocol("PopFirstValueToHeapArenaOneElement");

	HeapArena* arena = CreateHeapArena(100);
	InsertHeapArena(arena,(PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 3.0f, .h_value = 0.0f});

	PathNode return_value = PopHeapArena(arena);

	assert(return_value.f_value == 3.0f);
	assert(arena ->currendNodeCount ==0);

	PrintSucess();
}

void PopNoElementExists(){
	PrintTestProtocol("PopNoElementExists()");
	HeapArena* arena = CreateHeapArena(100);

	PathNode return_value = PopHeapArena(arena);

	assert(return_value.cellIndex == -1);

	PrintSucess();
}


void PopValueCheckStructureBubbleDown() {
	PrintTestProtocol("PopValueCheckStructureBubbleDown");
	HeapArena* arena = CreateHeapArena(100);

	
	PathNode testValues [] = TEST_ARRAY_HEAP_BUBBLE_DOWN;
	for (int i = 0; i<4;i++) {
		InsertHeapArena(arena, testValues[i]);
	}

	PathNode return_value = PopHeapArena(arena);


	assert(return_value.f_value == 1.0f);

	assert(arena -> buffer[0].f_value == 4.0f);
	assert(arena -> buffer[1].f_value == 5.0f);
	assert(arena -> buffer[2].f_value == 6.0f);


	PrintSucess();
}

int main(int argc, char **argv) {
	TestCreateHeapArena();
	AddFirstValueToHeapArena((PathNode){.cellIndex = 0, .g_value = 0.0f, .f_value = 3.0f, .h_value = 0.0f});
	AddOneMoreThanMax();
	AddValueCheckStructureNoBubbleUp();
	AddValueCheckStructureNoBubbleUp2();
	AddValueCheckStructureNoBubbleUp3();
	AddValueCheckStructureBubbleUp();
	AddValueCheckStructureBubbleUp2();
	PopFirstValueToHeapArenaOneElement();
	PopNoElementExists();
	PopValueCheckStructureBubbleDown();
}