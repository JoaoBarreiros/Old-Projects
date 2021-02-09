#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define MAX 25000

struct Pontos *pnt;

void f1(const char *NOME_DO_FICHEIRO);
void f2();
void f3(const char *NOME_DO_FICHEIRO_DE_SAIDA);
struct timespec timeSet(int);
struct timespec timeSum(struct timespec, struct timespec);
int timeLT(struct timespec, struct timespec);
int timeEQ(struct timespec, struct timespec);

struct Pontos
{
    double *posX, *posY, *posZ;
    int dim;
    double mediaX,mediaY,mediaZ,maxX,maxY,maxZ,minX,minY,minZ,devX,devY,devZ;
};
//=====================================================================================================================================
struct Pontos *LiDAR(const char *NOME_DO_FICHEIRO)//Le o ficheiro
{
	FILE *fich;
	fich = fopen(NOME_DO_FICHEIRO, "r");//Abrir ficheiro
	struct Pontos *array = malloc(sizeof(double)*15+sizeof(int));
	array->posX = (double*)malloc(sizeof(double)*MAX);
	array->posY = (double*)malloc(sizeof(double)*MAX);
	array->posZ = (double*)malloc(sizeof(double)*MAX);
	double x,y,z;
	int i = 0;

	while(1)
	{
		fscanf(fich, "%lf %lf %lf",&x,&y,&z);//Ler até EOF
		if( feof(fich) ) 
        	break ;
		array->posX[i] = x;
		array->posY[i] = y;
		array->posZ[i] = z;
		i++;
	}
	array->dim = i;
	array->posX = realloc(array->posX,sizeof(double)*array->dim);
	array->posY = realloc(array->posY,sizeof(double)*array->dim);
	array->posZ = realloc(array->posZ,sizeof(double)*array->dim);
	fclose(fich);
	return array;
}
//=====================================================================================================================================
void Escrever(struct Pontos *array, const char* fichout)//escreve ficheiro
{
	FILE *fich;
	fich = fopen(fichout, "w");//Abrir ficheiro

	int i = 0;

	while(i<array->dim)
	{
		fprintf(fich, "%lf %lf %lf\n",array->posX[i],array->posY[i],array->posZ[i]);
		i++;
	}
	fclose(fich);
}
//=====================================================================================================================================
//ex1
void MMMD(struct Pontos *a)//Min Max Mean Deviation -> MMMD
{
	//Calcula a media, o min, o max e o desvio 
	int i;
	double Sx=0.0,Sy=0.0,Sz=0.0;
	double totalX = 0, totalY = 0, totalZ = 0;
	a->maxX = a->minX = a->posX[0]; 
	a->maxY = a->minY = a->posY[0]; 
	a->maxZ = a->minZ = a->posZ[0]; 
	for(i=0;i<a->dim;i++)
	{
		a->maxX = a->maxX<a->posX[i]? a->posX[i] : a->maxX;
		a->maxY = a->maxY<a->posY[i]? a->posY[i] : a->maxY;
		a->maxZ = a->maxZ<a->posZ[i]? a->posZ[i] : a->maxZ;
		a->minX = a->minX>a->posX[i]? a->posX[i] : a->minX;
		a->minY = a->minY>a->posY[i]? a->posY[i] : a->minY;
		a->minZ = a->minZ>a->posZ[i]? a->posZ[i] : a->minZ;
		totalX += a->posX[i];
		totalY += a->posY[i];
		totalZ += a->posZ[i];
	}
	a->mediaX = totalX/i;
	a->mediaY = totalY/i;
	a->mediaZ = totalZ/i;
	
	for(i=0;i<a->dim;i++)
	{
		Sx += pow((a->posX[i]-a->mediaX),2);
		Sy += pow((a->posY[i]-a->mediaY),2);
		Sz += pow((a->posZ[i]-a->mediaZ),2);
	}

	a->devX = sqrt(Sx/(a->dim-1));
	a->devY = sqrt(Sy/(a->dim-1));
	a->devZ = sqrt(Sz/(a->dim-1));

}
//=====================================================================================================================================
//ex 2
void Pre_proc(struct Pontos *a)
{
	int i,j;
	double *posX = malloc(sizeof(double)*a->dim);
	double *posY = malloc(sizeof(double)*a->dim);
	double *posZ = malloc(sizeof(double)*a->dim);
	for(i=0,j=0;i<a->dim;i++)
	{
		if(a->posX[i] >= 0.0 && a->posX[i]<= 30.0)//Tira os pontos X negativos e define um limite positivo de 30 unidades
		{
			if(a->posY[i] <= 15.0 && a->posY[i] >= -15.0)//Tira os pontos Y das extremidades
			{
				if(a->posZ[i]<=a->1.5)//Tira alguns outliers e pontos que estão acima do carro
				{
					posX[j] = a->posX[i];
					posY[j] = a->posY[i];
					posZ[j] = a->posZ[i];
					j++;
				}
			}
		}
	}
	a->dim = j;
	a->posX = realloc(a->posX,sizeof(double)*a->dim);
	a->posY = realloc(a->posY,sizeof(double)*a->dim);
	a->posZ = realloc(a->posZ,sizeof(double)*a->dim);
	a->posX = posX;
	a->posY = posY;
	a->posZ = posZ;
}
//=====================================================================================================================================
//ex3

struct str_sort 
{
double var;
int index; 
};

int cmp(const void *a,const void *b) {
struct str_sort *a1 = (struct str_sort *)a;
struct str_sort *a2 = (struct str_sort *)b;
return ((*a1).var >= (*a2).var) ? 1 : -1; 
}

void Sort_array(struct Pontos *a)//Faz o sort da array dos pontos em ordem a x
{	
	double *posX,*posY,*posZ;
	posX = (double*)malloc(sizeof(double)*a->dim);
	posY = (double*)malloc(sizeof(double)*a->dim);
	posZ = (double*)malloc(sizeof(double)*a->dim);
	struct str_sort *sorted_array;
	sorted_array = malloc(sizeof(struct str_sort)*a->dim);
	int i;
	for(i=0;i<a->dim;i++)
	{
		sorted_array[i].var=a->posX[i];
		sorted_array[i].index = i;
	}
	qsort(sorted_array, a->dim, sizeof(sorted_array[0]), cmp);
	for (i=0; i<a->dim; i++)
	{	
		posX[i] = sorted_array[i].var;
		posY[i] = a->posY[sorted_array[i].index];
		posZ[i] = a->posZ[sorted_array[i].index];
	}
	free(sorted_array);
	free(a->posX);
	free(a->posY);
	free(a->posZ);
	a->posX = posX;
	a->posY = posY;
	a->posZ = posZ;
}
//=====================================================================================================================================
//ex3
void Proc(struct Pontos *a)
{
	//Encontrar os pontos do chão
	int i,j,k,counter = 0,dim = 0;
	double zmin,dist,distX,distY,distZ;
	double *pos_X = malloc(sizeof(double)*a->dim);
	double *pos_Y = malloc(sizeof(double)*a->dim);
	double *pos_Z = malloc(sizeof(double)*a->dim);


	for(i=0;i<a->dim;i+=(j-i))
	{
		zmin = a->posZ[i];
		for(j = i+1; abs(a->posX[j] - a->posX[i]) < 1; j++)
		{
			zmin = zmin < a->posZ[j] ? zmin  : a->posZ[j];//Calcular zmin para um dado posX+-1
		}
		for(k = i; k < j; k++)
		{
			if(a->posZ[k] <= (zmin+0.1) )
			{
				//Guardar os pontos muito pertos de zmin apenas
				pos_X[dim] = a->posX[k];
				pos_Y[dim] = a->posY[k];
				pos_Z[dim] = a->posZ[k];
				dim++;
			}
		}
	}
	//Verificar se os pontos guardados são clusters ou não:
	a->dim=0;
	for (i = 0; i < dim; i++)
	{
		counter = 0;
		for(j = i+1; j < dim; j++)
		{
			distX = pos_X[j] - pos_X[i];
			distY = pos_Y[j] - pos_Y[i];
			distZ = pos_Z[j] - pos_Z[i];
			dist = distX > distY? (distX > distZ? distX:distZ):(distY > distZ? distY:distZ);
			//Criar um cubo em volta do ponto i
			//Verificar se um outro ponto j se encontra dentro desse cubo
			if(dist<=1)
			{
				counter++;
			}
		}
		if(counter>20)//Caso existam mais de 20 pontos dentro desse cubo, podemos assumir que estamos perante um objeto ou superfície
		{
			a->posX[a->dim] = pos_X[i];
			a->posY[a->dim] = pos_Y[i];
			a->posZ[a->dim] = pos_Z[i];
			a->dim++;
		}
	}
	a->posX = realloc(a->posX,sizeof(double)*a->dim);
	a->posY = realloc(a->posY,sizeof(double)*a->dim);
	a->posZ = realloc(a->posZ,sizeof(double)*a->dim);
}

//=====================================================================================================================================
void Display(struct Pontos *inicio)
{
	//Mostra o Mínimo, o Máximo, a Média, o Desvio e ainda a Dimensão de cada componente
	printf("\nMIN: %lf %lf %lf",inicio->minX,inicio->minY,inicio->minZ);
	printf("\nMAX: %lf %lf %lf",inicio->maxX,inicio->maxY,inicio->maxZ);
	printf("\nMEDIAS: %lf %lf %lf",inicio->mediaX,inicio->mediaY,inicio->mediaZ);
	printf("\nDeviation: %lf %lf %lf",inicio->devX,inicio->devY,inicio->devZ);
	printf("\nDIM: %d\n",inicio->dim);
}

void f1(const char *NOME_DO_FICHEIRO)
{
	//printf("f1\n");
	pnt = LiDAR(NOME_DO_FICHEIRO);
	MMMD(pnt);
	Display(pnt);
	//printf("fim de f1\n");
}

void f2()
{
	//printf("f2\n");
	Pre_proc(pnt);
	//printf("fim de f2\n");
}

void f3(const char *NOME_DO_FICHEIRO_DE_SAIDA)
{
	//printf("f3\n");
	Sort_array(pnt);
	Proc(pnt);
	Escrever(pnt,NOME_DO_FICHEIRO_DE_SAIDA);
	//printf("fim de f3\n");
}

