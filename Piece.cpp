#include "Piece.h"
#include "Board.h"

Piece::Piece()
{
	row = 0;
	col = 0;
	pieceType = ' ';
	color = WHITE;
	myBoard = NULL;
}

Piece::Piece(int row, int col, char pieceType, int color, Board* newBoard) : row(row), col(col), pieceType(pieceType), color(color)
{
	myBoard = newBoard;
}

Piece::Piece(const Piece& other)
{
	row = other.row;
	col = other.col;
	pieceType = other.pieceType;
	color = other.color;
	myBoard = other.myBoard;
}

Piece& Piece::operator=(const Piece& other)
{
	if (this != &other) {
		pieceType = other.pieceType;
		color = other.color;
		row = other.row;
		col = other.col;
		myBoard = other.myBoard;
	}
	return *this;
}

char Piece::getPieceType() const
{
	return pieceType;
}

int Piece::getColor() const
{
	return color;
}

int Piece::getRow() const
{
	return row;
}

int Piece::getCol() const
{
	return col;
}

Board* Piece::getBoard() const
{
	return myBoard;
}

void Piece::setPieceType(char newType)
{
	pieceType = newType;
}

void Piece::setColor(int newColor)
{
	color = newColor;
}

void Piece::setRow(int newRow)
{
	row = newRow;
}

void Piece::setCol(int newCol)
{
	col = newCol;
}

void Piece::setMyBoard(Board* newBoard)
{
	myBoard = newBoard;
}

void Piece::setPosition(int newRow, int newCol)
{
	row = newRow;
	col = newCol;
}

std::vector<std::pair<int, int>> Piece::getMoves() const
{
	static const int bishopDirections[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	static const int rookDirections[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
	static const int knightMoves[8][2] = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2} };
	static const int kingMoves[8][2] = { {1, 0}, {1, 1}, {1, -1}, {-1, 0}, {-1, 1}, {-1, -1}, {0, 1}, {0, -1} };
	std::vector<std::pair<int, int>> moves;
	int i = 1;
	switch (tolower(pieceType)) {
	case PAWN:
		moves.push_back(std::make_pair(row + (color == WHITE ? -1 : 1), col)); // Normal move

		if ((row == 6 && color == WHITE) || (row == 1 && color == BLACK)) { // First move from 2nd or 7th rank
			moves.push_back(std::make_pair(row + (color == WHITE ? -2 : 2), col));
		}

		if (col + 1 < 8) {
			moves.push_back(std::make_pair(row + (color == WHITE ? -1 : 1), col + 1)); // Captures
		}
		if (col - 1 >= 0) {
			moves.push_back(std::make_pair(row + (color == WHITE ? -1 : 1), col - 1));
		}
		break;
	case KNIGHT:
		for (const auto& move : knightMoves) {
			int newRow = row + move[0], newCol = col + move[1];
			if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
				moves.emplace_back(newRow, newCol);
			}
		}


		/*if (row + 2 < 8) {
			if (col + 1 < 8)
				moves.push_back(std::make_pair(row + 2, col + 1));
			if (col - 1 >= 0)
				moves.push_back(std::make_pair(row + 2, col - 1));
		}
		if (row - 2 >= 0) {
			if (col + 1 < 8)
				moves.push_back(std::make_pair(row - 2, col + 1));
			if (col - 1 >= 0)
				moves.push_back(std::make_pair(row - 2, col - 1));
		}
		if (row + 1 < 8) {
			if (col + 2 < 8)
				moves.push_back(std::make_pair(row + 1, col + 2));
			if (col - 2 >= 0)
				moves.push_back(std::make_pair(row + 1, col - 2));
		}
		if (row - 1 >= 0) {
			if (col + 2 < 8)
				moves.push_back(std::make_pair(row - 1, col + 2));
			if (col - 2 >= 0)
				moves.push_back(std::make_pair(row - 1, col - 2));
		}*/


		/*moves.push_back(std::make_pair(row + 2, col + 1));
		moves.push_back(std::make_pair(row + 2, col - 1));
		moves.push_back(std::make_pair(row - 2, col + 1));
		moves.push_back(std::make_pair(row - 2, col - 1));
		moves.push_back(std::make_pair(row + 1, col + 2));
		moves.push_back(std::make_pair(row + 1, col - 2));
		moves.push_back(std::make_pair(row - 1, col + 2));
		moves.push_back(std::make_pair(row - 1, col - 2));*/
		break;
	case BISHOP:
		for (const auto& direction : bishopDirections) {
			int newRow = row + direction[0], newCol = col + direction[1];
			while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
				moves.emplace_back(newRow, newCol);
				if (myBoard->getPiece(newRow, newCol).getColor() != -1) {
					break;
				}
				newRow += direction[0];
				newCol += direction[1];
			}
		}
		break;
	case ROOK:
		for (const auto& direction : rookDirections) {
			int newRow = row + direction[0], newCol = col + direction[1];
			while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
				moves.emplace_back(newRow, newCol);
				if (myBoard->getPiece(newRow, newCol).getColor() != -1) {
					break;
				}
				newRow += direction[0];
				newCol += direction[1];
			}
		}
		break;
	case QUEEN:
		// Add queen moves
		/*for (int i = 1; i < 8; i++) {
			if (row + i < 8 && col + i < 8) {
				moves.push_back(std::make_pair(row + i, col + i));
			}
			if (row + i < 8 && col - i >= 0) {
				moves.push_back(std::make_pair(row + i, col - i));
			}
			if (row - i >= 0 && col + i < 8) {
				moves.push_back(std::make_pair(row - i, col + i));
			}
			if (row - i >= 0 && col - i >= 0) {
				moves.push_back(std::make_pair(row - i, col - i));
			}
			if (row + i < 8) {
				moves.push_back(std::make_pair(row + i, col));
			}
			if (row - i >= 0) {
				moves.push_back(std::make_pair(row - i, col));
			}
			if (col + i < 8) {
				moves.push_back(std::make_pair(row, col + i));
			}
			if (col - i >= 0) {
				moves.push_back(std::make_pair(row, col - i));
			}
		}*/
		for (const auto& direction : bishopDirections) {
			int newRow = row + direction[0], newCol = col + direction[1];
			while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
				moves.emplace_back(newRow, newCol);
				if (myBoard->getPiece(newRow, newCol).getColor() != -1) {
					break;
				}
				newRow += direction[0];
				newCol += direction[1];
			}
		}
		for (const auto& direction : rookDirections) {
			int newRow = row + direction[0], newCol = col + direction[1];
			while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
				moves.emplace_back(newRow, newCol);
				if (myBoard->getPiece(newRow, newCol).getColor() != -1) {
					break;
				}
				newRow += direction[0];
				newCol += direction[1];
			}
		}
		break;
	case KING:
		//moves.push_back(std::make_pair(row + 1, col));
		//moves.push_back(std::make_pair(row + 1, col + 1));
		//moves.push_back(std::make_pair(row + 1, col - 1));
		//moves.push_back(std::make_pair(row - 1, col));
		//moves.push_back(std::make_pair(row - 1, col + 1));
		//moves.push_back(std::make_pair(row - 1, col - 1));
		//moves.push_back(std::make_pair(row, col + 1));
		//moves.push_back(std::make_pair(row, col - 1));
		if (row + 1 < 8) {
			moves.push_back(std::make_pair(row + 1, col));
			if (col + 1 < 8)
				moves.push_back(std::make_pair(row + 1, col + 1));
			if (col - 1 >= 0)
				moves.push_back(std::make_pair(row + 1, col - 1));
		}
		if (row - 1 >= 0) {
			moves.push_back(std::make_pair(row - 1, col));
			if (col + 1 < 8)
				moves.push_back(std::make_pair(row - 1, col + 1));
			if (col - 1 >= 0)
				moves.push_back(std::make_pair(row - 1, col - 1));
		}
		if (col + 1 < 8)
			moves.push_back(std::make_pair(row, col + 1));
		if (col - 1 >= 0)
			moves.push_back(std::make_pair(row, col - 1));


		if (color == WHITE && row == 7 && col == 4) { // White king
			if (myBoard->getCastlingRights() & 8) moves.push_back(std::make_pair(7, 6)); // White kingside
			if (myBoard->getCastlingRights() & 4) moves.push_back(std::make_pair(7, 2)); // White queenside
		}
		else if (color == BLACK && row == 0 && col == 4) { // Black king
			if (myBoard->getCastlingRights() & 2) moves.push_back(std::make_pair(0, 6)); // Black kingside
			if (myBoard->getCastlingRights() & 1) moves.push_back(std::make_pair(0, 2)); // Black queenside
		}
		break;
	}
	return moves;
}

bool Piece::checkMove(int newRow, int newCol) const
{
	if (newRow < 0 || newRow > 7 || newCol < 0 || newCol > 7 || row == newRow && col == newCol) {
		return false;
	}

	if ((*myBoard)[newRow][newCol].getColor() == color) {
		return false;
	}

	switch (pieceType) {
	case PAWN:
		if (((*myBoard)[newRow][newCol].getColor() != -1) && col == newCol) {
			return false;
		}

		if (color == WHITE) {
			if ((newRow == row - 1 && newCol == col) || // Normal
				(newRow == row - 2 && row == 6 && newCol == col && (*myBoard)[5][newCol].getColor() == -1) || // First move from 2nd rank
				(newRow == row - 1 && abs(newCol - col) == 1 && ((*myBoard)[newRow][newCol].getColor() == BLACK || // Capture
					(newRow == myBoard->getEnPassantSquare().first && newCol == myBoard->getEnPassantSquare().second)))) // En passant handling
			{  
				return true; 
			}
			else {
				return false;
			}
		} 
		else if (color == BLACK) {
			if ((newRow == row + 1 && newCol == col) || // Normal
				(newRow == row + 2 && row == 1 && newCol == col && (*myBoard)[2][newCol].getColor() == -1) || // First move from 7th rank
				(newRow == row + 1 && abs(newCol - col) == 1 && ((*myBoard)[newRow][newCol].getColor() == WHITE || // And capture
					(newRow == myBoard->getEnPassantSquare().first && newCol == myBoard->getEnPassantSquare().second)))) // En passant handling
			{ 
				return true;
			}
			else {
				return false;
			}
		}
		break;

	case KNIGHT:
		if (abs(newRow - row) == 2 && abs(newCol - col) == 1 ||
			abs(newRow - row) == 1 && abs(newCol - col) == 2) {
			return true;
		}
		else {
			return false;
		}
		break;

	case BISHOP:
		if (abs(newRow - row) == abs(newCol - col)) {
			for (int i = 1; i < abs(newRow - row); i++) { // Check if there are any pieces in the way (getting sign by newCol - col)
				if ((*myBoard)[row + i * (newRow - row) / abs(newRow - row)][col + i * (newCol - col) / abs(newCol - col)].getColor() != -1) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
		break;

	case ROOK:
		if (newRow == row || newCol == col) {
			for (int i = 1; i < abs(newRow - row) + abs(newCol - col); i++) {
				if ((*myBoard)[row + i * (newRow - row) / (abs(newRow - row) + abs(newCol - col))][col + i * (newCol - col) / (abs(newRow - row) + abs(newCol - col))].getColor() != -1) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
		break;

	case QUEEN:
		if (abs(newRow - row) == abs(newCol - col) || newRow == row || newCol == col) {
			std::pair<int, int> direction = std::make_pair(
				(newRow > row) - (row > newRow), // Checking signs of the difference between the new and old row and column
				(newCol > col) - (col > newCol));
			for (int i = 1; i < std::max(abs(newRow - row), abs(newCol - col)); i++) {
				if ((*myBoard)[row + i * direction.first][col + i * direction.second].getColor() != -1) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
		break;

	case KING:
		if (abs(newRow - row) <= 1 && abs(newCol - col) <= 1) {
			return true;
		}
		else if ((newRow - row == 0) && abs(newCol - col) == 2) { // Castling
			if (color == WHITE) {
				if ((newCol == 6) && // white kingside
					(*myBoard)[7][7].getPieceType() == ROOK && // has to be a white rook
					(*myBoard)[7][7].getColor() == WHITE && 
					(*myBoard)[7][6].getPieceType() == ' ' && // two empty spaces in between
					(*myBoard)[7][5].getPieceType() == ' ' && 
					(myBoard->getCastlingRights() & 8)) // and the right to castle (bin 1000)
				{
					return true;
				}
				else if ((newCol == 2) && // white queenside
					(*myBoard)[7][0].getPieceType() == ROOK && // same for queenside
					(*myBoard)[7][0].getColor() == WHITE && 
					(*myBoard)[7][1].getPieceType() == ' ' && 
					(*myBoard)[7][2].getPieceType() == ' ' && 
					(*myBoard)[7][3].getPieceType() == ' ' &&
					(myBoard->getCastlingRights() & 4)) // bin 0100
				{
					return true;
				}
				else {
					return false;
				}
			}
			else if (color == BLACK) {
				if ((newCol == 6) && // black kingside
					(*myBoard)[0][7].getPieceType() == ROOK && // has to be a black rook
					(*myBoard)[0][7].getColor() == BLACK &&
					(*myBoard)[0][6].getPieceType() == ' ' && // two empty spaces in between
					(*myBoard)[0][5].getPieceType() == ' ' &&
					(myBoard->getCastlingRights() & 2)) // and the right to castle (bin 0010)
				{
					return true;
				}
				else if ((newCol == 2) && // black queenside
					(*myBoard)[0][0].getPieceType() == ROOK && // same for queenside
					(*myBoard)[0][0].getColor() == BLACK &&
					(*myBoard)[0][1].getPieceType() == ' ' &&
					(*myBoard)[0][2].getPieceType() == ' ' &&
					(*myBoard)[0][3].getPieceType() == ' ' &&
					(myBoard->getCastlingRights() & 1)) // bin 0001
				{
					return true;
				}
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}
		break;
	default:
		return false;
		break;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const Piece& piece)
{
	os << (piece.color ? static_cast<char>(toupper(piece.pieceType)) : static_cast<char>(piece.pieceType)) << " ";
	return os;
}

