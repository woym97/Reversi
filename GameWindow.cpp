#pragma once
#include "GameWindow.h"
#include "Board.h"
#include "Tile.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowTitle("Reversi");

    setCentralWidget(board_widget);     // Set up board widget

    setUpMenuBar();

    resize(100, 100);
}

void GameWindow::setMainWindowHeader()
{
    /* Called each time a successful turn is taken */

    QString turn{};
    switch (b->cur_player) {
    case TileColor::dark:
        turn = "Dark's Turn";
        break;
    case TileColor::light:
        turn = "Light's Turn";
        break;
    }
    label->setText("Reversi\n" + turn);
}

void GameWindow::displayWinner(TileColor winner)
{
    // Set up label widget
    QString winn{};
    switch (winner) {
    case TileColor::dark:
        winn = "Dark Wins!!";
        break;
    case TileColor::light:
        winn = "Light Wins!!";
        break;
    case TileColor::empty:
        winn = "It's a Tie!!";
        break;
    }
    QMessageBox msgBox;
    msgBox.setText(winn);
    msgBox.exec();
}

void GameWindow::setUpMenuBar()
{
    QGridLayout* top_menu_layout = new QGridLayout;

    // Set up label
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    QFont f("Consolas", 14, QFont::Bold);
    label->setFont(f);
    label->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    label->setText("Welcome to Reversi!\nLight's Turn");
    label->setFixedSize(300, 50);
    label->setStyleSheet("QLabel{ background-color: Black; color : white;}");

    // Set up abort game button
    QPushButton* abort_game_btn = new QPushButton(this);    
    connect(abort_game_btn, SIGNAL(clicked()), b, SLOT(getWinner())); // Connect button to action
    abort_game_btn->setText("End Current Game");
    abort_game_btn->setStyleSheet("QPushButton{ background-color: darkred; color : white;}");
    abort_game_btn->setFont(f);

    // Add components to menu
    top_menu_layout->addWidget(abort_game_btn, 0, 2);
    top_menu_layout->addWidget(label, 0, 1);

    // Set spacing of the grid
    int space{ 3 };
    top_menu_layout->setHorizontalSpacing(space);
    top_menu_layout->setVerticalSpacing(space);
    top_menu_layout->setSizeConstraint(QLayout::SetFixedSize);
    top_menu_widget->setLayout(top_menu_layout);

    setMenuWidget(top_menu_widget);
}
