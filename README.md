# Julia set
Program generating Julia set, written in C (with Allegro library) and x86-64 (NASM assembler). This project was made for *Computer Architecture* class at Warsaw University of Technology.

## Setup
In order to run this program, you need to have installed:
- `gcc` - C compiler
- `allegro` - image library
- `cmake` - compilation tool

To run this program in Linux (tested on Manjaro 21.3), execute these commands:
```bash
mkdir build
cd build
cmake ../CMakeLists.txt
cmake --build .
./julia_set
```

Opening and building project in CLion should work as well.

## Controls
- LMB - Move image
- RMB - Change c variable value
- Scroll - Zoom in/out
- Escape - Close program