#include "jogador.h"

void subir(jogador *j){
	j->y+=j->tamanho;
}

void descer(jogador *j){
	j->y-=j->tamanho/2;
}

void pontuar(jogador *j){
	j->pontos+=1;
}

void reset(jogador *j){
	j->y=0;
	j->pontos=0;
}

void aumentar(jogador *j){
	if(j->tamanho<=300)
		j->tamanho+=50;
}
