// PrimeiroPrograma.cpp
// Isabel H. Manssour e Marcelo Cohen
// Um programa OpenGL que abre uma janela, desenha uma casa
// e permite fazer zoom, pan e transla��o.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

GLfloat tx, ty;
GLfloat left, right, bottom, top;
GLfloat panX, panY;
GLint largura, altura;

void DesenhaEixos()
{
    glColor3ub(255,255,255);
	glBegin(GL_LINES);
		glVertex2f(0.0,bottom);
		glVertex2f(0.0,top);
		glVertex2f(left,0);
		glVertex2f(right,0);
	glEnd();
}
// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    // Estabelece a janela de sele��o (esquerda, direita, inferior,
	// superior) mantendo a propor��o com a janela de visualiza��o
	if (largura <= altura)
		gluOrtho2D (left+panX, right+panX, bottom*altura/largura+panY, top*altura/largura+panY);
	else
		gluOrtho2D (left*largura/altura+panX, right*largura/altura+panX, bottom+panY, top+panY);
	glMatrixMode(GL_MODELVIEW);

	// Limpa a janela de visualiza��o com a cor branca
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	DesenhaEixos();
	glTranslatef(tx, ty, 0);
	// Execu��o dos comandos de desenho
	glutSwapBuffers();
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa(void)
{
    // Inicializa��o das vari�veis globais
    tx = 0;
    ty = 0;
	left = -1.0;
	right = 1.0;
	bottom = -1.0;
	top = 1.0;
	panX = panY = 0;
	largura = 400;
	altura = 400;

	// Define a janela de visualiza��o 2D
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(left+panX, right+panX, bottom+panY, top+panY);
	glMatrixMode(GL_MODELVIEW);
}

// Programa Principal
int main(void)
{
	int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

	glutInit(&argc,argv);

	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(400,400);
	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Primeiro Programa");
	// Registra callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);
	// Chama a fun��o respons�vel por fazer as inicializa��es
	Inicializa();
	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}
