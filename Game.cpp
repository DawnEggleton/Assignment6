#include "Main.h"



Game::Game()
{
	p.SetX(200);
	p.SetY(200);
	p.SetScore(0);
	p.SetHealth(100);
	p.SetBmp(al_load_bitmap("player.bmp"));
	p1bmp = p.GetBmp();
	p.SetBmp(al_load_bitmap("player2.bmp"));
	p2bmp = p.GetBmp();

	for (int i = 0; i < 10; i++)
	{
		e[i].x = rand() % 620;
		e[i].y = rand() % 420;
		e[i].speedx = 1;
		e[i].speedy = 1;
		e[i].type = rand() % 2;
		if (e[i].type == 0)
			e[i].bmp = e1bmp = al_load_bitmap("enemy.bmp");
		else
			e[i].bmp = e2bmp = al_load_bitmap("enemy2.bmp");
	}

	bg = al_load_bitmap("bg.bmp");
	collide = false;
}

Game::~Game()
{
	al_destroy_bitmap(p1bmp);
	al_destroy_bitmap(p2bmp);
	al_destroy_bitmap(e1bmp);
	al_destroy_bitmap(e2bmp);
	al_destroy_bitmap(bg);
}

void Game::Run()
{
	quit = false;

	printf_s("Health: %d\n", p.GetHealth());
	printf_s("Score: %d\n\n", p.GetScore());
	while (quit == false)
	{
		Update();
		Draw();

		//wait 0.1 seconds
		al_rest(0.01);
	}
}

void Game::Update()
{
	ALLEGRO_KEYBOARD_STATE key_state;
	al_get_keyboard_state(&key_state);

	//end program
	if (al_key_down(&key_state, ALLEGRO_KEY_ESCAPE))
		quit = true;

	//move player object
	if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT) && p.GetBmp() == p1bmp)
		p.SetX(p.GetX() + 1);
	if (al_key_down(&key_state, ALLEGRO_KEY_LEFT) && p.GetBmp() == p1bmp)
		p.SetX(p.GetX() - 1);
	if (al_key_down(&key_state, ALLEGRO_KEY_UP) && p.GetBmp() == p1bmp)
		p.SetY(p.GetY() - 1);
	if (al_key_down(&key_state, ALLEGRO_KEY_DOWN) && p.GetBmp() == p1bmp)
		p.SetY(p.GetY() + 1);
	if (al_key_down(&key_state, ALLEGRO_KEY_SPACE))
		p.SetBmp(p2bmp);
	else
		p.SetBmp(p1bmp);

	//move enemy objects, check collision, print health and score if collision is detected
	for (int i = 0; i < 10; i++)
	{
		if (e[i].x > 620 || e[i].x < 0)
			e[i].speedx *= -1;
		if (e[i].y > 460 || e[i].y < 0)
			e[i].speedy *= -1;

		if (e[i].x < 700)
			e[i].Move(p.GetX(), p.GetY());

		if (p.Collision(p, e[i]))
			collide = true;
		if (collide == true && al_key_down(&key_state, ALLEGRO_KEY_SPACE))
		{
			e[i].x = 1000;
			p.SetScore(p.GetScore() + 1);
			printf_s("Health: %d\n", p.GetHealth());
			printf_s("Score: %d\n\n", p.GetScore());
			collide = false;
		}
		if (collide == true)
		{
			p.SetHealth(p.GetHealth() - 1);
			if (e[i].type == 1)
			{
				e[i].x = rand() % 620;
				e[i].y = rand() % 420;
			}

			printf_s("Health: %d\n", p.GetHealth());
			printf_s("Score: %d\n\n", p.GetScore());
			collide = false;
		}
	}

	if (p.GetScore() == 10)
	{
		printf_s("You Won!");
		quit = true;
	}
	if (p.GetHealth() == 0)
	{
		printf_s("You Lost...");
		quit = true;
	}

}

void Game::Draw()
{
	r.Begin(bg);
	for (int i = 0; i < 10; i++)
		r.DrawEnemy(e[i]);
	r.DrawPlayer(p);
	r.End();
}