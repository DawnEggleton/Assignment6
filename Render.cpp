#include "Main.h"



Render::Render()
{
}


Render::~Render()
{
}

void Render::DrawPlayer(Player p)
{
	al_draw_bitmap(p.GetBmp(), p.GetX(), p.GetY(), 0);
}
void Render::DrawEnemy(Enemy e)
{
	al_draw_bitmap(e.bmp, e.x, e.y, 0);
}
void Render::Begin(ALLEGRO_BITMAP* bg)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_bitmap(bg, 0, 0, 0);
}
void Render::End()
{
	al_flip_display();
}
