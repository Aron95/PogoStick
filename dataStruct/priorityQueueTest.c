#include "priorityQueue.h"
#include <assert.h>
#include <stdio.h>

#define TEST_ARRAY_HEAP {1,2,3,5,6,8,9,10,13,32,43,45,46,47}
#define TEST_ARRAY_HEAP_BUBBLE_DOWN {1,4,6,5}
#define TEST_ARRAY_HEAP_NO_BUBBLE_DOWN {1,4,6,5}

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

void AddFirstValueToHeapArena(int insertValue) {
	PrintTestProtocol("AddFirstValueToHeapArena");

	HeapArena* arena = CreateHeapArena(100);

	int return_value = InsertHeapArena(arena,insertValue);

	assert(return_value == 1);
	assert(arena ->buffer[0] == 3);
	assert(arena ->currendNodeCount == 1);

	PrintSucess();
}

void AddOneMoreThanMax() {
	PrintTestProtocol("AddOneMoreThanMax");
	HeapArena* arena = CreateHeapArena(1);
	
	int return_value = InsertHeapArena(arena, 1);
	return_value = InsertHeapArena(arena, 1);
	
	assert(return_value== -1);
	PrintSucess();
}

void AddValueCheckStructureNoBubbleUp(){// biggest number in whole heap
	PrintTestProtocol("AddValueCheckStructureNoBubbleUp");
	
	HeapArena* arena = CreateHeapArena(100);

	int testValues [] = TEST_ARRAY_HEAP;
	for (int i = 0; i<14;i++) {
		InsertHeapArena(arena, testValues[i]);
	}

	InsertHeapArena(arena,48);

	assert(arena ->buffer[14] == 48); // because in current Heap Parent is 9 no bubble up

	PrintSucess();
}

void AddValueCheckStructureNoBubbleUp2(){// relativly small number but parent is s
	PrintTestProtocol("AddValueCheckStructureNoBubbleUp2");
	
	HeapArena* arena = CreateHeapArena(100);

	int testValues [] = TEST_ARRAY_HEAP;
	for (int i = 0; i<14;i++) {
		InsertHeapArena(arena, testValues[i]);
	}

	InsertHeapArena(arena,14);	

	assert(arena ->buffer[14] == 14); // because in current Heap Parent is 9 no bubble up

	PrintSucess();
}

void AddValueCheckStructureNoBubbleUp3(){ // euqality
	PrintTestProtocol("AddValueCheckStructureNoBubbleUp3");
	
	HeapArena* arena = CreateHeapArena(100);

	int testValues [] = TEST_ARRAY_HEAP;
	for (int i = 0; i<14;i++) {
		InsertHeapArena(arena, testValues[i]);
	}

	InsertHeapArena(arena,9);	

	assert(arena ->buffer[14] == 9); //equal no move

	PrintSucess();
}

void AddValueCheckStructureBubbleUp(){ // one swap
	PrintTestProtocol("AddValueCheckStructureBubbleUp");
	HeapArena* arena = CreateHeapArena(100);

	int testValues [] = TEST_ARRAY_HEAP;
	for (int i = 0; i<14;i++) {
		InsertHeapArena(arena, testValues[i]);
	}

	InsertHeapArena(arena,8);

	assert(arena ->buffer[6] == 8); //swap
	assert(arena ->buffer[14] == 9); //swap

	PrintSucess();
}



void AddValueCheckStructureBubbleUp2(){ // swapp to the top
	PrintTestProtocol("AddValueCheckStructureBubbleUp");
	HeapArena* arena = CreateHeapArena(100);

	int testValues [] = TEST_ARRAY_HEAP;
	for (int i = 0; i<14;i++) {
		InsertHeapArena(arena, testValues[i]);
	}

	InsertHeapArena(arena,0);

	assert(arena ->buffer[0] == 0); //swap to top 

	PrintSucess();
}

/*________________________________________ Pop unit tests__________________________________________*/

void PopFirstValueToHeapArenaOneElement(){
	PrintTestProtocol("PopFirstValueToHeapArenaOneElement");

	HeapArena* arena = CreateHeapArena(100);
	InsertHeapArena(arena,3);

	int return_value = PopHeapArena(arena);

	assert(return_value = 3);
	assert(arena ->currendNodeCount ==0);

	PrintSucess();
}

void PopNoElementExists(){
	PrintTestProtocol("PopNoElementExists()");
	HeapArena* arena = CreateHeapArena(100);

	int return_value = PopHeapArena(arena);

	assert(return_value = -1);

	PrintSucess();
}


void PopValueCheckStructureBubbleDown() {
	PrintTestProtocol("PopValueCheckStructureBubbleDown");
	HeapArena* arena = CreateHeapArena(100);

	
	int testValues [] = TEST_ARRAY_HEAP_BUBBLE_DOWN;
	for (int i = 0; i<4;i++) {
		InsertHeapArena(arena, testValues[i]);
	}

	int return_value = PopHeapArena(arena);


	assert(return_value== 1);

	assert(arena -> buffer[0] == 4);
	assert(arena -> buffer[1] == 5);
	assert(arena -> buffer[2] == 6);


	PrintSucess();
}

int main(int argc, char **argv) {
	TestCreateHeapArena();
	AddFirstValueToHeapArena(3);
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