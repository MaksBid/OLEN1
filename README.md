# OLEN1.0 Chess Engine

OLEN1 is a simple chess engine written in C++. At the moment it uses depth 2 minimax algorithm and a simple evaluation function. The engine has basic UCI communication. This project is still in development and will be improved in the future.

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [UCI Commands](#uci-commands)
- [Code Overview](#code-overview)

## Features

- Implements UCI protocol for communication with chess GUI.
- Supports standard chess rules including castling, en passant, and promotion.
- Evaluates board positions and calculates the best move.
- Logging of all commands and board states for debugging.

## Requirements

- C++17 or later
- A UCI-compatible chess GUI (e.g., [Arena](http://www.playwitharena.de/), [Lucas Chess](https://lucaschess.pythonanywhere.com/), [ChessBase](https://en.chessbase.com/))

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/OLEN1.git
    cd OLEN1
    ```

2. Compile the project:

    ```bash
    g++ -std=c++17 main.cpp ChessEngine.cpp Board.cpp Piece.cpp -o chess_engine
    ```

## Usage

1. Run the chess engine:

    ```bash
    ./chess_engine
    ```

2. Connect it to your UCI-compatible GUI. Follow the instructions of your specific GUI to add a new UCI engine and point it to the `chess_engine` executable. You can also use the engine in console by typing `cli` instead of `uci`.

## UCI Commands

- **uci**: Identify the engine.
- **isready**: Check if the engine is ready.
- **ucinewgame**: Start a new game.
- **position [startpos | fen <fen_string>] [moves <move1> <move2> ...]**: Set up the board position.
  - `startpos`: Standard chess starting position.
  - `fen <fen_string>`: Set the board to a specific FEN position (currently in development).
  - `moves <move1> <move2> ...`: Apply moves to the position.
- **go**: Begin search for the best move.
- **quit**: Quit the engine.

## Code Overview

### Main Files

- `main.cpp`: Contains the main loop that processes UCI commands.
- `ChessEngine.cpp`: Contains the core logic of the chess engine, including move evaluation and selection.
- `Board.cpp`: Represents the chess board, manages piece placement, and validates moves.
- `Piece.cpp`: Represents individual chess pieces, their types, and their movement rules.

### Class Descriptions

- **ChessEngine**: Handles the decision-making process of the engine. Evaluates board positions and determines the best move.
- **Board**: Manages the state of the chessboard, including piece positions, turn management, and special moves (castling, en passant).
- **Piece**: Represents a single chess piece, its type, color, and valid movements.

### Key Methods

- `Piece::checkMove(int newRow, int newCol)`: Checks if a move is valid for a piece.
- `Board::movePiece(int startRow, int startCol, int endRow, int endCol)`: Moves a piece on a board with account for legality.
- `ChessEngine::bestMove(Board* board)`: Evaluates the best move given the current board state.
