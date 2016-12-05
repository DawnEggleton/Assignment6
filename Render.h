#pragma once
class Render
{
public:
	Player p;
	Enemy e;
	ALLEGRO_BITMAP* bg;
	Render();
	~Render();
	void DrawPlayer(Player p);
	void DrawEnemy(Enemy e);
	void Begin(ALLEGRO_BITMAP* bg);
	void End();
};

