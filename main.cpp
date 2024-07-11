#include <iostream>
#include <stdlib.h>
//#include "Board.h"
#include "ChessEngine.h"

int main() {
	Board board;
	ChessEngine engine(0);
	char chColFrom, chColTo; // Input letters for columns
	int rowFrom, colFrom, rowTo, colTo;
	
	while (1) {
		board.printBoard();
		std::cout << "Evaluation: " << engine.evaluateBoard(&board) << std::endl;
		if (board.isWhiteTurn() == 0) {
			std::pair<std::pair<int, int>, std::pair<int, int>> bestMove = engine.bestMove(&board);
			board.movePiece(bestMove.first.first, bestMove.first.second, bestMove.second.first, bestMove.second.second);
			std::cout << "Engine move: " << char(bestMove.first.second + 'a') << 8 - bestMove.first.first << " " << char(bestMove.second.second + 'a') << 8 - bestMove.second.first << std::endl;
			std::cout << std::endl;
			system("cls");
			continue;
		}
		std::cout << "Enter move: ";
		// Get a move with the format "e2 e4"
		std::cin >> chColFrom >> rowFrom >> chColTo >> rowTo;

		// Convert the column letter to an index
		colFrom = chColFrom - 'a';
		colTo = chColTo - 'a';
		// Convert the row number to an index
		rowFrom = 8 - rowFrom;
		rowTo = 8 - rowTo;

		if (board[rowFrom][colFrom].getColor() == -1) { // If there is no piece on the starting square
			system("cls");
			std::cout << "Invalid move" << std::endl;
			continue;
		}
		else if (board[rowFrom][colFrom].getColor() != board.isWhiteTurn()) { // If the piece is not the same color as the player's turn
			system("cls");
			std::cout << "Wrong turn" << std::endl;
			continue;
		}

		if (!board.movePiece(rowFrom, colFrom, rowTo, colTo)) {
			system("cls");
			std::cout << "Not a legal move" << std::endl;
			continue;
		};

		std::cout << std::endl;
		system("cls");
	}
	
	return 0;
}