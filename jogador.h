#include <stdlib.h>
#include <stdbool.h>

struct jogador{
	bool lado; //true esquerda, false direita
	float y; //altura do centro do jogador
	unsigned int pontos;
};

typedef struct jogador jogador;

void mover(jogador *jogador, float distancia);
void pontuar(jogador *jogador, int pontos);
void reset(jogador *jogador);