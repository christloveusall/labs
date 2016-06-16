#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "Point3D.h"
#include "ObjetoGrafico.h"

using namespace std;

/** Constantes **/

/** definição das constantes que identificam o objeto **/
const int CUBE = 0;
const int SPHERE = 1;
const int CONE = 2;
const int DODECAHEDRON = 3;
const int ICOSAEDRO = 4;
const int TEAPOT = 5;
const int TETRAHEDRON = 6;
const int TORUS = 7;
const int OCTAHEDRON = 8;

/** definição dos valores utilizados para as instancias dos objetos **/
GLdouble base = 5;
GLdouble height = 5;
GLint slices = 5;
GLint stacks = 5;
GLdouble size = 5;
GLdouble innerRadius = 5;
GLdouble outerRadius = 5;
GLdouble nsides = 5;
GLdouble rings = 5;

const int NRO_QDO_INTERMEDIARIOS = 100;

/** Variáveis **/
GLfloat angle, fAspect, rotX, rotY, obsZ;
GLfloat ratio;
GLint quadro;
GLint quadroChave;
GLint QuadroAnterior;
GLint QuadroSeguinte;


/** guarda os objetos graficos estanciados pelo o usuário **/
ObjetoGrafico* lista[2];

void inicializarLista() {

    lista[0] = new ObjetoGrafico(CUBE);
    Point3D* p1 = new Point3D(0, 0, 10);
    lista[0]->SetTranslacao(*p1);
    lista[0]->SetPosAltura(-9);
    lista[0]->SetPosInicial(10);
    lista[0]->SetPosInicial(-10);
    lista[0]->SetTX1(-10);
    lista[0]->SetTX2(10);
    lista[0]->SetRY1(0);
    lista[0]->SetRY2(360);

    lista[1] = new ObjetoGrafico(SPHERE);
    Point3D* p2 = new Point3D(0, 0, 10);
    lista[1]->SetTranslacao(*p2);
    lista[1]->SetPosAltura(9);
    lista[1]->SetPosInicial(10);
    lista[1]->SetPosInicial(-10);
    lista[1]->SetTX1(5);
    lista[1]->SetTX2(10);
    lista[1]->SetRY1(0);
    lista[1]->SetRY2(360);


    lista[1] = new ObjetoGrafico(CONE);
    Point3D* p3 = new Point3D(0, 0, 10);
    lista[1]->SetTranslacao(*p3);
    lista[1]->SetPosAltura(14);
    lista[1]->SetPosInicial(10);
    lista[1]->SetPosInicial(-10);
    lista[1]->SetTX1(15);
    lista[1]->SetTX2(-10);
    lista[1]->SetRY1(0);
    lista[1]->SetRY2(360);
}

/** Função responsável pela especificação dos parâmetros de iluminação **/
void DefineIluminacao (void)
{
    /** Define cores para um objeto dourado **/
    GLfloat LuzAmbiente[]   = {0.24725f, 0.1995f, 0.07f } ;
    GLfloat LuzDifusa[]   = {0.75164f, 0.60648f, 0.22648f, 1.0f };
    GLfloat LuzEspecular[] = {0.626281f, 0.555802f, 0.366065f, 1.0f };
    GLfloat PosicaoLuz0[]  = {3.0f, 3.0f, 0.0f, 1.0f };
    GLfloat PosicaoLuz1[]  = {-3.0f, -3.0f, 0.0f, 1.0f };
    GLfloat Especularidade[] = {1.0f, 1.0f, 1.0f, 1.0f };

    // Ativa o "Color Tracking"
	glEnable (GL_COLOR_MATERIAL);

    // Habilita o uso de iluminação
    glEnable(GL_LIGHTING);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);

    // Define os parametros da Luz número Zero
    glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa  );
    glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular  );
    glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0 );
    glEnable(GL_LIGHT0);

    // Define a reflectancia do material
    glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);

    // Define a concentração do brilho.
    // Quanto maior o valor do Segundo parametro, mais
    // concentrado será o brilho. (Valores válidos: de 0 a 128)
    glMateriali(GL_FRONT,GL_SHININESS,51);

    // Define os parametros da Luz número Um
    glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusa  );
    glLightfv(GL_LIGHT1, GL_SPECULAR, LuzEspecular  );
    glLightfv(GL_LIGHT1, GL_POSITION, PosicaoLuz1 );
    glEnable(GL_LIGHT1);

    // Define a reflectancia do material
    glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);

    // Define a concentração do brilho.
    // Quanto maior o valor do Segundo parametro, mais
    // concentrado será o brilho. (Valores válidos: de 0 a 128)
    glMateriali(GL_FRONT,GL_SHININESS,20);
}

// Função usada para especificar a posição do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	glTranslatef(0,0,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	PosicionaObservador();
}

/** Função que desenha um objeto **/
void DesenhaObjeto(int obj)
{
    switch (obj)
    {
        case CUBE: glutSolidCube(2);
                break;
        /** glutSolidSphere(radius, slices, stacks) **/
        case SPHERE: glutSolidSphere(5, 5, 5);
                break;
        /** glutSolidCone(base ,height ,slices, stacks) **/
        case CONE: glutSolidCone(base ,height ,slices, stacks);
                break;
        case DODECAHEDRON: glutSolidDodecahedron();
                break;
        case ICOSAEDRO: glutSolidIcosahedron();
                break;
        case TEAPOT: glutSolidTeapot(size);
                break;
        case TETRAHEDRON: glutSolidTetrahedron();
                break;
        case TORUS: glutSolidTorus(innerRadius, outerRadius, nsides, rings);
                break;
        case OCTAHEDRON: glutSolidOctahedron();
                break;
    }
}

/** Função que desenha um objeto no quadro especificado por parâmetro **/
void DesenhaObjetoNoQuadro (int obj, int quadrocorrente, int QChave_anterior, int QChave_seguinte)
{
    for(int i = 0 ; i < 2; i++){
        //float TX1, TX2, RY1, RY2;
        float TX, TY, TZ, RX, RY, RZ;

        /** Neste exemplo, como a estrutura de dados não existe, **/
        /** os valores são especificados à mão... **/
        /**
        TX1 = -10;
        TX2 =  10;
        RY1 = 0;
        RY2 = 360;
        **/

        /** Calcula o valor da translação e rotação no quadro corrente **/
        TX = (lista[i]->getTX2()-lista[i]->getTX1()) / NRO_QDO_INTERMEDIARIOS * quadrocorrente + lista[i]->getTX1();
        RY = (lista[i]->getRY2()-lista[i]->getRY1()) / NRO_QDO_INTERMEDIARIOS * quadrocorrente + lista[i]->getRY1();

        /** fazer o mesmo para TY, TZ, RX e RZ **/
        TY=TZ=RX=RZ=0;

        // desenha o objeto
        glPushMatrix();
            glTranslatef(TX, TY, TZ);
            glRotatef(RX, 1,0,0);
            glRotatef(RY, 0,1,0);
            glRotatef(RX, 0,0,1);
            DesenhaObjeto(obj);
        glPopMatrix();
    }
}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
	static double angY = 0;

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	DefineIluminacao();
	EspecificaParametrosVisualizacao();

	for(int i = 0; i < 2; i++) {

	DesenhaObjetoNoQuadro (lista[i]->getTipoDoObjeto(), // objeto a ser desenhado
                           quadro, // nro do quadro intermediário atual
                           QuadroAnterior, // nro do quadro chave anterior ao quadro intermediário
                           QuadroSeguinte); // nro do quadro chave seguinte ao quadro intermediário

	}

    // se não exibiu todos os quadros intermediários, passa para o próximo
	if (quadro < NRO_QDO_INTERMEDIARIOS)
	   quadro++;
 	else quadro=0; /** aqui o correto será avançar os nros dos Quadro-Chave **/

	/** Executa os comandos OpenGL **/
	glutSwapBuffers();
 }

 void SelecionaQuadroChave()
{
	static double angY = 0;

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	DefineIluminacao();
	EspecificaParametrosVisualizacao();

	DesenhaObjetoNoQuadro (CUBE, quadroChave, QuadroAnterior, QuadroSeguinte);

	glutSwapBuffers();
 }

void TodosQuadroChave() {
    static double angY = 0;

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	DefineIluminacao();
	EspecificaParametrosVisualizacao();

	DesenhaObjetoNoQuadro (CUBE, 0, QuadroAnterior, QuadroSeguinte);
    DesenhaObjetoNoQuadro (CUBE, 50, QuadroAnterior, QuadroSeguinte);
    DesenhaObjetoNoQuadro (CUBE, 100, QuadroAnterior, QuadroSeguinte);

	glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fundo de tela preto

	/** Inicializa as variáveis usadas para alterar a posição do **/
	/** observador virtual **/
	rotX = 30;
	rotY = 0;
	obsZ = 50;

	/** Inicializa a variável que especifica o ângulo da projeção **/
	/** perspectiva **/
	angle=30;

    quadro = 0;
    QuadroAnterior = 1;
    QuadroSeguinte = 2;

	glShadeModel(GL_SMOOTH);
	glColorMaterial (GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_DEPTH_TEST);
	glEnable (GL_CULL_FACE);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

/** Função callback chamada para gerenciar eventos de teclas **/
void Teclado (unsigned char tecla, int x, int y)
{
	if(tecla==27) /** ESC ? **/
		exit(0);
    if(tecla=='0') /** cria o primeiro quadro chave **/
        quadroChave = 0;
		SelecionaQuadroChave();
    if(tecla=='1') /** cria o primeiro quadro chave **/
        quadroChave = 50;
		SelecionaQuadroChave();
    if(tecla=='2') /** cria o primeiro quadro chave **/
        quadroChave = 100;
		SelecionaQuadroChave();
    /**
        TODO: ainda é preciso fazer para os outros quadros: 0'...'9'.
    **/
}

/** Função callback chamada pela GLUT a cada intervalo de tempo **/
void Anima(int value)
{
	// Faz o redesenho
	glutPostRedisplay();
	glutTimerFunc(60,Anima, 1);
}

/** Função callback chamada para gerenciar eventos de teclas especiais (F1,PgDn,...) **/
void TeclasEspeciais (int tecla, int x, int y)
{
	switch (tecla)
	{
		case GLUT_KEY_LEFT:	rotY--;
							break;
		case GLUT_KEY_RIGHT:rotY++;
							break;
		case GLUT_KEY_UP:	rotX++;
							break;
		case GLUT_KEY_DOWN:	rotX--;
							break;
        /** Modos de Exibição: Por quadro-chave **/
		case GLUT_KEY_HOME:	glutDisplayFunc(TodosQuadroChave);;
							break;
        /** Modos de Exibição: Por objeto **/
		case GLUT_KEY_END:	glutDisplayFunc(SelecionaQuadroChave);
							break;
        /** Modo de animação **/
		case GLUT_KEY_F1:   glutDisplayFunc(Desenha);
                            break;
	}
	PosicionaObservador();
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN)   // Zoom in
			if (angle >= 10) angle -= 5;

	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN)   // Zoom out
			if (angle <= 130) angle += 5;

	EspecificaParametrosVisualizacao();
}

// Programa Principal
int main(void)
{
    inicializarLista();
    int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

	glutInit(&argc,argv);

	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,350);
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Animacao por Quadros Chave");
	// Registra callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);
	/** Registra a função callback para tratamento das teclas ASCII **/
	glutKeyboardFunc (Teclado);
    /** Registra a função callback para tratamento das teclas especiais **/
	glutSpecialFunc (TeclasEspeciais);
	// Registra a função callback que gerencia os eventos do mouse
	glutMouseFunc(GerenciaMouse);
	// Registra a função callback que será chamada a cada intervalo de tempo
	glutTimerFunc(60, Anima, 1);
	// Registra a função callback de redimensionamento da janela de visualização
    glutReshapeFunc(AlteraTamanhoJanela);
	// Chama a função responsável por fazer as inicializações
	Inicializa();
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
