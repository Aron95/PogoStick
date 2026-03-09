#include "gameObjectDefinitions.h"
#include "enums/enum.h"
#include <string.h>


const GameObjectDefinition PLAYER_DEF = {
    .name = "Hero",
    .spritePath ="resource/PogoStick.png",
    .spriteSheetLength=20,
    .orientation = RIGHT_ORIENTATION,
    .gameObjectType = PLAYER_TYPE,
    .animationDescription = &((Animations){
        .leftAnimation   = {-1, 0, 9, 1},
        .rightAnimation  = {1, 0, 9, 1},
        .bottomAnimations = {1, 11, 20, 11},
        .topAnimations    = {1, 11, 20, 11},
        .deathAnimations  = {0, 0, 0, 0},
        .attackAnimations = {0, 0, 0, 0}}),
    .collisonBoxConfig= {
             42,
             58,
             12,
             32

    },  
    .attackSoundPath = "resource/music/meele attack.wav",
    .shootSoundPath = "resource/music/shoot.wav",
};



const GameObjectDefinition KRUG_DEF = {
    .name = "Krug",
    .spritePath ="resource/Krug.png",
    .spriteSheetLength=1,
    .orientation = RIGHT_ORIENTATION,
    .gameObjectType = ITEM_TYPE,
    .animationDescription = &((Animations){
        .leftAnimation   = {0, 0, 0, 0},
        .rightAnimation  = {0, 0, 0, 0},
        .bottomAnimations = {0, 0, 0, 0},
        .topAnimations    = {0, 0, 0, 0},
        .deathAnimations  = {0, 0, 0, 0},
        .attackAnimations = {0, 0, 0, 0}}),
    .collisonBoxConfig = {0,0,0,0} // means not configured
};