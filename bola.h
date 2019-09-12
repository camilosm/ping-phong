typedef struct bola{
	float x;
	float y;
	float tamanho;
	float vx;
	float vy;
} bola;

void centralizar(bola *b);
void rolar(bola *b);
void inverter_x(bola *b);
void inverter_y(bola *b);
void mudar_tamanho(bola *bola, float fator);
void mudar_velocidade(bola *bola, float fator);
