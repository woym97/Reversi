#pragma once
#include "ui_GameWindow.h"
#include "Header.h"
#include "Board.h"

/*
Class containing the main app window
*/

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = Q_NULLPTR);
    void setMainWindowHeader();
    void displayWinner(TileColor winner);

private:
    Ui::GameWindowClass ui;
    QLabel* label = new QLabel(this);
    QWidget* board_widget = new Board(this);
    QWidget* top_menu_widget = new QWidget(this);
    Board* b{ dynamic_cast<Board*>(board_widget) };
    void setUpMenuBar();
};
