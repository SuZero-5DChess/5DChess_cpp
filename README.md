# 5D Chess Implementation in C++

This repository contains a C++ implementation of 5D Chess, a multi-dimensional chess game that extends traditional chess mechanics into additional dimensions, including time and parallel boards. The game supports complex rules for piece movement and interactions across multiple timelines and boards.

---

## Features

- **5D Mechanics**:
    - Multiple boards to represent spatial and temporal dimensions.
    - Piece movements include standard chess rules and additional dimensional shifts.

- **Extensible Design**:
    - Class hierarchy for pieces allows easy addition of new piece types.
    - Virtual functions for flexible movement logic.

- **Game Logic**:
    - Initialization of chessboard states for both spatial and temporal timelines.
    - Dynamic handling of valid moves based on current board and timeline configurations.
    - Support for multiple timelines and game progression.

---

## Code Structure

- `Piece`: Base class for all chess pieces, with virtual methods for move generation.
- `Rook`, `Knight`, `Pawn`, etc.: Derived classes implementing specific movement logic.
- `Board`: Represents a single board in the game, managing pieces and their interactions.
- `Timeline`: Manages a sequence of boards representing a temporal progression.
- `Universe`: The overarching game state, containing all timelines and handling cross-timeline interactions.
- `Game`: Orchestrates the initialization and overall gameplay mechanics.

---

## How to Build and Run

### Prerequisites
- A C++ compiler that supports C++17 or later.
- CMake for building the project.
- [Optional] A debugger like GDB for troubleshooting.

### Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/5dchess.git
   cd 5dchess
   ```


2. Create a build directory and compile the project:
   ```bash
    mkdir build
    cd build
    cmake ..
    make
   ```

3. Run the program:
    ```bash
    ./5dchess
    ```

---

## How to Play

1. Start the game using the compiled executable.
2. Input your moves using the command line, the followings are the format:
- The input format follows (x, y, z, w)->(a, b, c, d), where a, b, c, d, x, y, z, w are integers.
- (x, y, z, w) is the position of the piece you choose, (a, b, c, d) is the destination of this piece.
- the x/a represents the horizontal position for a piece in the board, starts from 0, the positive direction is right.
- the y/b represents the vertical position for a piece in the board, starts from 0, the positive direction is down.
- the z/c represents the horizontal position for a board in the universe, starts from 0 ( the initial board ), the positive direction is right.
- the w/d represents the vertical position for a board in the universe, starts from 0 ( the initial board, this index could be negative), the positive direction is down.
- when the condition for the next turn is meet but you can still make moves, you will be asked if to continue. You can choose as you want.

---

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests for:

- Bug fixes
- Additional features (e.g., new piece types, enhanced UI, etc.)
- Documentation improvements

---

## License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).

---

## Acknowledgments

- Inspired by the mechanics of the official 5D Chess game.