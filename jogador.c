#include "jogador.h"

void subir(jogador *j, int limite){
	if(j->y+j->tamanho<=limite)
		j->y+=j->tamanho/2;
}

void descer(jogador *j, int limite){
	if(j->y-j->tamanho>=limite)
		j->y-=j->tamanho/2;
}

void pontuar(jogador *j){
	j->pontos+=1;
}

void reset(jogador *j){
	j->y=0;
	j->pontos=0;
}
