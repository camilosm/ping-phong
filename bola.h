#include <stdbool.h>

typedef struct bola{
	bool deadzone;
	float x;
	float y;
	float tamanho;
	float vx;
	float vy;
	unsigned int textura;
} bola;

void centralizar(bola *b);
void rolar(bola *b);
void inverter_x(bola *b);
void inverter_y(bola *b);
void deadzone(bola *b);
