# Dynamic Island Generator 🏝️

## Author: Sreeram Kondapalli

## Description

This project, Dynamic Island Generator, aims to simulate the dynamic creation of islands through randomized particle drops. By utilizing dynamic arrays and applying various algorithms, it generates an island landscape based on user inputs such as grid size, drop-zone coordinates, number of particles, and more. The islands are represented in different stages - raw, normalized, and a polished final version, all visualized through colorful terminal outputs and saved into text files.

---

## Screenshots

### Raw Island

Here is the representation of the raw island, showing the initial state of particle drops.

![Raw Island](images/Raw%20Island.png)

### Normalized Island

The normalized version of the island after applying certain algorithms for a more structured appearance.

![Normalized Island](images/Normalized%20Island.png)

### Final Island

The final polished representation of the island, showcasing a vivid and colorful display.

![Final Island](images/Final%20Island.png)

---

## How to Run

1. Clone this repository to your local machine.
2. Navigate to the project directory in the terminal.
3. Compile the project by typing `g++ -o island_generator main.cpp` and pressing enter.
4. Run the project by typing `./island_generator` and follow the on-screen instructions.

---

## Customization

Users can customize various parameters of the island generation such as:

- Grid Width and Height
- Drop-zone coordinates
- Number of particles to drop
- Maximum life of particles
- Waterline value

---

## Technologies Used

- C++
- Standard Template Library (STL)

---

## Acknowledgements

Special thanks to the termcolor library for enabling colorful terminal outputs.

---

Enjoy exploring your dynamically generated islands! 🌴

