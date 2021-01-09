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

### Windows

Mac/Linux are programmer friendly. So, now, Windows.

```
Visual Studio is pretty much required here.
(the plan is to switch between the gui and command line; recommendation is to learn cmd line though)
[personal note:  I wonder if he would mind if I just ignored the Windows part of this?]

Also, for editing, he recommends that people use Visual Studio Code, no matter which OS. Note that this
is not the same as Visual Studio.  [I don't agree, vscode configuration is worse than MAVEN to setup IMHO]

```

## Folder Structure of our System
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

### files included with course

```
A large number of assets are provided with the course.
The lua and glm files are included. (I am not familair with glm, but I see some vector/matrix stuff in there)
A Makefile ( a simple one) is provided.

When learning this course, you probably want to start with the professors zip file and expand on it.
```

## pausing to create a git repo now...

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
we needed to use the ubuntu -llua5.3 
other than that,

make # works
make run # works
make clean # works
```

## setting up on Windows Visual Studio.

```
I am not sure I want to bother with this?

Start with installing Visual Studio.
(I already use 17 for unity and what not, so done.)

... Not sure what to say here. It took a long time to add all the header files and library files, but its
a fairly straight ofrward process - project - properties etc etc. There are some nice things about using a IDE, 
like debugging and such, so maybe we will revisit later....
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

To use omni completion, type <C-X><C-O> while open in Insert mode. If matching names are found, a pop-up menu opens which can be navigated using the <C-N> and <C-P> keys. 

```

## Fixing the timestep

```
need to set the "speed" of the frame displays.
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
we used a while loop. but, maybe, this isnt great.
in the real world, a while loop is a processor instruction. So it locks the core.
(you may have noticed that it had a hard time catching your esc key? yah? yah.)
The while loop will use up 100% of the CPU core. So yah, this is bad.

Use a "proper" delay function.

SDL_Delay(Uint32 ms);  

so obviously, this uses a sleep, and a releases the CPU. (The CPU will wake us up.)

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

[comment: he has a entity manager, and owner pointer? interesting. and redundant, I think.]

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

[sigh, he creates a position vector, but not a one for width and height? ok doke.]

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

````


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

First, need t give credit, asset for tiles copied from:
https://github.com/carlbirch/BirchEngine/blob/master/BirchEngine/assets/terrain_ss.png
Also borrowed the map file. 

Next,

Recall .map and .png files. (so jungle.png and jungle.map)

So we need to read the csv file. And then load the vector of tiles based on this.
So, the png is a "texture"
Also, we have a camera, which tracks what part of the map should move. 

