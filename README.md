# Notes on the Fundamentals of 2D Game Engines with C++ SDL and Lua

## Why are we taking this course

```
link: https://www.udemy.com/course/cpp-2d-game-engine/learn/lecture/14431096#overview

This course is about core concepts.
```

## What are building?

```
this is a project course - we are working up to and creating a game.
LUA will be used to manipulate the game.
The core of the game will be in C++, but the "game" will be in C++.
```

## A 2D game engine from scratch.

```
Typically, people use tool sets to build game but fail to understand the basics.
We will cover the basics.

The tools we will use will be C++, SDL and LUA.

We will develop an Entity-Component System.

Lua scripting to configure our levels.
```


## Project and Folder structure

```
Libraries

C++-->  SDL (simple direct layer)
SDL covers video and sound
SDL works on Linux, MacOSX , Windows, Android, etc.

```

### Linux Dependencies

```
minimally. Need to install:

$ sudo apt-get install libsdl2-dev         # base
$ sudo apt-get install libsdl2-image-dev   # images
$ sudo apt-get install libsdl2-ttf-dev     # fonts
$ sudo apt-get install libsdl2-mixer-dev   # sounds
$ sudo apt-get install lua5.3              # lua
$ sudo apt-get install liblua5.3-dev       # lua dev (for Ubuntu)
```

### Mac OSX

```
$ brew install sdl2
$ brew install sdl2_image
$ brew install sdl2_ttf
$ brew install sdl2_mixer
$ brew install lua

also, in the Makefile you will use -llua  
```
(I added a Makefile.mac for this.  To use this, simply `make -f Makefile.mac`)



### Windows

Mac/Linux are programmer friendly. So, now, Windows.

```
Visual Studio is pretty much required here.
@todo: Add Windows notes here.

```

## (Initial) Folder Structure 
```
.
└── 2dgamesengine
    ├── Makefile
    ├── assets
    │   ├── fonts
    │   ├── images
    │   ├── sounds
    │   └── tilemaps
    ├── lib
    │   ├── lua 
    │   └── glm 
    └── src
        ├── Constants.h
        ├── Game.cpp
        ├── Game.h
        └── Main.cpp

```

### Files included with course

```
A large number of assets are provided with the course.
The lua and glm files are included. 
A Makefile ( a simple one) is provided.
Assets (images, sounds, fonts) are provided.

When learning this course, start with the professors zip file and expand on it.
```

## Create a git repo 

``` 
we have a starting point for the project at this point, so I will create the initial git repo
First, create it locally
From the top folder:

$ vi .gitignore     # create a simple ignore for C++
$ git init
$ git add --all
$ git commit -m "First commit"

Next, head over to your favorite repo and setup. 
Once its created, you should set the upstream and push.
In my case:

git remote add origin git@github.com:steve1281/cppluasdl_udemy.git
git branch -M main
git push -u origin main

```

### Discussion of tilemaps

```
tilemap is a matrix of images that are all the same size, and are numbered.

We have a file .png

  +---+---+---+---+
  | 0 | 2 | 3 | 4 |  
  +---+---+---+---+
  | 5 | 6 | 7 | 8 |  
  +---+---+---+---+

Then, when we want to create the game map (the images to be displayed) we can indicate in out "map" file:

  2,2,3,4,4
  1,2,2,2,1
  1,2,2,3,1

etc

We read the map file, load the image in the png tiles, and display.

```

## Work on the make file

```
I (primariliy) work in ubuntu neeed to use the ubuntu -llua5.3 
other than that,

make # works
make run # works
make clean # works
```

## setting up on Windows Visual Studio.

```

Start with installing Visual Studio.
(I already use 17 for unity and what not, so done.)

Not sure what to say here. It took a long time to add all the header 
files and library files, but it is a fairly straight forward process - project - properties etc. 
There are some nice things about using a IDE, like debugging and such, 
so maybe we will revisit later.

@todo: clean up notes for Windows installation.

```

## The Game Loop

```
What is it?

  +-> process -> update -> render -> +
  |                                  |
  +----------------------------------+

Frame by frame update.
Process any inputs.  Update the game state.  Render the game state.

while(true) {
  game->processInput();
  game->update();
  game->render();
}

```

### Some vim notes

```
tabe <filename>
gt
```

also:

```
set omnifunc=syntaxcomplete#Complete

and

To use omni completion, type <C-X><C-O> while open in Insert mode. 
If matching names are found, a pop-up menu opens which can be navigated 
using the <C-N> and <C-P> keys. 

@todo: This doesn't work on my ubuntu; re-visit.

```

## Fixing the timestep

```
Need to set the "speed" of the frame displays.
By default, a while (true) ... loop will go as fast as the CPU can handle it.
So, it will vary based on the CPU.

Need to think "how many pixels per delta time"
So:

float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

note that stuff comes in milliseconds, so divide by 1000 to be seconds.

deltatime is the amount elapsed since the last frame
we can now think in pixels per second

so:

projectile.position.x += 20 * deltaTime; 

will vary based on the time.

So, the object might "jump", but it will always end up where its supposed to be.
Framerate is no longer important.

```

### SDL_Delay

```
Initially, we used a while loop. This locks the porcessor - not great.
in the real world, a while loop is a processor instruction. So it locks the core.

The while loop will use up 100% of the CPU core. So yah, this is bad.

Use a "proper" delay function.

SDL_Delay(Uint32 ms);  

(probably) This uses a sleep, and a releases the CPU. (The CPU will wake us up.)

```

## Double Buffering

```
Discussion about double buffer.
- color buffer
- back buffer
- front buffer

swap buffers, prevents flickering and artifcats

1. clear the back buffer
2. draw all the game objects
3. swap front and back buffers

SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
...
SDL_RenderClear(renderer);
... // draw all game objects on back buffer
SDL_RenderPresent(renderer);

```

## Entity-Component

```
Data driven ? The game is a collection of data ... and based on this data, the engine does stuff.

Division of responsibilities.

Organizing game objects:
Scene
  - things (the all live in the scene)

Inheritance approach - they are objects. 
Thing 
   Player
   Enemy
   Obstacle
   Light

But, in our case, instructor doesn't like this approach in this case.
(his arguement pivots on "programmers suck, lets not do this" oh well)

Instead, think in terms of "Game Objects"
so a meta objects that as a series of data items
"Entity-Componment"


Entity(Player)
Entity(Enemy)
Entity(DoorTrigger)

Entity will have , for example, a TransformCompotent that we can add. Or a ColliderCompenent.
A different Entity, might had a TransformComponent, and a SpriteComponent.

If this sound like unity, I doubt thats an accident.

So classes:

Entity:
   List<Components>
      Update()
      Render()

Component
   Transform Component
   Sprite Component
   Collider Component
   ParticleEmitter Component

So, for example

class Entity {
    vector<Component*> components;
    AddComponent<T>(compnent(;
    Update();
    Render();
}

Need an EntityManager

class EntityManager {
    vector<Entity*> entities;

    AddEntity(entity);
    GetEntity(string entityName);
    Update();
    Render();
}

Need a parent class Component

class Compnent {
    Entity* owner;
    virtual Update();
    virtual Render();
}


So, we could create a child of the component like this:

class TransformComponent: public Component {
    glm::vec2 position;
    int width;
    int height;
    float scale;

    Update() override {
    ...
    }
    Renderer() override {
    ...
    }
}

And another:

class ColliderComponent : public Component {
    SDL_Rect collider;
    Update() override {
    ...
    }
    Renderer() override {
    ...
    }
}

So, the game loop changes.

Game holds the Entity manager.
  EntityManager holds a list of entities
  for each entity, update and render
    Entity have a list of components
    each components, Update and Render

[chain of responsibility]

```


## C++ Generics some notes

```
auto& newEntity(manager.AddEntity("Player"));

newEntity.AddComponent<TransformComponent>(10,10,40,40,40,40,1);
newEntity.AddComponent<SpriteComponent>("tank-image.png");

```
So, just not that between `<` and `>` is a type with a defined `template`.

Lets look at a template:

```
template <typename T, typename... TArgs>
T& AddComponent(TArgs&&... args) {
    T* component(new T(std::forward<TArgs>(args)...));
    component->entity = this;
    components.emplace_back(component);
    component->Initialize();
    return *component;
}
```

Notes:
```
T : is the type of the component
TArgs : are the types of the arguments 
```



## About Sprites

Recall a folder called assets/images.


In his game:

* sprite has a transparent background
* 32x32 pixels 
* pointer to asset manager
* has file map 

Animated sprites:

* one png file, transparent background
* but, broken into cells of equal size 2x4
* so you can cut 32x32 images
* SDL has utility for this.
* he has arranged so that top down is a change in direction
* so pressing an arrow key, change sprite down to the corrasponding cell.
* first column to second column basically moved the blades - so standing still animation

OK, back to code. :-)

```

## Maps and Tiles

```
First, need t give credit, asset for tiles copied from:
https://github.com/carlbirch/BirchEngine/blob/master/BirchEngine/assets/terrain_ss.png
Also borrowed the map file. 

Next:

Recall .map and .png files. (so jungle.png and jungle.map)

So we need to read the csv file. And then load the vector of tiles based on this.
So, the png is a "texture"
Also, we have a camera, which tracks what part of the map should move. 
```

## Issues with component-design

```
Issues with complexity; specifically the CheckCollisions.

```
For example, given entities A B C D E, we currently check:
  A - ( A B C D E)
  B - ( A B C D E)
  C - ( A B C D E)
  D - ( A B C D E)
  E - ( A B C D E)

(a if is used to check if its the not the same, but no other optimization)

First thoughts; you could check only once (like a bubble sort):
  A - (B C D E)
  B - (C D E)
  C - (D E)
  D - (E)

The issue is, we still are comparing, every single frame, all the components.
This is due the use of component based designed.

```

# General discussion of Entity Component System Design (ECS)

```
In modern systems, we don't use the component design we used.  (due to the complexity)

So, what is ECS, how does it work with data?

Our implementation, we use Entity-Component. 
An entity has a list of components inside of it. A container for components.
Components have data and logic.
With this approach, we need to loop all the entities, for things like collisions.
This is an OOP approach, so it leans for people to be able think about it. But performance...?

Professor... is trying to say OOP design is slower. I don't actually agree with this, but its his course.

Entity-Component-System

Engines like Unity use a ECS 
What is the difference?

Pure data oriented ECS.  Entities are nothing more than an ID (a number).
The represent objects.

Components are just data.

So Transform would like :

  struct TransformComponent {
      glm:vec2 position;
      glm:vec2 scale;
      double rotation;
  }

They are organized into a contigous lists to optimize access. 

Systems are the logic (code) that the game runs.
You could have a MovementSystem which updates the positions of all moving entities by their velocity frame by frame.
The movement system ONLY loops the entities that entities that have a "specific" type of component (Tranform)

Better example, CollisionSystem.  Checks the collisions of entities that have a collider component frame by frame.
(so no if to check if it has a collsion. somehow.)

Example:

// Entities: Just an ID
// Components: Plain data (no logic)
// Systems: Perform logic on components and entities

class Entity {
    int id;
}

struct TransformComponent {
    glm::vec2 position;
    glm::vec2 scale;
    double rotation;
};

struct VelocityComponent {
    glm::vec2 velocity;
};

class MovementSystem {
    public:
        MovementSystem() {
            RequireComponent<TransformComponent>();
            RequireComponent<VelocityComponent>();
        }
        void Update(double deltaTime) {
            for (auto entity: GetEntities()) {
                VelocityComponent& velocity = entity.GetComponent<VelocityComponent>();
                TranformComponent& transform = entity.GetComponent<TransformComponent>();
                transform.position.x += rigidbody.velocity.x * deltaTime;
                transform.position.y += rigidbody.velocity.y * deltaTime;
            }
        }
};



No exactly sure where he is going with this.

I suppose, given entity list like [ 0, 1, 2, 3, 4 , ..., 10000 ]
You could create seperate lists.

EntityWithTransform = [2 , 3]
EntityWithCollision = [1, 2, 3, 12]
etc.

So instead of hanging the property onto a complex thing like an attribute, you would create a
list of entites that have this attribute. 

(which is what I did to optimize the original collisions problem; create a list of those entities that
have this attribute of collisions.  Except in my solution, there was a huge redundancy.  Using the ECS 
approach removes that redundancy.)

Back to his examples.

So, using ECS, we can create a much better collision solution:

class Entity {
    int id;
}

struct ColliderComponent {
    SDL_Rect collider;
};

class CollisionSystem {
    public:
        CollisionSystem() {
            RequireComponent<ColliderComponent>();
        }
        void Update(double deltaTime) {
            //Loop
            for (auto entity: GetEntities()) {
                ColliderComponent& collider = entity.GetComponent<ColliderComponent>();
                   // collider logic ...
                   // ....
            }
        }
};


The key here is, _we know_ what the things have a collider up front. WE DO NOT IF to find them. 
Much faster.

At this point, we will continue with our approach.  Professor just want to point out that ECS is better.

Warning about the quiz that follows this.  The second question : One of the benefits is using data-oriented design is to improve performance by avoiding cache misses.

This is presumes that the we accept the collection of entities is someone cached someplace?  I think what he is trying get out of this question is "We only ever look at exactly what we need." So in effect, we are preloading the cache with a list of entities that match our criteria. (or in fact, maintaining seperate lists.) So, not a cache miss per se. 

```



        
## Text

```
Going to use Asset manager to add list of fonts(TTL_Font)s


```

## Projectile Emitter System

```


```
## Discussion of EVENT SYSTEMS

```
Used to decouple game loop from the things like the collisions.
The idea of "listening for events".
The listener isn't aware of who is emitting the event (well thats what he said? )
The entity emitting the even doesn't know who is listening to it. 

You don't necessarily need an event system (we are not implementing one in this course).
However, there are some circumstances when you may want to.

Commonly used for:
- key pressed
- collision happens
- player health reaches say 10%,
- mouse is clicked
- etc

Modern game systems typically use even system. You subscribe to event. Events are published.
```

## Adding and using LUA
```
The idea is to use a scripting langauge to modifying the "data" that drives the game.

You could use XML/json etc, but LUA is a a real programming language so we can get more uses from it.

LUA is pretty simple langauge.

Example:

    screen_width = 800
    screen_height = 600

    point = {
        x = 5.0,
        y = 0.0
    }

    function fullscreen_width(w, r)
        local w = 0
        if r == 1 then
            w = 14400
        end
        return w
    end

    function fullscreen_height(h, r)
        local h = 0
        if r ==1 then
            h = 900
        end
        return h
    end

The key advatage is that this is interpreted; it can be changed on the fly without recompilation.

Note the professer had us add this in early on, including sol.hpp:

  lib/lua
  ├── lauxlib.h
  ├── luaconf.h
  ├── lua.h
  ├── lua.hpp
  ├── lualib.h
  └── sol.hpp

Interpreting LUA (snippit code):

  extern "C" {
      #include "../lib/lua/lua.h"
      #include "../lib/lua/luaxlib.h"
      #include "../lib/lua/lualib.h" 
  }

  int main() {
        lua_State *L = luaL_state();
        std::string luaCommand = "ball_pos = 5 + 2"; 

        int res = luaL_dostring(L, luaCommand.c_str());

        if (res == LUA_OK) {
            lua_getglobal(L, "ball_pos");
            if (lua_isnumber(L, -1)) {
                float ball_pos_in_cpp = (float) lua_tonumber(L, -1); // 7.0
            }
        } else {
            std::string errorMsg = lua_tostring(L, -1);
            std::cout << errorMsg << std::endl;
        }
        return 0;
  }


This is pretty simple example, but you can read in a file, and that file is a full program.
This allows us to move a lot logic to an interpretted langauge, while keeping the stuff that
needs to be "fast" in the C++ code.

Discussion of LUA Stack:
LUA lets us refer via negative indices, so -1 lets us get the top of stack"

   |___| 4  | -1
   |___| 3  | -2
   |___| 2  | -3
   |___| 1  | -4
   |___| 0  | -5
 
The "sol2" library/framework simplifies this, example:

  #include "./lib/lua/sol.hpp"
  
  int main(int argc,  char *argv[]) {
        sol::state lua;
        lua.open_libraries(sol::lib::base, sol::lib::string); // variable list of libs
        lua.script("print('Hello world using LUA & Sol!')"); // or a filename 
        return 0;
  }

(note: lua --> moon, sol --> moon in Portuguese)

This is less verbose, and hides some of the complexity nicely.

More interesting example:

  -- ./assets/scripts/config.lua:
  config = {
    fullscreen  = false
    resolution = { x = 1024, y = 768 }
  }

  // main.cpp
  #include "./lib/lua/sol.hpp"
  
  int main() {
        sol::state lua;
        lua.script_file("./assets/scripts/config.lua");
        bool isFullScreen = lua["config"]["fullscreen"];
        sol::table config = lua["config"]
        int resolutionX = config["resolution"]["x"];
        int resolutionY = config["resolution"]["y"];

        if (isFullScreen) {
            std::cout << "It is full screen..." << std:endl;
        }
        return 0;
  }

Note. LUA script as created a table. Within the table, is also a table. 
Access is like a dictionary. (very python-like imho)
Note, sol is doing the casts for us, which is kinda neat.

```




## Replace C++ load level logic with LUA
```
Some notes on vim.

Professor uses "vsplit <filename>" to split the screen, which is cool. (alternatively, "vsp")
You can horizontal split with just "sp".
You can move using ctrl-w <direction> where direction is j,k,h,l.
There are number of other things, resizing and such. ctrl-w - and +
And you can close an active window with "ctrl-w q"

Also ctrl-w ctrl-w to switch between windows.

Also, if you go the vertical approach, recall you can turn wrap off with ":set nowrap"

```
