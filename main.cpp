#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "ChessEngine.h"

void uci_loop() {
    std::ofstream logFile("log.txt");
    Board board;
    ChessEngine engine(board.isWhiteTurn());

    std::string input, token;
    while (std::getline(std::cin, input)) {
        logFile << "GUI -> Engine: " << input << std::endl;
        std::istringstream iss(input);
        iss >> token;

        if (token == "uci") {
            std::cout << "id name OLEN1" << std::endl;
            std::cout << "id author Maksbid" << std::endl;
            std::cout << "uciok" << std::endl;
        }
        else if (token == "isready") {
            std::cout << "readyok" << std::endl;
			logFile << "Engine -> GUI: readyok" << std::endl;
        }
        else if (token == "ucinewgame") {
            board = Board(); // Reset the board
            engine = ChessEngine(board.isWhiteTurn());
        }
        else if (token == "position") {
            iss >> token;
            if (token == "startpos") {
                board = Board(); // Reset to starting position
                iss >> token; // This should be "moves" if there are any
            }
            else if (token == "fen") {
                // Implement FEN position setup here
                // Then read "moves" token if present
            }

            // Apply moves if any
            if (token == "moves") {
                std::string move;
                while (iss >> move) {
                    int colFrom = move[0] - 'a';
                    int rowFrom = '8' - move[1];
                    int colTo = move[2] - 'a';
                    int rowTo = '8' - move[3];
                    if (!board.movePiece(rowFrom, colFrom, rowTo, colTo)) {
						logFile << board.toString() << std::endl;
                        logFile << "Error: Illegal move " << move << std::endl;
                    }
                }
            }
            engine = ChessEngine(board.isWhiteTurn()); // Update engine with new board state
        }
        else if (token == "go") {
            // Parse time control info if needed
            std::pair<std::pair<int, int>, std::pair<int, int>> bestMove;
			logFile << "Board state before move: " << std::endl;
			logFile << board.toString() << std::endl;
            bestMove = engine.bestMove(&board);
            
            char colFromCh = 'a' + bestMove.first.second;
            char rowFromCh = '8' - bestMove.first.first;
            char colToCh = 'a' + bestMove.second.second;
            char rowToCh = '8' - bestMove.second.first;

            std::string moveStr = std::string() + colFromCh + rowFromCh + colToCh + rowToCh;
            std::cout << "bestmove " << moveStr << std::endl;
            logFile << "Engine -> GUI: bestmove " << moveStr << std::endl;
        }
        else if (token == "quit") {
            break;
        }

        logFile.flush();
    }
}

int main() {

	uci_loop();
	return 0;
}

//
//int main() {
//	Board board;
//	ChessEngine engine(0);
//	char chColFrom, chColTo; // Input letters for columns
//	int rowFrom, colFrom, rowTo, colTo;
//	
//	while (1) {
//		board.printBoard();
//		std::cout << "Evaluation: " << engine.evaluateBoard(&board) << std::endl;
//		if (board.isWhiteTurn() == 0) {
//			std::pair<std::pair<int, int>, std::pair<int, int>> bestMove = engine.bestMove(&board);
//			board.movePiece(bestMove.first.first, bestMove.first.second, bestMove.second.first, bestMove.second.second);
//			std::cout << "Engine move: " << char(bestMove.first.second + 'a') << 8 - bestMove.first.first << " " << char(bestMove.second.second + 'a') << 8 - bestMove.second.first << std::endl;
//			std::cout << std::endl;
//			system("cls");
//			continue;
//		}
//		std::cout << "Enter move: ";
//		// Get a move with the format "e2 e4"
//		std::cin >> chColFrom >> rowFrom >> chColTo >> rowTo;
//
//		// Convert the column letter to an index
//		colFrom = chColFrom - 'a';
//		colTo = chColTo - 'a';
//		// Convert the row number to an index
//		rowFrom = 8 - rowFrom;
//		rowTo = 8 - rowTo;
//
//		if (board[rowFrom][colFrom].getColor() == -1) { // If there is no piece on the starting square
//			system("cls");
//			std::cout << "Invalid move" << std::endl;
//			continue;
//		}
//		else if (board[rowFrom][colFrom].getColor() != board.isWhiteTurn()) { // If the piece is not the same color as the player's turn
//			system("cls");
//			std::cout << "Wrong turn" << std::endl;
//			continue;
//		}
//
//		if (!board.movePiece(rowFrom, colFrom, rowTo, colTo)) {
//			system("cls");
//			std::cout << "Not a legal move" << std::endl;
//			continue;
//		};
//
//		std::cout << std::endl;
//		system("cls");
//	}
//	
//	return 0;
//}