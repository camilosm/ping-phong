#include "bola.h"

void centralizar(bola *b){
	b->x=0;
	b->y=0;
	b->deadzone=false;
}

void rolar(bola *b){
	b->x+=b->vx;
	b->y+=b->vy;
}

void inverter_x(bola *b){
	if(!b->deadzone)
		b->vx*=-1;
}

void inverter_y(bola *b){
	b->vy*=-1;
}

void deadzone(bola *b){
	b->deadzone=true;
}
