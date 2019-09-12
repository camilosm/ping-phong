#include <stdbool.h>

typedef struct jogador{
	bool lado; //true esquerda, false direita
	float y; //posicao do centro do jogador
	float tamanho; //tamanho vertical do jogador
	unsigned int pontos;
} jogador;

void subir(jogador *j);
void descer(jogador *j);
void pontuar(jogador *j);
void reset(jogador *j);
void aumentar(jogador *j);
