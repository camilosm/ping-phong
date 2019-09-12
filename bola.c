#include "bola.h"

void centralizar(bola *b){
	b->x=0;
	b->y=0;
}

void rolar(bola *b){
	b->x+=b->vx;
	b->y+=b->vy;
}

void inverter_x(bola *b){
	b->vx*=-1;
}

void inverter_y(bola *b){
	b->vy*=-1;
}
