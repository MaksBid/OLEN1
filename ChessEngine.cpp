#include "ChessEngine.h"

ChessEngine::ChessEngine()
{
	myColor = 0;
}

ChessEngine::ChessEngine(int color)
{
	myColor = color;
}

ChessEngine::~ChessEngine()
{
}

std::pair<std::pair<int, int>, std::pair<int, int>> ChessEngine::bestMove(Board* board)
{
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> myLegalMoves = board->generateLegalMoves(),
		opponentLegalMoves;
	std::vector<double> evaluations(myLegalMoves.size());
	int bestMoveIndex = 0;

	for (int i = 0; i < myLegalMoves.size(); i++) {
		Board tempBoard = *board;
		tempBoard.movePiece(myLegalMoves[i].first.first, myLegalMoves[i].first.second, myLegalMoves[i].second.first, myLegalMoves[i].second.second);
		evaluations[i] = evaluateBoard(&tempBoard);
		opponentLegalMoves = tempBoard.generateLegalMoves(); // For every move, generate the opponent's legal moves
		
		for (int j = 0; j < opponentLegalMoves.size(); j++) {
			Board tempBoard2 = tempBoard;
			tempBoard2.movePiece(opponentLegalMoves[j].first.first, opponentLegalMoves[j].first.second, opponentLegalMoves[j].second.first, opponentLegalMoves[j].second.second);
			double positionEval = evaluateBoard(&tempBoard2);

			if (j == 0) {
				evaluations[i] = positionEval;
			}

			if (myColor == 0) {
				if (positionEval > evaluations[i]) { // If we found a better move that the opponent can make
					evaluations[i] = positionEval; // Assign new evaluation (if we are black it means the greater the eval, the better for opponent
				}
			}
			else {
				if (positionEval < evaluations[i]) {
					evaluations[i] = positionEval;
				}
			}
		}
	}

	for (int i = 0; i < evaluations.size(); i++) { // Finding best evaluation with respect to the color
		/*std::cout << "Move: " << char(myLegalMoves[i].first.second + 'a') << 8 - myLegalMoves[i].first.first << " " 
							  << char(myLegalMoves[i].second.second + 'a') << 8 - myLegalMoves[i].second.first << 
			" Eval: " << evaluations[i] << std::endl;*/
		if (myColor == 0) {
			if (evaluations[i] < evaluations[bestMoveIndex]) {
				bestMoveIndex = i;
			}
		} 
		else {
			if (evaluations[i] > evaluations[bestMoveIndex]) {
				bestMoveIndex = i;
			}
		}
	}

	return myLegalMoves[bestMoveIndex];
}

double ChessEngine::evaluateBoard(Board* board) const
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	double evaluation = 0;
	if (board->checkForCheckmate(1)) {
		return -1000;
	}
	else if (board->checkForCheckmate(0)) {
		return 1000;
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int color = (*board)[i][j].getColor();
			if (color == -1) continue;
			color == 0 ? color = -1 : color = 1; // Set the multiplier to -1 for black and 1 for white

			switch ((*board)[i][j].getPieceType())
			{
			case PAWN:
				evaluation += (1 + weights[i][j] * 0.2) * color;
				break;
			case KNIGHT:
				evaluation += (3 + weights[i][j]) * color;
				break;
			case BISHOP:
				evaluation += (3 + weights[i][j]) * color;
				break;
			case ROOK:
				evaluation += 5 * color;
				break;
			case QUEEN:
				evaluation += 9 * color;
				break;
			case KING:
				// The king's value is not added to the evaluation because it is not possible to capture the king
				break;
			default:
				break;
			}
		}
	}
	int random_number = ((std::rand() % 100) / 1000) - 0.05;
	return evaluation + random_number;
}
