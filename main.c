#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "jogador.h"
#include "bola.h"

#define LARGURA_MUNDO 1000
#define ALTURA_MUNDO 1000
#define LARGURA_JOGADOR 20
#define PONTOS_SET 11

bool pause=false, reinicia=false, sai=false;
int ganhador=0, textura_fundo;
jogador p1={-1, 0, 0.1*ALTURA_MUNDO, 0, 0}, p2={1, 0, 0.1*ALTURA_MUNDO, 0, 0};
bola b={0, 0, 20, 6, 3, 0};

unsigned int carregar_textura(char* arquivo){
    unsigned int id = SOIL_load_OGL_texture(arquivo, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    if(!id)
        printf("Erro carregando a textura '%s': '%s'\n", arquivo, SOIL_last_result());

    return id;
}

void fundo(){
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textura_fundo);
		glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(1, 1);
			glVertex2f(+LARGURA_MUNDO/2, +ALTURA_MUNDO/2);
			glTexCoord2f(0, 1);
			glVertex2f(-LARGURA_MUNDO/2, +ALTURA_MUNDO/2);
			glTexCoord2f(0, 0);
			glVertex2f(-LARGURA_MUNDO/2, -ALTURA_MUNDO/2);
			glTexCoord2f(1, 0);
			glVertex2f(+LARGURA_MUNDO/2, -ALTURA_MUNDO/2);
		glEnd();
	glDisable(GL_TEXTURE_2D);
}

void bolinha(bola b){
	glPushMatrix();
		glTranslatef(b.x, b.y, 0);
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, b.textura);
			glBegin(GL_TRIANGLE_FAN);
				glTexCoord2f(1, 1);
				glVertex2f(+b.tamanho/2, +b.tamanho/2);
				glTexCoord2f(0, 1);
				glVertex2f(-b.tamanho/2, +b.tamanho/2);
				glTexCoord2f(0, 0);
				glVertex2f(-b.tamanho/2, -b.tamanho/2);
				glTexCoord2f(1, 0);
				glVertex2f(+b.tamanho/2, -b.tamanho/2);
			glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void raquete(jogador j){
	float jogador_x=j.lado*(LARGURA_MUNDO/2-LARGURA_JOGADOR/2);
	glPushMatrix();
		glTranslatef(jogador_x, j.y, 0);
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, j.textura);
			glBegin(GL_TRIANGLE_FAN);
				glTexCoord2f(1, 1);
				glVertex2f(+LARGURA_JOGADOR/2, +j.tamanho/2);
				glTexCoord2f(0, 1);
				glVertex2f(-LARGURA_JOGADOR/2, +j.tamanho/2);
				glTexCoord2f(0, 0);
				glVertex2f(-LARGURA_JOGADOR/2, -j.tamanho/2);
				glTexCoord2f(1, 0);
				glVertex2f(+LARGURA_JOGADOR/2, -j.tamanho/2);
			glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void mensagem(){
	char placar[10];
	int posicao;

	glRasterPos3f(-200, 150, 0);
	if(reinicia)
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, "PRESSIONE NOVAMENTE PARA PAUSAR");
	if(sai)
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, "PRESSIONE NOVAMENTE PARA SAIR");

	glRasterPos3f(-37, 120, 0);
	if(pause)
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, "PAUSE");

	strcpy(placar, "P  GANHOU");
	switch(ganhador){
		case -1:
			placar[1]	='1';
			break;
		case 1:
			placar[1]='2';
			break;
		case 0:
			placar[0]=p1.pontos/10+'0';
			placar[1]=p1.pontos%10+'0';
			placar[2]=' ';
			placar[3]='-';
			placar[4]=' ';
			placar[5]=p2.pontos/10+'0';
			placar[6]=p2.pontos%10+'0';
			placar[7]='\0';
			break;
		}

	glRasterPos3f(-37, 90, 0);
	for(posicao=0;placar[posicao]!='\0';posicao++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, placar[posicao]);
}

void desenhar(){
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 1, 1);
	fundo();
	raquete(p1);
	raquete(p2);
	bolinha(b);
	mensagem();

	glutSwapBuffers();
}

void reiniciar(){
	if(reinicia){
		centralizar(&b);
		reset(&p1);
		reset(&p2);
		reinicia=false;
	}
	else
		reinicia=true;
		sai=false;
}

void sair(){
	if(sai)
		exit(0);
	else
		sai=true;
		reinicia=false;
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'w':
		case 'W':
			subir(&p1, ALTURA_MUNDO/2);
			break;
		case 's':
		case 'S':
			descer(&p1, -ALTURA_MUNDO/2);
			break;
		case '1':
			subir(&p2, ALTURA_MUNDO/2);
			break;
		case '0':
			descer(&p2, -ALTURA_MUNDO/2);
			break;
		case 'p':
		case 'P':
			pause^=true;
			break;
		case 'r':
		case 'R':
			reiniciar();
			break;
		case 27:
			sair();
			break;
	}
}

// void special(int key, int x, int y){
// 	switch(key){
// 		case GLUT_KEY_UP:
// 			subir(&p2, ALTURA_MUNDO/2);
// 			break;
// 		case GLUT_KEY_DOWN:
// 			descer(&p2, -ALTURA_MUNDO/2);
// 			break;
// 	}
// }

void atualiza(int periodo){
	float topo_fundo, laterais_jogadores, limite_laterais;

	//topo e fundo
	topo_fundo=ALTURA_MUNDO/2-b.tamanho/2;
	if(b.y>topo_fundo || b.y<-topo_fundo)
		b.vy*=-1;

	//colisão raquetes
	//problemas aqui, necessário remodelar detecçao de colisão
	laterais_jogadores=LARGURA_MUNDO/2-LARGURA_JOGADOR;
	if(b.x-b.tamanho/2<-laterais_jogadores)
		if(b.y<(p1.y+p1.tamanho/2+b.tamanho/2) && b.y>(p1.y-p1.tamanho/2-b.tamanho/2))
			inverter_x(&b);
	if(b.x+b.tamanho/2>laterais_jogadores)
		if(b.y<(p2.y+p2.tamanho/2+b.tamanho/2) && b.y>(p2.y-p2.tamanho/2-b.tamanho/2))
			inverter_x(&b);

	limite_laterais=LARGURA_MUNDO/2;
	if(b.x+b.tamanho/2>limite_laterais){
		if(pontuar(&p1, PONTOS_SET)){
			ganhador=-1;
			pause^=true;
			reset(&p1);
			reset(&p2);
		}
		else
			ganhador=0;

		inverter_x(&b);
		centralizar(&b);
	}
	if(b.x-b.tamanho/2<-limite_laterais){
		if(pontuar(&p2, PONTOS_SET)){
			ganhador=1;
			pause^=true;
			reset(&p1);
			reset(&p2);
		}
		else
			ganhador=0;

		inverter_x(&b);
		centralizar(&b);
	}

	if(!pause)
		rolar(&b);

	glutPostRedisplay();
	glutTimerFunc(periodo, atualiza, periodo);
}

void redimensiona(int largura, int altura){
    typedef struct viewport{
			float x;
			float y;
			float largura;
			float altura;
		} viewport;

		viewport vp;
		float razao_janela, razao_mundo;

		glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-LARGURA_MUNDO/2, LARGURA_MUNDO/2, -ALTURA_MUNDO/2, ALTURA_MUNDO/2, -1, 1);

    razao_janela = (float)largura/altura;
    razao_mundo = (float)LARGURA_MUNDO/ALTURA_MUNDO;

    if(razao_janela<razao_mundo){
			vp.altura = largura/razao_mundo;
			vp.y = (altura-vp.altura)/2;
			glViewport(0, vp.y, largura, vp.altura);
    }
    else if(razao_janela>razao_mundo){
			vp.largura = (float)altura*razao_mundo;
			vp.x = (largura-vp.largura)/2;
			glViewport(vp.x, 0, vp.largura, altura);
    }
		else
    	glViewport(0, 0, largura, altura);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void inicializar(){
    glClearColor(0, 0, 0, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    textura_fundo=carregar_textura("texturas/fundo.png");
		b.textura = carregar_textura("texturas/bola.png");
		p1.textura = carregar_textura("texturas/p1.png");
		p2.textura = carregar_textura("texturas/p2.png");
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Ping Phong");

	inicializar();

	glutDisplayFunc(desenhar);
	glutReshapeFunc(redimensiona);
	glutKeyboardFunc(keyboard);
	//glutSpecialFunc(special);
	glutTimerFunc(0, atualiza, 10);

	glutMainLoop();

	return 0;
}
