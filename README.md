# Angry Birds Game - Final Project

## Authors
- **Adi Yakoby**
- Michael Zargari 
- Ron Elian 

## Project Overview
This project was developed during the second year of my B.Sc. in Computer Science. It demonstrates the application of STL and advanced C++ techniques that I learned independently outside my degree curriculum. The game is a replica of the classic Angry Birds, where players use a slingshot to launch birds at pigs sheltered by various structures, aiming to eliminate all the pigs to advance through the levels.

## Media

### Photos
![Photo 1](https://github.com/adiyakoby/Angry-Birds/blob/master/angrybirds.png)
![Photo 2](https://github.com/adiyakoby/Angry-Birds/blob/master/angrybirds2.png)
![Photo 3](https://github.com/adiyakoby/Angry-Birds/blob/master/angrybird3.png)

### Video (YouTube)
[![Watch the video](https://img.youtube.com/vi/V4DrVV0S9NE/maxresdefault.jpg)](https://www.youtube.com/watch?v=V4DrVV0S9NE)

## Game Description
In this game, the player controls a flock of colorful birds trying to retrieve their eggs, which have been stolen by a group of hungry green pigs. At each stage, the pigs are protected by buildings made of different materials (such as wood, glass, or rocks). The goal is to eliminate all the pigs. Using a slingshot, the player launches a limited group of birds to hit the pigs directly or damage the buildings around them, causing structures to collapse and crush the pigs. Each bird type has unique abilities, and each level starts with a predetermined set of birds.

## Features
- **6 Stages:** Varying difficulty levels to challenge the player.
- **4 Bird Types:** Each with different abilities:
  - Red Bird: No special ability.
  - Blue Bird: Splits into three small birds.
  - Yellow Bird: Gains a power boost during flight.
  - Black Bird: Explodes on command.
- **Graphics and Physics:** 
  - Graphics are implemented using the SFML library.
  - Physics are handled using the BOX2D library.

## Installation

1. **Install SFML (version 2.5.1):**
    - Download SFML 2.5.1 from the [official website](https://www.sfml-dev.org/download.php).
    - Follow the installation instructions for your operating system.

2. **Update CMakeLists.txt:**
    - Open the `CMakeLists.txt` file.
    - Update the SFML path to match your installation location:
        ```cmake
        set(SFML_DIR "path_to_your_SFML_2.5.1_installation")
        find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
        ```

3. **Clone the repository:**
    ```sh
    git clone https://github.com/yourusername/Angry-Birds.git
    ```

4. **Build the project:**
    ```sh
    cd Angry-Birds
    mkdir build
    cd build
    cmake ..
    make
    ```

## Classes and Design
### States
- **State:** Abstract base class for all state classes in the game.
- **MainMenuState:** Handles the game menu, with options to start the game, access help, exit, or mute audio.
- **PlayState:** Manages the game flow, updating the game with every board movement.
- **LevelSelectState:** Displays available stages and the highest score for each stage.
- **TransitionScreensState:** Shows transition screens at the end of each stage.

### StateMachine
Manages all game states using a stack to handle state transitions:
1. **Delete:** Removes the current state.
2. **Replace:** Replaces the current state with a new one.
3. **Push:** Adds a new state without removing the current one.
4. **Switch:** Switches between states, preserving data.

### Game
The main class that runs the game.

### GameResources
Manages all game resources, such as textures, fonts, and music.

### Window
Creates and manages the game window.

### Bird
Abstract class representing a bird. Specific bird types (RedBird, BlackBird, YellowBird, BlueBird) inherit from this class, each with unique abilities.

### World
Defines the game world, including fields and gravity, and manages all bodies within the world.

### StaticObject
Abstract class for all static objects in the game.

### ObjectFactory
Template class for creating birds and static objects.

### Ground
Represents the ground, inheriting from StaticObject.

### Rogatka
Represents the slingshot, inheriting from StaticObject.

### Obstacles
Represents all destructible objects that the player can interact with.

### CircularObstacle
Represents round objects in the game, with unique graphic and physical behaviors.

### Guideline
Simulates the bird's trajectory when aiming, using physical objects from BOX2D.

### LevelManager
Reads level data from text files and creates appropriate objects based on predefined rules and signs.

### MyContactListener
Manages collisions in the game, implementing custom collision handling using multimethods.

## Design Patterns
- **State Pattern:** Each game state is a separate class managed by a state machine.
- **Factory Pattern:** ObjectFactory class for creating birds and static objects.
- **Singleton Pattern:** Ensures only one instance of certain classes (GameResources, GuideLine, ObjectFactory).
- **MultiMethods:** Custom collision handling using a map to bind functions to object pairs.

## Additional Notes
- Each stage starts in "Show" mode, displaying the layout for strategic planning.
- Levels are locked until previous ones are completed.
- Birds have unique abilities activated by clicking the screen during flight.
- The game's implementation includes several advanced C++ features, making extensive use of STL and design patterns.

## Libraries Used
- **SFML:** For graphics rendering.
- **BOX2D:** For physics simulation.

Enjoy playing our version of Angry Birds!
