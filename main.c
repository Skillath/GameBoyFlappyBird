/*
Game made by Xabier Gonzalez Goienetxea (@Skillath). Not designed by me.

GAMEBOY SPECIFICATIONS:
- CPU: Custom 8-bit Sharp LR35902 core at 4.19 MHz. 
- RAM: 8 kB internal S-RAM (can be extended up to 32 kB)
- Video RAM: 8 kB internal
- ROM: On-CPU-Die 256-byte bootstrap; 256 kb, 512 kb, 1 Mb, 2 Mb, 4 Mb and 8 Mb cartridges
- Sound: 2 pulse wave generators, 1 PCM 4-bit wave sample (64 4-bit samples played in 1×64 bank or 2×32 bank) channel, 1 noise generator, and one audio input from the cartridge.
- Display: Reflective STN LCD 160 × 144 pixels
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
	int cont = 0;
	int nPlumb = 1;

	set_sprite_data(0, 9, Bird);
	set_sprite_tile(0, 0); //Parameter 1 = number of the tile for reference from other functions. Parameter 2: The number of the tile of the GBTD
  	set_sprite_tile(1, 1);
  	set_sprite_tile(2, 2);
  	set_sprite_tile(3, 3);
	SHOW_SPRITES;

	for(cont = 0; cont < PLUMBS; cont ++)
		plumb[cont].xPlumb = 152;

	while (!0) 
	{		
		setPlumb(plumb, nPlumb);
		animateBird(iteration);
		jumpBird();
		addPoints();

	
		m_clock++;
		if(m_clock == 5)
		{
			m_clock = 0;
			iteration++;
			if(iteration >= 4)
				iteration = 0;
		}

		time++;
		if(time == 3000)
			time = 0;
	}
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
	int pad = joypad();

	if(pad == J_UP)
	{
		int y = yBird;
		if(y - 4 > 32)
		{
			yTailBird -= 4;
			yBird -= 4;
		}		
	}
	else if(pad == J_DOWN)
	{
		int y = yTailBird;
		if(y + 4 < 144)
		{
			yTailBird += 4;
			yBird += 4;
		}
	}
	if(pad == J_START)	
	{
		waitpad(J_START);
	}
}

void setPlumb(struct Plumb* plumb, int nPlumb)
{
	int cont;
	for(cont = 0; cont < nPlumb; cont ++)
	{
		if(plumb[cont].xPlumb == 0)
			plumb[cont].xPlumb = 160;
		if(plumb[cont].xPlumb == 160)
			plumb[cont].heightPlumb = randomize();
		if(plumb[cont].heightPlumb == 160)
			plumb[cont].heightPlumb = 82;
		else if(plumb[cont].heightPlumb == 0)
			plumb[cont].heightPlumb = 40;
		paintRectangle(plumb[cont].heightPlumb);

	}

	return;
}

void addPoints()
{
	points += 1;
	gotoxy(0, 0);
	printf("POINTS: %d", points);
}

//Custom rand function.
int randomize()
{
	gotoxy(0,2);
	printf("%d\n", positions[time % 10]);
	return positions[time % 10];
}

void paintRectangle(int safeZone)
{
	/*set_sprite_tile(4, 8);
	move_sprite(4, 152, 16);*/
	int i;
	int cont = 4;
	for(i = 24; i <= safeZone; i += 8)
	{
		set_sprite_tile(cont, 8);
		move_sprite(cont, 152, i);
		cont ++;
		set_sprite_tile(cont, 8);
		move_sprite(cont, 160, i);
		cont ++;
	}
	for(i = safeZone + 32; i <= 160; i += 8)
	{
		set_sprite_tile(cont, 8);
		move_sprite(cont, 152, i);
		cont ++;
		set_sprite_tile(cont, 8);
		move_sprite(cont, 160, i);
		cont ++;
	}
}

void movePlumb()
{

}