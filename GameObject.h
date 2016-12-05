#pragma once
class GameObject
{
public:
	int x;
	int y;

	int speedx;
	int speedy;

	ALLEGRO_BITMAP* bmp; //a pointer to bitmap

	GameObject();
	void Move();
	void Draw();
};
