#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include <conio.h>
#include <iostream>
#include <fstream>

using namespace std;

 struct Nodo{
      int classificacao;
      char pais[30];
      float consumo;
};

void leArquivoDeDados() {


    struct Nodo nodo[35];

    FILE *f = fopen("dados.csv","r");

    int x;
    for(x=0;x<35/*tamanho do vetor*/;x++){
    /* %d - l� um inteiro
       %30[^;] - l� os bytes at� o caractere ';'
       %f - l� um float
    */
        fscanf(f,"%d;%30[^;];%f\n", &nodo[x].classificacao, nodo[x].pais, &nodo[x].consumo); // l� os dados e armazena em nodo
        printf("%d - %s - %f\n", nodo[x].classificacao, nodo[x].pais, nodo[x].consumo);
    }
}

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void) {
	// Limpa a janela de visualiza��o com a cor branca
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(0.0f,0.0f,1.0f); // Define a cor de desenho: azul
	glBegin(GL_TRIANGLES); // Desenha tri�ngulo no centro da janela
		glVertex2f(-0.5,-0.5);
		glVertex2f( 0.0, 0.5);
		glVertex2f( 0.5,-0.5);
	glEnd();
	// Execu��o dos comandos de desenho
	glutSwapBuffers();
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa(void)
{
	// Define a janela de visualiza��o 2D
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-1.0,1.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
}

// Programa Principal
int main(void)
{
    leArquivoDeDados();
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
	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);
	// Chama a fun��o respons�vel por fazer as inicializa��es
	Inicializa();
	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();


	return 0;
}

