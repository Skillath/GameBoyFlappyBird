#include <gb/gb.h>
#include <stdio.h>
#include "Bird.c"

void main()
{
	int iteration = 0;
	set_sprite_data(0,8,Bird);
	set_sprite_tile(0,0); //Parameter 1 = number of the tile for reference from other functions. Parameter 2: The number of the tile of the GBTD
  	set_sprite_tile(1,1);
  	set_sprite_tile(2,2);
  	set_sprite_tile(3,3);

	SHOW_SPRITES;
	move_sprite(0,heightBird,70);
	move_sprite(1,heightBird,78);
	move_sprite(2,heightBirdLow,70);
	move_sprite(3,heightBirdLow,78);

	while (!0) 
	{
		animateBird(iteration);
		jumpBird();
		delay(75);
		iteration++;
		if(iteration >= 4)
			iteration = 0;
	}
}

void animateBird(int iter)
{
	switch(iter)
	{
		case 0:
			set_sprite_tile(2,4);
			move_sprite(2,heightBirdLow,70);
			set_sprite_tile(3,5);
			move_sprite(3,heightBirdLow,78);
			break;
		case 1:
			set_sprite_tile(2,2);
			move_sprite(2,heightBirdLow,70);
			set_sprite_tile(3,3);
			move_sprite(3,heightBirdLow,78);
			break;
		case 2:
			set_sprite_tile(2,4);
			move_sprite(2,heightBirdLow,70);
			set_sprite_tile(3,5);
			move_sprite(3,heightBirdLow,78);
			break;
		default:
			set_sprite_tile(2,6);
			move_sprite(2,heightBirdLow,70);
			set_sprite_tile(3,7);
			move_sprite(3,heightBirdLow,78);
			break;	
	}
}

void jumpBird()
{
	int pad = joypad();
	if(pad & J_A)
	{
		printf("%d", pad);
	}
}