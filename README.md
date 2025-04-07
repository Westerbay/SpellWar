
# 🔥 SpellWar - OpenGL 3D Third-Person Game

**SpellWar** is a third-person 3D game developed in C++ with OpenGL, featuring a custom-built game engine and real-time gameplay mechanics. This repository contains both the game logic and the engine from scratch.

---

## 🎮 Gameplay Overview

In *SpellWar*, players control characters across floating platforms. The game emphasizes mobility, precision jumping, and character selection.

### 🎮 Controls

- `ZQSD` — Move (AZERTY layout)
- `Z` — Up 
- `Q` — Left 
- `D` — Right 
- `S` — Down 
- `Shift (hold)` — Sprint
- `Space` — Jump
- `Escape` — Open the options menu

### 🧠 Movement Mechanic

To jump from one platform to another:
1. Look at the platform you want to reach.
2. Walk toward the edge.
3. Jump while moving toward it to "launch" across.
4. There must be no collisions between you and the platform.

---

## 🚀 How to Launch

- Run the game in fullscreen:
  ```bash
  ./SpellWar
  ```
- Run the game in windowed mode with custom resolution:
  ```bash
  ./SpellWar <width> <height>
  ```

> 🕒 Note: The loading time at the start can be long — this is due to initial map loading.

---

## 🧱 Project Structure

The codebase is split between two main components:

### 📁 `src/wgame/` and `include/wgame/`
This folders contain the **custom game engine**, built from scratch. It handles core systems like:
- Rendering
- Animation
- Input
- Camera
- Window management
- Scene and entity systems
- etc...

### 📁 `src/spellwar/` and `include/spellwar/`
This folder holds the **game-specific logic**, such as:
- Character behavior
- Platform mechanics
- Game rules and gameplay scripting

### 📁 `shaders/`
GLSL shaders used for visual rendering.

---

## ✅ MVP 1.0 Features

- Floating platforms
- Multiple playable characters
- Third-person movement
- Platform-jumping mechanic

---

## 🔜 TODO — MVP 2.0 Goals

- Add enemies
- Add combat/attacks for characters

---

## 📦 Asset Credits

### 🪐 Background
- **Space Environment**  
  Source: [Space Sphere Maps](https://www.spacespheremaps.com/hdr-spheremaps/)

### 🎨 Materials
- **Texture Pack by Lynocs**  
  Source: [Itch.io - Texture Pack](https://lynocs.itch.io/texture-pack)

### 🔤 Fonts
- **Monogram Font by datagoblin**  
  Source: [Itch.io - Monogram](https://datagoblin.itch.io/monogram)

### 🪨 Rocks & Terrain
- **Rock** by Siesta  
  Source: [Sketchfab - Rock](https://sketchfab.com/3d-models/rock-b66d5b63deb447299ca3effa904bc789)

- **Stalagmite** by DaniEve  
  Source: [Sketchfab - Stalagmite](https://sketchfab.com/3d-models/stalagmite-976ebf9b96ea4fdaa83746eed3272513)

### 🌱 Plants
- **Low Poly Water Plant** by Natural_Disbuster  
  Source: [Sketchfab - Water Plant](https://sketchfab.com/3d-models/low-poly-water-plant-9929031abf784da58b02d725e6191997)

- **Fantasy Plant 2** by Mainul  
  Source: [Sketchfab - Fantasy Plant](https://sketchfab.com/3d-models/fantasy-plant-2-0ea642fda9f14e6c94296914b1dc11f5)

### 🌳 Trees
- **Tree with Pink Leaves** by ChamberSu1996  
  Source: [Sketchfab - Tree](https://sketchfab.com/3d-models/laying-under-a-tree-with-pink-leaves-and-wind-7c256555f2b04315bd301fd42b19be50)

### ☀️ Celestial Bodies
- **The Sun** by ARCTIC WOLVES™  
  Source: [Sketchfab - The Sun](https://sketchfab.com/3d-models/the-star-sun-519dddb6998545e2bf84225394dc71fe)

### 🔥 Characters
- **Flame Wraith** by YT-XTREMENINJA  
  Source: [Sketchfab - Flame Wraith](https://sketchfab.com/3d-models/flame-wraith-set-3d-angry-animation-c8e3e43a845d42bd8a65ce79597ee01f)

- **Taila (Frost)** by Partaevil  
  Source: [Sketchfab - Taila](https://sketchfab.com/3d-models/taila-original-work-8ae231b61fc34827be30e2a1edc5b811)

---

## 🧊 Built With

- **C++17**
- **OpenGL**
- **GLFW**
- **GLM**
- **TinyGLTF**

---

## Authors

Wester
