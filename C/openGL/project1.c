#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
/**                                                    ,---------------.     **/
/**    COMPUTACAO GRAFICA                              |        .-.    |     **/
/**    MIEEC - FCTUC                                   |        !o|    |     **/
/**                                                    |>-,   ,-' | ,-<|     **/
/**    AUTORES: - João Barreiros, 2014196880           |  `---'   `-'  |     **/
/**             - João Ferreira, 2013139657            `---------------'     **/
/******************************************************************************/
/* DESCRICAO: PROJETO 1: Programa que suporta a Gestão Financeira Familiar..  */
/*            ..............................................................  */
/*            ..............................................................  */
/******************************************************************************/
//
//  Bibliotecas a incluir //////////////////////////////////////////////////////
//
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <math.h>
#include <string.h>
#include <time.h>
//
//  Definições e Variáveis globais /////////////////////////////////////////////
//
#define PI    3.1415927
#define largura 1280
#define altura 720
#define MAX 6000
#define larguraMenu 0
//===============================================================================
int diaAtual, mesAtual, anoAtual;
int NumeroDados = 0;
int modoDeVisualizacao = 0;
int currentTab = 0;
int currentM;
int currentM2;
int currentA;
int currentA2 = 10;
float rateAnim = 0;
//Cores da interface
const float fundoR = 0.64;
const float fundoG = 0.82;
const float fundoB = 0.85;
const float menuR = 0.25;
const float menuG = 0.25;
const float menuB = 0.25;
const float btt = 0.68;
//===============================================================================
//
// Estruturas
//
// estrutura que representa a informação do rato
typedef struct Rato
{
	int x, y;   // coordenadas x e y do rato
	int lmb;    // botão esquerdo do rato
	int mmb;    // botão central do rato
	int rmb;    // botão direito do rato
	int xpress, ypress; // coordenadas x e y do botão pressionado
}Rato;
Rato rato = { 0, 0, 0, 0, 0 };
//===============================================================================
typedef void(*ButtonCallback)();
// estrutura dos botões
typedef struct Botao
{
	int id;
	int x, y;                         // coordenadas x e y do botão
	int width, height;                // comprimento e altura do botão
	int state;						  // estado do botão (1- pressionado,0- não pressionado)
	boolean hover;					  // rato sobre botao
	char* label;                      // texto do botão
	ButtonCallback callbackFunction;  // função a chamar quando botão for pressionado
}Botao;
//===============================================================================
typedef struct Familia
{
	int ID;
	char name[100];  // nome da familia
	float orcamentoAnual;
	float *gastoTotalDia;
	float *custoAlimentacaoDia;
	float *custoVestuarioDia;
	float *custoDeslocacoesDia;
	float *custoLazerDia;
	float *custoOutrosDia;
	float corAli[3];
	float corVes[3];
	float corDes[3];
	float corLaz[3];
	float corOut[3];
	float corOrcamento[3];
	boolean isEmpty; // se não existem dados
}Familia;
struct Familia *familia = NULL;
typedef struct Auxiliar
{
	float MaxMensal[120];
	float MaxAnual[10];
	float MaxSempre;
	float MinMensal[120];
	float MinAnual[10];
	float MinSempre;
	float MedMensal[120];
	float MedAnual[10];
	float MedSempre;
	float DevMensal[120];
	float DevAnual[10];
	float DevSempre;
};
struct Auxiliar *ali = NULL;
struct Auxiliar *ves = NULL;
struct Auxiliar *des = NULL;
struct Auxiliar *laz = NULL;
struct Auxiliar *out = NULL;
struct Auxiliar *tot = NULL;
//===============================================================================
//
//  FUNÇÕES ////////////////////////////////////////////////////////////////////
//
//===============================================================================
void getCurrentDate()
{
	time_t timer;
	struct tm* tm_info;
	char dia[3];
	char mes[3];
	char ano[5];
	time(&timer);
	tm_info = localtime(&timer);
	strftime(dia, 3, "%d", tm_info);
	strftime(mes, 3, "%m", tm_info);
	strftime(ano, 5, "%Y", tm_info);
	diaAtual = atoi(dia);
	mesAtual = atoi(mes);
	anoAtual = atoi(ano);

	currentM = mesAtual - 1;
	currentM2 = 119;
	currentA = anoAtual;
}
//===============================================================================
void reshape(GLint nova_largura, GLint nova_altura)
{
	glutReshapeWindow(largura, altura);
}
//===============================================================================
void Font(void *font, char *text, int x, int y)
{
	glRasterPos2i(x, y);

	while (*text != '\0')
	{
		glutBitmapCharacter(font, *text);
		++text;
	}
}
//===============================================================================

void legendasVertical(int x_pos, int y_pos)
{
	glColor3f(0.24, 0.24, 0.24);
	Font(GLUT_BITMAP_HELVETICA_18, "Legenda:", x_pos + 185, y_pos + 155);
	glColor3f(familia->corOut[0], familia->corOut[1], familia->corOut[2]);

	glBegin(GL_POLYGON);
	glVertex2f(x_pos + 170, y_pos + 133);
	glVertex2f(x_pos + 180, y_pos + 133);
	glVertex2f(x_pos + 180, y_pos + 143);
	glVertex2f(x_pos + 170, y_pos + 143);
	glEnd();
	glColor3f(familia->corOut[0], familia->corOut[1], familia->corOut[2]);

	Font(GLUT_BITMAP_HELVETICA_18, "Outros", x_pos + 185, y_pos + 135);
	glColor3f(familia->corLaz[0], familia->corLaz[1], familia->corLaz[2]);

	glBegin(GL_POLYGON);
	glVertex2f(x_pos + 170, y_pos + 103);
	glVertex2f(x_pos + 180, y_pos + 103);
	glVertex2f(x_pos + 180, y_pos + 113);
	glVertex2f(x_pos + 170, y_pos + 113);
	glEnd();
	Font(GLUT_BITMAP_HELVETICA_18, "Lazer", x_pos + 185, y_pos + 105);
	glColor3f(familia->corDes[0], familia->corDes[1], familia->corDes[2]);
	glBegin(GL_POLYGON);
	glVertex2f(x_pos + 170, y_pos + 73);
	glVertex2f(x_pos + 180, y_pos + 73);
	glVertex2f(x_pos + 180, y_pos + 83);
	glVertex2f(x_pos + 170, y_pos + 83);
	glEnd();
	Font(GLUT_BITMAP_HELVETICA_18, "Deslocacoes", x_pos + 185, y_pos + 75);

	glColor3f(familia->corVes[0], familia->corVes[1], familia->corVes[2]);
	glBegin(GL_POLYGON);
	glVertex2f(x_pos + 170, y_pos + 43);
	glVertex2f(x_pos + 180, y_pos + 43);
	glVertex2f(x_pos + 180, y_pos + 53);
	glVertex2f(x_pos + 170, y_pos + 53);
	glEnd();
	Font(GLUT_BITMAP_HELVETICA_18, "Vestuario", x_pos + 185, y_pos + 45);

	glColor3f(familia->corAli[0], familia->corAli[1], familia->corAli[2]);
	glBegin(GL_POLYGON);
	glVertex2f(x_pos + 170, y_pos + 13);
	glVertex2f(x_pos + 180, y_pos + 13);
	glVertex2f(x_pos + 180, y_pos + 23);
	glVertex2f(x_pos + 170, y_pos + 23);
	glEnd();
	Font(GLUT_BITMAP_HELVETICA_18, "Alimentacao", x_pos + 185, y_pos + 15);
	glColor3f(familia->corOrcamento[0], familia->corOrcamento[1], familia->corOrcamento[2]);
	glBegin(GL_POLYGON);
	glVertex2f(x_pos + 170, y_pos - 3);
	glVertex2f(x_pos + 180, y_pos - 3);
	glVertex2f(x_pos + 180, y_pos - 13);
	glVertex2f(x_pos + 170, y_pos - 13);
	glEnd();
	Font(GLUT_BITMAP_HELVETICA_18, "Orcamento", x_pos + 185, y_pos -15);
}
//==========================================================================
void grafico_circulo(int Dia) {
	float angle_rad;
	int aux;
	int x_pos = 1100, y_pos = 120;
	glColor3f(familia->corAli[0], familia->corAli[1], familia->corAli[2]);
	glBegin(GL_POLYGON);
	glVertex2f(x_pos, y_pos);
	//primeiro fazemos alimentacao
	int degree = (int)((familia->custoAlimentacaoDia[Dia] * 360) / familia->gastoTotalDia[Dia]); //racio entre X gasto/gasto total
	for (int angle_deg = 0; angle_deg <= degree; angle_deg += 360 / degree) {
		angle_rad = angle_deg * PI / 180;

		glColor3f(familia->corAli[0], familia->corAli[1], familia->corAli[2]);
		glVertex2f(x_pos + cos(angle_rad) * 100, y_pos + sin(angle_rad) * 100);
		aux = angle_deg;

	}
	glEnd();
	//vestuario
	glColor3f(familia->corVes[0], familia->corVes[1], familia->corVes[2]);
	glBegin(GL_POLYGON);
	glVertex2f(x_pos, y_pos);
	degree = (int)((familia->custoVestuarioDia[Dia] * 360) / familia->gastoTotalDia[Dia]) + aux;
	for (int angle_deg = aux; angle_deg <= degree; angle_deg += 360 / degree) {
		angle_rad = angle_deg * PI / 180;

		glVertex2f(x_pos + cos(angle_rad) * 100, y_pos + sin(angle_rad) * 100);
		aux = angle_deg;
	}
	glEnd();
	//deslocacoes
	glColor3f(familia->corDes[0], familia->corDes[1], familia->corDes[2]);
	glBegin(GL_POLYGON);
	glVertex2f(x_pos, y_pos);
	degree = (int)((familia->custoDeslocacoesDia[Dia] * 360) / familia->gastoTotalDia[Dia]) + aux;
	for (int angle_deg = aux; angle_deg <= degree; angle_deg += 360 / degree) {
		angle_rad = angle_deg * PI / 180;

		glVertex2f(x_pos + cos(angle_rad) * 100, y_pos + sin(angle_rad) * 100);
		aux = angle_deg;
	}
	//lazer
	glEnd();
	glColor3f(familia->corLaz[0], familia->corLaz[1], familia->corLaz[2]);
	glBegin(GL_POLYGON);
	glVertex2f(x_pos, y_pos);
	degree = (int)((familia->custoLazerDia[Dia] * 360) / familia->gastoTotalDia[Dia]) + aux;
	for (int angle_deg = aux; angle_deg <= degree; angle_deg += 360 / degree) {
		angle_rad = angle_deg * PI / 180;

		glVertex2f(x_pos + cos(angle_rad) * 100, y_pos + sin(angle_rad) * 100);
		aux = angle_deg;
	}
	glEnd();
	//outros
	glColor3f(familia->corOut[0], familia->corOut[1], familia->corOut[2]);
	glBegin(GL_POLYGON);
	glVertex2f(x_pos, y_pos);
	degree = (int)((familia->custoOutrosDia[Dia] * 360) / familia->gastoTotalDia[Dia]) + aux;
	for (int angle_deg = aux; angle_deg <= 360; angle_deg += 360 / degree) {
		angle_rad = angle_deg * PI / 180;

		glVertex2f(x_pos + cos(angle_rad) * 100, y_pos + sin(angle_rad) * 100);
		aux = angle_deg;
	}
	glEnd();








}



void grafico_barra(int Dia) {
	//alim
	int x_pos = 450, y_pos = 20;
	glColor3f(familia->corAli[0], familia->corAli[1], familia->corAli[2]);
	int ant;
	int aux = (160 * familia->custoAlimentacaoDia[Dia] / familia->gastoTotalDia[Dia]);
	glBegin(GL_POLYGON);
	glVertex2f(x_pos, y_pos);
	glVertex2f(x_pos + 100, y_pos);
	glVertex2f(x_pos + 100, y_pos + aux);
	glVertex2f(x_pos, y_pos + aux);
	glEnd();

	// vestuario
	glColor3f(familia->corVes[0], familia->corVes[1], familia->corVes[2]);
	ant = aux;
	aux = aux + (int)(160 * familia->custoVestuarioDia[Dia] / familia->gastoTotalDia[Dia]);
	glBegin(GL_POLYGON);
	glVertex2f(x_pos, y_pos + ant);
	glVertex2f(x_pos + 100, y_pos + ant);
	glVertex2f(x_pos + 100, y_pos + aux);
	glVertex2f(x_pos, y_pos + aux);
	glEnd();
	//Deslocacoes
	glColor3f(familia->corDes[0], familia->corDes[1], familia->corDes[2]);
	ant = aux;
	aux = aux + (int)(160 * familia->custoDeslocacoesDia[Dia] / familia->gastoTotalDia[Dia]);
	glBegin(GL_POLYGON);
	glVertex2f(x_pos, y_pos + ant);
	glVertex2f(x_pos + 100, y_pos + ant);
	glVertex2f(x_pos + 100, y_pos + aux);
	glVertex2f(x_pos, y_pos + aux);
	glEnd();
	//Lazer
	glColor3f(familia->corLaz[0], familia->corLaz[1], familia->corLaz[2]);
	ant = aux;
	aux = aux + (int)(160 * familia->custoLazerDia[Dia] / familia->gastoTotalDia[Dia]);
	glBegin(GL_POLYGON);
	glVertex2f(x_pos, y_pos + ant);
	glVertex2f(x_pos + 100, y_pos + ant);
	glVertex2f(x_pos + 100, y_pos + aux);
	glVertex2f(x_pos, y_pos + aux);
	glEnd();
	//Outros
	glColor3f(familia->corOut[0], familia->corOut[1], familia->corOut[2]);
	ant = aux;
	aux = aux + (int)(160 * familia->custoOutrosDia[Dia] / familia->gastoTotalDia[Dia]);
	glBegin(GL_POLYGON);
	glVertex2f(x_pos, y_pos + ant);
	glVertex2f(x_pos + 100, y_pos + ant);
	glVertex2f(x_pos + 100, y_pos + aux);
	glVertex2f(x_pos, y_pos + aux);
	glEnd();



}
//=====================================================================================================
void plot(int x_pos, int y_pos, float *TabelaDados, int min_value, int max_value, float cor[])
{
	int espacamento;
	int origin_x = x_pos + 10; // nova origem a considerar
	int origin_y = y_pos + 10; // nova origem a considerar
							   // eixo x

							   //desenhar grafico
	if (modoDeVisualizacao == 0)
	{
		espacamento = 0;
		glPointSize(2);

		glColor3f(familia->corOrcamento[0], familia->corOrcamento[1], familia->corOrcamento[2]);
		glBegin(GL_LINES);
		glVertex2f(origin_x , origin_y + 20 + (familia->orcamentoAnual / 365 - min_value) * 360 / max_value);
		glVertex2f(origin_x + 620, origin_y + 20 + (familia->orcamentoAnual / 365 - min_value) * 360 / max_value);

		glEnd();
		for (int i = (currentM2 - 1) * 30; i < (currentM2 - 1) * 30 + 30; i++)
		{
			// assegura que são colocados os pontos correctos nos traços marcados
			if (TabelaDados[i] >= 0 && TabelaDados[i + 1] >= 0)
			{
				glBegin(GL_LINES);
				glColor3f(cor[0], cor[1], cor[2]);
				glVertex2f(origin_x + espacamento, origin_y + 20 + (TabelaDados[i] - min_value) * 360 / max_value);
				glVertex2f(origin_x + espacamento + 21, origin_y + 20 + (TabelaDados[i + 1] - min_value) * 360 / max_value);
				glEnd();
			}
			espacamento = espacamento + 20;
		}
	}

	if (modoDeVisualizacao == 1)
	{
		espacamento = 0;
		glPointSize(2);
		glColor3f(familia->corOrcamento[0], familia->corOrcamento[1], familia->corOrcamento[2]);
		glBegin(GL_LINES);
		glVertex2f(origin_x, origin_y + 20 + (familia->orcamentoAnual / 12 - min_value) * 360 / max_value);
		glVertex2f(origin_x + 620, origin_y + 20 + (familia->orcamentoAnual / 12 - min_value) * 360 / max_value);

		for (int i = (currentA2 - 1) * 12; i < (currentA2 - 1) * 12 + 12; i++)
		{
			// assegura que são colocados os pontos correctos nos traços marcados
			if (TabelaDados[i] >= 0 && TabelaDados[i + 1] >= 0)
			{
				glBegin(GL_LINES);
				glColor3f(cor[0], cor[1], cor[2]);
				glVertex2f(origin_x + espacamento, origin_y + 20 + (TabelaDados[i] - min_value) * 360 / max_value);
				glVertex2f(origin_x + espacamento + 50, origin_y + 20 + (TabelaDados[i + 1] - min_value) * 360 / max_value);
				glEnd();
			}
			espacamento = espacamento + 50;
		}
	}
	if (modoDeVisualizacao == 2)
	{
		espacamento = 0;
		glPointSize(2);
		glColor3f(familia->corOrcamento[0], familia->corOrcamento[1], familia->corOrcamento[2]);
		glBegin(GL_LINES);
		glVertex2f(origin_x, origin_y + 20 + (familia->orcamentoAnual / 1 - min_value) * 360 / max_value);
		glVertex2f(origin_x + 620, origin_y + 20 + (familia->orcamentoAnual / 1 - min_value) * 360 / max_value);
		for (int i = (currentA - 1) * 12; i < (currentA - 1) * 12 + 12; i++)
		{
			// assegura que são colocados os pontos correctos nos traços marcados
			if (TabelaDados[i] >= 0 && TabelaDados[i + 1] >= 0)
			{
				glBegin(GL_LINES);
				glColor3f(cor[0], cor[1], cor[2]);
				glVertex2f(origin_x + espacamento, origin_y + 20 + (TabelaDados[i] - min_value) * 360 / max_value);
				glVertex2f(origin_x + espacamento + 55, origin_y + 20 + (TabelaDados[i + 1] - min_value) * 360 / max_value);
				glEnd();
			}
			espacamento = espacamento + 54;
		}
	}
	glColor3f(0, 0, 0);
}
//=====================================================================================================
void desenharEixos(int x_pos, int y_pos)
{
	// desenhar eixos (tendo em conta que o gráfico ocupa 200x300)
	glLineWidth(2);
	int origin_x = x_pos + 10; // nova origem a considerar
	int origin_y = y_pos + 10; // nova origem a considerar 
	int Maximo, Minimo, Delta, DeltaDeCadaVez, espacoEntreChar;
	// eixo x
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(x_pos, origin_y);
	glVertex2f(x_pos + 650, origin_y);
	glEnd();
	//seta
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0, 0, 0);
	glVertex2f(x_pos + 650, origin_y + 5);
	glVertex2f(x_pos + 650, origin_y - 5);
	glVertex2f(x_pos + 660, origin_y);
	glEnd();

	// eixo y
	glBegin(GL_LINES);
	glVertex2f(origin_x, y_pos);
	glVertex2f(origin_x, y_pos + 350);
	glEnd();
	//seta
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0, 0, 0);
	glVertex2f(x_pos + 5, origin_y + 340);
	glVertex2f(x_pos + 15, origin_y + 340);
	glVertex2f(x_pos + 10, origin_y + 350);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	glVertex2f(x_pos, origin_y - 127);
	glVertex2f(x_pos + 300, origin_y - 127);
	glEnd();
	Font(GLUT_BITMAP_HELVETICA_18, "Maximo:", x_pos, y_pos - 100);
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	glVertex2f(x_pos, origin_y - 177);
	glVertex2f(x_pos + 300, origin_y - 177);
	glEnd();
	Font(GLUT_BITMAP_HELVETICA_18, "Minimo:", x_pos, y_pos - 150);
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	glVertex2f(x_pos, origin_y - 227);
	glVertex2f(x_pos + 300, origin_y - 227);
	glEnd();
	Font(GLUT_BITMAP_HELVETICA_18, "Media:", x_pos, y_pos - 200);
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);
	glVertex2f(x_pos + 150, origin_y - 80);
	glVertex2f(x_pos + 150, origin_y - 280);
	glEnd();
	Font(GLUT_BITMAP_HELVETICA_18, "Desvio Padrao:", x_pos, y_pos - 250);
	char Buffer[100];
	if (currentTab == 1)
	{


		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			Maximo = ali->MaxMensal[currentM2];
			Minimo = ali->MinMensal[currentM2];
			Delta = Maximo - Minimo;
			plot(x_pos, y_pos, familia->custoAlimentacaoDia, Minimo, Maximo, familia->corAli);
			DeltaDeCadaVez = Delta / 10;
			espacoEntreChar = 0;
			for (int i = 0; i <= 11; i++)
			{
				sprintf(Buffer, "%d", (int)(Minimo + i * DeltaDeCadaVez));
				Font(GLUT_BITMAP_HELVETICA_10, Buffer, origin_x - 25, y_pos + espacoEntreChar + 35);
				espacoEntreChar = espacoEntreChar + 27;
				glBegin(GL_LINES);
				glLineWidth(1);
				glVertex2f(origin_x, origin_y + espacoEntreChar);
				glVertex2f(origin_x - 5, origin_y + espacoEntreChar);
				glEnd();
			}
			sprintf(Buffer, "%f", ali->MaxMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 100);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			Maximo = ali->MaxAnual[currentA2];
			Minimo = ali->MinAnual[currentA2];
			plot(x_pos, y_pos, ali->MedMensal, Minimo, Maximo, familia->corAli);
			Delta = Maximo - Minimo;
			DeltaDeCadaVez = Delta / 10;
			espacoEntreChar = 0;
			for (int i = 0; i <= 11; i++)
			{
				sprintf(Buffer, "%d", (int)(Minimo + i * DeltaDeCadaVez));
				Font(GLUT_BITMAP_HELVETICA_10, Buffer, origin_x - 25, y_pos + espacoEntreChar + 35);
				espacoEntreChar = espacoEntreChar + 27;
				glBegin(GL_LINES);
				glLineWidth(1);
				glVertex2f(origin_x, origin_y + espacoEntreChar);
				glVertex2f(origin_x - 5, origin_y + espacoEntreChar);
				glEnd();
			}
			sprintf(Buffer, "%f", ali->MaxAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 100);
		}
		else
		{
			Maximo = ali->MaxSempre;
			Minimo = ali->MinSempre;
			Delta = Maximo - Minimo;
			plot(x_pos, y_pos, ali->MedMensal, Minimo, Maximo, familia->corAli);

			DeltaDeCadaVez = Delta / 10;
			espacoEntreChar = 0;
			for (int i = 0; i <= 11; i++)
			{
				sprintf(Buffer, "%d", (int)(Minimo + i * DeltaDeCadaVez));
				Font(GLUT_BITMAP_HELVETICA_10, Buffer, origin_x - 25, y_pos + espacoEntreChar + 35);
				espacoEntreChar = espacoEntreChar + 27;
				glBegin(GL_LINES);
				glLineWidth(1);
				glVertex2f(origin_x, origin_y + espacoEntreChar);
				glVertex2f(origin_x - 5, origin_y + espacoEntreChar);
				glEnd();

			}
			sprintf(Buffer, "%f", ali->MaxSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 100);
		}

	}
	else if (currentTab == 2)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			Maximo = ves->MaxMensal[currentM2];
			Minimo = ves->MinMensal[currentM2];
			plot(x_pos, y_pos, familia->custoVestuarioDia, Minimo, Maximo, familia->corVes);
			Delta = Maximo - Minimo;
			DeltaDeCadaVez = Delta / 10;
			espacoEntreChar = 0;
			for (int i = 0; i <= 11; i++)
			{
				sprintf(Buffer, "%d", (int)(Minimo + i * DeltaDeCadaVez));
				Font(GLUT_BITMAP_HELVETICA_10, Buffer, origin_x - 25, y_pos + espacoEntreChar + 35);
				espacoEntreChar = espacoEntreChar + 27;
				glBegin(GL_LINES);
				glLineWidth(1);
				glVertex2f(origin_x, origin_y + espacoEntreChar);
				glVertex2f(origin_x - 5, origin_y + espacoEntreChar);
				glEnd();
			}
			sprintf(Buffer, "%f", ves->MaxMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 100);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			Maximo = ves->MaxAnual[currentA2];
			Minimo = ves->MinAnual[currentA2];
			plot(x_pos, y_pos, ves->MedMensal, Minimo, Maximo, familia->corVes);
			Delta = Maximo - Minimo;
			DeltaDeCadaVez = Delta / 10;
			espacoEntreChar = 0;
			for (int i = 0; i <= 11; i++)
			{
				sprintf(Buffer, "%d", (int)(Minimo + i * DeltaDeCadaVez));
				Font(GLUT_BITMAP_HELVETICA_10, Buffer, origin_x - 25, y_pos + espacoEntreChar + 35);
				espacoEntreChar = espacoEntreChar + 27;
				glBegin(GL_LINES);
				glLineWidth(1);
				glVertex2f(origin_x, origin_y + espacoEntreChar);
				glVertex2f(origin_x - 5, origin_y + espacoEntreChar);
				glEnd();
			}
			sprintf(Buffer, "%f", ves->MaxAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 100);
		}
		else
		{
			Maximo = ves->MaxSempre;
			Minimo = ves->MinSempre;
			Delta = Maximo - Minimo;
			plot(x_pos, y_pos, ves->MedMensal, Minimo, Maximo, familia->corVes);

			DeltaDeCadaVez = Delta / 10;
			espacoEntreChar = 0;
			for (int i = 0; i <= 11; i++)
			{
				sprintf(Buffer, "%d", (int)(Minimo + i * DeltaDeCadaVez));
				Font(GLUT_BITMAP_HELVETICA_10, Buffer, origin_x - 25, y_pos + espacoEntreChar + 35);
				espacoEntreChar = espacoEntreChar + 27;
				glBegin(GL_LINES);
				glLineWidth(1);
				glVertex2f(origin_x, origin_y + espacoEntreChar);
				glVertex2f(origin_x - 5, origin_y + espacoEntreChar);
				glEnd();
			}
			sprintf(Buffer, "%f", ves->MaxSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 100);
		}

	}
	else if (currentTab == 3)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			Maximo = des->MaxMensal[currentM2];
			Minimo = des->MinMensal[currentM2];
			plot(x_pos, y_pos, familia->custoDeslocacoesDia, Minimo, Maximo, familia->corDes);
			Delta = Maximo - Minimo;
			DeltaDeCadaVez = Delta / 10;
			espacoEntreChar = 0;
			for (int i = 0; i <= 11; i++)
			{
				sprintf(Buffer, "%d", (int)(Minimo + i * DeltaDeCadaVez));
				Font(GLUT_BITMAP_HELVETICA_10, Buffer, origin_x - 25, y_pos + espacoEntreChar + 35);
				espacoEntreChar = espacoEntreChar + 27;
				glBegin(GL_LINES);
				glLineWidth(1);
				glVertex2f(origin_x, origin_y + espacoEntreChar);
				glVertex2f(origin_x - 5, origin_y + espacoEntreChar);
				glEnd();
			}
			sprintf(Buffer, "%f", des->MaxMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 100);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			Maximo = des->MaxAnual[currentA2];
			Minimo = des->MinAnual[currentA2];
			plot(x_pos, y_pos, des->MedMensal, Minimo, Maximo, familia->corDes);
			Delta = Maximo - Minimo;
			DeltaDeCadaVez = Delta / 10;
			espacoEntreChar = 0;
			for (int i = 0; i <= 11; i++)
			{
				sprintf(Buffer, "%d", (int)(Minimo + i * DeltaDeCadaVez));
				Font(GLUT_BITMAP_HELVETICA_10, Buffer, origin_x - 25, y_pos + espacoEntreChar + 35);
				espacoEntreChar = espacoEntreChar + 27;
				glBegin(GL_LINES);
				glLineWidth(1);
				glVertex2f(origin_x, origin_y + espacoEntreChar);
				glVertex2f(origin_x - 5, origin_y + espacoEntreChar);
				glEnd();
			}
			sprintf(Buffer, "%f", des->MaxAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 100);
		}
		else
		{

			Maximo = des->MaxSempre;
			Minimo = des->MinSempre;
			plot(x_pos, y_pos, des->MedMensal, Minimo, Maximo, familia->corDes);

			Delta = Maximo - Minimo;
			DeltaDeCadaVez = Delta / 10;
			espacoEntreChar = 0;
			for (int i = 0; i <= 11; i++)
			{
				sprintf(Buffer, "%d", (int)(Minimo + i * DeltaDeCadaVez));
				Font(GLUT_BITMAP_HELVETICA_10, Buffer, origin_x - 25, y_pos + espacoEntreChar + 35);
				espacoEntreChar = espacoEntreChar + 27;
				glBegin(GL_LINES);
				glLineWidth(1);
				glVertex2f(origin_x, origin_y + espacoEntreChar);
				glVertex2f(origin_x - 5, origin_y + espacoEntreChar);
				glEnd();
			}
			sprintf(Buffer, "%f", des->MaxSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 100);
		}

	}
	else if (currentTab == 4)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			Maximo = laz->MaxMensal[currentM2];
			Minimo = laz->MinMensal[currentM2];
			plot(x_pos, y_pos, familia->custoLazerDia, Minimo, Maximo, familia->corLaz);
			Delta = Maximo - Minimo;
			DeltaDeCadaVez = Delta / 10;
			espacoEntreChar = 0;
			for (int i = 0; i <= 11; i++)
			{
				sprintf(Buffer, "%d", (int)(Minimo + i * DeltaDeCadaVez));
				Font(GLUT_BITMAP_HELVETICA_10, Buffer, origin_x - 25, y_pos + espacoEntreChar + 35);
				espacoEntreChar = espacoEntreChar + 27;
				glBegin(GL_LINES);
				glLineWidth(1);
				glVertex2f(origin_x, origin_y + espacoEntreChar);
				glVertex2f(origin_x - 5, origin_y + espacoEntreChar);
				glEnd();
			}



			sprintf(Buffer, "%f", laz->MaxMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 100);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			Maximo = laz->MaxAnual[currentA2];
			Minimo = laz->MinAnual[currentA2];
			plot(x_pos, y_pos, laz->MedMensal, Minimo, Maximo, familia->corLaz);
			Delta = Maximo - Minimo;
			DeltaDeCadaVez = Delta / 10;
			espacoEntreChar = 0;
			for (int i = 0; i <= 10; i++)
			{
				sprintf(Buffer, "%d", (int)(Minimo + i * DeltaDeCadaVez));
				Font(GLUT_BITMAP_HELVETICA_10, Buffer, origin_x - 25, y_pos + espacoEntreChar + 35);
				espacoEntreChar = espacoEntreChar + 27;
				glBegin(GL_LINES);
				glLineWidth(1);
				glVertex2f(origin_x, origin_y + espacoEntreChar);
				glVertex2f(origin_x - 5, origin_y + espacoEntreChar);
				glEnd();

			}
			sprintf(Buffer, "%f", laz->MaxAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 100);
		}
		else
		{
			Maximo = laz->MaxSempre;
			Minimo = laz->MinSempre;
			plot(x_pos, y_pos, ali->MedMensal, Minimo, Maximo, familia->corLaz);

			Delta = Maximo - Minimo;

			DeltaDeCadaVez = Delta / 10;
			espacoEntreChar = 0;
			for (int i = 0; i <= 11; i++)
			{
				sprintf(Buffer, "%d", (int)(Minimo + i * DeltaDeCadaVez));
				Font(GLUT_BITMAP_HELVETICA_10, Buffer, origin_x - 25, y_pos + espacoEntreChar + 35);
				espacoEntreChar = espacoEntreChar + 27;
				glBegin(GL_LINES);
				glLineWidth(1);
				glVertex2f(origin_x, origin_y + espacoEntreChar);
				glVertex2f(origin_x - 5, origin_y + espacoEntreChar);
				glEnd();

			}
			sprintf(Buffer, "%f", laz->MaxSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 100);
		}

	}
	else if (currentTab == 5)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			Maximo = out->MaxMensal[currentM2];
			Minimo = out->MinMensal[currentM2];
			plot(x_pos, y_pos, familia->custoOutrosDia, Minimo, Maximo, familia->corOut);
			Delta = Maximo - Minimo;
			DeltaDeCadaVez = Delta / 10;
			espacoEntreChar = 0;
			for (int i = 0; i <= 11; i++)
			{
				sprintf(Buffer, "%d", (int)(Minimo + i * DeltaDeCadaVez));
				Font(GLUT_BITMAP_HELVETICA_10, Buffer, origin_x - 25, y_pos + espacoEntreChar + 35);
				espacoEntreChar = espacoEntreChar + 27;
				glBegin(GL_LINES);
				glLineWidth(1);
				glVertex2f(origin_x, origin_y + espacoEntreChar);
				glVertex2f(origin_x - 5, origin_y + espacoEntreChar);
				glEnd();

			}



			sprintf(Buffer, "%f", out->MaxMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 100);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			Maximo = out->MaxAnual[currentA2];
			Minimo = out->MinAnual[currentA2];
			plot(x_pos, y_pos, out->MedMensal, Minimo, Maximo, familia->corOut);
			Delta = Maximo - Minimo;
			DeltaDeCadaVez = Delta / 10;
			espacoEntreChar = 0;
			for (int i = 0; i <= 11; i++)
			{
				sprintf(Buffer, "%d", (int)(Minimo + i * DeltaDeCadaVez));
				Font(GLUT_BITMAP_HELVETICA_10, Buffer, origin_x - 25, y_pos + espacoEntreChar + 35);
				espacoEntreChar = espacoEntreChar + 27;
				glBegin(GL_LINES);
				glLineWidth(1);
				glVertex2f(origin_x, origin_y + espacoEntreChar);
				glVertex2f(origin_x - 5, origin_y + espacoEntreChar);
				glEnd();

			}
			sprintf(Buffer, "%f", out->MaxAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 100);
		}
		else
		{
			Maximo = des->MaxSempre;
			Minimo = des->MinSempre;
			plot(x_pos, y_pos, des->MedMensal, Minimo, Maximo, familia->corOut);

			Delta = Maximo - Minimo;
			DeltaDeCadaVez = Delta / 10;
			espacoEntreChar = 0;
			for (int i = 0; i <= 11; i++)
			{
				sprintf(Buffer, "%d", (int)(Minimo + i * DeltaDeCadaVez));
				Font(GLUT_BITMAP_HELVETICA_10, Buffer, origin_x - 25, y_pos + espacoEntreChar + 35);
				espacoEntreChar = espacoEntreChar + 27;
				glBegin(GL_LINES);
				glLineWidth(1);
				glVertex2f(origin_x, origin_y + espacoEntreChar);
				glVertex2f(origin_x - 5, origin_y + espacoEntreChar);
				glEnd();

			}
			sprintf(Buffer, "%f", des->MaxSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 100);
		}

	}
	else if (currentTab == 6)
	{
		Font(GLUT_BITMAP_HELVETICA_18, "Total:", x_pos + 200, y_pos - 50);
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			legendasVertical(450, 20);

			for (float i = 0; i <= 1; i = i + 0.003) {
				glPushMatrix();
				glTranslated(1, 20, 1);
				glScaled(1, i, 1);
				grafico_barra(currentM2);
				glPopMatrix();
				glFlush();
			}
			legendasVertical(880, 350);

			grafico_circulo(currentM2);

			glColor3f(0, 0, 0);

			Maximo = ali->MaxMensal[currentM2] > ves->MaxMensal[currentM2] ? ali->MaxMensal[currentM2] : ves->MaxMensal[currentM2];
			Maximo = Maximo > des->MaxMensal[currentM2] ? Maximo : des->MaxMensal[currentM2];
			Maximo = Maximo > laz->MaxMensal[currentM2] ? Maximo : laz->MaxMensal[currentM2];
			Maximo = Maximo > out->MaxMensal[currentM2] ? Maximo : out->MaxMensal[currentM2];

			Minimo = ali->MinMensal[currentM2] > ves->MinMensal[currentM2] ? ves->MinMensal[currentM2] : ali->MinMensal[currentM2];
			Minimo = Minimo < des->MinMensal[currentM2] ? Minimo : des->MinMensal[currentM2];
			Minimo = Minimo < laz->MinMensal[currentM2] ? Minimo : laz->MinMensal[currentM2];
			Minimo = Minimo < out->MinMensal[currentM2] ? Minimo : out->MinMensal[currentM2];
			plot(x_pos, y_pos, familia->custoAlimentacaoDia, Minimo, Maximo, familia->corAli);
			plot(x_pos, y_pos, familia->custoVestuarioDia, Minimo, Maximo, familia->corVes);
			plot(x_pos, y_pos, familia->custoDeslocacoesDia, Minimo, Maximo, familia->corDes);
			plot(x_pos, y_pos, familia->custoLazerDia, Minimo, Maximo, familia->corLaz);

			plot(x_pos, y_pos, familia->custoOutrosDia, Minimo, Maximo, familia->corOut);
			glColor3f(0, 0, 0);

			Delta = Maximo - Minimo;
			DeltaDeCadaVez = Delta / 10;
			espacoEntreChar = 0;
			for (int i = 0; i <= 11; i++)
			{
				sprintf(Buffer, "%d", (int)(Minimo + i * DeltaDeCadaVez));
				Font(GLUT_BITMAP_HELVETICA_10, Buffer, origin_x - 25, y_pos + espacoEntreChar + 35);

				espacoEntreChar = espacoEntreChar + 27;
				glBegin(GL_LINES);
				glLineWidth(1);
				glVertex2f(origin_x, origin_y + espacoEntreChar);
				glVertex2f(origin_x - 5, origin_y + espacoEntreChar);
				glEnd();
			}

			sprintf(Buffer, "%f", tot->MaxMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 100);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			legendasVertical(450, 20);

			for (float i = 0; i <= 1; i = i + 0.003) {
				glPushMatrix();
				glTranslated(1, 20, 1);
				glScaled(1, i, 1);
				grafico_barra(currentA2 * 120);
				glPopMatrix();
				glFlush();
			}
			legendasVertical(880, 350);

			grafico_circulo(currentA2 * 120);
			glColor3f(0, 0, 0);


			Maximo = ali->MaxAnual[currentA2 * 120] > ves->MaxAnual[currentA2 * 120] ? ali->MaxAnual[currentA2 * 120] : ves->MaxAnual[currentA2 * 120];
			Maximo = Maximo > des->MaxAnual[currentA2 * 120] ? Maximo : des->MaxAnual[currentA2 * 120];
			Maximo = Maximo > laz->MaxAnual[currentA2 * 120] ? Maximo : laz->MaxAnual[currentA2 * 120];
			Maximo = Maximo > out->MaxAnual[currentA2 * 120] ? Maximo : out->MaxAnual[currentA2 * 120];

			Minimo = ali->MinAnual[currentA2 * 120] > ves->MinAnual[currentA2 * 120] ? ves->MinAnual[currentA2 * 120] : ali->MinAnual[currentA2 * 120];
			Minimo = Minimo < des->MinAnual[currentA2 * 120] ? Minimo : des->MinAnual[currentA2 * 120];
			Minimo = Minimo < laz->MinAnual[currentA2 * 120] ? Minimo : laz->MinAnual[currentA2 * 120];
			Minimo = Minimo < out->MinAnual[currentA2 * 120] ? Minimo : out->MinAnual[currentA2 * 120];
			plot(x_pos, y_pos, familia->custoAlimentacaoDia, Minimo, Maximo, familia->corAli);
			plot(x_pos, y_pos, familia->custoVestuarioDia, Minimo, Maximo, familia->corVes);
			plot(x_pos, y_pos, familia->custoDeslocacoesDia, Minimo, Maximo, familia->corDes);
			plot(x_pos, y_pos, familia->custoLazerDia, Minimo, Maximo, familia->corLaz);
			plot(x_pos, y_pos, familia->custoOutrosDia, Minimo, Maximo, familia->corOut);
			glColor3f(0, 0, 0);


			Delta = Maximo - Minimo;
			DeltaDeCadaVez = Delta / 10;
			espacoEntreChar = 0;
			for (int i = 0; i <= 11; i++)
			{
				sprintf(Buffer, "%d", (int)(Minimo + i * DeltaDeCadaVez));
				Font(GLUT_BITMAP_HELVETICA_10, Buffer, origin_x - 25, y_pos + espacoEntreChar + 35);
				glBegin(GL_LINES);
				glLineWidth(1);
				glVertex2f(origin_x, origin_y + espacoEntreChar);
				glVertex2f(origin_x - 5, origin_y + espacoEntreChar);
				glEnd();
				espacoEntreChar = espacoEntreChar + 28;
			}
			sprintf(Buffer, "%f", tot->MaxAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 100);
		}
		else
		{
			legendasVertical(450, 20);

			for (float i = 0; i <= 1; i = i + 0.003) {
				glPushMatrix();
				glTranslated(1, 20, 1);
				glScaled(1, i, 1);
				grafico_barra(currentA2 * 120);
				glPopMatrix();
				glFlush();
			}
			legendasVertical(880, 350);

			grafico_circulo(currentA2 * 120);

			Maximo = ali->MaxSempre > ves->MaxSempre ? ali->MaxSempre : ves->MaxSempre;
			Maximo = Maximo > des->MaxSempre ? Maximo : des->MaxSempre;
			Maximo = Maximo > laz->MaxSempre ? Maximo : laz->MaxSempre;
			Maximo = Maximo > out->MaxSempre ? Maximo : out->MaxSempre;

			Minimo = ali->MinSempre > ves->MinSempre ? ves->MinSempre : ali->MinSempre;
			Minimo = Minimo < des->MinSempre ? Minimo : des->MinSempre;
			Minimo = Minimo < laz->MinSempre ? Minimo : laz->MinSempre;
			Minimo = Minimo < out->MinSempre ? Minimo : out->MinSempre;
			printf("%d", Minimo);
			plot(x_pos, y_pos, ali->MedMensal, Minimo, Maximo, familia->corAli);
			plot(x_pos, y_pos, ves->MedMensal, Minimo, Maximo, familia->corVes);
			plot(x_pos, y_pos, des->MedMensal, Minimo, Maximo, familia->corDes);
			plot(x_pos, y_pos, laz->MedMensal, Minimo, Maximo, familia->corLaz);
			plot(x_pos, y_pos, out->MedMensal, Minimo, Maximo, familia->corOut);

			glColor3f(0, 0, 0);

			Maximo = tot->MaxSempre;
			Minimo = tot->MinSempre;
			Delta = Maximo - Minimo;
			DeltaDeCadaVez = Delta / 10;
			espacoEntreChar = 0;
			for (int i = 0; i <= 10; i++)
			{
				sprintf(Buffer, "%d", (int)(Minimo + i * DeltaDeCadaVez));
				Font(GLUT_BITMAP_HELVETICA_10, Buffer, origin_x - 25, y_pos + espacoEntreChar + 35);
				glBegin(GL_LINES);
				glLineWidth(1);
				glVertex2f(origin_x, origin_y + espacoEntreChar);
				glVertex2f(origin_x - 5, origin_y + espacoEntreChar);
				glEnd();
				espacoEntreChar = espacoEntreChar + 28;
			}
			sprintf(Buffer, "%f", tot->MaxSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 100);
		}

	}

	if (currentTab == 1)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			sprintf(Buffer, "%f", ali->MinMensal[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 150);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			sprintf(Buffer, "%f", ali->MinAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 150);
		}
		else
		{
			sprintf(Buffer, "%f", ali->MinSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 150);
		}

	}
	else if (currentTab == 2)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			sprintf(Buffer, "%f", ves->MinMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 150);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			sprintf(Buffer, "%f", ves->MinAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 150);
		}
		else
		{
			sprintf(Buffer, "%f", ves->MinSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 150);
		}

	}
	else if (currentTab == 3)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{

			sprintf(Buffer, "%f", des->MinMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 150);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			sprintf(Buffer, "%f", des->MinAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 150);
		}
		else
		{
			sprintf(Buffer, "%f", des->MinSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 150);
		}

	}
	else if (currentTab == 4)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			sprintf(Buffer, "%f", laz->MinMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 150);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			sprintf(Buffer, "%f", laz->MinAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 150);
		}
		else
		{
			sprintf(Buffer, "%f", laz->MinSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 150);
		}

	}
	else if (currentTab == 5)
	{

		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			char Buffer2[100];
			sprintf(Buffer2, "%f", out->MinMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer2, x_pos + 200, y_pos - 150);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			sprintf(Buffer, "%f", out->MinAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 150);
		}
		else
		{
			sprintf(Buffer, "%f", out->MinSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 150);
		}

	}
	else if (currentTab == 6)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			sprintf(Buffer, "%f", tot->MinMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 150);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			sprintf(Buffer, "%f", tot->MinAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 150);
		}
		else
		{
			sprintf(Buffer, "%f", tot->MinSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 150);
		}

	}

	if (currentTab == 1)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			sprintf(Buffer, "%f", ali->MedMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 200);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			sprintf(Buffer, "%f", ali->MedAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 200);
		}
		else
		{
			sprintf(Buffer, "%f", ali->MedSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 200);
		}

	}
	else if (currentTab == 2)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			sprintf(Buffer, "%f", ves->MedMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 200);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			sprintf(Buffer, "%f", ves->MedAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 200);
		}
		else
		{
			sprintf(Buffer, "%f", ves->MedSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 200);
		}

	}
	else if (currentTab == 3)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			sprintf(Buffer, "%f", des->MedMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 200);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			sprintf(Buffer, "%f", des->MedAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 200);
		}
		else
		{
			sprintf(Buffer, "%f", des->MedSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 200);
		}

	}
	else if (currentTab == 4)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			sprintf(Buffer, "%f", laz->MedMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 200);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			sprintf(Buffer, "%f", laz->MedAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 200);
		}
		else
		{
			sprintf(Buffer, "%f", laz->MedSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 200);
		}

	}
	else if (currentTab == 5)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			sprintf(Buffer, "%f", out->MedMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 200);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			sprintf(Buffer, "%f", out->MedAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 200);
		}
		else
		{
			sprintf(Buffer, "%f", out->MedSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 200);
		}

	}
	else if (currentTab == 6)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			sprintf(Buffer, "%f", tot->MedMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 200);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			sprintf(Buffer, "%f", tot->MedAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 200);
		}
		else
		{
			sprintf(Buffer, "%f", tot->MedSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 200);
		}

	}

	if (currentTab == 1)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			sprintf(Buffer, "%f", ali->DevMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 250);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			sprintf(Buffer, "%f", ali->DevAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 250);
		}
		else
		{
			sprintf(Buffer, "%f", ali->DevSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 250);
		}

	}
	else if (currentTab == 2)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			sprintf(Buffer, "%f", ves->DevMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 250);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			sprintf(Buffer, "%f", ves->DevAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 250);
		}
		else
		{
			sprintf(Buffer, "%f", ves->DevSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 250);
		}

	}
	else if (currentTab == 3)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			sprintf(Buffer, "%f", des->DevMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 250);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			sprintf(Buffer, "%f", des->DevAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 250);
		}
		else
		{
			sprintf(Buffer, "%f", des->DevSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 250);
		}

	}
	else if (currentTab == 4)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			sprintf(Buffer, "%f", laz->DevMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 250);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			sprintf(Buffer, "%f", laz->DevAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 250);
		}
		else
		{
			sprintf(Buffer, "%f", laz->DevSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 250);
		}

	}
	else if (currentTab == 5)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			sprintf(Buffer, "%f", out->DevMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 250);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			sprintf(Buffer, "%f", out->DevAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 250);
		}
		else
		{
			sprintf(Buffer, "%f", out->DevSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 250);
		}

	}
	else if (currentTab == 6)
	{
		if (modoDeVisualizacao == 0) // se estivermos a ver em dias
		{
			sprintf(Buffer, "%f", tot->DevMensal[currentM2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 250);
		}
		else if (modoDeVisualizacao == 1) // se estivermos a ver em mes
		{
			sprintf(Buffer, "%f", tot->DevAnual[currentA2]);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 250);
		}
		else
		{
			sprintf(Buffer, "%f", tot->DevSempre);
			Font(GLUT_BITMAP_HELVETICA_18, Buffer, x_pos + 200, y_pos - 250);
		}

	}

	espacoEntreChar = 0;

	if (modoDeVisualizacao == 0)//Dia
	{
		// default view 
		char aux[12];
		for (int i = 1; i <= 30; i++)
		{
			//eixo x
			sprintf(aux, "%d", i);
			Font(GLUT_BITMAP_HELVETICA_10, aux, origin_x + espacoEntreChar - 3, y_pos - 13);
			glBegin(GL_LINES);
			glLineWidth(1);
			glVertex2f(origin_x + espacoEntreChar, origin_y);
			glVertex2f(origin_x + espacoEntreChar, origin_y - 7);
			glEnd();
			espacoEntreChar = espacoEntreChar + 21;
		}



		espacoEntreChar = 0;
		Font(GLUT_BITMAP_HELVETICA_18, "Dias", x_pos + 675, y_pos);


		char *auxMes0[12] = { "Janeiro", "Fevereiro", "Marco", "Abril", "Maio","Junho","Julho","Agosto","Setembro","Outubro","Novembro","Dezembro" };
		char auxAno[12];
		sprintf(auxAno, "%d", currentA);
		Font(GLUT_BITMAP_HELVETICA_18, auxMes0[currentM], x_pos + 370, y_pos + 370);
		Font(GLUT_BITMAP_HELVETICA_18, auxAno, x_pos + 300, y_pos + 370);

	}
	else if (modoDeVisualizacao == 1)//Mes
	{
		//eixo x
		char *auxMes1[12] = { "Jan", "Fev", "Mar", "Abr", "Mai","Jun","Jul","Ago","Set","Out","Nov","Dez" };
		for (int i = 0; i < 12; i++)
		{
			Font(GLUT_BITMAP_HELVETICA_10, auxMes1[i], origin_x + espacoEntreChar - 3, y_pos - 13);
			glBegin(GL_LINES);
			glLineWidth(1);
			glVertex2f(origin_x + espacoEntreChar, origin_y);
			glVertex2f(origin_x + espacoEntreChar, origin_y - 7);
			glEnd();
			espacoEntreChar = espacoEntreChar + 56;
		}
		espacoEntreChar = 0;
		char auxAno[12];
		sprintf(auxAno, "%d", currentA);
		Font(GLUT_BITMAP_HELVETICA_18, auxAno, x_pos + 370, y_pos + 370);
		Font(GLUT_BITMAP_HELVETICA_18, "Meses", x_pos + 675, y_pos);
	}
	else//Ano
	{
		//eixo x
		char aux[12];
		int counter = anoAtual - 9;
		for (int i = 1; i <= 10; i++)
		{
			sprintf(aux, "%d", counter++);
			Font(GLUT_BITMAP_HELVETICA_10, aux, origin_x + espacoEntreChar - 3, y_pos - 13);
			glBegin(GL_LINES);
			glLineWidth(1);
			glVertex2f(origin_x + espacoEntreChar, origin_y);
			glVertex2f(origin_x + espacoEntreChar, origin_y - 7);
			glEnd();
			espacoEntreChar = espacoEntreChar + 70;
		}
		espacoEntreChar = 0;
		Font(GLUT_BITMAP_HELVETICA_18, "Anos", x_pos + 675, y_pos);
	}
}
//===============================================================================
void desenharBotoesExtra(int x, int y)
{

	glBegin(GL_LINE_STRIP);
	glLineWidth(1);
	glColor3f(0, 0, 0);
	glVertex2f(855, 275);
	glVertex2f(880, 285);
	glVertex2f(880, 265);
	glVertex2f(855, 275);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glLineWidth(1);
	glColor3f(0, 0, 0);
	glVertex2f(larguraMenu + 915, 275);
	glVertex2f(larguraMenu + 890, 285);
	glVertex2f(larguraMenu + 890, 265);
	glVertex2f(larguraMenu + 915, 275);
	glEnd();

	if (modoDeVisualizacao == 0 || modoDeVisualizacao == 1)
	{
		glBegin(GL_LINE_STRIP);
		glLineWidth(1);
		glColor3f(0, 0, 0);
		glVertex2f(larguraMenu + 560, 645);
		glVertex2f(larguraMenu + 585, 655);
		glVertex2f(larguraMenu + 585, 635);
		glVertex2f(larguraMenu + 560, 645);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glLineWidth(1);
		glColor3f(0, 0, 0);
		glVertex2f(larguraMenu + 595, 655);
		glVertex2f(larguraMenu + 620, 645);
		glVertex2f(larguraMenu + 595, 635);
		glVertex2f(larguraMenu + 595, 655);
		glEnd();
	}

	/*
	glBegin(GL_LINE_STRIP);
	glLineWidth(1);
	glColor3f(0, 0, 0);
	glVertex2f(larguraMenu + 915, 305);
	glVertex2f(larguraMenu + 890, 315);
	glVertex2f(larguraMenu + 890, 295);
	glVertex2f(larguraMenu + 915, 305);
	glEnd();
	*/
}
//===============================================================================
void botaoAlimentacao(Botao * b)
{
	currentTab = 1;
	glClearColor(fundoR, fundoG, fundoB, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	desenharEixos(100, 270);
	desenharBotoesExtra(100, 270);

}

void botaoVestuario(Botao * b)
{
	currentTab = 2;
	glClearColor(fundoR, fundoG, fundoB, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	desenharEixos(100, 270);
	desenharBotoesExtra(100, 270);
}
void botaoDeslocacoes(Botao * b)
{
	currentTab = 3;
	glClearColor(fundoR, fundoG, fundoB, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	desenharEixos(100, 270);
	desenharBotoesExtra(100, 270);
}
void botaoLazer(Botao * b)
{
	currentTab = 4;
	glClearColor(fundoR, fundoG, fundoB, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	desenharEixos(100, 270);
	desenharBotoesExtra(100, 270);
}
void botaoOutros(Botao * b)
{
	currentTab = 5;
	glClearColor(fundoR, fundoG, fundoB, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	desenharEixos(100, 270);
	desenharBotoesExtra(100, 270);
}
void botaoTotal(Botao * b)
{
	currentTab = 6;
	glClearColor(fundoR, fundoG, fundoB, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	desenharEixos(100, 270);
	desenharBotoesExtra(100, 270);
}

void botaoProxVis()
{
	if (modoDeVisualizacao == 2)
	{
		modoDeVisualizacao = 0;
	}
	else
		modoDeVisualizacao++;
	glClear(GL_COLOR_BUFFER_BIT);
	desenharEixos(100, 270);
	desenharBotoesExtra(100, 270);
}
void botaoAntVis()
{
	if (modoDeVisualizacao == 0)
	{
		modoDeVisualizacao = 2;
	}
	else
		modoDeVisualizacao--;
	glClear(GL_COLOR_BUFFER_BIT);
	desenharEixos(100, 270);
	desenharBotoesExtra(100, 270);
}
void botaoProxMes()
{
	if (currentA <anoAtual || (currentA == anoAtual && currentM < mesAtual - 1))
	{
		if (currentM == 11)
		{
			currentM = 0;
			currentA++;
			currentA2++;

			currentM2++;
		}
		else
			currentM++;
		currentM2++;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	desenharEixos(100, 270);
	desenharBotoesExtra(100, 270);
}
void botaoAntMes()
{
	if (currentA > anoAtual - 9 || (currentA == anoAtual - 9 && currentM >0))
	{
		if (currentM == 0)
		{
			currentM = 11;
			currentA--;
			currentA2--;
			currentM2--;
		}
		else
			currentM--;
		currentM2--;
	}

	glClear(GL_COLOR_BUFFER_BIT);
	desenharEixos(100, 270);
	desenharBotoesExtra(100, 270);
}
void botaoProxAno()
{
	if (currentA < anoAtual) {
		currentA++;
		currentA2++;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	desenharEixos(100, 270);
	desenharBotoesExtra(100, 270);
}
void botaoAntAno()
{
	if (currentA > anoAtual - 9) {
		currentA--;
		currentA2--;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	desenharEixos(100, 270);
	desenharBotoesExtra(100, 270);
}
//===============================================================================
//ID, x, y, width, height, state, hover, label, callbackFunction;
Botao alimentacao = { 1, 0, altura*0.93, 182, altura*0.07, 0, 0, "Alimentacao",botaoAlimentacao };
Botao vestuario = { 2, 183, altura*0.93, 182, altura*0.07, 0, 0, "Vestuario",botaoVestuario };
Botao deslocacoes = { 3, 366, altura*0.93, 182, altura*0.07, 0, 0, "Deslocacoes",botaoDeslocacoes };
Botao lazer = { 4, 549, altura*0.93, 182, altura*0.07, 0, 0, "Lazer",botaoLazer };
Botao outros = { 5, 732, altura*0.93, 182, altura*0.07, 0, 0, "Outros",botaoOutros };
Botao total = { 6, 915, altura*0.93, 182, altura*0.07, 0, 0, "Comparar",botaoTotal };

Botao anteriorVis = { 8, 850,260,35,25,0,0,"",botaoAntVis };
Botao proximaVis = { 9, 890,260,35,25,0,0,"",botaoProxVis };
Botao anteriorMes = { 10,560,631,30,25,0,0,"",botaoAntMes };
Botao proximoMes = { 11,595,631,30,25,0,0,"",botaoProxMes };
Botao anteriorAno = { 12,560,631,30,25,0,0,"",botaoAntAno };
Botao proximoAno = { 13,595,631,30,25,0,0,"",botaoProxAno };
//===============================================================================
// verifica se o rato está sobre botão
boolean isHoveringButton(Botao *b, int x, int y)
{
	if (x > b->x && x < b->x + b->width && y > b->y && y < b->y + b->height)// area do botão
	{
		return 1;
	}
	else
		return 0;
}
//===============================================================================
void resetState()
{
	alimentacao.state = 0;
	vestuario.state = 0;
	deslocacoes.state = 0;
	lazer.state = 0;
	outros.state = 0;
	total.state = 0;
	proximaVis.state = 0;
	anteriorVis.state = 0;
	proximoMes.state = 0;
	anteriorMes.state = 0;
	proximoAno.state = 0;
	anteriorAno.state = 0;
}
//===============================================================================
void ButtonRelease(Botao *b, int x, int y)
{
	if (b)
	{
		// se houve clique no botão (pressionado e libertado)
		if (isHoveringButton(b, rato.xpress, rato.ypress) && isHoveringButton(b, x, y))
		{
			// chama respectiva função
			if (b->callbackFunction)
			{
				b->callbackFunction(b);
			}
			if (b->id < 8)
			{
				resetState();
				b->state = 1;
			}
			else
			{
				b->state = 0;
			}

		}
	}
}
//===============================================================================
void ButtonPress(Botao *b, int x, int y)
{
	if (isHoveringButton(b, x, y))
	{
		b->state = 1;
	}
}
//===============================================================================
void checkButton(Botao *b, int x, int y)
{
	// se o rato passar por cima do botão
	if (isHoveringButton(b, x, y))
	{
		b->hover = 1;
		glutPostRedisplay();
	}
	else
	{
		b->hover = 0;
		glutPostRedisplay();
	}
}
//===============================================================================
void MouseButton(int button, int state, int x, int y)
{
	rato.x = x;
	rato.y = altura - y;

	if (state == GLUT_DOWN)
	{
		rato.xpress = x;
		rato.ypress = altura - y;

		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			rato.lmb = 1;
			ButtonPress(*botaoAlimentacao, x, altura - y);
			ButtonPress(*botaoVestuario, x, altura - y);
			ButtonPress(*botaoDeslocacoes, x, altura - y);
			ButtonPress(*botaoLazer, x, altura - y);
			ButtonPress(*botaoOutros, x, altura - y);
			ButtonPress(*botaoTotal, x, altura - y);
			if (currentTab <7 && currentTab != 0)
			{
				ButtonPress(*botaoProxVis, x, altura - y);
				ButtonPress(*botaoAntVis, x, altura - y);
				if (modoDeVisualizacao == 0)
				{
					ButtonPress(*botaoProxMes, x, altura - y);
					ButtonPress(*botaoAntMes, x, altura - y);
				}
				if (modoDeVisualizacao == 1)
				{
					ButtonPress(*botaoProxAno, x, altura - y);
					ButtonPress(*botaoAntAno, x, altura - y);
				}


			}
			break;
		case GLUT_MIDDLE_BUTTON:
			rato.mmb = 1;
			break;
		case GLUT_RIGHT_BUTTON:
			rato.rmb = 1;
			break;
		}
	}

	else {
		switch (button) {
		case GLUT_LEFT_BUTTON:
			rato.lmb = 0;
			ButtonRelease(&alimentacao, x, altura - y);
			ButtonRelease(&vestuario, x, altura - y);
			ButtonRelease(&deslocacoes, x, altura - y);
			ButtonRelease(&lazer, x, altura - y);
			ButtonRelease(&outros, x, altura - y);
			ButtonRelease(&total, x, altura - y);
			if (currentTab < 7 && currentTab != 0)
			{
				ButtonRelease(&proximaVis, x, altura - y);
				ButtonRelease(&anteriorVis, x, altura - y);
				if (modoDeVisualizacao == 0)
				{
					ButtonRelease(&proximoMes, x, altura - y);
					ButtonRelease(&anteriorMes, x, altura - y);
				}
				if (modoDeVisualizacao == 1)
				{
					ButtonRelease(&proximoAno, x, altura - y);
					ButtonRelease(&anteriorAno, x, altura - y);
				}

			}
			break;
		case GLUT_MIDDLE_BUTTON:
			rato.mmb = 0;
			break;
		case GLUT_RIGHT_BUTTON:
			rato.rmb = 0;
			break;
		}
	}
	glutPostRedisplay();
}
//===============================================================================
void MouseMotion(int x, int y)
{
	rato.x = x;
	rato.y = altura - y;

	checkButton(&alimentacao, x, altura - y);
	checkButton(&vestuario, x, altura - y);
	checkButton(&deslocacoes, x, altura - y);
	checkButton(&lazer, x, altura - y);
	checkButton(&outros, x, altura - y);
	checkButton(&total, x, altura - y);
	if (currentTab < 7 && currentTab != 0)
	{
		checkButton(&proximaVis, x, altura - y);
		checkButton(&anteriorVis, x, altura - y);
		if (modoDeVisualizacao == 0)
		{
			checkButton(&proximoMes, x, altura - y);
			checkButton(&anteriorMes, x, altura - y);
		}
		if (modoDeVisualizacao == 1)
		{
			checkButton(&proximoAno, x, altura - y);
			checkButton(&anteriorAno, x, altura - y);
		}

	}
	glutPostRedisplay();
}
//===============================================================================
void MousePassiveMotion(int x, int y)
{
	rato.x = x;
	rato.y = y;

	checkButton(&alimentacao, x, altura - y);
	checkButton(&vestuario, x, altura - y);
	checkButton(&deslocacoes, x, altura - y);
	checkButton(&lazer, x, altura - y);
	checkButton(&outros, x, altura - y);
	checkButton(&total, x, altura - y);
	if (currentTab < 7 && currentTab != 0)
	{
		checkButton(&proximaVis, x, altura - y);
		checkButton(&anteriorVis, x, altura - y);
		if (modoDeVisualizacao == 0)
		{
			checkButton(&proximoMes, x, altura - y);
			checkButton(&anteriorMes, x, altura - y);
		}
		if (modoDeVisualizacao == 1)
		{
			checkButton(&proximoAno, x, altura - y);
			checkButton(&anteriorAno, x, altura - y);
		}

	}
	glutPostRedisplay();
}
//===============================================================================
void desenharBotao(Botao *b)
{
	int fx;
	int fy;

	if (b)
	{
		// se o rato estiver em cima do botão muda a sua cor
		if (b->id < 8)
		{
			if (b->hover || b->state)
				glColor3f(fundoR, fundoG, fundoB);
			else
				glColor3f(menuR, menuG, menuB);
		}
		else if (b->id == 8 || b->id == 9)
		{
			glColor3f(0.88, 0.88, 0.88);
		}


		// desenha o botão
		glBegin(GL_QUADS);

		glVertex2i(b->x, b->y);
		glVertex2i(b->x, b->y + b->height);
		glVertex2i(b->x + b->width, b->y + b->height);
		glVertex2i(b->x + b->width, b->y);

		glEnd();

		// TEXTO 
		//Centralizar

		fx = b->x + (b->width - glutBitmapLength(GLUT_BITMAP_HELVETICA_18, b->label)) / 2;
		fy = (b->y + (b->height + 10) / 2) - 10;


		glColor3f(1, 1, 1);
		Font(GLUT_BITMAP_HELVETICA_18, b->label, fx, fy);
	}
}
//===============================================================================

void desenhaEuro() {

	glColor3f(fundoR + 0.4, fundoG + 0.4, fundoB - 0.2);
	glBegin(GL_LINE_LOOP);
	for (double i = 0; i < 2 * PI; i += PI / 10)
		glVertex3f(1200 + cos(i) * 20, 695 + sin(i) * 20, 0.0);
	glEnd();
	glColor3f(0.25, 0.25, 0.25);

	glBegin(GL_POLYGON);
	glVertex3f(1200, 695, 0);
	glVertex3f(1224, 669, 0);
	glVertex3f(1224, 750, 0);
	glEnd();

	glColor3f(fundoR + 0.4, fundoG + 0.4, fundoB - 0.2);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glVertex3f(1200 - 30, 700, 0);
	glVertex3f(1200 - 10, 700, 0);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3f(1200 - 30, 690, 0);
	glVertex3f(1200 - 10, 690, 0);
	glEnd();



}


void desenhar()
{
	desenharBotao(&alimentacao);
	desenharBotao(&vestuario);
	desenharBotao(&deslocacoes);
	desenharBotao(&lazer);
	desenharBotao(&outros);
	desenharBotao(&total);
	desenhaEuro();
	//desenharBotao(&definicoes);
	//desenharBotao(&anteriorMes);
	//desenharBotao(&proximoMes);
}
//===============================================================================
void desenhaBarraMenu(void)
{
	glColor3f(menuR, menuG, menuB);
	glBegin(GL_POLYGON);
	glVertex2f(0, altura);
	glVertex2f(largura, altura);
	glVertex2f(largura, altura*0.93);
	glVertex2f(0, altura*0.93);
	glEnd();
	glLineWidth(3);
}
//===============================================================================
void init(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(fundoR, fundoG, fundoB, 1);
	gluOrtho2D(0, largura, 0, altura);
	// Limpa a janela
	glClear(GL_COLOR_BUFFER_BIT);
}
//===============================================================================



void display(void)
{
	glViewport(0, 0, largura, altura);

	desenhaBarraMenu();//Desenha a barra do menu
	desenhar();//Desenha os botoes
	glColor3f(0, 0, 0);
	if (currentTab == 0) {
		Font(GLUT_BITMAP_HELVETICA_18, "Bem-vindo! Por favor carregue num dos menus da barra acima!", altura / 2 + 20, largura / 2);
		Font(GLUT_BITMAP_HELVETICA_18, "Para Inserir valores ou Mudar a cor dos graficos, use o botao direito do rato.", altura / 2 - 30, largura / 2 - 30);

	}

	// Desencadeia a geração da imagem (rendering)
	glFlush();
}
//===============================================================================

void CustoTotal(void) {
	for (int i = 0; i < 3650 - 1; i++) {
		familia->gastoTotalDia[i] = familia->custoAlimentacaoDia[i] + familia->custoVestuarioDia[i] + familia->custoDeslocacoesDia[i] + familia->custoLazerDia[i] + familia->custoOutrosDia[i];
	}

}
void savefile() {
	FILE *fpA, *fpV, *fpD, *fpL, *fpO, *fpOR;

	if (!familia->isEmpty) {
		fpA = fopen("DadosAlimentacao.txt", "w");
		fpV = fopen("DadosVestuario.txt", "w");
		fpD = fopen("DadosDeslocacoes.txt", "w");
		fpL = fopen("DadosLazer.txt", "w");
		fpO = fopen("DadosOutros.txt", "w");
		fpOR = fopen("DadosOrcamento.txt", "w");

		fprintf(fpOR, " %f", familia->orcamentoAnual);


		for (int i = 0; i < NumeroDados; i++)
		{
			fprintf(fpA, " %f\n", familia->custoAlimentacaoDia[i]);
			fprintf(fpV, " %f\n", familia->custoVestuarioDia[i]);
			fprintf(fpD, " %f\n", familia->custoDeslocacoesDia[i]);
			fprintf(fpL, " %f\n", familia->custoLazerDia[i]);
			fprintf(fpO, " %f\n", familia->custoOutrosDia[i]);

		}
		fclose(fpA);
		fclose(fpV);
		fclose(fpD);
		fclose(fpL);
		fclose(fpO);
		fclose(fpOR);
		CustoTotal();

	}

}
//===============================================================================
void readfile()
{
	FILE *fpA, *fpV, *fpD, *fpL, *fpO, *fpOR;
	familia = malloc(sizeof(struct Familia));
	familia->custoAlimentacaoDia = malloc(sizeof(float)*MAX);
	familia->custoVestuarioDia = malloc(sizeof(float)*MAX);
	familia->custoDeslocacoesDia = malloc(sizeof(float)*MAX);
	familia->custoLazerDia = malloc(sizeof(float)*MAX);
	familia->custoOutrosDia = malloc(sizeof(float)*MAX);
	familia->gastoTotalDia = malloc(sizeof(float)*MAX);

	fpA = fopen("DadosAlimentacao.txt", "r");
	fpV = fopen("DadosVestuario.txt", "r");
	fpD = fopen("DadosDeslocacoes.txt", "r");
	fpL = fopen("DadosLazer.txt", "r");
	fpO = fopen("DadosOutros.txt", "r");
	fpOR = fopen("DadosOrcamento.txt", "r");
	if (fpA == NULL || fpV == NULL || fpD == NULL || fpL == NULL || fpO == NULL || fpOR == NULL);
	{

	}
	if (fpA == NULL)
	{
		printf("ERRO: Nao existe ficheiro de dados de alimentacao\n"); // debug
	}
	if (fpV == NULL)
	{
		printf("ERRO: Nao existe ficheiro de dados de vestuario\n"); // debug
	}
	if (fpD == NULL)
	{
		printf("ERRO: Nao existe ficheiro de dados de deslocacoes\n"); // debug
	}
	if (fpL == NULL)
	{
		printf("ERRO: Nao existe ficheiro de dados de Lazer\n"); // debug
	}
	if (fpO == NULL)
	{
		printf("ERRO: Nao existe ficheiro de dados de Outros\n"); // debug
	}
	if (fpOR == NULL)
	{
		printf("ERRO: Nao existe ficheiro de dados de Orçamento\n"); // debug
	}
	else
	{

		int i = 0;
		fscanf(fpOR, " %f", &familia->orcamentoAnual);

		while (1)
		{
			fscanf(fpA, "%f", &familia->custoAlimentacaoDia[i]);
			if (feof(fpA))
				break;
			i++;

		}
		i = 0;
		while (1)
		{
			fscanf(fpV, "%f", &familia->custoVestuarioDia[i]);
			if (feof(fpV))
				break;
			i++;

		}
		i = 0;
		while (1)
		{
			fscanf(fpD, "%f", &familia->custoDeslocacoesDia[i]);
			if (feof(fpD))
				break;
			i++;
		}
		i = 0;
		while (1)
		{
			fscanf(fpL, "%f", &familia->custoLazerDia[i]);
			if (feof(fpL))
				break;
			i++;
		}
		i = 0;
		while (1)
		{
			fscanf(fpO, "%f", &familia->custoOutrosDia[i]);
			if (feof(fpO))
				break;
			i++;
		}
		NumeroDados = i - 1;

		CustoTotal();
		familia->isEmpty = FALSE;
		fclose(fpA);
		fclose(fpV);
		fclose(fpD);
		fclose(fpL);
		fclose(fpO);
		fclose(fpOR);


	}
}
//===============================================================================

void subMenuAddDados(GLint tipogasto) {
	float entrada;
	system("cls");
	switch (tipogasto) {
	case 1:
		printf("\nGastos de hoje com Alimentacao: ");
		scanf("%f", &entrada);
		for (int i = 0; i < NumeroDados - 1; i++) {
			familia->custoAlimentacaoDia[i] = familia->custoAlimentacaoDia[i + 1];
		}
		familia->custoAlimentacaoDia[(NumeroDados - 1)] = entrada;
		savefile();
		break;

	case 2:
		printf("\nGastos de hoje com vestuario: ");
		scanf("%f", &entrada);
		for (int i = 0; i < NumeroDados - 1; i++) {
			familia->custoVestuarioDia[i] = familia->custoVestuarioDia[i + 1];
		}
		familia->custoVestuarioDia[(NumeroDados - 1)] = entrada;
		savefile();
		break;
	case 3:
		printf("\nGastos de hoje com Deslocacoes: ");
		scanf("%f", &entrada);
		for (int i = 0; i < NumeroDados - 1; i++) {
			familia->custoDeslocacoesDia[i] = familia->custoDeslocacoesDia[i + 1];
		}
		familia->custoDeslocacoesDia[(NumeroDados - 1)] = entrada;
		savefile();
		break;
	case 4:
		printf("Gastos de hoje com Lazer: ");
		scanf("%f", &entrada);
		for (int i = 0; i < NumeroDados - 1; i++) {
			familia->custoLazerDia[i] = familia->custoLazerDia[i + 1];
		}
		familia->custoLazerDia[(NumeroDados - 1)] = entrada;
		savefile();
		break;
	case 5:
		printf("Gastos de hoje com Outros: ");
		scanf("%f", &entrada);
		for (int i = 0; i < NumeroDados - 1; i++) {
			familia->custoOutrosDia[i] = familia->custoOutrosDia[i + 1];
		}
		familia->custoOutrosDia[(NumeroDados - 1)] = entrada;
		savefile();
		break;
	case 6:
		printf("Novo Orcamento Anual");
		scanf("%f", &entrada);
		familia->orcamentoAnual = entrada;
		savefile();
		break;


	}
	// funcao para fazer calculo dos novos consumos totais/mensais AQUI ########################################################
}
//===============================================================================
void MenuPrincipal(GLint Insercao) {
}
//===============================================================================
void MaxMinMedDP(int TipoDados, float *TabelaValores) {


	int c, tamanho = 29, Maximo, Minimo = 0, Soma = 0, intervalo = 0;
	float Media = 0, DesvioPadrao = 0, Deviation = 0;
	for (int i = 0; i < 120; i++) {
		Maximo = TabelaValores[0 + intervalo];

		for (c = 1 + intervalo; c < tamanho + intervalo; c++)
		{
			if (TabelaValores[c] > Maximo)
			{
				if (TabelaValores[c] < 0) break;
				Maximo = TabelaValores[c];
			}
		}
		intervalo += 30;
		if (TipoDados == 1) ali->MaxMensal[i] = Maximo;
		if (TipoDados == 2) ves->MaxMensal[i] = Maximo;
		if (TipoDados == 3) des->MaxMensal[i] = Maximo;
		if (TipoDados == 4) laz->MaxMensal[i] = Maximo;
		if (TipoDados == 5) out->MaxMensal[i] = Maximo;
		if (TipoDados == 6) tot->MaxMensal[i] = Maximo;

	}
	tamanho = 365;
	intervalo = 0;

	for (int i = 0; i < 10; i++) {
		Maximo = TabelaValores[0 + intervalo];

		for (int c = 1 + intervalo; c < tamanho + intervalo; c++)
		{

			if (TabelaValores[c] > Maximo)
			{
				if (TabelaValores[c] < 0) break;
				Maximo = TabelaValores[c];
			}
		}
		intervalo += 365;
		if (TipoDados == 1) ali->MaxAnual[i] = Maximo;
		if (TipoDados == 2) ves->MaxAnual[i] = Maximo;
		if (TipoDados == 3) des->MaxAnual[i] = Maximo;
		if (TipoDados == 4) laz->MaxAnual[i] = Maximo;
		if (TipoDados == 5) out->MaxAnual[i] = Maximo;
		if (TipoDados == 6) tot->MaxAnual[i] = Maximo;
	}

	Maximo = TabelaValores[0];
	for (int c = 0; c < 3650 - 1; c++)
	{
		if (TabelaValores[c] > Maximo)
		{
			if (TabelaValores[c] < 0) break;
			Maximo = TabelaValores[c];
		}
	}
	if (TipoDados == 1) ali->MaxSempre = Maximo;
	if (TipoDados == 2) ves->MaxSempre = Maximo;
	if (TipoDados == 3) des->MaxSempre = Maximo;
	if (TipoDados == 4) laz->MaxSempre = Maximo;
	if (TipoDados == 5) out->MaxSempre = Maximo;
	if (TipoDados == 6) tot->MaxSempre = Maximo;

	//###########################################
	intervalo = 0;
	tamanho = 29;
	for (int i = 0; i < 120; i++) {
		Minimo = TabelaValores[0 + intervalo];

		for (c = 1 + intervalo; c < tamanho + intervalo; c++)
		{
			if (TabelaValores[c] < Minimo)
			{
				if (TabelaValores[c] < 0) break;

				Minimo = TabelaValores[c];
			}
		}
		intervalo += 30;
		if (TipoDados == 1) ali->MinMensal[i] = Minimo;
		if (TipoDados == 2) ves->MinMensal[i] = Minimo;
		if (TipoDados == 3) des->MinMensal[i] = Minimo;
		if (TipoDados == 4) laz->MinMensal[i] = Minimo;
		if (TipoDados == 5) out->MinMensal[i] = Minimo;
		if (TipoDados == 6) tot->MinMensal[i] = Minimo;
	}
	tamanho = 365;
	intervalo = 0;

	for (int i = 0; i < 10; i++) {
		Minimo = TabelaValores[0 + intervalo];
		for (int c = 1 + intervalo; c < tamanho + intervalo; c++)
		{
			if (TabelaValores[c] < Minimo)
			{
				if (TabelaValores[c] < 0) break;
				Minimo = TabelaValores[c];
			}
		}
		intervalo += 365;
		if (TipoDados == 1) ali->MinAnual[i] = Minimo;
		if (TipoDados == 2) ves->MinAnual[i] = Minimo;
		if (TipoDados == 3) des->MinAnual[i] = Minimo;
		if (TipoDados == 4) laz->MinAnual[i] = Minimo;
		if (TipoDados == 5) out->MinAnual[i] = Minimo;
		if (TipoDados == 6) tot->MinAnual[i] = Minimo;
	}

	Minimo = TabelaValores[0];
	for (int c = 0; c < 3650 - 1; c++)
	{
		if (TabelaValores[c] < Minimo)
		{
			if (TabelaValores[c] < 0) break;

			Minimo = TabelaValores[c];
		}
	}
	if (TipoDados == 1) ali->MinSempre = Minimo;
	if (TipoDados == 2) ves->MinSempre = Minimo;
	if (TipoDados == 3) des->MinSempre = Minimo;
	if (TipoDados == 4) laz->MinSempre = Minimo;
	if (TipoDados == 5) out->MinSempre = Minimo;
	if (TipoDados == 6) tot->MinSempre = Minimo;

	//##############################################################################
	//MEDIA
	Soma = Media = 0;
	tamanho = 29;
	intervalo = 0;
	Deviation = 0;
	for (int i = 0; i < 120; i++) {
		for (c = 0 + intervalo; c < tamanho + intervalo; c++)
		{
			if (TabelaValores[c] < 0) break;
			Soma = Soma + TabelaValores[c];
		}

		Media = Soma / c;
		//intervalo += 30;
		for (c = 0 + intervalo; c < tamanho + intervalo; c++)
		{
			if (TabelaValores[c] > 200) break;
			Deviation += pow(TabelaValores[c] - Media, 2);
		}
		DesvioPadrao = sqrt(Deviation / 30);
		intervalo += 30;
		if (TipoDados == 1) ali->DevMensal[i] = DesvioPadrao;
		if (TipoDados == 2) ves->DevMensal[i] = DesvioPadrao;
		if (TipoDados == 3) des->DevMensal[i] = DesvioPadrao;
		if (TipoDados == 4) laz->DevMensal[i] = DesvioPadrao;
		if (TipoDados == 5) out->DevMensal[i] = DesvioPadrao;
		if (TipoDados == 6) tot->DevMensal[i] = DesvioPadrao;

		if (TipoDados == 1) ali->MedMensal[i] = Media;
		if (TipoDados == 2) ves->MedMensal[i] = Media;
		if (TipoDados == 3) des->MedMensal[i] = Media;
		if (TipoDados == 4) laz->MedMensal[i] = Media;
		if (TipoDados == 5) out->MedMensal[i] = Media;
		if (TipoDados == 6) tot->MedMensal[i] = Media;
	}
	Soma = Media = 0;
	tamanho = 365;
	intervalo = 0;
	Deviation = 0;
	for (int i = 0; i < 10; i++) {
		for (c = 0 + intervalo; c < tamanho + intervalo; c++)
		{
			if (TabelaValores[c] < 0) break;

			Soma = Soma + TabelaValores[c];
		}

		Media = Soma / c;

		for (c = 0 + intervalo; c < tamanho + intervalo; c++)
		{
			if (TabelaValores[c] > 200) break;
			Deviation += pow(TabelaValores[c] - Media, 2);
		}
		DesvioPadrao = sqrt(Deviation / 365);
		intervalo += 365;
		if (TipoDados == 1) ali->DevAnual[i] = DesvioPadrao;
		if (TipoDados == 2) ves->DevAnual[i] = DesvioPadrao;
		if (TipoDados == 3) des->DevAnual[i] = DesvioPadrao;
		if (TipoDados == 4) laz->DevAnual[i] = DesvioPadrao;
		if (TipoDados == 5) out->DevAnual[i] = DesvioPadrao;
		if (TipoDados == 6) tot->DevAnual[i] = DesvioPadrao;

		if (TipoDados == 1) ali->MedAnual[i] = Media;
		if (TipoDados == 2) ves->MedAnual[i] = Media;
		if (TipoDados == 3) des->MedAnual[i] = Media;
		if (TipoDados == 4) laz->MedAnual[i] = Media;
		if (TipoDados == 5) out->MedAnual[i] = Media;
		if (TipoDados == 6) tot->MedAnual[i] = Media;
	}
	Soma = Media = 0;
	Deviation = 0;
	for (c = 0; c < 3650 - 1; c++) {
		if (TabelaValores[c] < 0) break;

		Soma = Soma + TabelaValores[c];
	}
	Media = Soma / 3650;

	for (c = 0; c < 3650 - 1; c++)
	{
		if (TabelaValores[c] > 200) break;

		Deviation += pow((TabelaValores[c] - Media), 2);
	}
	DesvioPadrao = sqrt(Deviation / 30);
	if (TipoDados == 1) ali->DevSempre = DesvioPadrao;
	if (TipoDados == 2) ves->DevSempre = DesvioPadrao;
	if (TipoDados == 3) des->DevSempre = DesvioPadrao;
	if (TipoDados == 4) laz->DevSempre = DesvioPadrao;
	if (TipoDados == 5) out->DevSempre = DesvioPadrao;
	if (TipoDados == 6) tot->DevSempre = DesvioPadrao;

	if (TipoDados == 1) ali->MedSempre = Media;
	if (TipoDados == 2) ves->MedSempre = Media;
	if (TipoDados == 3) des->MedSempre = Media;
	if (TipoDados == 4) laz->MedSempre = Media;
	if (TipoDados == 5) out->MedSempre = Media;
	if (TipoDados == 6) tot->MedSempre = Media;


}
//===============================================================================
void CalculosEstat(void) {
	MaxMinMedDP(1, familia->custoAlimentacaoDia);
	MaxMinMedDP(2, familia->custoVestuarioDia);
	MaxMinMedDP(3, familia->custoDeslocacoesDia);
	MaxMinMedDP(4, familia->custoLazerDia);
	MaxMinMedDP(5, familia->custoOutrosDia);
	MaxMinMedDP(6, familia->gastoTotalDia);

}
void setCor(int modo, float red, float green, float blue)
{
	if (modo == 1)//alimentacao
	{
		familia->corAli[0] = red;
		familia->corAli[1] = green;
		familia->corAli[2] = blue;
	}
	else if (modo == 2)//vestuario
	{
		familia->corVes[0] = red;
		familia->corVes[1] = green;
		familia->corVes[2] = blue;
	}
	else if (modo == 3)//deslocaçoes
	{
		familia->corDes[0] = red;
		familia->corDes[1] = green;
		familia->corDes[2] = blue;
	}
	else if (modo == 4)//lazer
	{
		familia->corLaz[0] = red;
		familia->corLaz[1] = green;
		familia->corLaz[2] = blue;
	}
	else if (modo == 5)//outros
	{
		familia->corOut[0] = red;
		familia->corOut[1] = green;
		familia->corOut[2] = blue;
	}
	else if (modo == 6)
	{
		familia->corOrcamento[0] = red;
		familia->corOrcamento[1] = green;
		familia->corOrcamento[2] = blue;
	}
}
void subMenuAlterarCor(GLint tipo)
{
	float red, green, blue;
	system("cls");
	switch (tipo)
	{
	case 1:
		printf("\nAlimentacao");
		printf("\nIndique a cor que pretende em formato RGB(de 0 a 1):");
		printf("\nRed: ");
		scanf("%f", &red);
		printf("Green: ");
		scanf("%f", &green);
		printf("Blue: ");
		scanf("%f", &blue);
		setCor(1, red, green, blue);
		break;
	case 2:
		printf("\nVestuario");
		printf("\nIndique a cor que pretende em formato RGB(de 0 a 1):");
		printf("\nRed: ");
		scanf("%f", &red);
		printf("Green: ");
		scanf("%f", &green);
		printf("Blue: ");
		scanf("%f", &blue);
		setCor(2, red, green, blue);
		break;
	case 3:
		printf("\nDeslocacoes");
		printf("\nIndique a cor que pretende em formato RGB(de 0 a 1):");
		printf("\nRed: ");
		scanf("%f", &red);
		printf("Green: ");
		scanf("%f", &green);
		printf("Blue: ");
		scanf("%f", &blue);
		setCor(3, red, green, blue);
		break;
	case 4:
		printf("\nLazer");
		printf("\nIndique a cor que pretende em formato RGB(de 0 a 1):");
		printf("\nRed: ");
		scanf("%f", &red);
		printf("Green: ");
		scanf("%f", &green);
		printf("Blue: ");
		scanf("%f", &blue);
		setCor(4, red, green, blue);
		break;
	case 5:
		printf("\nOutros");
		printf("\nIndique a cor que pretende em formato RGB(de 0 a 1):");
		printf("\nRed: ");
		scanf("%f", &red);
		printf("Green: ");
		scanf("%f", &green);
		printf("Blue: ");
		scanf("%f", &blue);
		setCor(5, red, green, blue);
		break;
	case 6:
		printf("\nOrcamento");
		printf("\nIndique a cor que pretende em formato RGB(de 0 a 1):");
		printf("\nRed: ");
		scanf("%f", &red);
		printf("Green: ");
		scanf("%f", &green);
		printf("Blue: ");
		scanf("%f", &blue);
		setCor(6, red, green, blue);
		break;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	desenharEixos(100, 270);
	desenharBotoesExtra(100, 270);

}
//===============================================================================
int main(int argc, char** argv)
{

	ali = malloc(sizeof(struct Auxiliar));
	ves = malloc(sizeof(struct Auxiliar));
	des = malloc(sizeof(struct Auxiliar));
	laz = malloc(sizeof(struct Auxiliar));
	out = malloc(sizeof(struct Auxiliar));
	tot = malloc(sizeof(struct Auxiliar));

	getCurrentDate();
	readfile();
	savefile();
	CalculosEstat();
	setCor(1, 0.15, 0.62, 0.64);
	setCor(2, 0, 0.43, 0.75);
	setCor(3, 0.95, 0.61, 0.07);
	setCor(4, 0.95, 0.2, 0.07);
	setCor(5, 0.95, 0, 0);
	glutInit(&argc, argv);

	glutInitWindowSize(largura, altura);

	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - largura) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - altura) / 2);

	// Cria a janela GLUT de visualização
	glutCreateWindow("Gestão Financeira Familiar");

	init();
	glutReshapeFunc(reshape);
	// Obrigatório registar uma "callback function", neste caso de visualização
	glutDisplayFunc(display);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	// Esperando por eventos

	GLint AddDados = glutCreateMenu(subMenuAddDados);
	glutAddMenuEntry("Gastos de Alimentacao", 1);
	glutAddMenuEntry("Gastos de Vestuario", 2);
	glutAddMenuEntry("Gastos de Deslocacoes", 3);
	glutAddMenuEntry("Gastos de Lazer", 4);
	glutAddMenuEntry("Gastos de Outros", 5);
	glutAddMenuEntry("Orcamento", 6);
	GLint alterarCor = glutCreateMenu(subMenuAlterarCor);
	glutAddMenuEntry("Alimentacao", 1);
	glutAddMenuEntry("Vestuario", 2);
	glutAddMenuEntry("Deslocacoes", 3);
	glutAddMenuEntry("Lazer", 4);
	glutAddMenuEntry("Outros", 5);
	glutAddMenuEntry("Orcamento", 6);

	glutCreateMenu(MenuPrincipal);
	glutAddSubMenu("Adicionar dados de hoje:", AddDados);
	glutAddSubMenu("Alterar cor do grafico:", alterarCor);
	glutAttachMenu(GLUT_RIGHT_BUTTON);



	glutMainLoop();

	return EXIT_SUCCESS;
}