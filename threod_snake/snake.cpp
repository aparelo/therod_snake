#include "snake.h"

snake::snake(int len, int spd) {
	//set up the snake body as a rectangle
	length = len;
	speed = spd;

	for (int i=0; i < length; i++) {
		body[i] = QRect();
		int headX = head.left();
		int headY = head.top();
		body[i].moveTo(headX, headY - 10 * (i + 1));
		body[i].setWidth(0);
		body[i].setHeight(0);
	}
}

void snake::moveSnake(int x, int y) {
	//save current head pos
	int headX = head.left();
	int headY = head.top();

	//move head to new pos
	head.moveTo(x, y);
	head.setWidth(10);
	head.setHeight(10);

	int lastX = body[0].left();
	int lastY = body[0].top();
	body[0].moveTo(headX, headY);
	body[0].setWidth(10);
	body[0].setHeight(10);

	for (int i = 1; i < length; i++) {
		int tempX = body[i].left();
		int tempY = body[i].top();
		body[i].moveTo(lastX, lastY);
		lastX = tempX;
		lastY = tempY;
		if (lastX == 0 && lastY == 0) {
			body[i].setWidth(0);
			body[i].setHeight(0);
		}
		else { //set the new elements to 0 width, while they wait for their turn
			body[i].setWidth(10);
			body[i].setHeight(10);
		}
		
	}
}

void snake::jumpSnake(int x, int y) { //jump the snake to a random location on the board

	//move head to new pos
	head.moveTo(x, y);
	head.setWidth(10);
	head.setHeight(10);

	int headX = head.left();
	int headY = head.top();

	body[0].moveTo(headX-10, headY-10);
	body[0].setWidth(10);
	body[0].setHeight(10);

	int lastX = body[0].left();
	int lastY = body[0].top();

	for (int i = 1; i < length; i++) {
		body[i].moveTo(lastX, lastY);
		lastX = body[i].left();
		lastY = body[i].top();
		if (lastX == 0 && lastY == 0) {
			body[i].setWidth(0);
			body[i].setHeight(0);
		}
		else { //set the new elements to 0 width, while they wait for their turn
			body[i].setWidth(10);
			body[i].setHeight(10);
		}

	}
}

void snake::addLength(int l) {
	length += l;
}