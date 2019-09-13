#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include "jogador.h"
#include "bola.h"

bool pause=false, reinicia=false, sai=false;
jogador p1={true, 0, 50, 0}, p2={false, 0, 50, 0};
bola b={0, 0, 10, 3, 2};

void bolinha(bola b){
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(b.x,b.y);
		glVertex2f(b.x+b.tamanho/2,b.y+b.tamanho/2);
		glVertex2f(b.x-b.tamanho/2,b.y+b.tamanho/2);
		glVertex2f(b.x-b.tamanho/2,b.y-b.tamanho/2);
		glVertex2f(b.x+b.tamanho/2,b.y-b.tamanho/2);
		glVertex2f(b.x+b.tamanho/2,b.y+b.tamanho/2);
	glEnd();
}

void retangulo(jogador j){
	glBegin(GL_TRIANGLE_FAN);
		if(j.lado){
			glVertex2f(-500,j.y-j.tamanho/2);
			glVertex2f(-480,j.y-j.tamanho/2);
			glVertex2f(-480,j.y+j.tamanho/2);
			glVertex2f(-500,j.y+j.tamanho/2);
		}
		else{
			glVertex2f(480,j.y-j.tamanho/2);
			glVertex2f(500,j.y-j.tamanho/2);
			glVertex2f(500,j.y+j.tamanho/2);
			glVertex2f(480,j.y+j.tamanho/2);
		}
	glEnd();
}

void desenhar(){
	char pt1, pt2;
	pt1=p1.pontos+'0';
	pt2=p2.pontos+'0';

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 1);
	retangulo(p1);
	retangulo(p2);
	bolinha(b);

	glRasterPos3f(-200, 60, 0);
	if(reinicia)
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, "PRESSIONE NOVAMENTE PARA REINICIAR");
	if(sai)
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, "PRESSIONE NOVAMENTE PARA SAIR");

	glRasterPos3f(-38, 30, 0);
	if(pause)
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, "PAUSE");

	glRasterPos3f(-25, 0, 0);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, pt1);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, " - ");
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, pt2);

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
			if(p1.y<450)
				subir(&p1);
			break;
		case 's':
		case 'S':
			if(p1.y>-450)
				descer(&p1);
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

void special(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
			if(p2.y<450)
				subir(&p2);
			break;
		case GLUT_KEY_DOWN:
			if(p2.y>-450)
				descer(&p2);
			break;
	}
}

void atualiza(int periodo){
	//topo e fundo
	if(b.y>490 || b.y<-490)
		b.vy*=-1;

	//laterais
	if(b.x<-480)
		if(b.y<(p1.y+p1.tamanho/2+b.tamanho/2) && b.y>(p1.y-p1.tamanho/2-b.tamanho/2))
			inverter_x(&b);
	if(b.x>480)
		if(b.y<(p2.y+p2.tamanho/2+b.tamanho/2) && b.y>(p2.y-p2.tamanho/2-b.tamanho/2))
			inverter_x(&b);

	if(b.x>495){
		pontuar(&p1);
		centralizar(&b);
	}

	if(b.x<-495){
		pontuar(&p2);
		centralizar(&b);
	}

	if(!pause)
		rolar(&b);

	glutPostRedisplay();
	glutTimerFunc(periodo, atualiza, periodo);
}

void redimensiona(int largura, int altura){
	glViewport(0, 0, largura, altura);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-500, 500, -500, 500, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Ping Phong");
	glClearColor(0, 0, 0, 0);

	glutDisplayFunc(desenhar);
	glutReshapeFunc(redimensiona);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutTimerFunc(0, atualiza, 15);

	glutMainLoop();
	return 0;
}
