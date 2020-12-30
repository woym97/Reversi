#pragma once
#include "Header.h"

/*
Class representing the main board in the window
*/

class Board : public QWidget
{
	Q_OBJECT;

public:
	Board(QWidget* parent = Q_NULLPTR);
	// Create a new layout object for the board
	QGridLayout* layout = new QGridLayout;
	bool gameComplete();
	// Tracks current turn
	TileColor cur_player = TileColor::light;
	bool moveInitiated(Coord& coord);
	int moves_left = (B_DIM + 1) ^ 2;		// Keeps track of how many moves are left to be played

public slots:
	void getWinner();

private:
	void setFormat();
	void addTiles();
	void addStartingPieces();
	void swapTurn();
	TileColor getColorAtCoord(Coord& coord);
	Coord getAnchorPiece(Coord& coord, Direction dir);	// Gets the corresponding anchor piece for the direction given
	bool capturePieces(Coord& start, Coord& end, Direction dir);
	void setPiece(Coord& coord);
};

