#include "Main.h"

Enemy::Enemy()
{
	x = y = speedx = speedy = 0;
	type = 0;
	bmp = NULL;
}
void Enemy::Move(int px, int py)
{
	if (type == 0)
	{
		x += speedx;
		y += speedy;
	}
	else
	{
		if (x < px)
			x++;
		if (x > px)
			x--;
		if (y < py)
			y++;
		if (y > py)
			y--;
	}
}