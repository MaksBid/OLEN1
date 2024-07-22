#pragma once
#include "Board.h"
#include "Piece.h"
#include <cstdlib>
#include <ctime>

class ChessEngine
{
private:
	int myColor;
	int depth = 2;

    void logAction(const std::string&);
public:
	ChessEngine();
	ChessEngine(int color);
	~ChessEngine();

	std::pair<std::pair<int, int>, std::pair<int, int>> bestMove(Board* board);
	double minimax(Board* board, int depth, double* alpha, double* beta, bool maximizingPlayer);

	double evaluateBoard(Board* board) const;
};

const double weights[8][8] = {
    { -0.5, -0.4, -0.3, -0.3, -0.3, -0.3, -0.4, -0.5 },
    { -0.4, -0.2,  0.0,  0.0,  0.0,  0.0, -0.2, -0.4 },
    { -0.3,  0.0,  0.1,  0.15, 0.15, 0.1,  0.0, -0.3 },
    { -0.3,  0.05, 0.15, 0.2,  0.2,  0.15, 0.05, -0.3 },
    { -0.3,  0.05, 0.15, 0.2,  0.2,  0.15, 0.05, -0.3 },
    { -0.3,  0.0,  0.1,  0.15, 0.15, 0.1,  0.0, -0.3 },
    { -0.4, -0.2,  0.0,  0.05, 0.05, 0.0, -0.2, -0.4 },
    { -0.5, -0.4, -0.3, -0.3, -0.3, -0.3, -0.4, -0.5 }
};
