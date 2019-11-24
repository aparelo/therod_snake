#include "apple.h"
#include <stdlib.h>

apple::apple(int minWidth, int minHeight, int maxWidth, int maxHeight) {
	//init rand seed
	srand(time(NULL));

	minFieldWidth = minWidth;
	minFieldHeight = minHeight;

	maxFieldWidth = maxWidth;
	maxFieldHeight = maxHeight;

	int x = rand() % maxFieldWidth + minFieldWidth;
	int y = rand() % maxFieldHeight + minFieldHeight;
	rect = QRect(x, y, 10, 10);

	//init timer to random value between 10 and 50 ticks
	timer = rand() % 50 + 30;

}

void apple::moveApple()
{
	//generate new random coordinates
	int newX = rand() % maxFieldWidth + minFieldWidth;
	int newY = rand() % maxFieldHeight + minFieldHeight;

	resetTimer();

	rect.moveTo(newX, newY);

}

void apple::resetTimer() {
	timer = rand() % 50 + 30;
}
