#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include "raylib.h"
#include "collision/collision.h"
#include <gameObject/gameObject.h>





void currentTime(char* occasionName);
void DrawAnimationsInList(GameObject* toAnimateArry [], int toAnimationSize);
void UpdateAnimationRectangle(GameObject* gameObject);




#endif
