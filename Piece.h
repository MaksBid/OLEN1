#pragma once
#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <sstream>
class Board;
#define WHITE 1
#define BLACK 0
#define PAWN 'p'
#define KNIGHT 'n'
#define BISHOP 'b'
#define ROOK 'r'
#define QUEEN 'q'
#define KING 'k'
class Piece
{
private:
	char pieceType;
	int color;
	int row;
	int col;

	Board* myBoard;

	friend std::ostream& operator<<(std::ostream& os, const Piece& piece);
public:
	Piece();
	Piece(int row, int col, char pieceType, int color, Board* myBoard);

	char getPieceType() const;
	int getColor() const;
	int getRow() const;
	int getCol() const;
	Board* getBoard() const;

	void setPieceType(char);
	void setColor(int);
	void setRow(int);
	void setCol(int);
	void setMyBoard(Board* newBoard);
	void setPosition(int newRow, int newCol);

	std::vector<std::pair<int, int>> getMoves() const;
	bool checkMove(int newRow, int newCol) const;
};

