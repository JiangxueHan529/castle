# Castle
<img src='https://github.com/JiangxueHan529/castle/blob/main/images/testing29.png'>

## Table of Contents
1. [Features](#Features)
2. [Algorithms](#Algorithms)
3. [Instructions](#Instructions)
4. [Results](#Results)

## Features
* procedurally generate the castle using grammar rules, with various types of patterns
* user can input each unit's size and the number of units, along with size of the canvas
* user can also choose what color pattern is preferred from monochromatic, colorful and complementary
* I added methods to draw semi-circle and fill in circles, which were not done in assignment 2


## Algorithms
### Grammar Rules
* T(N) -> Base(N)
* T(N) -> Base(N) top
* T(N) -> Base(N) top-C
* T(N) -> Base(N) semi-sphere
* Base(N) -> $\epsilon$ *N
* Base(N) -> T(N/2) T(N/2) T(N/2) T(N/2)
* Base(1) -> block
* Base(1) -> block-C
* Base(1) -> block-T \
Image: <img src ='https://github.com/JiangxueHan529/castle/blob/main/images/elements.jpg' width = '500' height = '500'>
### Color Patterns 
* colorful pattern: This pattern uses random colors for each component, resulting in a colorful effect
* monochromatic pattern: This pattern makes sure that all colors used are of the same r,g,b ratio, just different brightness. It's achieved by randomly generate a base color, and apply one random ratios to r,g,b for each component
* complementary pattern: This pattern uses two base colors that are complementary to each other, and then apply different brightness level to each component

### Additional Methods
* To ensure two different tops don't overlap, I calculate the bounding box of each shape, and before drawing the top at each level I set all pixels inside the bounding box to black(background color)
* I only draw a top when the base of this level is not empty(epsilon). This is achieved by checking the pixel color of both left and right side of the top of base. It's not perfect because in a smaller recursion level there might be emptiness, which causes the top to look weird. I will illustrate this with an image below
* I addressed the issue where a block of the tower is built but it's empty below. I made sure that within a recursion the top square is only drawn if the lower square is drawn. However, there might be smaller empty units. It's hard to determine what shapes are physically possible and what are not. Some emptiness just made the part above it look like balcony. I will also address this with an image later
* If the size of a square is too big, epsilon is not allowed. This is because it can let the entire picture look empty or even just black
* If a square is at the bottom of the canvas it is not allowed to be epsilon because it will results in nothing being able to be built on top of it

### Difficulties and Bug Acknowledgement
* There was a dilemma when I needed to address two issues, but addressing one would cause the other
    * I need to make sure a top is only drawn if the base is not empty. To do this I have to draw base first so that I know if it will be empty or not
    * I need to make sure no overlapping tops are drawn. To do this I have to decide if I will draw a top first and pass this information to next recursion to avoid drawing smaller tops that overlap this one
    * I solved this by "erasing" smaller tops if a bigger top is needed in the same area. I created a function in canvas.cpp to set an area black
* The issue where a block is on top of epsilon
    * I made sure that in the same recursion level nothing can be drawn over epsilon, however it's hard to decide and implement other scenarios. Here are two different situations, one seems ok but the other is not. I did not succeed in making this distinction
<img src= 'https://github.com/JiangxueHan529/castle/blob/main/images/testing30.png' width = '480' height = '285'>
<img src= 'https://github.com/JiangxueHan529/castle/blob/main/images/testing33.png' width = '480' height = '480'>
* The issue where a top is drawn but there is partial emptiness in the base
    * To fully solve this I have to check all pixels in the top level to see if there is a gap. My program is already not very fast so I chose to not address this. An example image showing this problem is below:
<img src= 'https://github.com/JiangxueHan529/castle/blob/main/images/testing42.png' width = '480' height = '480'>

* This program only work on squares with side length that is 2^n (2,4,8,16...)
    * It does not work otherwise because I keep dividing into 4 sub-squares

## Instructions
*Windows*

Open git bash to the directory containing this repository.

```
castle$ mkdir build
castle$ cd build
castle/build $ cmake -G "Visual Studio 16 2019" ..
castle/build $ start Draw-2D.sln
```

To run from the git bash command shell, 

```
castle/build $ ../bin/Debug/draw_art canvas_width canvas_height num_units size_of_unit color_pattern

```
canvas_width: width of canvas\
canvas_height: height of canvas\
num_units: number of blocks on each side of the square\
size_of_unit: the side length of each block\
color_pattern: "colorful", "monochromatic", or "complementary"\
**Restriction: canvas_height > num_units * size_of_unit * 1.5f &&  canvas_width < num_units * size_of_unit**\
If your input does not meet the requirement an exception will be thrown. An example input:
```
castle/build $ ../bin/Debug/draw_art 1000 1000 8 80 colorful

```

*macOS*

Open terminal to the directory containing this repository.

```
castle $ mkdir build
castle $ cd build
castle/build $ cmake ..
castle/build $ make
```

To run each program from build, you would type

```
castle/build $ ../bin/draw_art canvas_width canvas_height num_units size_of_unit color_pattern

```
See explanation of the command line arguments in the Windows section.


## Results
* Colorful
<img src= 'https://github.com/JiangxueHan529/castle/blob/main/images/testing12.png' width = '480' height = '285'>
<img src= 'https://github.com/JiangxueHan529/castle/blob/main/images/testing27.png' width = '480' height = '285'>
<img src= 'https://github.com/JiangxueHan529/castle/blob/main/images/testing29.png' width = '480' height = '285'>
<img src= 'https://github.com/JiangxueHan529/castle/blob/main/images/testing43.png' width = '480' height = '480'>

* Monochromatic
<img src= 'https://github.com/JiangxueHan529/castle/blob/main/images/testing39.png' width = '480' height = '480'>
<img src= 'https://github.com/JiangxueHan529/castle/blob/main/images/testing44.png' width = '480' height = '480'>
<img src= 'https://github.com/JiangxueHan529/castle/blob/main/images/testing45.png' width = '480' height = '480'>

* Complementary
<img src= 'https://github.com/JiangxueHan529/castle/blob/main/images/testing46.png' width = '480' height = '480'>
<img src= 'https://github.com/JiangxueHan529/castle/blob/main/images/testing47.png' width = '480' height = '480'>
<img src= 'https://github.com/JiangxueHan529/castle/blob/main/images/testing48.png' width = '480' height = '480'>
<img src= 'https://github.com/JiangxueHan529/castle/blob/main/images/testing49.png' width = '480' height = '480'>
