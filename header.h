#include <gb/gb.h>
#include <stdio.h>
#include <gb/drawing.h>
#include <gb/console.h>
#include "Bird.c"

int xBird = 30;  
int xBirdLow = xBird - 8;  
int yBird = 78;
int yTailBird = yBird - 8;
int xUpperPlumb, xLowerPlumb;

struct Plumb
{
	int xPlumb;
	int heightPlumb;
};

void animateBird(int iter);
void jumpBird();
void setPlumb(struct Plumb* plumb, int nPlumb);
void addPoints(int* p);
int collision(struct Plumb* plumb, int nPlumb);
int countPoints(struct Plumb* plumb, int nPlumb, int *p);
int rand(int lim);