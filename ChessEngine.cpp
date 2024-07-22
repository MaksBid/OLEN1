#include "ChessEngine.h"

void ChessEngine::logAction(const std::string& message)
{
	std::ofstream logFile("log.txt", std::ios_base::app); // Open in append mode
	if (logFile.is_open())
	{
		logFile << message << std::endl;
	}
}

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
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> myLegalMoves = board->generateLegalMoves();
	std::vector<double> evaluations(myLegalMoves.size());
	int bestMoveIndex = 0;
	double alpha = -1000, beta = 1000;

	for (int i = 0; i < myLegalMoves.size(); i++) {
		Board tempBoard = *board;
		tempBoard.movePiece(myLegalMoves[i].first.first, myLegalMoves[i].first.second, myLegalMoves[i].second.first, myLegalMoves[i].second.second);
		evaluations[i] = minimax(&tempBoard, depth, &alpha, &beta, tempBoard.isWhiteTurn()); // Here we pass depth of the search (currently 2)
	}

	for (int i = 0; i < evaluations.size(); i++) { // Finding best evaluation with respect to the color
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

double ChessEngine::minimax(Board* board, int depth, double* alpha, double* beta, bool maximizingPlayer)
{
	if (depth == 0) {
		
		return evaluateBoard(board);
	}
	Board tempBoard = *board;
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> legalMoves = tempBoard.generateLegalMoves();

	if (maximizingPlayer == WHITE) {
		double maxEval = -1000;
		for (int i = 0; i < legalMoves.size(); i++) {
			double eval;
			bool notCheck;
			Board tempBoard2 = tempBoard;
			if (tempBoard2.checkForCheck(WHITE)) { // If a piece is captured, do not subtract depth
				notCheck = 0;
			}
			else {
				notCheck = 1;
			}
			tempBoard2.movePiece(legalMoves[i].first.first, legalMoves[i].first.second, legalMoves[i].second.first, legalMoves[i].second.second);
			eval = minimax(&tempBoard2, depth - notCheck, alpha, beta, BLACK);
			maxEval = std::max(maxEval, eval);
			*alpha = std::max(*alpha, eval);
			if (beta <= alpha) {
				break;
			}
		}
		return maxEval;
	}
	else {
		double minEval = 1000;
		for (int i = 0; i < legalMoves.size(); i++) {
			double eval;
			int notCheck;
			Board tempBoard2 = tempBoard;
			if (tempBoard2.checkForCheck(BLACK)) { // If a piece is captured, do not subtract depth
				notCheck = 0;
			}
			else {
				notCheck = 1;
			}
			tempBoard2.movePiece(legalMoves[i].first.first, legalMoves[i].first.second, legalMoves[i].second.first, legalMoves[i].second.second);
			eval = minimax(&tempBoard2, depth - notCheck, alpha, beta, WHITE);
			minEval = std::min(minEval, eval);
			*beta = std::min(*beta, eval);
			if (beta <= alpha) {
				break;
			}
		}
		return minEval;
	}
}

double ChessEngine::evaluateBoard(Board* board) const
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	double evaluation = 0;
	if (board->checkForCheckmate(WHITE)) {
		return -1000;
	}
	else if (board->checkForCheckmate(BLACK)) {
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
	int random_number = ((std::rand() % 100) / 1000) - 0.05; // Add a random number between -0.05 and 0.05
	return evaluation + random_number;
}
