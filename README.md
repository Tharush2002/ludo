# 🎲 Ludo Board Game

A fully-featured digital implementation of the classic Ludo board game built with C and Raylib. Experience the timeless fun of Ludo with smooth animations, intelligent AI opponents, and authentic gameplay mechanics.

![Ludo Game](https://img.shields.io/badge/Game-Ludo-blue)
![Language](https://img.shields.io/badge/Language-C-brightgreen)
![Graphics](https://img.shields.io/badge/Graphics-Raylib-orange)
![License](https://img.shields.io/badge/License-MIT-yellow)

## ✨ Features

### 🎯 Core Gameplay
- **Classic Ludo Rules** - Authentic Ludo experience following traditional game mechanics
- **4-Player Support** - Play with up to 4 players (Red, Blue, Green, Yellow)
- **Intelligent AI** - Smart computer opponents with strategic decision-making
- **Turn-Based System** - Proper turn management with dice rolling mechanics
- **Win Conditions** - First player to get all pieces to the center wins

### 🎮 Game Modes
- **Automatic Mode** - Watch AI players compete automatically
- **Manual Mode** - Step-by-step debugging mode for development
- **Mixed Play** - Human vs AI gameplay support

### 🎨 Visual & Audio
- **Smooth Animations** - Fluid piece movement across the board
- **Visual Dice Rolling** - Animated dice display with realistic timing
- **Colorful Graphics** - Distinct piece colors and clear board visualization
- **Real-time Rendering** - 60 FPS gameplay with Raylib graphics

### 🧠 AI Features
- **Strategic Scoring System** - AI evaluates multiple move factors:
  - 🏠 Entering pieces from base (priority on rolling 6)
  - 🎯 Capturing opponent pieces
  - 🛡️ Safety considerations (avoiding danger zones)
  - 🏃 Progress toward home and center
  - 🚪 Clearing start positions for base pieces
  - 🛡️ Defensive formations and positioning

### 🎲 Game Mechanics
- **Dice System** - Random dice rolling (1-6)
- **Six Roll Bonus** - Extra turns on rolling 6 (max 3 consecutive)
- **Piece Capture** - Send opponents back to base
- **Safe Zones** - Home stretch protection from captures
- **Victory Conditions** - Reach center and stay for 2 seconds to finish

### 🔧 Technical Features
- **Modular Design** - Clean separation of concerns (Game Engine, GUI, Utils)
- **File-based Board Mapping** - Configurable board layout via CSV
- **Memory Management** - Efficient resource handling
- **Cross-platform** - Windows and Linux support
- **Debug Mode** - Manual stepping for development and testing

## 🚀 Installation

### Prerequisites

Before installing the game, make sure you have the following dependencies:

#### On Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential cmake git
sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```

#### On Fedora/CentOS/RHEL:
```bash
sudo dnf groupinstall "Development Tools"
sudo dnf install cmake git
sudo dnf install alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel libXxf86vm-devel
```

#### On macOS:
```bash
# Install Homebrew if you haven't already
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install cmake git
```

#### On Windows:
- Install [MinGW-w64](https://www.mingw-w64.org/) or [Microsoft Visual Studio](https://visualstudio.microsoft.com/)
- Install [CMake](https://cmake.org/download/)
- Install [Git](https://git-scm.com/download/win)

### Installing Raylib

#### Option 1: Install Raylib from Source (Recommended)
```bash
# Clone raylib repository
git clone https://github.com/raysan5/raylib.git
cd raylib

# Create build directory
mkdir build && cd build

# Generate makefiles
cmake .. -DBUILD_EXAMPLES=OFF

# Compile raylib
make -j4

# Install raylib
sudo make install

# Update library cache (Linux only)
sudo ldconfig
```

#### Option 2: Package Manager Installation

**Ubuntu/Debian:**
```bash
sudo apt install libraylib-dev
```

**macOS:**
```bash
brew install raylib
```

**Windows (using vcpkg):**
```bash
vcpkg install raylib
```

### Building the Game

1. **Clone the repository:**
```bash
git clone https://github.com/yourusername/ludo-game.git
cd ludo-game
```

2. **Create required directories:**
```bash
mkdir -p assets
```

3. **Add game assets:**
   - Place your board image as `assets/board.png`
   - Add piece images: `assets/red.png`, `assets/blue.png`, `assets/green.png`, `assets/yellow.png`
   - Add dice images: `assets/1.png` through `assets/6.png`
   - Create board mapping file: `assets/mappings.csv`

4. **Compile the game:**
```bash
# Using GCC
gcc -std=c99 -Wall -Wextra -O2 *.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o ludo

# Or using a Makefile (create one based on your system)
make
```

5. **Run the game:**
```bash
./ludo
```

## 📁 Project Structure

```
ludo-game/
├── src/
│   ├── main.c              # Main game loop and entry point
│   ├── game_engine.c/.h    # Core game logic and AI
│   ├── board_mapping.c/.h  # Board layout and square management
│   ├── gui.c/.h           # Graphics and rendering
│   ├── utils.c/.h         # Utility functions
│   └── types.h            # Data structures and constants
├── assets/
│   ├── board.png          # Game board image
│   ├── *.png              # Piece and dice images
│   └── mappings.csv       # Board coordinate mappings
└── README.md
```

## 🎮 How to Play

1. **Launch the game** - Run the executable
2. **Game starts automatically** - Players are ordered by dice roll
3. **Watch the AI play** - In automatic mode, AI handles all moves
4. **Manual debugging** - Use manual mode for step-by-step gameplay
5. **Win condition** - First player to get all 4 pieces to center wins!

### Game Rules
- Roll 6 to move pieces out of base
- Capture opponents by landing on their pieces
- Rolling 6 gives an extra turn (max 3 consecutive)
- Home stretch is safe from captures
- Reach center and stay 2 seconds to finish a piece

## 🛠️ Development

### Debug Mode
Enable manual mode in `main.c` to step through moves:
- **SPACE** - Make next move
- **ESC** - Exit game

### Configuration
- Modify `types.h` for game constants
- Update `assets/mappings.csv` for custom board layouts
- Adjust AI scoring in `game_engine.c`

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes, please open an issue first to discuss what you would like to change.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- [Raylib](https://www.raylib.com/) - Amazing graphics library
- Classic Ludo game designers for the timeless gameplay
- Open source community for inspiration and tools

## 📧 Contact

Your Name - your.email@example.com

Project Link: [https://github.com/yourusername/ludo-game](https://github.com/yourusername/ludo-game)

---

**Enjoy playing Ludo! 🎲🎉**
