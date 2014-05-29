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

void main()
{
	struct Plumb plumb[3];
	int points = 0;
	int iteration = 0;
	int cont;
	int nPlumb = 0;

	/*color(BLACK,LTGREY,SOLID);
	box(0,130,40,143,M_NOFILL);
    box(50,130,90,143,M_FILL);*/
	set_sprite_data(0, 15, Bird);
	set_sprite_tile(0, 0); //Parameter 1 = number of the tile for reference from other functions. Parameter 2: The number of the tile of the GBTD
  	set_sprite_tile(1, 1);
  	set_sprite_tile(2, 2);
  	set_sprite_tile(3, 3);

	SHOW_SPRITES;
	move_sprite(0, xBird, yTailBird);
	move_sprite(1, xBird, yBird);
	move_sprite(2, xBirdLow, yTailBird);
	move_sprite(3, xBirdLow, yBird);
	

	for(cont = 0; cont < 3; cont ++)
		plumb[cont].xPlumb = 160;

	while (!0) 
	{
		setPlumb(plumb, nPlumb);
		animateBird(iteration);
		jumpBird();
		addPoints(&points);

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
		yTailBird -= 4;
		yBird -= 4;
	}
	else if(pad == J_DOWN)
	{
		yTailBird += 4;
		yBird += 4;
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
			plumb[cont].xPlumb = 20;
		if(plumb[cont].xPlumb == 20)
			plumb[cont].heightPlumb = rand(18);
		//set_sprite_tile(plumb[cont].xPlumb, 6);
		//box(plumb[cont].xPlumb,plumb[cont].heightPlumb, plumb[cont].xPlumb + 1, 0,M_FILL);
	}
	return;
}

void addPoints(int* p)
{
	*p += 1;
	gotoxy(0, 0);
	printf("POINTS: %d", *p);
}

//Custom rand function.
int rand(int lim)
{
	long a = 3;
    a = (((a * 214013L + 2531011L) >> 16) & 32767);
        
    return ((a % lim) + 1);
}
