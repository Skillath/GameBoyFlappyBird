#include <gb/gb.h>
#include <gb/console.h>
#include <stdio.h>

#include "Bird.c"

#define PLUMBS 					1
#define GRAVITY 				1
#define BIRD_VELOCITY 			1
#define SPACE_TILE			 	8
#define MAX_FALL_VELOCITY	 	4
#define SPACE_POINTS_BAR		24
#define SAFE_ZONE_SPACE			40
#define SCREEN_DIMENSION		160

int xBird 			= 64;  
int xBirdLow 		= xBird - SPACE_TILE;  
int yBird 			= 78;
int yTailBird 		= yBird - SPACE_TILE;
int points 			= 0;
int time 			= 0;
int m_clock 		= 0;
int falling 		= 0;
int timeJumping 	= 0;
int flag 			= -1;
int leftPlumbSprite = SCREEN_DIMENSION;
int rightPlumbSprite = SCREEN_DIMENSION + SPACE_TILE;
int painted = 0;
int isFirstTime = 1;

int xUpperPlumb, xLowerPlumb;

int positions[10] = {72, 80, 124, 32, 64, 112, 24, 48, 32, 96};

struct Plumb
{
	int xPlumb;
	int heightPlumb;
};

void init();
void animateBird(int iter);
void jumpBird();
void setPlumb(struct Plumb* plumb);
void addPoints();
void collision(int safeZone);
int countPoints(struct Plumb* plumb, int nPlumb, int *p);
int randomize();
void paintRectangle(int safeZone);
void movePlumb(int safeZone);
