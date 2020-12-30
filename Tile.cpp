#include "Tile.h"
#include "Board.h"

Tile::Tile(int x, int y, Board* parent)	: QPushButton(parent)
{
	/* Construct empty tile with coordinates */
	connect(this, SIGNAL(clicked()), this, SLOT(t_clicked())); // Connect button to action
	coord = Coord{ x, y };
	setFixedSize(t_size, t_size);
	setStyleSheet("QPushButton{ background-color: #006600 }");
	setParent(parent);
}

void Tile::setLight()
{
	/* Set the style of the tile to light and change the state */
	state = TileColor::light;
	setStyleSheet("QPushButton{ background-color: white; border: 2px white; border-radius: 30px}");
}

void Tile::setDark()
{
	/* Set the style of the tile to dark and change the state */
	state = TileColor::dark;
	setStyleSheet("QPushButton{ background-color: black; border: 2px black; border-radius: 30px}");
}

void Tile::t_clicked()
{
	/* Main tile action */

	if (state != TileColor::empty) {	// If the space was not empty then break out
		return;
	}
	bool move_success{ dynamic_cast<Board*>(parent())->moveInitiated(coord) };
}

