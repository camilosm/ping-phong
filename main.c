#include <GL/glew.h>
#include <GL/freeglut.h>
#include "jogador.h"
#include "bola.h"

jogador p1={true, 0, 0}, p2={false, 0, 0};
bola b={5, 0, 0, 1, 1};

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
	glColor3f(1, 1, 1);
	retangulo(p1);
	retangulo(p2);
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'w':
			p1.y++;
			break;
		case 's':
			p1.y--;
			break;
		case 27:
			exit(0);
	}
}

void special(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
			p2.y+=100;
			break;
		case GLUT_KEY_DOWN:
			p2.y-=100;
			break;
		case 27:
			exit(0);
	}
}

void atualiza(int periodo){
	if(b.x>500 || b.x<-500)
		b.vx*=-1;
	if(b.y>500 || b.y<-500)
		b.vy*=-1;
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
