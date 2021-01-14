# 2020 NCTU Computer Graphics Final Project
* Title: UFO vs Spaceship
* Author: zeze

## Introduction
It is my final project of the computer graphics in NCTU. Me, who is totally novice to the computer graphics, finally complete the project. 
Any suggestion and any kind of uses are welcome.

## Technique
1. Load UFO and spaceship objects.
2. Translate spaceship in y-axis while rotating in the mean time.
3. Detect y-axis value of the spaceship and if it bumps into the UFO, then explode.
4. The explosion animation is taking advantage of geometry shader, in which I use a variable explosion to present the progress of the explosion. The variable explosion will increase in every round of the loop.

## Snapshot
* Before bumping
![img](assets/img1)

* Explosion
![img](assets/img2)

## Reference
1. [3D model - Intergalactic Spaceship In Blender 2.8 Eevee](https://free3d.com/3d-model/intergalactic-spaceship-in-blender-28-eevee-394046.html)
2. [3D model - Modular UFO](https://free3d.com/3d-model/modular-ufo-190921.html)
3. [Learn OpenGL - Geometry](https://learnopengl.com/Advanced-OpenGL/Geometry-Shader)
