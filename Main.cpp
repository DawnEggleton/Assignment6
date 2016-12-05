#include "Main.h"

/*
Title: Assignment - 2
Author : Dawn Eggleton

Objective : Create a simple game with 10 enemies and a single player, similar to pacman in which the player can "eat" the enemies - but only if the spacebar is held.There are two enemy types(follow player or move randomly) and the player moves based on keyboard cues and has both health and score.

Player Class :
	   Initialize x, y, bmp, score, and health privately
		   Constructor Function
		   x = y = score = 0
		   bmp = NULL
		   health = 100
		   SetX / GetX
		   SetY / GetY
		   SetScore / GetScore
		   SetHealth / GetHealth
		   SetBmp / GetBmp
		   Collision
		   Include functions :
	   struct Rect
		   float Distance
		   bool InRect
		   Include parameters Player p and Enemy e to determine collision between them by defining each object as a Rect, calculating Distance, and checking if one object is in the other using InRect

Enemy Class :
	   Initialize x, y, bmp, speedx, speedy, type
		   Constructor Function
		   x = y = speedx = speedy = type = 0;
	   bmp = NULL
		   Move Function
		   if type == 0
			   x += speedx
			   y += speedy
			   if type == 1
				   if (x < px)
					   x++;
	   if (x > px)
		   x--;
	   if (y < py)
		   y++;
	   if (y > py)
		   y--;

Render Class :
	DrawPlayer Function
		Include parameter Player p
		al_draw_bitmap for Player p
	DrawEnemy Function
		Include parameter Enemy e
		al_draw_bitmap for Enemy e
	Note : DrawPlayer and DrawEnemy were written separately to allow the drawing of the player after the drawing of the enemy so the player was never hidden behind the enemy and so the player was not drawn multiple times when drawing the array of enemies
	Begin Function
		al_clear_to_color
		Include parameter ALLEGRO_BITMAP* bg
		al_draw_bitmap for ALLEGRO_BITMAP* bg
	End Function
		flip display

Game Function :
	   Intialize Player p, Enemy e[10], Render r, bool quit, bool collide, and bitmaps p1bmp, p2bmp, e1bmp, e2bmp, and bg
		   Constructor Function
			   Set x and y of Player p to 200
			   Set score of Player p to 0
			   Set health of Player p to 100
			   Set bmp of Player p to the first bitmap - create p1bmp variable and set equal to p.bmp
			   Set bmp of Player p to the second bitmap - create p2bmp variable and set equal to p.bmp
			   Set array of 10 enemies to random x and y locations, with speedx and speedy at 1, type randomly 0 or 1
			   Set enemy bitmaps based on type
			   Set bg to bg.bmp
			   Set collide to false
		   Run Function
			   Set quit to false
			   Print health and score to screen
			   While(quit == false)
			   Call Update and Draw functions
			   Wait time
		   Update Function
			   Initialize Keyboard State
			   if escape is pressed, quit = true
				// Move Player
				if right is pressed and p.GetBmp() == p1bmp
					p.x++
				if left is pressed and p.GetBmp() == p1bmp
					p.x--
				if up is pressed and p.GetBmp() == p1bmp
					p.y++
				if down is pressed and p.GetBmp() == p1bmp
					p.y--
				if space is pressed
					p.bmp = p2bmp
				else
					p.bmp = p1bmp
				// Move Enemy
				for loop to get all enemies of the array
					set enemy speed *= -1 if the enemy reaches the bounds of the screen
					if enemy is on the screen, call e.Move(p.GetX(), p.(GetY())
						include the player's coordinates for the sake of the enemy that follows
					Check for collision with p.Collision(p, e[i])
						if collide == true && space is pressed
							e[i].x = 1000 to move off screen
							p.Score ++
							Print health and score
							Set collide to false
						 if collide == true
							p.Health--
							if e[i].type == 1
								Set e[i].x and e[i].y randomly again // assumption that the enemy is not destroyed, but if hit, the player will die too quickly, so enemy is reset until destroyed
								Print health and score
								collide = false
						if score == 10, all enemies are deleted, so end game
						if health == 0, player died, so end game

		 Draw Function
			Call r.Begin(bg)
			Draw Enemies with r.DrawEnemy(e[i])
			Draw Player with r.DrawPlayer(p)
			Call r.End
 */

//global variable for display
ALLEGRO_DISPLAY* display = NULL;

void InitAllegro(int W, int H)
{

	//initialize allegro
	if (!al_init())
	{
		printf("failed to initialize allegro!\n");
	}

	//initialize display screen
	display = al_create_display(W, H);
	if (!display)
	{
		printf("failed to create display!\n");
		exit(0);
	}
	else
	{
		printf("ok");
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	//initialize keyboard
	if (!al_install_keyboard())
	{
		printf("failed to install keyboard!\n");
		exit(0);
	}

	//initialize image addon
	if (!al_init_image_addon())
	{
		printf("failed to initialize image addon!\n");
		exit(0);
	}

	//initialize mouse
	if (!al_install_mouse())
	{
		printf("failed to install mouse!\n");
		exit(0);
	}
	//initialize primitive shapes
	if (!al_init_primitives_addon())
	{
		printf("failed to initialize primitives!\n");
		exit(0);
	}
}
void EndAllegro()
{
	al_destroy_display(display);
}


void main()
{
	//initialize allegro
	int sw = 640;
	int sh = 480;
	InitAllegro(sw, sh);

	Game g;
	g.Run();

	EndAllegro();
}