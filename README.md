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





