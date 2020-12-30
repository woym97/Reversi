#pragma once
#include "Board.h"
#include "Tile.h"
#include "GameWindow.h"

Board::Board(QWidget* parent) :QWidget(parent)
// Main constructor
{
	setFormat();
	addTiles();
	addStartingPieces();
	setParent(parent);
	show();
	std::cout << "Board Initialized" << std::endl;
}

void Board::setFormat()
{
	QPalette pal = palette();
	pal.setColor(QPalette::Background, "#004d00");
	setAutoFillBackground(true);
	setPalette(pal);
}

void Board::addTiles()
{
	// Add tiles to the board
	for (int x = 0; x <= B_DIM; x++) {						// Loop through all the rows
		for (int y = 0; y <= B_DIM; y++) {					// Loop through all the columns
			QPushButton *tile_temp = new Tile(x, y, this);
			layout->addWidget(tile_temp, x, y);			// Add the tile to the layout
		}
	}
	// Set spacing of the grid
	int space{ 3 };
	layout->setHorizontalSpacing(space);			
	layout->setVerticalSpacing(space);
	layout->setSizeConstraint(QLayout::SetFixedSize);
	// Apply the layout to the widget
	setLayout(layout);
}

void Board::addStartingPieces()
{
	dynamic_cast<Tile*>(layout->itemAtPosition(3, 3)->widget())->setLight();
	dynamic_cast<Tile*>(layout->itemAtPosition(4, 4)->widget())->setLight();
	dynamic_cast<Tile*>(layout->itemAtPosition(4, 3)->widget())->setDark();
	dynamic_cast<Tile*>(layout->itemAtPosition(3, 4)->widget())->setDark();
}

bool Board::gameComplete()
{
	if (moves_left > 0) {
		return false;
	}
	else {
		return true;
	}
}

void Board::swapTurn() {
	// Swaps the current players turn
	if (cur_player == TileColor::light) {
		cur_player = TileColor::dark;
	}
	else {
		cur_player = TileColor::light;
	}
}

TileColor Board::getColorAtCoord(Coord &coord)
{
	// Returns the tile color at a given coordinate
	auto* temp{ dynamic_cast<Tile*>(layout->itemAtPosition(coord.x, coord.y)->widget()) };	
	return temp->state;
}

Coord Board::getAnchorPiece(Coord& coord, Direction dir)
{
	/*Gets the corresponding anchor piece for the passed coordinate and given direction
	If no valid anchor piece is found then return the original coordinate */
	
	Coord anchor{ coord }; // Create original anchor by copying original coord

	// Create first temp coordinate and init color holder
	Coord temp{ anchor };
	temp.moveCoord(dir);
	TileColor c_temp{};

	// Loop through all pieces in given direction until end of board
	while (temp.x <= B_DIM && temp.y <= B_DIM) {

		c_temp = getColorAtCoord(temp);		// Grab the color

		if (c_temp == TileColor::empty) {	// If empty then the previous anchor is the one to return
			break;
		}
		else if (c_temp == cur_player) {	// If same color as player then this is the anchor
			anchor.setNew(temp.x, temp.y);
			break;
		}
		else {								// Else keep searching 
			temp.moveCoord(dir);
		}
	}
	return anchor;
}

bool Board::capturePieces(Coord& start, Coord& end, Direction dir)
{
	Coord temp{ start };
	temp.moveCoord(dir);
	bool captured_piece{ false };
	while (true) {
		if (temp != end) {
			// Capture the piece
			setPiece(temp);
			temp.moveCoord(dir);
			captured_piece = true;
		}
		else {
			break;
		};
	};
	return captured_piece;
}

void Board::setPiece(Coord& coord)
{
	// Capture piece at given coord, switching it to the current active color
	auto* temp_tile{ dynamic_cast<Tile*>(layout->itemAtPosition(coord.x, coord.y)->widget()) };
	switch (cur_player) {
	case TileColor::dark:
		temp_tile->setDark();
		break;
	case TileColor::light:
		temp_tile->setLight();
		break;
	}
}

bool Board::moveInitiated(Coord& coord)
{
	// Returns true if move was successful, otherwise false
	
	bool valid_turn{ false };
	Coord anchor{coord};
	Direction dir{};

	for (int i = 0; i < 7; i++)
		// Loop through all possible directions
	{
		dir = (Direction)i;
		anchor.adoptCoords(getAnchorPiece(anchor, dir));	// Get the anchor piece for that direction
		if (anchor != coord) {								// If the anchor piece is not the original piece anchor.x != coord.x && anchor.y != coord.y
			if (capturePieces(coord, anchor, dir)) {
				valid_turn = true;							// Capture the pieces in between, if successful then mark a valid turn
			};				
		};
		anchor.adoptCoords(coord);							// Reset the anchor for the next call
	}

	if (valid_turn) {										// Check the valid turn flag
		setPiece(coord);									// Set original piece
		swapTurn();											// Swap turns 
		dynamic_cast<GameWindow*>(parent())->setMainWindowHeader();
		--moves_left;
		return true;
	}
	else {
		return false;
	}

}

void Board::getWinner()
{
	/* Returns the winner of the game */
	int dark_count{ 0 };
	int light_count{ 0 };
	TileColor color{ TileColor::empty };
	for (int x = 0; x <= B_DIM; x++) {						// Loop through all the rows
		for (int y = 0; y <= B_DIM; y++) {					// Loop through all the columns
			color = getColorAtCoord(Coord{ x, y });			// Get the tiles color
			// Inc counter respectively
			if (color == TileColor::dark) {
				++dark_count;
			}
			else if (color == TileColor::light) {
				++light_count;
				}
		}
	}
	// Return the winner to the caller
	if (dark_count > light_count) {
		dynamic_cast<GameWindow*>(parent())->displayWinner(TileColor::dark);
	}
	else if (dark_count == light_count) {
		dynamic_cast<GameWindow*>(parent())->displayWinner(TileColor::empty);
	}
	else {
		dynamic_cast<GameWindow*>(parent())->displayWinner(TileColor::light);
	}
	
}
