#include <gb/gb.h>
#include <gb/console.h>
#include <stdio.h>

#include "Bird.c"

#define PLUMBS 					1
#define GRAVITY 				1
#define BIRD_VELOCITY 			1
#define SPACE_BETWEEN_PLUMBS 	8

int xBird 			= 64;  
int xBirdLow 		= xBird - 8;  
int yBird 			= 78;
int yTailBird 		= yBird - 8;
int points 			= 0;
int time 			= 0;
int m_clock 		= 0;
int maxTime 		= 2;
int falling 		= 0;
int timeJumping 	= 0;
int flag 			= 0;
int leftPlumbSprite = 160;
int rightPlumbSprite = 168;
int painted = 0;
int isFirstTime = 1;

int xUpperPlumb, xLowerPlumb;

int positions[10] = {72, 80, 124, 32, 64, 112, 132, 40, 46, 96};

struct Plumb
{
	int xPlumb;
	int heightPlumb;
};

void animateBird(int iter);
void jumpBird();
void setPlumb(struct Plumb* plumb);
void addPoints();
void collision(int safeZone);
int countPoints(struct Plumb* plumb, int nPlumb, int *p);
int randomize();
void paintRectangle(int safeZone);
void movePlumb(int safeZone);
