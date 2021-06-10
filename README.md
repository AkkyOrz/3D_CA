# 3D_CA  (3D cell automaton)

This is an extension of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life), which is a type of cellular automaton.
We made it look good by implementing something different from traditional life games, such as expanding into 3D space, changing the number of states, and adding the concept of lifespan.
In addition, you can edit cells and change the cell update speed by keyboard input.

Sample movie is [here](https://www.youtube.com/playlist?list=PL0oc7AkB1TQK4kQ9fDaY6qSUhQsMoNwQf)

![movie](./Sample_movie/4-6-7-12-13.gif)

install OpenGL
```
$ sudo apt-get install libglu1-mesa-dev mesa-common-dev freeglut3-dev
```

install OpenMP
```
$ sudo apt install libomp-dev
```

install OpenCL
```
$ sudo apt install clinfo
$ sudo apt install ocl-icd-libopencl1
$ sudo apt install opencl-headers
$ sudo apt install ocl-icd-opencl-dev
```

## Compile
Normal mode
```
$ make
$ ./3D_LifeGame
```
Use OpenMP
```
$ make ACC=mp
$ ./3D_LifeGame
```
Use OpenCL
```
$ make ACC=cl
$ ./3D_LifeGame
```

How to manupulate follows the top left of the motion screen.

### Normal mode
|Input key | action |
| :--: | :--:|
|v | Shifting to automatic movement mode/returning to normal mode|
|s | stop/resume|
|r | Initialization of the sell status|
|f | Faster|
|d | Slower|
|l | Camera position reset |
|c | Changing the state at cell initialization |
|n | Color change |
|e | Edit mode |
|q | Quit |

### Edit mode

|Input key| action |
| :--: | :--:|
|i/o |z-axis move|
|up down left right array | x,y-axis 2D move|
|p| change sell state|

# License
The code is licensed under the MIT license.
