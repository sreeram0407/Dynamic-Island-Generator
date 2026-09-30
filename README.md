# Dynamic Island Generator

A C++ procedural terrain generator based on randomized particle deposition. Particles move across a grid to form a height map, which is normalized and rendered as a colored island in the terminal.

## Preview

![Generated island terrain](images/Final%20Island.png)

[Raw height map](images/Raw%20Island.png) · [Normalized height map](images/Normalized%20Island.png)

## Build and run

From the repository root:

```bash
g++ -std=c++11 main.cpp -o island_generator
./island_generator
```

For repeatable generation, pass a nonzero seed:

```bash
./island_generator -s 42
```

The program prompts for grid width and height, drop-zone coordinates and radius, particle count, particle lifetime, and waterline. Keep the circular drop zone inside the grid, use a positive particle count, and follow the displayed parameter ranges.

Raw, normalized, and terrain views appear in the terminal. `Island.txt` contains the normalized height map and final character map.

## Files

- [main.cpp](main.cpp): particle simulation, normalization, and rendering.
- [termcolor.hpp](termcolor.hpp): bundled terminal-color library.
- [images/](images/): example outputs.

**Author:** Sreeram Kondapalli
