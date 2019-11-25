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

//move the apple in a random direction by the given amount, make sure it does not end up under the snake
void apple::moveAppleBy(int dx, int dy, snake snake_1)
{
	//generate new random coordinates
	int iterations = 0;
	int radius = 1;
	while (true && iterations < 100) {
		iterations++;
		int newX = rect.x() + (rand() % 3 - 1) * radius*dx;
		int newY = rect.y() + (rand() % 3 - 1) * radius*dy;

		if (newX < maxFieldWidth && newX > minFieldWidth&& newY < maxFieldHeight && newY > minFieldHeight) { //is in the field
			int misses = 0;
			for (int i = 0; i < snake_1.length; i++) {
				if (abs(snake_1.body[i].x() - rect.x()) > 30 && abs(snake_1.body[i].y() - rect.y()) > 30) {
					misses++;
				}
				else {
					break;
				}
			}
			if (misses == snake_1.length) {
				rect.moveTo(newX, newY);
				break;
			}
			
		}
		else if (iterations % 10 == 0) { //if the apple cant be moved out from under the snake in 10 tries, increase dx and dy
			radius++;
		}
	}

	resetTimer();

	

}

void apple::resetTimer() {
	timer = rand() % 50 + 30;
}
