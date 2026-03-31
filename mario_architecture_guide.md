# Rebuilding Mario in Raylib: Project Structure & Architecture

Creating a platformer like Super Mario in C++ using Raylib requires a solid, scalable file structure. Because Raylib is purely a framework (it gives you functions to draw, play audio, and get input, but doesn't dictate how you structure your code), you need to build your own mini-engine architecture to keep things clean.

Here is the perfect structural blueprint for a platformer based on modern C++ best practices.

## Recommended Folder Structure

```text
RaylibTemplate/
├── src/                    # All source files go here
│   ├── main.cpp            # Application entry point
│   ├── Core/               # Engine fundamentals (Window, Input, Game Loop)
│   │   ├── Game.h/.cpp     # Manages the main delta-time loop and state
│   │   └── ResourceManager.h/.cpp # Caches Textures, Sounds, and Fonts
│   ├── Entities/           # Game objects
│   │   ├── Entity.h/.cpp   # Base class for all game objects
│   │   ├── Player.h/.cpp   # Mario's logic, states, and input handling
│   │   ├── Enemy.h/.cpp    # Goombas, Koopas
│   │   └── Item.h/.cpp     # Coins, Mushrooms, Fire Flowers
│   ├── Graphics/           # Rendering systems
│   │   ├── Animator.h/.cpp # Handles sprite sheet animations and frame delays
│   │   └── CameraController.h/.cpp # Tracks player and stops at boundaries
│   ├── Physics/            # Movement and Collision
│   │   ├── AABB.h/.cpp     # Axis-Aligned Bounding Box math
│   │   └── Collider.h/.cpp # Handles interactions between Player, Enemies, Tiles
│   ├── World/              # Level Management
│   │   ├── Level.h/.cpp    # Parses level data (e.g., from Tiled TMX/JSON)
│   │   └── Tilemap.h/.cpp  # Manages and renders the grid of tiles
│   └── States/             # Game State Machine
│       ├── State.h         # Base interface
│       ├── MainMenu.h/.cpp 
│       └── PlayState.h/.cpp
├── assets/                 # Game resources
│   ├── graphics/           # mario_sheet.png, tileset.png
│   ├── audio/              # jump.wav, overworld.mp3
│   ├── fonts/              # ui_font.ttf
│   └── levels/             # level_1_1.json 
├── vendor/                 # Third-party code (nlohmann json for level parsing)
└── Makefile / CMake        # Build configuration (already in template)
```

---

## How to map Raylib features into this structure

When implementing this structure, you want to encapsulate Raylib's C-API inside your C++ classes so your codebase remains object-oriented and organized.

### 1. The Resource Manager (Crucial for Memory!)
**Why you need it:** Raylib expects you to load a texture via `LoadTexture()` and unload it with `UnloadTexture()`. If 50 Goombas instantiate and each runs `LoadTexture("goomba.png")`, you will crash your GPU memory and waste processing power. 
**Solution:** Create a `ResourceManager` (often a Singleton or passed via dependency injection) that stores maps: `std::unordered_map<std::string, Texture2D>`.
* When an object requests `goomba.png`, the manager checks if it's already loaded. If yes, it returns the reference. If no, it calls Raylib's `LoadTexture()`, stores it, and returns the reference.
* Make sure to call `UnloadTexture()`, `UnloadSound()`, etc., in the `ResourceManager`'s destructor.

### 2. The Entity System
Since Mario has distinct behaviors, encapsulate them. Create a Base `Entity` class.
```cpp
class Entity {
protected:
    Vector2 position;
    Vector2 velocity;
    Texture2D* spriteSheet;
public:
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
};
```
Then `Player` inherits from `Entity`. 
* In `Player::Update(float deltaTime)`, you will use Raylib's `IsKeyDown(KEY_RIGHT)` to adjust velocity, apply gravity, and update the animation frame.
* In `Player::Draw()`, you will use Raylib's `DrawTextureRec()` to draw the specific frame of Mario from a spritesheet.

### 3. State Machine (Title Screen -> Gameplay -> Death Route)
Games aren't just one screen. Use a simple pointer-based State Machine. 
Have a `State` base class with `Enter()`, `Update()`, `Draw()`, and `Exit()`.
Your `Game::Update()` simply calls `currentState->Update()`. This prevents your `main.cpp` from becoming a mess of `if (isTitleScreen) { ... } else if (isPlaying) { ... }`.

### 4. Physics and Collision
Mario games rely heavily on AABB (Axis-Aligned Bounding Box) collisions. 
Raylib provides `CheckCollisionRecs(Rectangle rec1, Rectangle rec2)`. 
* Inside your `Collider` or `Physics` class, you will check Mario's next predicted position (`position + velocity * deltaTime`) against the Tilemap rectangles to resolve wall/floor collisions *before* applying the final position. Wait to apply Gravity and Velocity until collision tests are resolved.

### 5. Tilemap / World Generation
Don't hardcode your levels. Use a tool like **Tiled (mapeditor.org)**. 
Export your maps as `.json`, include a JSON parsing library (like `nlohmann/json`) into your `vendor/` folder, and read the generic level files into a 2D array or `std::vector` inside your `Tilemap` class. 
In your `Tilemap::Draw()`, you iterate through the visible tiles on screen and use `DrawTextureRec()` to select the specific tile from your `tileset.png`.

## Recommended First Steps:
1. **Setup the folders** in your current repository according to the `src/` layout.
2. **Refactor `main.cpp`** so it initializes the window and immediately delegates the game loop to a `Game` class.
3. **Write the `ResourceManager`** to load your Mario spritesheet safely.
4. **Implement the `Player` class** capable of moving left/right and jumping using simple gravity physics.
5. **Create a basic hard-coded floor array** to test collisions using Raylib's `CheckCollisionRecs`.
