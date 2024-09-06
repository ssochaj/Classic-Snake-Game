# Classic Snake Game: C++ OOD
## Overview

This project is a classic snake game implemented using Object-Oriented Design (OOD) principles in C++. The game features a simple UI library and object-oriented design to manage game mechanics, player movement, and rendering. The game is designed to be modular, with well-defined classes handling different aspects of the game.

## Features
- **Object-Oriented Design:** Modular and maintainable code with minimal global variables.
- **Dynamic Board Size:** Configurable game board dimensions.
- **Food Generation:** Random food placement on the board.
- **Score Tracking:** Display and update player score.
- **Real-Time Rendering:** ASCII-based graphical display of the game state.
- **Player Movement:** Control snake movement and direction.

## Components
- **MacUILib.h:** User interface library for rendering and input handling.
- **objPos.h:** Defines the position and symbol of game objects.
- **GameMechs.h:** Manages game mechanics including board state and food generation.
- **objPosArrayList.h:** Manages a list of objPos objects for the snake's body.
- **Player.h:** Handles player input and movement.
