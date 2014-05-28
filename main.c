#include <gb/gb.h>
#include <stdio.h>
#include <gb/console.h>
#include "Bird.c"

void main()
{
	int iteration = 0;
	set_sprite_data(0, 8, Bird);
	set_sprite_tile(0, 0); //Parameter 1 = number of the tile for reference from other functions. Parameter 2: The number of the tile of the GBTD
  	set_sprite_tile(1, 1);
  	set_sprite_tile(2, 2);
  	set_sprite_tile(3, 3);

	SHOW_SPRITES;
	move_sprite(0, xBird, yTailBird);
	move_sprite(1, xBird, yBird);
	move_sprite(2, xBirdLow, yTailBird);
	move_sprite(3, xBirdLow, yBird);

	while (!0) 
	{
		animateBird(iteration);
		jumpBird();
		delay(50);
		iteration++;
		if(iteration >= 4)
			iteration = 0;
	}
}

void animateBird(int iter)
{
	move_sprite(0, xBird, yTailBird);
	move_sprite(1, xBird, yBird);
	switch(iter)
	{
		case 0:
			set_sprite_tile(2,4);
			move_sprite(2,xBirdLow,yTailBird);
			set_sprite_tile(3,5);
			move_sprite(3,xBirdLow,yBird);
			break;
		case 1:
			set_sprite_tile(2,2);
			move_sprite(2,xBirdLow,yTailBird);
			set_sprite_tile(3,3);
			move_sprite(3,xBirdLow,yBird);
			break;
		case 2:
			set_sprite_tile(2,4);
			move_sprite(2,xBirdLow,yTailBird);
			set_sprite_tile(3,5);
			move_sprite(3,xBirdLow,yBird);
			break;
		default:
			set_sprite_tile(2,6);
			move_sprite(2,xBirdLow,yTailBird);
			set_sprite_tile(3,7);
			move_sprite(3,xBirdLow,yBird);
			break;	
	}
}

void jumpBird()
{
	int pad = joypad();

	if(pad == J_UP)
	{
		yTailBird -= 4;
		yBird -= 4;
	}
	else if(pad == J_DOWN)
	{
		yTailBird += 4;
		yBird += 4;
	}	
}