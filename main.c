/*
Game made by Xabier Gonzalez Goienetxea (@Skillath). Not designed by me.

GAMEBOY SPECIFICATIONS:
- CPU: Custom 8-bit Sharp LR35902 core at 4.19 MHz. 
- RAM: 8 kB internal S-RAM (can be extended up to 32 kB)
- Video RAM: 8 kB internal
- ROM: On-CPU-Die 256-byte bootstrap; 256 kb, 512 kb, 1 Mb, 2 Mb, 4 Mb and 8 Mb cartridges
- Sound: 2 pulse wave generators, 1 PCM 4-bit wave sample (64 4-bit samples played in 1×64 bank or 2×32 bank) channel, 1 noise generator, and one audio input from the cartridge.
- Display: Reflective STN LCD SCREEN_DIMENSION × 144 pixels
- Frame Rate: Approx. 59.7 frames per second on a regular Game Boy, 61.1 on a Super Game Boy
- Vertical Blank Rate: Approx 1.1 ms
- Screen size: 66 mm (2.6 in) diagonal
- Color Palette: 2-bit (4 shades of "gray")
- Power: 6 V, 0.7 W (4 AA batteries provide 15–30+ hours)
- Dimensions: 90 mm (W) × 148 mm (H) × 32 mm (D) / 3.5″ × 5.8″ × 1.3″ 
*/

#include "header.h"

void main(void)
{
	struct Plumb plumb[PLUMBS];
	int iteration = 0;
	int nPlumb = 1;

	set_sprite_data(0, 9, Bird);
	set_sprite_tile(0, 0); //Parameter 1 = number of the tile for reference from other functions. Parameter 2: The number of the tile of the GBTD
  	set_sprite_tile(1, 1);
  	set_sprite_tile(2, 2);
  	set_sprite_tile(3, 3);
	SHOW_SPRITES;

	plumb[0].xPlumb = SCREEN_DIMENSION;

	while (!0) 
	{		
		int pad;
		switch(flag)
		{
			case -1:
				flag = -1;
				gotoxy(0, 0);
				printf("POINTS: %d", points);
				gotoxy(4, 8);
				printf("FLAPPY BIRD");
				gotoxy(3, 9);
				printf("by: @Skillath");				
				
				pad = joypad();
				if(pad & J_START)
				{
					plumb[0].xPlumb = SCREEN_DIMENSION;
					init();
				}
				break;	
			case 0:
				gotoxy(4, 8);
				printf("GAME OVER");
				
				pad = joypad();
				if(pad & J_START)
				{
					iteration = 0;
					plumb[0].xPlumb = SCREEN_DIMENSION;
					init();
				}					
				break;
			default:
				gotoxy(0, 0);
				printf("POINTS: %d     ", points);

				setPlumb(plumb);
				animateBird(iteration);
				jumpBird();

				m_clock++;
				if(m_clock == 15)
				{
					m_clock = 0;
					iteration++;
					if(iteration >= 4)
						iteration = 0;
				}
				time++;
				if(time == 3000)
					time = 0;
				break;
		}	
	}
}

void init()
{
	xBird 				= 64;  
	xBirdLow 			= xBird - SPACE_TILE;  
	yBird 				= 78;
	yTailBird 			= yBird - SPACE_TILE;
	points 				= 0;
	time 				= 0;
	m_clock 			= 0;
	falling 			= 0;
	timeJumping 		= 0;
	flag 				= 1;
	leftPlumbSprite 	= SCREEN_DIMENSION;
	rightPlumbSprite 	= SCREEN_DIMENSION + SPACE_TILE;
	isFirstTime 		= 1;
	hasPassedThePlumb 	= 0;

	gotoxy(4, 8);
	printf("               ");

	gotoxy(3, 9);
	printf("               ");
}

void animateBird(int iter)
{
	move_sprite(0, xBird, yTailBird);
	move_sprite(1, xBird, yBird);
	switch(iter)
	{
		case 0:
			set_sprite_tile(2, 4);
			move_sprite(2, xBirdLow, yTailBird);
			set_sprite_tile(3, 5);
			move_sprite(3, xBirdLow, yBird);
			break;
		case 1:
			set_sprite_tile(2, 2);
			move_sprite(2, xBirdLow, yTailBird);
			set_sprite_tile(3, 3);
			move_sprite(3, xBirdLow, yBird);
			break;
		case 2:
			set_sprite_tile(2, 4);
			move_sprite(2, xBirdLow, yTailBird);
			set_sprite_tile(3, 5);
			move_sprite(3, xBirdLow, yBird);
			break;
		default:
			set_sprite_tile(2, 6);
			move_sprite(2, xBirdLow, yTailBird);
			set_sprite_tile(3, 7);
			move_sprite(3, xBirdLow, yBird);
			break;	
	}
}

void jumpBird()
{
	int vY;
	if(falling > 0)
	{
		int pad = joypad();
		if(pad & J_A)
			falling = -1 * GRAVITY;
	}

	vY = GRAVITY * falling;

	if(yTailBird + vY < SCREEN_DIMENSION && yBird + vY > 32)
	{
		yTailBird += vY;
		yBird += vY;
	}

	if(yTailBird + SPACE_TILE + vY >= SCREEN_DIMENSION)
		flag = 0;
	if(m_clock == 4)
		falling ++;
	if(falling == 0)
		falling ++;
	if(falling >= MAX_FALL_VELOCITY)		
		falling = MAX_FALL_VELOCITY;

}

void setPlumb(struct Plumb* plumb)
{
	if(painted == 0)
	{
		if(plumb[0].xPlumb == 0)
			plumb[0].xPlumb = SCREEN_DIMENSION;
		if(plumb[0].xPlumb == SCREEN_DIMENSION)
			plumb[0].heightPlumb = randomize();
		if(plumb[0].heightPlumb >= SCREEN_DIMENSION)
			plumb[0].heightPlumb = 82;
		else if(plumb[0].heightPlumb <= 0)
			plumb[0].heightPlumb = 40;
		paintRectangle(plumb[0].heightPlumb);
		painted = 1;
	}
	movePlumb(plumb[0].heightPlumb);
}

void addPoints()
{
	points += 1;
	gotoxy(0, 0);
	printf("POINTS: %d     ", points);
}

//Custom rand function.
int randomize()
{
	return positions[time % 10];
}

void paintRectangle(int safeZone)
{
	int i;
	int cont = 4;
	if(isFirstTime == 1)
	{
		isFirstTime = 0;
		for(i = SPACE_POINTS_BAR; i <= safeZone; i += SPACE_TILE)
		{
			set_sprite_tile(cont, 8);
			move_sprite(cont, SCREEN_DIMENSION, i);
			cont ++;
			set_sprite_tile(cont, 8);
			move_sprite(cont, SCREEN_DIMENSION + SPACE_TILE, i);
			cont ++;
		}
		for(i = safeZone + SAFE_ZONE_SPACE; i <= SCREEN_DIMENSION; i += SPACE_TILE)
		{
			set_sprite_tile(cont, 8);
			move_sprite(cont, SCREEN_DIMENSION, i);
			cont ++;
			set_sprite_tile(cont, 8);
			move_sprite(cont, SCREEN_DIMENSION + SPACE_TILE, i);
			cont ++;
		}
	}
	else
	{
		for(i = SPACE_POINTS_BAR; i <= safeZone; i += SPACE_TILE)
		{
			move_sprite(cont, SCREEN_DIMENSION, i);
			cont ++;
			move_sprite(cont, SCREEN_DIMENSION + SPACE_TILE, i);
			cont ++;
		}
		for(i = safeZone + SAFE_ZONE_SPACE; i <= SCREEN_DIMENSION; i += SPACE_TILE)
		{
			move_sprite(cont, SCREEN_DIMENSION, i);
			cont ++;
			move_sprite(cont, SCREEN_DIMENSION + SPACE_TILE, i);
			cont ++;
		}
	}
}

void movePlumb(int safeZone)
{
	int i;
	int cont = 4;

	collision(safeZone);

	leftPlumbSprite -= BIRD_VELOCITY;
	rightPlumbSprite -= BIRD_VELOCITY;
	
	for(i = SPACE_POINTS_BAR; i <= safeZone; i += SPACE_TILE)
	{
		move_sprite(cont, leftPlumbSprite, i);
		cont ++;
		move_sprite(cont, rightPlumbSprite, i);
		cont ++;
	}
	for(i = safeZone + SAFE_ZONE_SPACE; i <= SCREEN_DIMENSION; i += SPACE_TILE)
	{
		move_sprite(cont, leftPlumbSprite, i);
		cont ++;
		move_sprite(cont, rightPlumbSprite, i);
		cont ++;
	}

	if(leftPlumbSprite < 0)
	{
		leftPlumbSprite = SCREEN_DIMENSION;
		rightPlumbSprite = SCREEN_DIMENSION + SPACE_TILE;
		painted = 0;
		hasPassedThePlumb = 0;
	}	
}

void collision(int safeZone)
{
	if(xBird == leftPlumbSprite - SPACE_TILE)
	{
		if(yBird > safeZone && yTailBird < safeZone + SAFE_ZONE_SPACE - SPACE_TILE)
			return;
		else
			flag = 0;
		
	}
	else if (xBird > leftPlumbSprite - SPACE_TILE)
	{
		if(yBird < safeZone && yTailBird > safeZone + SAFE_ZONE_SPACE - SPACE_TILE)
			flag = 0;
		else
		{
			if(hasPassedThePlumb == 0)
				addPoints();
		}
		hasPassedThePlumb = 1;
	}
}
