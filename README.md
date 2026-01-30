# C Adventure

A 2D adventure game written in C using the Raylib game development library.

## Build Instructions

### Using CMake (Recommended)

1. **Clone or navigate to the project directory:**

   ```bash
   cd c_adventure
   ```

2. **Create a build directory:**

   ```bash
   mkdir -p build
   cd build
   ```

3. **Configure the project with CMake:**

   ```bash
   cmake .. && make
   ```

4. **Run the game:**
   ```bash
   ./CAdventure
   ```

## Controls

- **W** - Move up
- **A** - Move left
- **S** - Move down
- **D** - Move right
- **ESC** - Exit game

## Troubleshooting

### Compiler Issues

The project uses your system's default C compiler. If you want to use a specific compiler, edit `CMakeLists.txt` and uncomment/modify these lines:

```cmake
set(CMAKE_C_COMPILER "/path/to/your/clang")
set(CMAKE_CXX_COMPILER "/path/to/your/clang++")
```

For example, to use Homebrew's LLVM on macOS:

```cmake
set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")
```
