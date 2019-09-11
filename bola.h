#include <stdlib.h>

typedef struct bola{
	float raio;
	float x;
	float y;
	float vx;
	float vy;
} bola;

void mover(bola *bola);
void mudar_tamanho(bola *bola, float fator);
void mudar_velocidade(bola *bola, fator);
