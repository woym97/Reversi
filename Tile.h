#pragma once

#include <QPushButton>
#include "Header.h"
#include "Board.h"

/*
Class representing the tiles of the board
*/

class Tile : public QPushButton
{
	Q_OBJECT

public:
	Tile(int x, int y, Board *parent = Q_NULLPTR);
	Coord coord;
	TileColor state{ TileColor::empty };
	void setLight();
	void setDark();

public slots:
	void t_clicked();

private:
	const int t_size{ 60 };

};
