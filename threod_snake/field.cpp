#include "field.h"
#include <QtCore>
#include <QTimer>
#include <QKeyEvent>
#include <iostream>
#include <stdlib.h>
#include <qgraphicsitem.h>
#include <cstdlib>

field::field(QWidget *parent)
	: QMainWindow(parent)
{


	ui.setupUi(this);
	

	ui.graphicsView->setScene(scene);

	//event filter to capture keystrokes
	ui.graphicsView->installEventFilter(this);

	//define some pens
	QPen blackpen(Qt::black);
	QPen blackpen_thick(Qt::black, 8);
	QBrush redBrush(Qt::red);
	QBrush greenBrush(Qt::green);
	QBrush yellowBrush(Qt::yellow);


	//get field width and height
	fieldWidth = ui.graphicsView->width();
	fieldHeight = ui.graphicsView->height();

	minWidth = 20;
	minHeight = 20;

	leftEdge = QLine(0.0, -16.0, 0.0, fieldHeight - 25);
	rightEdge = QLine(fieldWidth - 10, -16.0, fieldWidth - 10, fieldHeight - 25);
	topEdge = QLine(0.0, -16.0, fieldWidth, -16.0);
	bottomEdge = QLine(0.0, fieldHeight - 25.0, fieldWidth, fieldHeight - 25.0);

	//draw field borders
	scene->addLine(leftEdge, blackpen_thick);
	scene->addLine(topEdge, blackpen_thick);
	scene->addLine(bottomEdge, blackpen_thick);
	scene->addLine(rightEdge, blackpen_thick);

	initGame(true);

	timerId = startTimer(DELAY);

}

void field::initGame(bool firstGame) {
	//define some pens
	QPen blackpen(Qt::black);
	QBrush redBrush(Qt::red);
	QBrush greenBrush(Qt::green);
	QBrush yellowBrush(Qt::yellow);

	if (firstGame) { //if it's the first game, init the snake and apple

		snake_1.jumpSnake(fieldWidth / 2, fieldHeight / 2);
		//draw the initial snake
		QGraphicsRectItem* head = scene->addRect(snake_1.head, blackpen, greenBrush);
		snake_1.snake_head = dynamic_cast<QGraphicsItem*>(head);

		for (int j = 0; j < snake_1.length; j++) {
			QGraphicsRectItem* element = scene->addRect(snake_1.body[j], blackpen, redBrush);
			snake_1.snake_body[j] = dynamic_cast<QGraphicsItem*>(element);
		}

		//draw the apple
		apple1 = apple(minWidth, minHeight, fieldWidth - 50, fieldHeight - 60);
		QGraphicsRectItem* tempApple = scene->addRect(apple1.rect, blackpen, yellowBrush);
		apple1.graphics = dynamic_cast<QGraphicsItem*>(tempApple);
	}
	else {
		if (!message.isNull()) {
			removeItem(game_over_text);
		}
		score = 0;
		ui.lcdNumber->display(score);
		//remove the current snake, draw snake removes the snake, but only up to the new length
		int new_length = 3;
		for (int i = 0; i < snake_1.length; i++) {
			scene->removeItem(snake_1.snake_body[i]);
			snake_1.body[i] = QRect();
		}
		snake_1.length = new_length;
		snake_1.direction[0] = 0;
		snake_1.direction[1] = -1;

		drawSnake(fieldWidth/2, fieldHeight/2);
	}

	playing = true;
	drawApple();

}

//check if the snake has collided with something
void field::checkCollision() {
	//check if the snake head has hit an edge

	//collides with the side
	if (snake_1.head.x() >= rightEdge.x1()-8 || snake_1.head.x() <= leftEdge.x1()+4) {
		gameOver();
	}
	//collides with the top or bottom
	if (snake_1.head.y() <= topEdge.y1()+4 || snake_1.head.y() >= bottomEdge.y1()-8) {
		gameOver();
	}

	//collides with itself
	for (int i = 0; i < snake_1.length; i++) {
		if (snake_1.head.x() == snake_1.body[i].x() && snake_1.head.y() == snake_1.body[i].y()) {
			gameOver();
		}
	}

}

void field::drawSnake(int x, int y) {
	QPen blackpen(Qt::black);
	QBrush redBrush(Qt::red);
	QBrush greenBrush(Qt::green);

	//delete the old snake
	removeItem(snake_1.snake_head);

	//loop over the body and delete all elements
	for (int j = 0;j < snake_1.length;j++) {
		removeItem(snake_1.snake_body[j]);
	}

	//move snake to new location
	snake_1.moveSnake(x, y);

	//draw the moved snake
	QGraphicsRectItem* head = scene->addRect(snake_1.head, blackpen, greenBrush);
	snake_1.snake_head = dynamic_cast<QGraphicsItem*>(head);

	for (int j = 0; j < snake_1.length; j++) {
		QGraphicsRectItem* element = scene->addRect(snake_1.body[j], blackpen, redBrush);
		snake_1.snake_body[j] = dynamic_cast<QGraphicsItem*>(element);
	}

	repaint();
}

void field::drawApple() {

	QPen blackpen(Qt::black);
	QBrush yellowBrush(Qt::yellow);

	removeItem(apple1.graphics);

	int loops = 0;
	while (true && loops < 100) {
		loops++;
		apple1.moveApple();
		//check that the apple doesn't appear under the snake
		int misses = 0;
		for (int i = 0; i < snake_1.length; i++) {
			if (abs(snake_1.body[i].x() - apple1.rect.x()) > 30 && abs(snake_1.body[i].y() - apple1.rect.y()) > 30) {
				misses++;
			}
			else {
				break;
			}
		}
		if (misses == snake_1.length) {
			break;
		}
	}
	if (loops == 100) { //if random moving fails, move the apple 10 units in a random direction
		apple1.moveAppleBy(10, 10, snake_1);
	}
	

	QGraphicsRectItem* tempApple = scene->addRect(apple1.rect, blackpen, yellowBrush);
	apple1.graphics = dynamic_cast<QGraphicsItem*>(tempApple);

}

void field::checkApple() {
	//check if you got the apple
	if (abs(snake_1.head.x() - apple1.rect.x()) < 10 && abs(snake_1.head.y() - apple1.rect.y()) < 10) {
		score++;
		ui.lcdNumber->display(score);
		snake_1.addLength(5);
		drawApple();
	}
}

void field::gameOver() {

	playing = false;

	message = "Game over \n Press R to restart";
	QFont font("Courier", 15, QFont::DemiBold);

	QGraphicsSimpleTextItem *text = scene->addSimpleText(message, font);
	game_over_text = dynamic_cast<QGraphicsItem*>(text);
	text->setX(fieldWidth/2);
	text->setY(fieldHeight/2);

	
}



void field::pauseGame() {
	if (playing) {
		playing = false;

	}
	else {
		playing = true;
	}

}

void field::removeItem(QGraphicsItem* item) {
	scene->removeItem(item);
	delete item;
}

void field::timerEvent(QTimerEvent* e) {

	Q_UNUSED(e);

	if (playing) {
		int currentX = snake_1.head.left();
		int currentY = snake_1.head.top();

		int newX = currentX + snake_1.direction[0] * snake_1.speed;
		int newY = currentY + snake_1.direction[1] * snake_1.speed;

		drawSnake(newX, newY);

		checkCollision();
		checkApple();

		apple1.timer--;
		if (apple1.timer == 0) {
			drawApple();
		}
	}
	
}

void field::keyPressEvent(QKeyEvent* key) {

	
	switch (key->key())
	{
	case(Qt::Key_Up):
	case(Qt::Key_W):
		if (snake_1.direction[1] != 1) {
			snake_1.direction[0] = 0;
			snake_1.direction[1] = -1;
		}
		break;
	case(Qt::Key_Down):
	case(Qt::Key_S):
		if (snake_1.direction[1] != -1) {
			snake_1.direction[0] = 0;
			snake_1.direction[1] = 1;
		}
		break;
	case(Qt::Key_Left):
	case(Qt::Key_A):
		if (snake_1.direction[0] != 1) {
			snake_1.direction[0] = -1;
			snake_1.direction[1] = 0;
		}
		break;
	case(Qt::Key_Right):
	case(Qt::Key_D):
		if (snake_1.direction[0] != -1) {
			snake_1.direction[0] = 1;
			snake_1.direction[1] = 0;
		}
		break;
	case(Qt::Key_P): //pause
		pauseGame();
		break;
	case(Qt::Key_R):
		initGame(false);
		break;
	default:
		break;
	}
}

bool field::eventFilter(QObject* obj,
	QEvent* event)
{
	QKeyEvent* keyEvent = NULL;//event data, if this is a keystroke event
	bool result = false;//return true to consume the keystroke

	if (event->type() == QEvent::KeyPress)
	{
		keyEvent = dynamic_cast<QKeyEvent*>(event);
		this->keyPressEvent(keyEvent);
		result = true;
	}//if type()

	else if (event->type() == QEvent::KeyRelease)
	{
		keyEvent = dynamic_cast<QKeyEvent*>(event);
		this->keyReleaseEvent(keyEvent);
		result = true;
	}//else if type()

	//### Standard event processing ###
	else
		result = QObject::eventFilter(obj, event);

	return result;
}//eventFilter
