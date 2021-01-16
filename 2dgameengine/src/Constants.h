#ifndef CONSTANTS_H
#define CONSTANTS_H

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT= 600;

const unsigned int FPS = 60; 
const unsigned int FRAME_TARGET_TIME = 1000/FPS;

enum CollisionType {
    NO_COLLISION,
    PLAYER_ENEMY_COLLISION,
    PLAYER_PROJECTILE_COLLISION,
    ENEMY_PROJECTILE_COLLISION,
    PLAYER_VEGETATION_COLLIDER,
    PLAYER_LEVEL_COMPLETE_COLLISION
};

enum LayerType {
    TILEMAP_LAYER = 0,
    VEGETATION_LAYER = 1,
    ENEMY_LAYER =2,
    OBSTACLE_LAYER = 3,
    PLAYER_LAYER = 4,
    PROJECTILE_LAYER =5,
    UI_LAYER = 6
};

const unsigned int NUM_LAYERS =7;

#endif
