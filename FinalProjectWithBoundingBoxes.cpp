#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h" 
#include <allegro5/allegro_image.h>
#include "time.h"
#include "iostream"
using namespace std;
#define BUGNUM 500

ALLEGRO_DISPLAY* display = NULL;


///////////////////////////////////////////////////////////////////////
//
// Helper functions to simplify using Allegro
//
///////////////////////////////////////////////////////////////////////

//initialzie Allegro components
void InitAllegro(int W, int H)
{

	//initialize allegro
	if (!al_init())
	{
		printf("failed to initialize allegro!\n");
	}

	//initialize image addon
	if (!al_init_image_addon())	{
		printf("failed to initialize image addon!\n");
	}

	//initialize display screen
	display = al_create_display(W, H);
	if (!display)		//if(display == NULL)
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

	//initialize primitives
	if (!al_init_primitives_addon())
	{
		printf("failed to initialize primitives!\n");
		exit(0);
	}
}

//End and clean up Allegro components
void EndAllegro()
{
	al_destroy_display(display);
}

//helper function for drawing a pixel
void PutPixel(int x, int y, int r, int g, int b)
{
	al_put_pixel(x, y, al_map_rgb(r, g, b));
	//alternative way
	//ALLEGRO_COLOR c = al_map_rgb(r,g,b); //ALLEGRO_COLOR is a "user define type" in Allegro
	//al_put_pixel(x, y, c);
}

void DrawRect(int x, int y, int w, int h, int r, int g, int b)		// how to form PutPixel drawing into a bitmap for quicker loading - but NOT ON EXAM
{
	ALLEGRO_BITMAP* target = al_get_target_bitmap();
	al_lock_bitmap(target, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);
	for (int j = y; j < y + h; j++)
	{
		for (int i = x; i < x + w; i++)
			PutPixel(i, j, r, g, b);
	}
	al_unlock_bitmap(target);
}

//helper function for drawing a line
void DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b)
{
	al_draw_line(x1, y1, x2, y2, al_map_rgb(r, g, b), 1);
}

//helper function to wait for a key
void WaitForKey(int k)
{
	ALLEGRO_KEYBOARD_STATE key_state; //ALLEGRO_KEYBOARD_STATE is a "user define type" in Allegro
	bool quit = false;
	while (!quit)
	{
		al_get_keyboard_state(&key_state);
		//end program
		if (al_key_down(&key_state, k))
		{
			quit = true;
		}

	}
}

struct GameObject
{
	int x, y, speedx, speedy, frame;
	ALLEGRO_BITMAP* bmp[3];
};

void DrawObject(GameObject obj)
{
	al_draw_bitmap(obj.bmp[obj.frame], obj.x, obj.y, 0);
}


float Distance(GameObject o1, GameObject o2)
{
	float b = o2.x - o1.x;
	float a = o2.y - o1.y;
	float c_squared = (a*a) + (b*b);
	float c = sqrt(c_squared);
	return c;
}


///////////////////////////////////////////////////////////////////////
//main function
///////////////////////////////////////////////////////////////////////


void main()
{
	//initialize
	int sw = 800;
	int sh = 600;
	InitAllegro(sw, sh);
	srand(time(NULL));


	ALLEGRO_BITMAP* bg2 = al_load_bitmap("map2.bmp");
	al_lock_bitmap(bg2, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);

	//Location
	GameObject player;
	player.x = 210;
	player.y = 10;
	player.speedx = 4;
	player.speedy = 4;
	player.bmp[0] = al_load_bitmap("player.bmp");
	player.bmp[1] = al_load_bitmap("player2.bmp");
	player.bmp[2] = al_load_bitmap("player3.bmp");
	player.frame = 0;

	GameObject bug[BUGNUM];
	for (int i = 0; i < BUGNUM; i++)
	{
		bug[i].x = (rand() % 580) + 200;
		bug[i].y = rand() % 580;
		bug[i].speedx = 1;
		bug[i].speedy = 1;
		bug[i].bmp[0] = al_load_bitmap("enemy.bmp");
		bug[i].bmp[1] = al_load_bitmap("enemy2.bmp");
		bug[i].bmp[2] = al_load_bitmap("enemy3.bmp");
		bug[i].frame = 0;
	}

	GameObject goal;
	goal.x = (rand() % 580) + 200;
	goal.y = rand() % 580;
	goal.speedx = 1;
	goal.speedy = 1;
	goal.bmp[0] = al_load_bitmap("goal.bmp");
	goal.bmp[1] = al_load_bitmap("goal2.bmp");
	goal.bmp[2] = al_load_bitmap("goal3.bmp");
	goal.frame = 0;


	int sign = -1;
	int fatigue = 0;
	int bugCount = 1;
	int goalGeneration = (rand() % 7) + 3;

	ALLEGRO_KEYBOARD_STATE key_state;
	bool quit = false;
	bool goalPresent = false;
	float counter = 0;

	while (quit == false)
	{
		//Update program variables by checking user input
		al_get_keyboard_state(&key_state);


		int dx = 0;
		int dy = 0;

		

		//calculate distances
		for (int i = 0; i <= bugCount; i++)
		{
			if (Distance(player, bug[i]) <= 10 && fatigue <= 100)
			{
				bug[i].x += 1000;
				bugCount += 3;
				fatigue++;
			}	
		}

			if (Distance(player, goal) <= 10)
				quit = true;

		//set key presses for player movement and exit

		if (al_key_down(&key_state, ALLEGRO_KEY_ESCAPE))
			break;
		if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT))
		{
			if (player.x <= 780)
				player.x += player.speedx;
		}

		if (al_key_down(&key_state, ALLEGRO_KEY_LEFT))
		{
			if (player.x >= 200)
				player.x -= player.speedx;
		}

		if (al_key_down(&key_state, ALLEGRO_KEY_DOWN))
		{
			if (player.y <= 580)
				player.y += player.speedy;
		}

		if (al_key_down(&key_state, ALLEGRO_KEY_UP))
		{
			if (player.y >= 0)
				player.y -= player.speedy;
		}

		//move enemies
		for (int i = 0; i < bugCount; i++)
		{
			if (bug[i].x < 200 || bug[i].x > 780)
			{
				bug[i].speedx *= sign;
				bug[i].x += bug[i].speedx;
			}
			else
				bug[i].x += bug[i].speedx;
			if (bug[i].y < 0 || bug[i].y > 580)
			{
				bug[i].speedy *= sign;
				bug[i].y += bug[i].speedy;
			}
			else
				bug[i].y += bug[i].speedy;
		}

		counter += 0.1;
		player.frame += counter;
		if (counter > 2)
			counter = 0;
		if (player.frame > 2)
			player.frame = 0;
		for (int i = 0; i < bugCount; i++)
		{
			bug[i].frame += counter;
			if (bug[i].frame > 2)
				bug[i].frame = 0;
		}
		goal.frame += counter;
		if (goal.frame > 2)
			goal.frame = 0;
			

		//create objects
		al_draw_bitmap(bg2, 0, 0, 0);
		DrawObject(player);
		for (int i = 0; i < bugCount; i++)
			DrawObject(bug[i]);
		if (goalGeneration == fatigue)
			goalPresent = true;
		if (goalPresent == true)
			DrawObject(goal);





		al_flip_display();
		al_rest(0.01);
	}

	//wait
	WaitForKey(ALLEGRO_KEY_ESCAPE);

	//clean up
	EndAllegro();
}