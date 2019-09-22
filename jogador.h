typedef struct jogador{
	int id;
	int lado; //-1 esquerda, 1 direita
	float y; //posicao do centro do jogador
	float tamanho; //tamanho vertical do jogador
	unsigned int pontos;
	unsigned int textura_padrao;
	unsigned int textura_ganhando;
} jogador;

void subir(jogador *j, int limite);
void descer(jogador *j, int limite);
int pontuar(jogador *j, unsigned int oponent, int set);
void reset(jogador *j);
