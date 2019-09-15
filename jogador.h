typedef struct jogador{
	int lado; //-1 esquerda, 1 direita
	float y; //posicao do centro do jogador
	float tamanho; //tamanho vertical do jogador
	unsigned int pontos;
} jogador;

void subir(jogador *j, int limite);
void descer(jogador *j, int limite);
void pontuar(jogador *j);
void reset(jogador *j);
void aumentar(jogador *j);
