#include "jogador.h"

void subir(jogador *j, int limite){
	if(j->y+j->tamanho<=limite)
		j->y+=j->tamanho/2;
}

void descer(jogador *j, int limite){
	if(j->y-j->tamanho>=limite)
		j->y-=j->tamanho/2;
}

int pontuar(jogador *j, int set){
	if(j->pontos+1==set){
		j->pontos=0;
		return 1;
	}
	j->pontos++;
	return 0;
}

void reset(jogador *j){
	j->y=0;
	j->pontos=0;
}
