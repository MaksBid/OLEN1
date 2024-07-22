#pragma once
#include "Piece.h"
class Board
{
private:
	Piece board[8][8];
	bool whiteTurn = true;
	uint8_t castlingRights = 15; // 00001111, 1st bit white king side, 2nd wQ, 3rd bK, 4th bQ
	std::pair<int, int> enPassantSquare = std::make_pair(-1, -1); // If there is no en passant square, it is (-1, -1)
	bool lastMoveCastling = false;
	bool lastMoveEnPassant = false;

	void logAction(const std::string&) const;
public:
	Board();
	Board(std::string fen);
	Board(const Board& other);
	~Board();

	Piece getPiece(int row, int col) const;
	void setPiece(int row, int col, Piece piece);

	void printBoard() const;
	std::string toString() const;
	void clearBoard();

	void changeTurn();

	bool isWhiteTurn() const;
	std::pair<int, int> getKingPosition(int color) const;
	uint8_t getCastlingRights() const;
	std::pair<int, int> getEnPassantSquare() const;
	
	bool checkForCheckmate(int color);
	bool checkForCheck(int color);
	bool movePiece(int startRow, int startCol, int endRow, int endCol);
	void unMovePiece(int startRow, int startCol, int endRow, int endCol, Piece capturedPiece/*, bool isCastling, bool isEnPassant*/);

	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> generateLegalMoves() const;

	Piece* operator[](int index);
	Board& operator=(const Board& other);
};

