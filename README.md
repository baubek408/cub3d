# Cub3D - 42 Prague

![42 Prague](https://img.shields.io/badge/42-Prague-black.svg?style=flat&logo=42)
![Language](https://img.shields.io/badge/Language-C-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)

A 3D game engine project inspired by the classic Wolfenstein 3D. This project was completed as part of the curriculum at 42 Prague. The goal is to render a 3D graphical representation of a 2D map using the principles of raycasting.

## Demo

![Cub3D Gameplay](./assets/cub3d_demo.gif)

## Project Overview

Cub3D is a first-person 3D maze exploration game. The rendering engine is built from scratch using C and the MiniLibX graphical library provided by 42. The project involves parsing a scene description file (`.cub`), handling textures, implementing a raycasting algorithm to create a 3D perspective, and managing player movement and controls.

## Features

### Mandatory Part
- **Graphical Representation**: Renders a 3D view from a 2D map.
- **Raycasting Engine**: Uses the DDA (Digital Differential Analyzer) algorithm to cast rays and find wall intersections.
- **Scene Parsing**: Parses `.cub` files containing map layout, textures, and colors.
- **Textured Walls**: Applies different textures to walls based on their orientation (North, South, East, West).
- **Player Movement**: Full player controls including moving forward/backward, strafing left/right, and rotating the camera.
- **Window Management**: Smooth window management using MiniLibX, including graceful exit.
- **Error Handling**: Robust parsing and handling of invalid map files or missing assets.

## Technologies Used

* **Language**: C
* **Compiler**: `gcc`
* **Build System**: `make`
* **Graphics Library**: `MiniLibX` (a custom, simple X-Window programming library provided by 42).

## Installation & Usage

### Prerequisites
This project is designed for a Linux environment and relies on `X11` libraries for the MiniLibX. You may need to install the following dependencies:

```bash
# For Debian/Ubuntu-based systems
sudo apt-get update && sudo apt-get install libx11-dev libxext-dev zlib1g-dev
