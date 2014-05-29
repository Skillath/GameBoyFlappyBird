#include <gb/gb.h>
#include <gb/console.h>
#include <stdio.h>

#include "Bird.c"

#define PLUMBS 3

int xBird = 30;  
int xBirdLow = xBird - 8;  
int yBird = 78;
int yTailBird = yBird - 8;
int xUpperPlumb, xLowerPlumb;
int points = 0;
int time = 0;
int m_clock = 0;

int positions[10] = {72, 80, 160, 32, 64, 112, 132, 40, 152, 96};

struct Plumb
{
	int xPlumb;
	int heightPlumb;
};

void animateBird(int iter);
void jumpBird();
void setPlumb(struct Plumb* plumb, int nPlumb);
void addPoints();
int collision(struct Plumb* plumb, int nPlumb);
int countPoints(struct Plumb* plumb, int nPlumb, int *p);
int randomize();
void paintRectangle(int safeZone);
void movePlumb();