# ifndef COLLISION_H
# define COLLISION_H
# include <SDL2/SDL.h>

class Collision {
    private:
    public:
        // AABB
        static bool CheckRectangleCollision(const SDL_Rect& rectangleA, const SDL_Rect& rectangleB); 

};

#endif
