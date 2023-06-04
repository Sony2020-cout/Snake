#include <iostream>
#include <conio.h>


using std::cout;
using std::cin;
using std::endl;

bool isGameOver;
const int width = 20;
const int height = 20;
int x, y, foodX, foodY, score;
int tailX[100], tailY[100];
int nTail;

enum snakeDirection
{
	STOP = 0,
	LEFT,
	RIGHT,
	DOWN,
	UP

};

snakeDirection snDir;

void setUp()
{
	isGameOver = false;
	snDir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	foodX = rand() % width;
	foodY = rand() % height;
	score = 0;

}

void draw()
{
	system("cls");
	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
				cout << "#";

			if (i == y && j == x)
				cout << "s";
			else if (i == foodY && j == foodX)
				cout << "f";
			else {
				bool print = false;
				for (int k = 0; k < nTail; ++k)
				{
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << 't';
					}
				}
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; ++i)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;

}

void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			snDir = UP;
			break;
		case 'a':
			snDir = LEFT;
			break;

		case 's':
			snDir = DOWN;
			break;

		case 'd':
			snDir = RIGHT;
			break;
		case 'x':
			isGameOver = true;
			break;
		}
	}
}

void logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;

	}
	switch (snDir) {
	case UP:
		y--;
		break;

	case LEFT:
		x--;
		break;

	case RIGHT:
		x++;
		break;

	case DOWN:
		y++;
		break;
	}
	/*if (x > width || x < 0 || y > height || y < 0)
		isGameOver = true;*///для нормальной игры змейки, когда змейка касаеться 
		//границы, игра заканчивается
		//проходим через границу)))
	if (x >= width - 1)
		x = 0;
	else if (x < 0)
		x = width - 2;
	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;

	for (int i = 0; i < nTail; ++i)
	{
		if (tailX[i] == x && tailY[i] == y)
			isGameOver = true;
	}
	if (x == foodX && y == foodY) {
		score += 10;
		foodX = rand() % width;
		foodY = rand() % height;
		nTail++;
	}

}

int main()
{
	
	setUp();
	while (!isGameOver)
	{
		draw();
		input();
		logic();
	}
	
	
	
	
	system("pause");
	return 0;
}