#pragma once
#include <QPushButton>
#include <QtWidgets/QMainWindow>
#include <iostream>
#include <QLayout>
#include <sstream>
#include <QLabel>
#include <QMessageBox>

enum class Direction {
    north, east, south, west, north_east, south_east, south_west, north_west
};

struct Coord {
    /* Represents the coordinates of a space on the board */

    int x;
    int y;

    Coord() {
        x = -1;
        y = -1;
    }

    Coord(int &x_coord, int &y_coord) { 
        x = x_coord;
        y = y_coord;
    }

    void setNew(int& x_coord, int& y_coord) {
        x = x_coord;
        y = y_coord;
    }

    void adoptCoords(Coord coord) {
        x = coord.x;
        y = coord.y;
    }

    void moveCoord(Direction dir) {
        // Move coordinate in the given direction
        switch (dir) {
        case Direction::north:
            x = x - 1;
            y = y;
            break;
        case Direction::east:
            x = x;
            y = y + 1;
            break;
        case Direction::south:
            x = x + 1;
            y = y ;
            break;
        case Direction::west:
            x = x;
            y = y - 1;
            break;
        case Direction::north_east:
            x = x - 1;
            y = y - 1;
            break;
        case Direction::north_west:
            x = x - 1;
            y = y + 1;
            break;
        case Direction::south_east:
            x = x + 1;
            y = y + 1;
            break;
        case Direction::south_west:
            x = x + 1;
            y = y - 1;
            break;
        }
    }

    bool operator!=(Coord &other) {
        return (other.x != x || other.y != y);
    }
};

enum class TileColor {
// Gives the tiles color 
    light, empty, dark
};

// Dimension of the board
const int B_DIM = 7;