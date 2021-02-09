//  Bibliotecas a incluir //////////////////////////////////////////////////////
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <Windows.h>
//
// Constantes //////////////////////////////////////////////////////////////////
//
#ifndef M_PI
#define ESCAPE 27
#define M_PI 3.14159265
#endif
int largura_janela = 800;					  // largura da nossa janela de visualização
int altura_janela = 600;					   // altura da nossa janela de visualização
double razao_aspeto = 1;		   // razão de aspecto da janela de visualização

double limite_z_anterior = 1;			            // plano de recorte anterior
double limite_z_posterior = 10000;		           // plano de recorte posterior

double camara_x = 100;					                // posição da câmara (x)
double camara_y = 100;					                // posição da câmara (y)
double camara_z = 1000;					                // posição da câmara (z)

double mira_x = 1;				        // direção de visualização da câmara (x)
double mira_y = 1;				        // direção de visualização da câmara (y)
double mira_z = 1;				        // direção de visualização da câmara (z)

double teta_x = 0;				                         // orientação da câmara
double teta_z = 0;				                         // orientação da câmara
double campo_visao_y = 50;		                          // campo de visão em y


float move_x = -2.5;
float angle = 0;
boolean automatico = TRUE;
float view_rotx = 0;
float view_roty = 0;
float view_rotz = 0;


void Font(void *font, char *text, float x, float y)
{
	glRasterPos2f(x, y);

	while (*text != '\0')
	{
		glutBitmapCharacter(font, *text);
		++text;
	}
}



void desenhaUI(void) {
	//zona da UI
	glPushMatrix();
	glViewport(0, 0, 800, 100);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST);

	//fundo
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2f(-100, -100);
	glVertex2f(100, -100);
	glVertex2f(100, 100);
	glVertex2f(-100, 100);
	glEnd();

	//separador
	glColor3f(0.4, 0.4, 0.9);
	glLineWidth(5.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-8, 5.8);
	glVertex2f(8, 5.8);
	glEnd();
	//separador vertical
	glBegin(GL_LINE_LOOP);
	glVertex2f(3, 6);
	glVertex2f(3, -6);
	glEnd();

	//linha do eixo
	glColor3f(0, 0, 0);
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-7, 0);
	glVertex2f(2, 0);
	glEnd();
	//marcas + e -
	//-
	glBegin(GL_LINE_LOOP);
	glVertex2f(-7.7, 0);
	glVertex2f(-7.3, 0);
	glEnd();
	//+
	glBegin(GL_LINE_LOOP);
	glVertex2f(2.45, 1);
	glVertex2f(2.45, -1);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex2f(2.3, 0);
	glVertex2f(2.6, 0);
	glEnd();
	//origem
	glBegin(GL_LINE_LOOP);
	glVertex2f(-2.50, 2.2);
	glVertex2f(-2.50, -2.2);
	glEnd();
	glPopMatrix();

	//quadrado para seleccionar
	glPushMatrix();
	glTranslatef(move_x, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(-0.2, -2);
	glVertex2f(0.2, -2);
	glVertex2f(0.2, 2);
	glVertex2f(-0.2, 2);
	glEnd();
	glPopMatrix();



	Font(GLUT_BITMAP_HELVETICA_18, "Modo:", 5, 3.5);

	glBegin(GL_POLYGON);
	glVertex2f(4.9, -2);
	glVertex2f(6.1, -2);
	glVertex2f(6.1, 2);
	glVertex2f(4.9, 2);
	glEnd();
	Font(GLUT_BITMAP_HELVETICA_18, "MAN", 4, -0.7);
	Font(GLUT_BITMAP_HELVETICA_18, "AUTO", 6.2, -0.7);

	glColor3f(1, 1, 1);
	if (automatico == TRUE) {
		glBegin(GL_POLYGON);
		glVertex2f(5.8, -1.9);
		glVertex2f(6, -1.9);
		glVertex2f(6, 1.9);
		glVertex2f(5.8, 1.9);
		glEnd();
	}
	else if (automatico == FALSE) {
		glBegin(GL_POLYGON);
		glVertex2f(5, -1.9);
		glVertex2f(5.2, -1.9);
		glVertex2f(5.2, 1.9);
		glVertex2f(5, 1.9);
		glEnd();
	}
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

}

void MouseButton(int button, int state, int x, int y)
{

	if (state == GLUT_DOWN)
	{
		switch (button)
		{

		case GLUT_LEFT_BUTTON:

			if (x >= 645 && x <= 707 && y >= 530 && y <= 570) {
				automatico = !automatico;
				move_x = -2.5;
				break;
			}
		default:
			break;
		}
	}
}


void Mover(int x, int y)
{
	float k = x;
	float move_x_temp = (k / 50) - 8;
	if (move_x_temp <= 3 && y >= 530 && y <= 570) { //para nao mexer no slider quando se carrega no botao
		if (move_x_temp <= -7)move_x = -7;
		else if (move_x_temp >= 2) move_x = 2;
		else {
			move_x = move_x_temp;
		}
	}
	//RATO TEM DE ESTAR ENTRE 50 e 500

	glutPostRedisplay();
}


void roda2D(float raio, float largura, int dentes, float tamanho, float min, float max, float da, boolean sentido)
{
	float alpha;
	if (sentido == 1)
	{
		glNormal3f(0.0, 0.0, 1.0);
		glBegin(GL_QUAD_STRIP);
		for (int i = 0; i <= dentes; i++)
		{
			alpha = i * 2.0 * M_PI / dentes;
			glVertex3f(0, 0, largura * 0.5);
			glVertex3f(min * cos(alpha), min * sin(alpha), largura * 0.5);
			glVertex3f(0, 0, largura * 0.5);
			glVertex3f(min * cos(alpha + 3 * da), min * sin(alpha + 3 * da), largura * 0.5);
		}
		glEnd();

		glBegin(GL_QUADS);
		for (int i = 0; i < dentes; i++)
		{
			alpha = i * 2.0 * M_PI / dentes;
			glVertex3f(min * cos(alpha), min * sin(alpha), largura * 0.5);
			glVertex3f(max * cos(alpha + da), max * sin(alpha + da), largura * 0.5);
			glVertex3f(max * cos(alpha + 2 * da), max * sin(alpha + 2 * da), largura * 0.5);
			glVertex3f(min * cos(alpha + 3 * da), min * sin(alpha + 3 * da), largura * 0.5);
		}
		glEnd();
	}
	else
	{
		glNormal3f(0.0, 0.0, -1.0);
		glBegin(GL_QUAD_STRIP);
		for (int i = 0; i <= dentes; i++)
		{
			alpha = i * 2.0 * M_PI / dentes;
			glVertex3f(min * cos(alpha), min * sin(alpha), largura * 0.5);
			glVertex3f(0, 0, largura * 0.5);
			glVertex3f(min * cos(alpha + 3 * da), min * sin(alpha + 3 * da), largura * 0.5);
			glVertex3f(0, 0, largura * 0.5);
		}
		glEnd();

		glBegin(GL_QUADS);
		for (int i = 0; i < dentes; i++)
		{
			alpha = i * 2.0 * M_PI / dentes;
			glVertex3f(min * cos(alpha + 3 * da), min * sin(alpha + 3 * da), largura * 0.5);
			glVertex3f(max * cos(alpha + 2 * da), max * sin(alpha + 2 * da), largura * 0.5);
			glVertex3f(max * cos(alpha + da), max * sin(alpha + da), largura * 0.5);
			glVertex3f(min * cos(alpha), min * sin(alpha), largura * 0.5);
		}
		glEnd();
	}

}


void roda3D(float raio, float largura, int dentes, float tamanho)
{
	float min, max, alpha, da;

	min = raio - tamanho / 2;
	max = raio + tamanho / 2;
	da = 2.0 * M_PI / dentes / 4.0;

	roda2D(raio, largura, dentes, tamanho, min, max, da, 1);

	roda2D(raio, -largura, dentes, tamanho, min, max, da, -1);

	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < dentes; i++)
	{
		alpha = i * 2.0 * M_PI / dentes;
		glVertex3f(min * cos(alpha), min * sin(alpha), largura * 0.5);
		glVertex3f(min * cos(alpha), min * sin(alpha), -largura * 0.5);
		glVertex3f(max * cos(alpha + da), max * sin(alpha + da), largura * 0.5);
		glVertex3f(max * cos(alpha + da), max * sin(alpha + da), -largura * 0.5);
		glVertex3f(max * cos(alpha + 2 * da), max * sin(alpha + 2 * da), largura * 0.5);
		glVertex3f(max * cos(alpha + 2 * da), max * sin(alpha + 2 * da), -largura * 0.5);
		glVertex3f(min * cos(alpha + 3 * da), min * sin(alpha + 3 * da), largura * 0.5);
		glVertex3f(min * cos(alpha + 3 * da), min * sin(alpha + 3 * da), -largura * 0.5);
	}

	glVertex3f(min * cos(0), min * sin(0), largura * 0.5);
	glVertex3f(min * cos(0), min * sin(0), -largura * 0.5);
	glEnd();
}

void desenha()
{



	glViewport(0, 100, 800, 500); //IMPORTANTE
								  // posicionamento da câmara virtual com transformações elementares
	glLoadIdentity();
	glTranslatef(-camara_x, -camara_y, -camara_z);
	glRotatef(teta_x, 1, 0, 0);
	glRotatef(teta_z, 0, 0, 1);
	glScalef(1, 1, 1);

	// posicionamento da câmara virtual com função gluLookAt
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(camara_x, camara_y, camara_z, mira_x, mira_y, mira_z, 0, 0, 1);

	// desenha objectos

	glPushMatrix();
	glRotatef(view_rotx, 1.0, 0.0, 0.0);
	glRotatef(view_roty, 0.0, 1.0, 0.0);
	glRotatef(view_rotz, 0.0, 0.0, 1.0);

	glPushMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.0);
	glColor3f(1, 0, 0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	roda3D(100.0, 40.0, 10, 30);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-145, -60, 0.0);
	glColor3f(0, 1, 0);
	glRotatef(-1.6666*angle - 15, 0.0, 0.0, 1.0);
	roda3D(50, 50, 6, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(205, -130, 0.0);
	glColor3f(0, 0, 1);
	glRotatef(-angle - 3, 0.0, 0.0, 1.0);
	roda3D(130, 50, 10, 30);
	glPopMatrix();

	glPopMatrix();


	//tudo o que for 2D tem de ser abaixo desta linha, para separar o que faz cada matriz Modelview/projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-8, 8, -6, 6, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	desenhaUI();

	glMatrixMode(GL_PROJECTION); //regressar à matriz 3D
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);


	glutSwapBuffers();
}

void tecla_premida(unsigned char tecla, int x, int y)
{
	double k = 20;					        // o que a janela aumenta ou desloca

	double nx = mira_x - camara_x;		   // vector de orientação da câmara (x)
	double ny = mira_y - camara_y;		   // vector de orientação da câmara (y)
	double nz = mira_z - camara_z;		   // vector de orientação da câmara (z)

	double n = sqrt(nx*nx + ny * ny + nz * nz);	                      // norma do vector

	double x_mira = mira_x;
	double y_mira = mira_y;
	double xc = camara_x;
	double yc = camara_y;
	double teta = k / 180 * 3.14159265 / 10;

	nx /= n;						                                 // normalização
	ny /= n;
	nz /= n;

	switch (tecla)
	{
	case ESCAPE:			     // tecla de escape, para saída da aplicação
		exit(0);
		break;

	case '+':			  	                                      // zoom in
		campo_visao_y -= k / 2;
		break;

	case '-':			  	                                     // zoom out
		campo_visao_y += k / 2;
		break;

	case 'w':				                              // olhar para cima
		mira_z += k;
		break;

	case 's':			                                 // olhar para baixo
		mira_z -= k;
		break;

	case 'd':			  	                         // olhar para a direita
		mira_x = cos(-teta)*(x_mira - xc) - sin(-teta)*(y_mira - yc) + xc;
		mira_y = sin(-teta)*(x_mira - xc) + cos(-teta)*(y_mira - yc) + yc;
		break;

	case 'a':			  	                        // olhar para a esquerda
		mira_x = cos(teta)*(x_mira - xc) - sin(teta)*(y_mira - yc) + xc;
		mira_y = sin(teta)*(x_mira - xc) + cos(teta)*(y_mira - yc) + yc;
		break;

	case ' ':			  	                              // andar em frente
		camara_x += nx * k;
		mira_x += nx * k;
		camara_y += ny * k;
		mira_y += ny * k;
		camara_z += nz * k;
		mira_z += nz * k;
		break;

	case 'c':			  	                              // andar para trás
		camara_x -= nx * k;
		mira_x -= nx * k;
		camara_y -= ny * k;
		mira_y -= ny * k;
		camara_z -= nz * k;
		mira_z -= nz * k;
		break;

		//rodar o objecto
	case 'i':
		view_rotx += 5.0;
		break;
	case 'k':
		view_rotx -= 5.0;
		break;
	case 'j':
		view_roty += 5.0;
		break;
	case 'l':
		view_roty -= 5.0;
		break;
	default:			  	             // por defeito, não há nenhuma ação
		break;
	}
}

//
//	Função para controlo das ações nas teclas especiais
//	tecla  - tecla premida
//	x,y	   - posição do cursor a tecla do rato e premida
//

void tecla_especial_premida(int tecla, int x, int y)
{
	double k = 20;					        // o que a janela aumenta ou desloca

	double nx = mira_x - camara_x;		   // vector de orientação da câmara (x)
	double ny = mira_y - camara_y;		   // vector de orientação da câmara (y)
	double nz = mira_z - camara_z;		   // vector de orientação da câmara (z)

	double n = sqrt(nx*nx + ny * ny + nz * nz);	                      // norma do vector

	double x_mira = mira_x;
	double y_mira = mira_y;
	double xc = camara_x;
	double yc = camara_y;
	double teta = k / 180 * 3.14159265 / 10;

	nx /= n;						                                 // normalização
	ny /= n;
	nz /= n;

	switch (tecla)
	{
	case GLUT_KEY_UP:			                  // tecla de seta para cima
		camara_z += k;
		mira_z += k;
		break;

	case GLUT_KEY_DOWN:			                 // tecla de seta para baixo
		camara_z -= k;
		mira_z -= k;
		break;

	case GLUT_KEY_LEFT:			                    // tecla para a esquerda
		camara_x -= ny * k;
		camara_y += nx * k;
		mira_x -= ny * k;
		mira_y += nx * k;
		break;

	case GLUT_KEY_RIGHT:		                     // tecla para a direita
		camara_x += ny * k;
		camara_y -= nx * k;
		mira_x += ny * k;
		mira_y -= nx * k;
		break;

	default:				             // por defeito, não há nenhuma ação
		break;
	}
}


//
//	Função para redesenhar a cena
//
void redesenha_cena()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);   // definição da cor de limpeza da janela

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	  // limpeza dos buffers

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);	  // definição do modelo
														  // de iluminação	
	desenha();						                      // desenho
}

//
//	Função de redimensionamento da janela
//
void redimensiona_janela(int param_largura, int param_altura)
{

	if (param_altura == 0)					// teste se a janela está minimizada
	{
		return;
	}
	glutReshapeWindow(800, 600);
	glViewport(0, 0, param_largura, param_altura);

	razao_aspeto = (double)param_largura / (double)param_altura;

	largura_janela = param_largura;				// armazenamento da nova largura
	altura_janela = param_altura;					// armazenamento da nova altura

	glMatrixMode(GL_PROJECTION);			// definição, como matriz activa,
											// da matriz de projecção

	glLoadIdentity();						// reset à matriz activa

	gluPerspective(campo_visao_y, razao_aspeto, limite_z_anterior,
		limite_z_posterior);

	glMatrixMode(GL_MODELVIEW);
}

void mostra_cena(void)
{
	if (automatico == TRUE) angle += (move_x + 2.5) / 10; //modo automatico
	else  angle = move_x * 10; //modo manual

	redesenha_cena();
}
void InitGLUT()
{
	// definição do modo inicial de visualização
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// definição do tamanho inicial da janela de visualização
	glutInitWindowSize(largura_janela, altura_janela);

	// definição da posição inicial da janela
	glutInitWindowPosition(100, 100);

	// criação da janela de visualização
	glutCreateWindow("Mecanismo - Projecto CG 2 - João Barreiros & João Ferreira");

	// chamada da função de redimensionamento
	glutReshapeFunc(redimensiona_janela);

	// redesenho a cena
	glutDisplayFunc(redesenha_cena);

	// ação quando uma tecla e premida
	glutKeyboardFunc(tecla_premida);

	// ação quando uma tecla especial e premida
	glutSpecialFunc(tecla_especial_premida);

	//accao quando se carrega num botao do rato
	glutMouseFunc(MouseButton);

	//accao quando se move o rato
	glutMotionFunc(Mover);

	// função para ir mostrando a cena
	glutIdleFunc(mostra_cena);
}

//
//	Função de inicialização das diversas configurações do OpenGL
//

void InitGL()
{
	// definição da cor do fundo da janela de visualização (azul celeste)
	glClearColor(0.7f, 0.7f, 1.0f, 0.0f);

	// parâmetros de profundidade
	// definição do valor de limpeza do buffer de profundidade
	glClearDepth(1.0);
	// definição da função de comparação de profundidade
	glDepthFunc(GL_LEQUAL);
	// activação do teste de profundidade
	glEnable(GL_DEPTH_TEST);

	// modo de preenchimento de polígonos
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
}

////////////////////////////////////////////////////////////////////////////////
// Programa Principal //////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	printf("\nInstruccoes:\n");
	printf("\nOlhar com a camara:\nA,S,D,W\n");
	printf("\nRodar o objecto: \nI,J,K,L\n");
	printf("\nAndar com Camara para tras e frente: \nc e espaco\n");
	printf("\nAndar com Camara sobre os eixos: \nSetas do teclado\n");

	InitGLUT();

	InitGL();

	glutMainLoop();

	return EXIT_SUCCESS;
}