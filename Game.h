#pragma once
class Game
{
public:

	Player p;
	ALLEGRO_BITMAP* p1bmp;
	ALLEGRO_BITMAP* p2bmp;
	Enemy e[10];
	ALLEGRO_BITMAP* e1bmp;
	ALLEGRO_BITMAP* e2bmp;
	Render r;
	ALLEGRO_BITMAP* bg;
	bool quit;
	bool collide;

	Game();
	~Game();

	void Run();
	void Update();
	void Draw();
};

