#pragma once
#include <QGraphicsItem>
class apple
{
public:
	apple(int minHeight, int minWidth, int maxHeight, int maxWidth);

	QRect rect;
	QGraphicsItem* graphics;

	int timer;

	void moveApple();
	void resetTimer();
private:
	int minFieldWidth;
	int minFieldHeight;

	int maxFieldWidth;
	int maxFieldHeight;
};

