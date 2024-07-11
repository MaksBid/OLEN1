#include "Board.h"

Board::Board()
{
	board[0][0] = Piece(0, 0, ROOK, BLACK, this);
	board[0][1] = Piece(0, 1, KNIGHT, BLACK, this);
	board[0][2] = Piece(0, 2, BISHOP, BLACK, this);
	board[0][3] = Piece(0, 3, QUEEN, BLACK, this);
	board[0][4] = Piece(0, 4, KING, BLACK, this);
	board[0][5] = Piece(0, 5, BISHOP, BLACK, this);
	board[0][6] = Piece(0, 6, KNIGHT, BLACK, this);
	board[0][7] = Piece(0, 7, ROOK, BLACK, this);
	for (int i = 0; i < 8; i++) {
		board[1][i] = Piece(1, i, PAWN, BLACK, this);
	}
	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = Piece(i, j, ' ', -1, this);
		}
	}
	for (int i = 0; i < 8; i++) {
		board[6][i] = Piece(6, i, PAWN, WHITE, this);
	}
	board[7][0] = Piece(7, 0, ROOK, WHITE, this);
	board[7][1] = Piece(7, 1, KNIGHT, WHITE, this);
	board[7][2] = Piece(7, 2, BISHOP, WHITE, this);
	board[7][3] = Piece(7, 3, QUEEN, WHITE, this);
	board[7][4] = Piece(7, 4, KING, WHITE, this);
	board[7][5] = Piece(7, 5, BISHOP, WHITE, this);
	board[7][6] = Piece(7, 6, KNIGHT, WHITE, this);
	board[7][7] = Piece(7, 7, ROOK, WHITE, this);
}

Board::Board(const Board& other)
{
	whiteTurn = other.whiteTurn;
	castlingRights = other.castlingRights;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = other.board[i][j];
			board[i][j].setMyBoard(this);
		}
	}
}

Board::~Board()
{
}

Piece Board::getPiece(int row, int col) const
{
	return board[row][col];
}

void Board::setPiece(int row, int col, Piece piece)
{
	board[row][col] = piece;
}

void Board::printBoard() const
{
	for (int i = 0; i < 8; i++)	{
		std::cout << 8 - i << "  ";
		for (int j = 0; j < 8; j++)
			std::cout << board[i][j] << " ";
		std::cout << std::endl;
	}
	//std::cout << "   a  b  c  d  e  f  g  h" << std::endl;
}

bool Board::isWhiteTurn() const
{
	return whiteTurn;
}

std::pair<int, int> Board::getKingPosition(int color) const
{
	std::pair<int, int> kingPosition = std::make_pair(-1, -1);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j].getPieceType() == KING && board[i][j].getColor() == color) {
				kingPosition = std::make_pair(i, j);
				break;
			}
		}
	}
	return kingPosition;
}

void Board::changeTurn()
{
	whiteTurn = !whiteTurn;
}

uint8_t Board::getCastlingRights() const
{
	return castlingRights;
}

std::pair<int, int> Board::getEnPassantSquare() const
{
	return enPassantSquare;
}

void Board::clearBoard()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = Piece(i, j, ' ', -1, this);
		}
	}
}

bool Board::checkForCheckmate(int color)
{
	if (!checkForCheck(color)) return false;

	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> legalMoves = generateLegalMoves();

	if (legalMoves.size() == 0) {
		return true;
	}

	return false;
}

bool Board::checkForCheck(int color)
{
	std::pair<int, int> kingPosition = getKingPosition(color);
	int kingRow = kingPosition.first;
	int kingCol = kingPosition.second;
	if (kingRow == -1 || kingCol == -1) {
		std::cerr << "King not found." << std::endl;
		return false;
	}

	for (int i = 0; i < 8; i++) { // Checking for checks
		for (int j = 0; j < 8; j++) {
			if (board[i][j].getColor() != color && board[i][j].getColor() != -1) {
				if (board[i][j].checkMove(kingRow, kingCol)) {
					return true;
				}
			}
		}
	}

	return false;
}

bool Board::movePiece(int startRow, int startCol, int endRow, int endCol)
{
	if (board[startRow][startCol].checkMove(endRow, endCol)) {
		// Creating temporary board with the move already made to check if our king is attacked
		Board tempBoard = *this;

		tempBoard.board[endRow][endCol] = tempBoard.board[startRow][startCol]; // Moving the piece
		tempBoard.board[endRow][endCol].setPosition(endRow, endCol); // Updating the position of the piece
		tempBoard.board[startRow][startCol] = Piece(startRow, startCol, ' ', -1, this); // Clearing the starting square

		// If castling then move the rook too
		if (board[startRow][startCol].getPieceType() == KING && abs(startCol - endCol) == 2) {
			if (endCol == 2) { // Queen side castling
				tempBoard.board[startRow][3] = tempBoard.board[startRow][0];
				tempBoard.board[startRow][3].setPosition(startRow, 3);
				tempBoard.board[startRow][0] = Piece(startRow, 0, ' ', -1, this);
			}
			else if (endCol == 6) { // King side castling
				tempBoard.board[startRow][5] = tempBoard.board[startRow][7];
				tempBoard.board[startRow][5].setPosition(startRow, 5);
				tempBoard.board[startRow][7] = Piece(startRow, 7, ' ', -1, this);
			}
		}
		if (board[startRow][startCol].getPieceType() == PAWN) { // Remove the pawn if en passant
			if (endRow == enPassantSquare.first && endCol == enPassantSquare.second) {
				tempBoard.board[startRow][endCol] = Piece(startRow, endCol, ' ', -1, this);
			}
		}

		if (tempBoard.checkForCheck(board[startRow][startCol].getColor())) {
			return false;
		}

		char movedPieceType = board[startRow][startCol].getPieceType();

		board[endRow][endCol] = board[startRow][startCol]; // Moving the piece
		board[endRow][endCol].setPosition(endRow, endCol); // Updating the position of the piece
		board[startRow][startCol] = Piece(startRow, startCol, ' ', -1, this); // Clearing the starting square
		// If castling then move the rook too
		if (movedPieceType == KING && abs(startCol - endCol) == 2) {
			if (endCol == 2) { // Queen side castling
				board[startRow][3] = board[startRow][0];
				board[startRow][3].setPosition(startRow, 3);
				board[startRow][0] = Piece(startRow, 0, ' ', -1, this);
			}
			else if (endCol == 6) { // King side castling
				board[startRow][5] = board[startRow][7];
				board[startRow][5].setPosition(startRow, 5);
				board[startRow][7] = Piece(startRow, 7, ' ', -1, this);
			}
		}
		if (movedPieceType == PAWN) { // Remove the pawn if en passant
			if (endRow == enPassantSquare.first && endCol == enPassantSquare.second) {
				board[startRow][endCol] = Piece(startRow, endCol, ' ', -1, this);
			}
		}
		enPassantSquare = std::make_pair(-1, -1); // If a move is made, en passant is no longer available

		if (movedPieceType == ROOK && // If rook moved, adjust castling var 
			(startRow == 0 || startRow == 7) && 
			(startCol == 0 || startCol == 7)) 
		{
			if (startRow == 0 && startCol == 0) { // a8 black rook
				castlingRights &= 14; // 1110
			}
			else if (startRow == 0 && startCol == 7) { // h8 black rook
				castlingRights &= 13; // 1101
			}
			else if (startRow == 7 && startCol == 0) { // a1 white rook
				castlingRights &= 11; // 1011
			}
			else if (startRow == 7 && startCol == 7) { // h1 white rook
				castlingRights &= 7; // 0111
			}
		}
		else if ((movedPieceType == KING) &&
			(startRow == 0 || startRow == 7) && 
			(startCol == 4)) 
		{
			if (startRow == 0) {
				castlingRights &= 12; // 1100, white king moved, no white castling
			}
			else if (startRow == 7) {
				castlingRights &= 3; // 0011, black king moved, no black castling
			}
		}
		else if (movedPieceType == PAWN) {
			if (endRow == 0 || endRow == 7) {
				board[endRow][endCol].setPieceType(QUEEN);
			} // If moved two tiles, set en passant as available
			else if (abs(endRow - startRow) == 2) {
				enPassantSquare = std::make_pair((startRow + endRow) / 2, startCol);
			}
		}
		
		changeTurn();
		
		return true;
	}
	else {
		return false;
	}
}

std::vector<std::pair<std::pair<int, int>, std::pair<int,int>>> Board::generateLegalMoves() const
{
	std::vector< // A vector
		std::pair<std::pair<int,int>, std::pair<int,int>> // Basically 2x2 matrix
	> legalMoves, pseudoLegalMoves;
	for (int i = 0; i < 8; i++) { // Get all possible moves for all pieces of our color
		for (int j = 0; j < 8; j++) {
			if (board[i][j].getColor() == -1) continue; // If there is no piece on the square
			if (board[i][j].getColor() != whiteTurn) continue; // If the piece is not the same color as the player's turn
			std::vector<std::pair<int, int>> moves = board[i][j].getMoves(); // Get all moves for the piece
			for (int k = 0; k < moves.size(); k++) { // For every received move, add it to the list: <from<row,col>, to<row,col>>
				pseudoLegalMoves.push_back(std::make_pair(std::make_pair(i, j), moves[k])); // Add the move to the list
			}
		}
	}

	for (int i = 0; i < pseudoLegalMoves.size(); i++) { // For every pseudo legal move, check if it is legal
		Board tempBoard = *this;
		int startRow = pseudoLegalMoves[i].first.first;
		int startCol = pseudoLegalMoves[i].first.second;
		int endRow = pseudoLegalMoves[i].second.first;
		int endCol = pseudoLegalMoves[i].second.second;

		if (tempBoard.movePiece(startRow, startCol, endRow, endCol)) {
			legalMoves.push_back(pseudoLegalMoves[i]);
		}
	}

	return legalMoves;
}

Piece* Board::operator[](int index)
{
	if (index < 0 || index > 7) {
		std::cerr << "Index out of range." << std::endl;
		return nullptr;
	}
	return board[index];
}
