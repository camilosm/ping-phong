#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include "jogador.h"
#include "bola.h"

jogador p1={true, 0, 0}, p2={false, 0, 0};
bola b={5, 0, 0, -3, 2};

void bolinha(bola b){
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(b.x,b.y,0);
		glVertex3f(b.x+10,b.y+10,0);
		glVertex3f(b.x-10,b.y+10,0);
		glVertex3f(b.x-10,b.y-10,0);
		glVertex3f(b.x+10,b.y-10,0);
		glVertex3f(b.x+10,b.y+10,0);
	glEnd();
}

void retangulo(jogador j){
	glBegin(GL_TRIANGLE_FAN);
		if(j.lado){
			glVertex3f(-500,j.y-50,0);
			glVertex3f(-480,j.y-50,0);
			glVertex3f(-480,j.y+50,0);
			glVertex3f(-500,j.y+50,0);
		}
		else{
			glVertex3f(480,j.y-50,0);
			glVertex3f(500,j.y-50,0);
			glVertex3f(500,j.y+50,0);
			glVertex3f(480,j.y+50,0);
		}
	glEnd();
}

void desenhar(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 1);
	retangulo(p1);
	retangulo(p2);
	bolinha(b);
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'w':
			if(p1.y<450)
				p1.y+=50;
			break;
		case 's':
			if(p1.y>-450)
				p1.y-=50;
			break;
		case 27:
			exit(0);
	}
}

void special(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
			if(p2.y<450)
				p2.y+=50;
			break;
		case GLUT_KEY_DOWN:
			if(p2.y>-450)
				p2.y-=50;
			break;
		case 27:
			exit(0);
	}
}

void atualiza(int periodo){
	//topo e fundo
	if(b.y>490 || b.y<-490)
		b.vy*=-1;

	//laterais
	if(b.x<-480)
		if(b.y<p1.y+60 && b.y>p1.y-60)
			b.vx*=-1;
	if(b.x>480)
		if(b.y<p2.y+60 && b.y>p2.y-60)
			b.vx*=-1;

	if(b.x>495){
		p1.pontos++;
		b.x=0;
		b.y=0;
	}

	if(b.x<-495){
		p2.pontos++;
		b.x=0;
		b.y=0;
	}

	b.x+=b.vx;
	b.y+=b.vy;

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