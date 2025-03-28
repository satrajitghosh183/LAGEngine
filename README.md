# LAGEngine

## 🧠 Overview

GameEngineX is built from the ground up with a focus on:
- Custom rendering using **OpenGL 4.5+**
- Modular physics and AI systems
- No external windowing system dependencies (GLFW used temporarily)
- Support for **procedural content**, **smart NPCs**, and **real-time physics**
- A long-term vision to support **multiplayer**, **in-engine tools**, and **VR**

---

## ✅ Milestones Completed


- Temporary window created using GLFW and OpenGL context set up
- Minimal physics engine implemented (gravity + bounce demo)
- Successfully rendering 2D shapes via OpenGL

---

## 🧭 Roadmap / To-Do

### 🔧 Core Engine
- [ ] Implement custom cross-platform **windowing system**
- [ ] Add custom **OpenGL extension loader**
- [ ] Design low-level **rendering abstraction layer**

### 🎨 Graphics Engine
- [ ] Shader management system (loading, compiling, hot-reload)
- [ ] 3D model loading via **Assimp**
- [ ] First-person / third-person **camera system**
- [ ] Lighting (Directional, Point, Spot, PBR support)
- [ ] Deferred rendering pipeline
- [ ] Post-processing (Bloom, SSAO, Motion Blur)

### 🧠 AI & NPC System
- [ ] Behavior Tree system
- [ ] Navigation (A* pathfinding, NavMesh)
- [ ] Dialogue system powered by LLM
- [ ] Procedural NPC generation (traits, appearance, logic)
- [ ] AI memory, emotion & adaptability framework

### 🧪 Physics Engine
- [x] Basic rigid-body + gravity simulation
- [ ] Collision detection (AABB, circle, polygon)
- [ ] Soft body physics (cloth, deformation)
- [ ] Destruction system (fracturable objects)
- [ ] Vehicle physics (acceleration, friction, steering)

### ⚙️ Engine Infrastructure
- [ ] Entity-Component System (ECS)
- [ ] Scene graph & serialization
- [ ] Lua or Python scripting backend

### 🧑‍🎨 UI & Tooling
- [ ] Custom UI system (panels, buttons, sliders)
- [ ] Debug rendering overlays (colliders, stats)
- [ ] In-game scene editor & dev tools

### 🌐 Multiplayer (Future Phase)
- [ ] Server-client networking (WebSocket or UDP)
- [ ] AI integration in multiplayer context
- [ ] World state sync and prediction

---

## 🛠️ Build Instructions

### 📦 Requirements
- **C++17** or higher
- **CMake** 3.16+
- **GLFW** (temporarily, will be removed)
- **OpenGL** 4.5+
- (Optional) **GLAD**, **Assimp**, **OpenAL**, **Bullet**

### 🧪 Build 
```bash
git clone https://github.com/satrajitghosh183/LAGEngine.git
cd LAGEngine
mkdir build
cd build
cmake ..
make  # or cmake --build .

You can also use the run_game_engine.sh to do all these steps all at once 

