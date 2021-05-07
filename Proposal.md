Final Project Proposal
===

# Castle

## Table of Contents
1. [Idea](#Idea)
1. [Features](#Features)
1. [Timeline](#Timeline)
2. [Algorithms](#Algorithms)

## Idea
I'm planning to procedurally generate a castle. The inspiration is from tinyspires: https://twitter.com/tinyspires. Some examples of what I'm working towards are below:

This is unique from the work we already did in this course because we have never done an assignment that involves generating shapes procedurally. This is a new challenge!

## Features
### Basic
* Generate basic castle with just square blocks and triangle tops. This basic version of castle always has complete squares and a triangle at the top. I will describe this in Algorithms section later.
* Apply coloring to each components.
* Generate a more advanced version of castle with more features such as different types of tops and design within the square blocks. I will describe this in more detail in Algorithms section as well.

### Stretch
* Apply better coloring design to look more artistic.
* Make this work on non-square rectangle spaces as well.

## Timeline
* May, 6th - May, 7th: Finish up with thoughts for designing.
* May, 8th - May, 9th: Implement the most basic version of castle and coloring.
* May, 10th - May, 13th: Presentation. Implement the more advanced version with more features.
* May, 14th - May, 15th: Buffer time for debugging.
* May, 16th - May, 19th: Aim for the stretch features. More Debugging. Final Presentation. Writing report. 


## Algorithms
* The most basic version of castle:
    * Shape Grammar: 
        * T(N) -> Base(N) top
        * Base(N) -> Base(N/4) Base(N/4) Base(N/4) Base(N/4)
        * Base(1) -> block
    * Example:
        * Image:
        * T(4)
        * Base(4) top
        * Base(1) Base(1) Base(1) Base(1) top
        * block block block block top
* More advanced version of castle:
    * Shape Grammar:
        * T(N) -> Base(N)
        * T(N) -> Base(N) top
        * T(N) -> Base(N) top-C
        * T(N) -> Base(N) semi-sphere
        * Base(N) -> ε*N
        * Base(N) -> T(N/4) T(N/4) T(N/4) T(N/4)
        * Base(1) -> block
        * Base(1) -> block-C
        * Base(1) -> block-T
    * Example:
        * Image:
        * T(16)
        * Base(16)
        * T(4) T(4) T(4) T(4)
        * Base(4) top-C Base(4) Base(4) Base(4) semi-sphere
        * Base(1) Base(1) Base(1) Base(1) top-C Base(1) Base(1) Base(1) Base(1) ε ε ε εBase(1) Base(1) Base(1) Base(1) semi-sphere
        * block-C block block block block top-C block block block-T block ε ε ε ε block-C block block block-T semi-sphere
        
            
