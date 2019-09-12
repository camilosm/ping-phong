#include <stdbool.h>

typedef struct jogador{
	bool lado; //true esquerda, false direita
	float y; //altura do centro do jogador
	unsigned int pontos;
} jogador;

void mover(jogador *j);
void pontuar(jogador *j);
void reset(jogador *j);
