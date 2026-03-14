#include "grid.h"
#include "dataStruct/priorityQueue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void PrintTestProtocol(const char* functionName) {
    printf("_______________ Test Protocol: %s _______________\n", functionName);
}

void PrintSucess() {
    printf("_______________ Test SUCCESS _______________\n\n");
}

// Helper to find a node by cell index in the closed list (HeapArena)
PathNode* FindNodeInClosedList(HeapArena* closedList, int cellIndex) {
    if (!closedList) return NULL;
    for (int i = 0; i < closedList->currendNodeCount; i++) {
        if (closedList->buffer[i].cellIndex == cellIndex) {
            return &closedList->buffer[i];
        }
    }
    return NULL;
}

// Helper to free grid resources
void FreeGrid(Grid* grid) {
    if (grid) {
        if (grid->cells) free(grid->cells);
        free(grid);
    }
}

// Helper to free HeapArena (since no library function exists)
void FreeHeapArenaLocal(HeapArena* heap) {
    if (heap) {
        if (heap->buffer) free(heap->buffer);
        free(heap);
    }
}

/*________________________________________ Unit Tests __________________________________________*/

void TestAStarAlgorithmSimplePath() {
    PrintTestProtocol("TestAStarAlgorithmSimplePath");

    // Create a 3x3 grid (300x300, 100x100 cells)
    // 0 1 2
    // 3 4 5
    // 6 7 8
    Grid* grid = InitNavigationGrid(300, 300, 100, 100, false);
    assert(grid != NULL);
    assert(grid->cellsLenght == 9);

    int startIndex = 0; // Top-left
    int targetIndex = 8; // Bottom-right

    // Run A* Algorithm
    HeapArena* closedList = AStarAlgorithm(grid, startIndex, targetIndex);
    assert(closedList != NULL);

    // 1. Verify target is in the closed list
    PathNode* targetNode = FindNodeInClosedList(closedList, targetIndex);
    assert(targetNode != NULL);
    assert(targetNode->cellIndex == targetIndex);

    // 2. Verify path can be reconstructed back to start using parentIndex
    int current = targetIndex;
    int nodesInPath = 0;
    int safetyCounter = 0;
    while (current != startIndex && safetyCounter < 100) {
        PathNode* node = FindNodeInClosedList(closedList, current);
        assert(node != NULL);
        current = node->parentIndex;
        nodesInPath++;
        safetyCounter++;
    }
    assert(current == startIndex);
    
    // Minimal nodes in path (including start) for 0 to 8 is 5 nodes: 0, 1, 2, 5, 8 (or similar)
    assert(nodesInPath + 1 >= 5);

    // 3. Verify closed list size is reasonable (at least 5 nodes visited)
    assert(closedList->currendNodeCount >= 5);

    FreeHeapArenaLocal(closedList);
    FreeGrid(grid);
    PrintSucess();
}

void TestAStarAlgorithmShortPath() {
    PrintTestProtocol("TestAStarAlgorithmShortPath");

    // 2x1 grid
    Grid* grid = InitNavigationGrid(200, 100, 100, 100, false);
    assert(grid->cellsLenght == 2);

    int startIndex = 0;
    int targetIndex = 1;

    HeapArena* closedList = AStarAlgorithm(grid, startIndex, targetIndex);
    assert(closedList != NULL);

    PathNode* targetNode = FindNodeInClosedList(closedList, targetIndex);
    assert(targetNode != NULL);
    assert(targetNode->parentIndex == startIndex);

    FreeHeapArenaLocal(closedList);
    FreeGrid(grid);
    PrintSucess();
}

void TestAStarAlgorithmSameStartEnd() {
    PrintTestProtocol("TestAStarAlgorithmSameStartEnd");

    Grid* grid = InitNavigationGrid(100, 100, 100, 100, false);
    int startIndex = 0;
    int targetIndex = 0;

    HeapArena* closedList = AStarAlgorithm(grid, startIndex, targetIndex);
    assert(closedList != NULL);
    
    PathNode* targetNode = FindNodeInClosedList(closedList, targetIndex);
    assert(targetNode != NULL);
    assert(targetNode->cellIndex == startIndex);

    FreeHeapArenaLocal(closedList);
    FreeGrid(grid);
    PrintSucess();
}

int main(int argc, char **argv) {
    TestAStarAlgorithmSimplePath();
    TestAStarAlgorithmShortPath();
    TestAStarAlgorithmSameStartEnd();
    return 0;
}
