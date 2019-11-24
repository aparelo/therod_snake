#pragma once
#include <QRect>
#include <QGraphicsItem>
class snake
{
public:
	snake(int len, int spd);
	int length;


	QRect head = QRect(0, 0, 0, 0);
	QRect body[20000];

	QGraphicsItem *snake_head;
	QGraphicsItem *snake_body[20000];

	int direction[2] = { 0, -1 };
	int speed;

	void moveSnake(int x, int y);
	void jumpSnake(int x, int y);
	void addLength(int l);
private:
	

};

