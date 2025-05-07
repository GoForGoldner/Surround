![alt text](image.png)

# Multiplayer Surround Game

A modern multiplayer take on the classic Atari Surround, developed as a solo side project. This game features real-time competitive gameplay with optimized networking and enhanced visuals.

## 🕹️ Overview

This project reimagines the classic *Atari Surround* with multiplayer support and modern 2D graphics. Players compete by navigating a grid-based arena, avoiding collisions with trails or walls.

## ✨ Features

- **Multiplayer Support**  
  Built on a custom **client-server architecture** using **ENet** (UDP) for efficient real-time networking.

- **Low-Latency Optimization**  
  Addressed and minimized latency issues by profiling and optimizing data transmission between clients and server.

- **SFML Graphics Engine**  
  Utilized **SFML** for rendering, with integrated **shaders** to enhance visual effects and polish gameplay.

- **Efficient Data Structures**  
  - Used **vectors** to represent the game board and movement logic.  
  - Employed **hash maps** for fast and scalable player state management.

- **Performance Improvements**  
  Profiling tools were used to optimize both rendering and networking performance, reducing overhead and increasing frame consistency.

## 🧱 Technologies Used

- **Programming Language**: C++
- **Graphics**: [SFML](https://www.sfml-dev.org/)
- **Networking**: [ENet](http://enet.bespin.org/)
- **Build Tools**: CMake, Make, Git

## 🚀 Getting Started

### Prerequisites

Make sure you have the following installed:

- C++17 or later
- SFML (2.5+)
- ENet
- CMake or Make

## 🛠 Future Plans

- Add matchmaking and lobby system  
- Implement AI bots for offline practice  
- Introduce power-ups and trail customization  
- Expand UI with scoreboards and menus
