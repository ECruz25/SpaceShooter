#include<allegro5/allegro5.h>
#include<allegro5/allegro_primitives.h>
#include "objects.h"
#include <iostream>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 400;
enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};
bool keys[5] = {false,false,false,false,false};

void InitShip(Spaceship &ship);
void DrawShip(Spaceship &ship);
void MoveShipUp(Spaceship &ship);
void MoveShipDown(Spaceship &ship);
void MoveShipLeft(Spaceship &ship);
void MoveShipRight(Spaceship &ship);


int main()
{

    const int FPS = 60;
	bool done = false;
	bool redraw = true;;

    Spaceship ship;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;

    if(!al_init())
        return -1;

    display = al_create_display(WIDTH, HEIGHT);

    if(!display)
        return -1;

    al_init_primitives_addon();
    al_install_keyboard();

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    InitShip(ship);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

    al_start_timer(timer);

    while(!done)
    {

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}

        else if(event.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
            if(keys[UP])
				MoveShipUp(ship);
			if(keys[DOWN])
				MoveShipDown(ship);
			if(keys[LEFT])
				MoveShipLeft(ship);
			if(keys[RIGHT])
				MoveShipRight(ship);
        }

        else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {

            switch(event.keyboard.keycode)
            {

                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    break;

                case ALLEGRO_KEY_UP:
                    keys[UP] = true;
                    break;

                case ALLEGRO_KEY_DOWN:
                    keys[DOWN] = true;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = true;
                    break;

                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = true;
                    break;

                case ALLEGRO_KEY_SPACE:
                    keys[SPACE] = true;
                    break;
            }

        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {

            switch(event.keyboard.keycode)
            {

                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    break;

                case ALLEGRO_KEY_UP:
                    keys[UP] = false;
                    break;

                case ALLEGRO_KEY_DOWN:
                    keys[DOWN] = false;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = false;
                    break;

                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = false;
                    break;

                case ALLEGRO_KEY_SPACE:
                    keys[SPACE] = false;
                    break;
            }
        }

        if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			DrawShip(ship);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
    }

    al_destroy_display(display);
    al_destroy_timer(timer);
	al_destroy_display(display);

    return 0;
}

void InitShip(Spaceship &ship)
{

    ship.x = 20;
    ship.y = HEIGHT/2;
    ship.ID = PLAYER;
    ship.lives = 3;
    ship.speed = 7;
    ship.boundx = 6;
    ship.boundy = 0;

}

void DrawShip(Spaceship &ship)
{
	al_draw_filled_rectangle(ship.x, ship.y - 9, ship.x + 10, ship.y - 7, al_map_rgb(255, 0, 0));
	al_draw_filled_rectangle(ship.x, ship.y + 9, ship.x + 10, ship.y + 7, al_map_rgb(255, 0, 0));

	al_draw_filled_triangle(ship.x - 12, ship.y - 17, ship.x + 12, ship.y, ship.x - 12, ship.y + 17, al_map_rgb(0, 255, 0));
	al_draw_filled_rectangle(ship.x - 12, ship.y - 2, ship.x + 15, ship.y + 2, al_map_rgb(0, 0, 255));
}

void MoveShipLeft(Spaceship &ship)
{
	ship.x -= ship.speed;
	if(ship.x < 0)
		ship.x = 0;

}
void MoveShipUp(Spaceship &ship)
{
	ship.y -= ship.speed;
	if(ship.y < 0)
		ship.y = 0;
}
void MoveShipDown(Spaceship &ship)
{
	ship.y += ship.speed;
	if(ship.y > HEIGHT)
		ship.y = HEIGHT;

}
void MoveShipRight(Spaceship &ship)
{
	ship.x += ship.speed;
	if(ship.x > 300)
		ship.x = 300;
}
