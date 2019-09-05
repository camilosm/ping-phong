#include "jogador.h"

void mover(jogador *jogador, float distancia){
	jogador->y+=distancia;
}

void pontuar(jogador *jogador, int pontos){
	jogador->pontos+=pontos;
}

void reset(jogador *jogador){
	jogador->y=0;
}
