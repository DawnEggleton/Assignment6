#include "Main.h"

Player::Player()
{
	x = y = score = 0;
	health = 10;
	bmp = NULL;
}
void Player::Draw()
{
	al_draw_bitmap(bmp, x, y, 0);
}


void Player::SetX(int checkx)
{
	x = checkx;
}
int Player::GetX()
{
	return x;
}

void Player::SetY(int checky)
{
	y = checky;
}
int Player::GetY()
{
	return y;
}

void Player::SetScore(int checks)
{
	score = checks;
}
int Player::GetScore()
{
	return score;
}

void Player::SetHealth(int checkh)
{
	health = checkh;
}
int Player::GetHealth()
{
	return health;
}

void Player::SetBmp(ALLEGRO_BITMAP* img)
{
	bmp = img;
}
ALLEGRO_BITMAP* Player::GetBmp()
{
	return bmp;
}


struct Rect
{
	int x;
	int y;
	int w;
	int h;
};
float Distance(int x1, int y1, int x2, int y2)
{
	float d = (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
	d = sqrt(d);
	return d;
}
bool InRect(int x, int y, Rect r)
{
	if (x >= r.x && x < r.x + r.w && y >= r.y && y < r.y + r.h)
		return true;
	else
		return false;
}
bool Player::Collision(Player p, Enemy e)
{
	//method 3 (check if one is inside the other)
	int w1 = al_get_bitmap_width(p.bmp);
	int h1 = al_get_bitmap_height(p.bmp);
	int w2 = al_get_bitmap_width(e.bmp);
	int h2 = al_get_bitmap_height(e.bmp);
	Rect r;
	r.x = e.x;
	r.y = e.y;
	r.w = w2;
	r.h = h2;
	bool in_TopLeft = InRect(p.x, p.y, r);
	bool in_TopRight = InRect(p.x + w1 - 1, p.y, r);
	bool in_BottomLeft = InRect(p.x, p.y + h1 - 1, r);
	bool in_BottomRight = InRect(p.x + w1 - 1, p.y + h1 - 1, r);
	if (in_TopLeft || in_TopRight || in_BottomLeft || in_BottomRight)
		return true;
	else
		return false;
}