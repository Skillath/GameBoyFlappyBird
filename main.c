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
#include "sound.c"

struct LowerPlumb lowerPlumb;
struct UpperPlumb upperPlumb;
struct Peluchito peluchito;
int iteration = 0;

void main(void)
{
	awake();
	//start();

	while(TRUE)
	{
		update();
		draw();

		wait_vbl_done();	
	}
}

void awake()
{
	DISPLAY_ON; // TURNS ON THE GAMEBOY LCD
	soundInit();
	initrand(DIV_REG); // SEED OUR RANDOMIZER

	peluchito.x = 64;
	peluchito.y = 78;
	peluchito.width = 16;
	peluchito.height = 16;
	peluchito.vX = 0;
	peluchito.vY = 0;

	lowerPlumb.x = SCREEN_DIMENSION;
	lowerPlumb.y = 0;
	lowerPlumb.width = 16;
	lowerPlumb.vX = -1;
	lowerPlumb.vY = 0;
	lowerPlumb.height = SCREEN_DIMENSION;

	upperPlumb.x = SCREEN_DIMENSION;
	upperPlumb.y = 0;
	upperPlumb.width = 16;
	upperPlumb.vX = -1;
	upperPlumb.vY = 0;
	upperPlumb.height = SCREEN_DIMENSION;

	set_sprite_data(0, 20, GameSprites);
	/*BIRD*/
	set_sprite_tile(0, 12); //Parameter 1 = number of the tile for reference from other functions. Parameter 2: The number of the tile of the GBTD
  	set_sprite_tile(1, 13);
  	set_sprite_tile(2, 14);
  	set_sprite_tile(3, 15);
	set_sprite_tile(4, 16); //Parameter 1 = number of the tile for reference from other functions. Parameter 2: The number of the tile of the GBTD
  	set_sprite_tile(5, 17);
  	set_sprite_tile(6, 18);
  	set_sprite_tile(7, 19);

	/*Lower Plumb */
	set_sprite_tile(10, 0);
	set_sprite_tile(11, 1);
	set_sprite_tile(12, 2);
	set_sprite_tile(13, 3);
	set_sprite_tile(14, 3);
	set_sprite_tile(15, 3);

	/*Upper Plumb */
	set_sprite_tile(20, 0);
	set_sprite_tile(21, 1);
	set_sprite_tile(22, 2);
	set_sprite_tile(23, 3);
	set_sprite_tile(24, 3);
	set_sprite_tile(25, 3);
	SHOW_SPRITES;

	flag = SPLASH_SCREEN;
}

void start()
{
	initRandomizer();

	iteration 			= 0;
	points 				= 0;
	time 				= 0;
	m_clock 			= 0;
	falling 			= 0;
	timeJumping 		= 0;
	flag 				= GAME;
	leftPlumbSprite 	= SCREEN_DIMENSION;
	rightPlumbSprite 	= SCREEN_DIMENSION + SPACE_TILE;
	isFirstTime 		= TRUE;
	hasPassedThePlumb 	= FALSE;

	gotoxy(2, 7);
	printf("                                                                ");

	gotoxy(3, 9);
	printf("                                                                ");
}

void update()
{
	int pad = joypad();
			updateMusicMenu(); //Play the music.
	switch(flag)
	{
		default:
		case SPLASH_SCREEN:	
			if(pad & J_START)
				start();
			break;
		case GAME:
				gotoxy(0, 0);
				printf("POINTS: %d                  ", points);

				//setPlumb(&lowerPlumb);
				//animateBird(iteration);
				//jumpBird();

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
			break;
		case GAME_OVER:
			if(pad & J_START)
			{
				iteration = 0;
				start();
			}	
			break;
	}
}

void draw()
{
	switch(flag)
	{
		default:
		case SPLASH_SCREEN:
			gotoxy(0, 0);
			printf("POINTS: %d", points);
			gotoxy(2, 7);
			printf("FLAPPY PELUCHITO");
			gotoxy(3, 9);
			printf("Xabier Gonzalez\n    (@Skillath)");				
			break;
		case GAME:
			animateBird(0);
			break;
		case GAME_OVER:
			gotoxy(4, 8);
			printf("GAME OVER");
			break;
	}
}

void soundInit()
{
    NR52_REG = 0xFFU;
    NR51_REG = 0x00U;
    NR50_REG = 0x77U;
}

void soundCleanNoise()
{
	NR41_REG = 1;//0x0FU; //Duration
    NR42_REG = 1;         //Volumen
    NR43_REG = 1;         //Tone
    NR44_REG = 0xC0U;
    NR51_REG |= 0x88;
}

void initRandomizer()
{
	UWORD seed = DIV_REG;
	seed |= (UWORD)DIV_REG << 8;
	initarand(seed);
}

void updateBird()
{

}

void animateBird(int iter)
{
	move_sprite(0, peluchito.x, peluchito.y);
	move_sprite(1, peluchito.x, peluchito.y + peluchito.height / 2);
	move_sprite(2, peluchito.x + peluchito.width / 2, peluchito.y);
	move_sprite(3, peluchito.x + peluchito.width / 2, peluchito.y + peluchito.height / 2);
	/*switch(iter)
	{
		case 0:
			set_sprite_tile(2, 4);
			move_sprite(2, xBirdLow, peluchito.height);
			set_sprite_tile(3, 5);
			move_sprite(3, peluchito.x, peluchito.height);
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
	}*/
}

/*void jumpBird()
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
		flag = GAME_OVER;
	if(m_clock == 4)
		falling ++;
	if(falling == 0)
		falling ++;
	if(falling >= MAX_FALL_VELOCITY)		
		falling = MAX_FALL_VELOCITY;

}

void setLowerPlumb(struct LowerPlumb* lowerPlumb)
{
	if(painted == 0)
	{
		if(lowerPlumb->x == 0)
			lowerPlumb->x = SCREEN_DIMENSION;
		if(lowerPlumb->x == SCREEN_DIMENSION)
			lowerPlumb->height = randomize();
		if(lowerPlumb->height >= SCREEN_DIMENSION)
			lowerPlumb->height = 82;
		else if(lowerPlumb->height <= 0)
			lowerPlumb->height = 40;
		paintRectangle(lowerPlumb->height);
		painted = 1;
	}

	movePlumb(lowerPlumb->height);
}*/

void addPoints()
{
	points += 1;
	gotoxy(0, 0);
	printf("POINTS: %d                  ", points);
}

//Custom rand function.
unsigned int randomize()
{
	
	return positions[time % 10];
}

unsigned int random(unsigned int min, unsigned int max)
{
	return rand() % (max + 1 - min) + min;
}
/*
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
			flag = GAME_OVER;
		
	}
	if (xBird > leftPlumbSprite - SPACE_TILE)
	{
		if(yBird < safeZone && yTailBird > safeZone + SAFE_ZONE_SPACE - SPACE_TILE)
			flag = GAME_OVER;
		else
		{
			if(hasPassedThePlumb == 0)
				addPoints();
		}
		hasPassedThePlumb = 1;
	}
}

int collisionCheck(UINT8 x1, UINT8 y1, UINT8 w1, UINT8 h1, UINT8 x2, UINT8 y2, UINT8 w2, UINT8 h2)
{
	if(((x1 < (x2+w2)) && ((x1+w1) > x2) && (y1 < (h2+y2)) && ((y1+h1) > y2)))
		return TRUE;

	return FALSE;
}
*/