# WorldIMaker

3D field and scene viewer editor. School project for IMAC.
This is a project mixed with C++, OpenGL 3.3 and SDL2.

## Table of Contents

+ [Getting started](#Getting-started)
+ [Build project](#Build-project)
+ [Run project](#Run-project)
+ [Guide of the editor](#Guide-of-the-editor)


## Getting started :

### Librairies :

#### On Linux :

CMAKE : 

```bash
sudo apt-get install g++ cmake
```

SDL2 : 
```bash
sudo apt-get install libsdl2-dev
```

OpenGL : 

```bash
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

GLEW :

```bash
sudo apt-get install glew
```

DOXYGEN : 

```bash
sudo apt install graphviz doxygen
```


## Build project

There are mainly 2 ways of handling the CMake :

### Option 1

Go to the folder of this project and :

```bash
mkdir build
cd build
cmake ..
make
```

### Option 2 : Visual Studio Code

Use the `CMakeTools` plugin, build with `f7`.

## Run project : 

Depending on the solution chosen on the build, you'll either have to run the exe with your terminal or with VSCode.

### Option 1

Make sure you're still in your build folder and :
```bash
./bin/worldIMaker
```

### Option 2

Build with `f5`

## Guide of the editor