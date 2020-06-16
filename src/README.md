# Overview
I chose Option 2 and added a new feature to the game.

The food has three types: Orange, Red and Green:
- If the snake eats the orange food, it behaves as before: moves faster and gets one point
- If the sname eats the red food, it moves faster and gets two points
- If the snake eats the green food, it gets one point but doesn't move faster

# Rubric Satisfied
- The project demonstrates an understanding of C++ functions and control structures (game.cpp 58-77, 115-129)
- The project uses Object Oriented Programming techniques (food.h)
- Classes use appropriate access specifiers for class members (food.h 7)
- Class constructors utilize member initialization lists (food.h 8-9)
- The project makes use of references in function declarations (game.cpp 79; renderer.cpp 41)

# Basic Build Instructions
1. Clone this repo
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`

# Code Structure
I added `food` class to the original code, which encapsulates all attributes of food.