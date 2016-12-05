#include "Main.h"

GameObject::GameObject()
{
	x = y = speedx = speedy = 0;
	bmp = NULL;
}
void GameObject::Move()
{
	x += speedx;
	y += speedy;
}
void GameObject::Draw()
{
	al_draw_bitmap(bmp, x, y, 0);
}