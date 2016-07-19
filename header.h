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

#include <gb/gb.h> // INCLUDE GBDK FUNCTION LIBRARY
#include <gb/hardware.h> // INCLUDE HANDY HARDWARE REFERENCES
#include <gb/sample.h>
#include <gb/console.h>
#include <rand.h>// INCLUDE RANDOM FUNCTIONS
#include <stdio.h>


#include "sprites.c"

#define PLUMBS 					1
#define GRAVITY 				1
#define SPACE_TILE			 	8
#define MAX_FALL_VELOCITY	 	4
#define SPACE_POINTS_BAR		24
#define SAFE_ZONE_SPACE			40
#define SCREEN_DIMENSION		160

typedef enum 
{
	SPLASH_SCREEN = -1,
	GAME_OVER = 0,
	GAME = 1
} GameStatus;

int xBird 				= 		64;  
int xBirdLow 			= 		xBird - SPACE_TILE;  
int yBird 				= 		78;
int yTailBird 			= 		yBird - SPACE_TILE;
int points 				= 		0;
UBYTE time 		= 		0x00;
int m_clock 			= 		0;
int falling 			= 		0;
int timeJumping 		= 		0;
GameStatus flag 		= 		SPLASH_SCREEN;
int leftPlumbSprite 	= 		SCREEN_DIMENSION;
int rightPlumbSprite 	= 		SCREEN_DIMENSION + SPACE_TILE;
int painted 			= 		0;
int isFirstTime 		= 		1;
int hasPassedThePlumb 	= 		0;

int positions[10] 		= 		{72, 80, 124, 32, 64, 112, 24, 48, 32, 96};

struct LowerPlumb
{
	int x;
	int y;
	unsigned int height;
	unsigned int width;

	int vX;
	int vY;
};

struct UpperPlumb
{
	int x;
	int y;
	unsigned int height;
	unsigned int width;

	int vX;
	int vY;
};

struct Peluchito
{
	int x;
	int y;
	unsigned int height;
	unsigned int width;

	int vX;
	int vY;
};

const unsigned int lowerPlumbTiles[] = {0, 1, 2, 3, 4, 5};
const unsigned int upperPlumbTiles[] = {6, 7, 8, 9, 10, 11};
const unsigned int peluchitoTiles[] = {12,13,14,15,16,17,18,19};

void awake();
void start();
void update();
void draw();

void soundInit();
void soundCleanNoise();

void animateBird();
void updateBird();
void jumpBird();
void moveBird(int x, int y);
void setLowerPlumb(struct LowerPlumb* plumb);
void setUpperPlumb(struct UpperPlumb* plumb);
void addPoints();
void collision(int safeZone);
void initRandomizer();
unsigned int randomize();
unsigned int random(unsigned int min, unsigned int max);
void paintRectangle(int safeZone);
void movePlumb(int safeZone);
int collisionCheck(UINT8 x1, UINT8 y1, UINT8 w1, UINT8 h1, UINT8 x2, UINT8 y2, UINT8 w2, UINT8 h2);
