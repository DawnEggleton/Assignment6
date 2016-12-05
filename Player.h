#pragma once
class Player
{
	int x;
	int y;
	int score;
	int health;
	ALLEGRO_BITMAP* bmp;

public:
	Player();
	void Draw();

	void SetX(int checkx);
	int GetX();

	void SetY(int checky);
	int GetY();

	void SetScore(int checks);
	int GetScore();

	void SetHealth(int checkh);
	int GetHealth();

	void SetBmp(ALLEGRO_BITMAP* img);
	ALLEGRO_BITMAP* GetBmp();

	bool Collision(Player p, Enemy e);
};
