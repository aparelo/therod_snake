#pragma once

#include <QtWidgets/QMainWindow>
#include <QRect>
#include <QGraphicsItem>

#include "ui_threod_snake.h"
#include <snake.h>
#include <apple.h>

class field : public QMainWindow
{
	Q_OBJECT;

public:
	field(QWidget *parent = Q_NULLPTR);

protected:
	void timerEvent(QTimerEvent *);
	void keyPressEvent(QKeyEvent *);
	bool eventFilter(QObject* obj, QEvent* event);

private:

	static const int DELAY = 140;

	Ui::threod_snakeClass ui;
	QGraphicsScene* scene = new QGraphicsScene(this);

	snake snake_1 = snake(3, 10);

	apple apple1 = apple(1,1,1,1);

	QGraphicsItem* game_over_text;

	QLine leftEdge;
	QLine rightEdge;
	QLine topEdge;
	QLine bottomEdge;

	QString message;
	

	int timerId;
	bool playing;

	
	int score = 0;

	int fieldHeight = 0;
	int fieldWidth = 0;

	int minWidth = 0;
	int minHeight = 0;

	void checkCollision();
	void drawSnake(int x, int y);
	void gameOver();
	void drawApple();
	void checkApple();
	void pauseGame();
	void initGame(bool firstGame);
};
