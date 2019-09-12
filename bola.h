typedef struct bola{
	float raio;
	float x;
	float y;
	float vx;
	float vy;
} bola;

void centro(bola b);
void mudar_tamanho(bola *bola, float fator);
void mudar_velocidade(bola *bola, float fator);
