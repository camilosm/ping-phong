#include <stdlib.h>

struct bola{
	float raio;
	float x;
	float y;
	float vx;
	float vy;
}

typedef struct bola bola;

void mover(bola *bola);
void mudar_tamanho(bola *bola, float fator);
void mudar_velocidade(bola *bola, fator);
