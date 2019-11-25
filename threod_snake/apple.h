#pragma once
#include <QGraphicsItem>
#include "snake.h"
class apple
{
public:
	apple(int minHeight, int minWidth, int maxHeight, int maxWidth);

	QRect rect;
	QGraphicsItem* graphics;

	int timer;

	void moveApple();
	void moveAppleBy(int dx, int dy, snake snake_1);
	void resetTimer();
private:
	int minFieldWidth;
	int minFieldHeight;

	int maxFieldWidth;
	int maxFieldHeight;
};

