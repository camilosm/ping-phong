#include "jogador.h"

void mover(jogador *j){
	j->y+=50;
}

void pontuar(jogador *j){
	j->pontos+=1;
}

void reset(jogador *j){
	j->y=0;
}
