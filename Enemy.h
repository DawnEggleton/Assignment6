#pragma once
class Enemy
{
public:
	int x;
	int y;
	int speedx;
	int speedy;
	int type;
	ALLEGRO_BITMAP* bmp;




	Enemy();
	void Move(int px, int py);
};

