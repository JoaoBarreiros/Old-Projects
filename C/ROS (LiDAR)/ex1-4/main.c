#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>
#define MAX 25000

//=====================================================================================================================================
//Para testar tempos de execução
struct timespec timeDiff(struct timespec start, struct timespec end)
{
        struct timespec temp;
        if ((end.tv_nsec - start.tv_nsec) < 0) 
        {
                temp.tv_sec = end.tv_sec - start.tv_sec - 1;
                temp.tv_nsec = 1E9 + end.tv_nsec - start.tv_nsec;
        } 
        else 
        {
                temp.tv_sec = end.tv_sec - start.tv_sec;
                temp.tv_nsec = end.tv_nsec - start.tv_nsec;
        }
        return temp;//Retorna uma struct timespec cujo os atributos são a diferença entre os atributos da timespec end e timespec start
}
//=====================================================================================================================================
//Para testar tempos de execução
long double timeInMs(struct timespec a) //retorna um double que corresponde ao valor temporal em ms dos atributos da struct timespec a
{
	return (long double)(a.tv_sec * (long double)1E3 + a.tv_nsec / (long double)1E6);
}
//=====================================================================================================================================
struct Pontos
{
    double *posX, *posY, *posZ;
    int dim;
    double mediaX,mediaY,mediaZ,maxX,maxY,maxZ,minX,minY,minZ,devX,devY,devZ;
};

//=====================================================================================================================================
//ex1
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
				if(a->posZ[i]<=1.5)//Tira alguns outliers e pontos que estão acima do carro
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
//=====================================================================================================================================
int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("Erro no número de argumentos\n");
		printf("Deverá especificar o ficheiro de texto para leitura e o ficheiro texto para escrita\n");
		printf("Exemplo: %s point_cloud1.txt preprocessed1.txt \n",argv[0]);
		exit(1);
	}
	struct timespec T1,T2,T3,T4;
	struct Pontos *inicio;
	if (clock_gettime(CLOCK_MONOTONIC, &T1) == -1)
	{
		perror( "Error on clock_gettime()" );
		exit( EXIT_FAILURE );
	}
	inicio = LiDAR(argv[1]);
	MMMD(inicio);
	Display(inicio);
	if (clock_gettime(CLOCK_MONOTONIC, &T2) == -1)
	{
		perror( "Error on clock_gettime()" );
		exit( EXIT_FAILURE );
	}
	Pre_proc(inicio);
	if (clock_gettime(CLOCK_MONOTONIC, &T3) == -1)
	{
		perror( "Error on clock_gettime()" );
		exit( EXIT_FAILURE );
	}
	Sort_array(inicio);
	Proc(inicio);
	Escrever(inicio,argv[2]);
	if (clock_gettime(CLOCK_MONOTONIC, &T4) == -1)
	{
		perror( "Error on clock_gettime()" );
		exit( EXIT_FAILURE );
	}
	struct timespec final=timeDiff(T1,T4);//ex4
	struct timespec ex1=timeDiff(T1,T2);//ex4
	struct timespec ex2=timeDiff(T2,T3);//ex4
	struct timespec ex3=timeDiff(T3,T4);//ex4
	printf("Tempo de execução do ex1 em ms: %Lf \n",timeInMs(ex1));
	printf("Tempo de execução do ex2 em ms: %Lf \n",timeInMs(ex2));
	printf("Tempo de execução do ex3 em ms: %Lf \n",timeInMs(ex3));
	printf("Tempo de execução total em ms: %Lf \n",timeInMs(final)); //<95ms
	

	free(inicio->posX);
	free(inicio->posY);
	free(inicio->posZ);
	free(inicio);
	return 0;
}
