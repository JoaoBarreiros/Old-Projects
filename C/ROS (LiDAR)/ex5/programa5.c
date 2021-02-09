#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <math.h>
#include "func2.c"
#include <sched.h>

#define NUM_T 3
#define T1 100 //milissegundos
#define T2 100 //milissegundos
#define T3 100 //milissegundos
#define TIME_OF_EXECUTION 300
#define WAIT_TIME 1000
pthread_mutex_t lock;

struct argEntrada//Argumentos de entrada da thread
{
	unsigned int    tarefa;  //Tarefa a ser executada por uma thread
	struct timespec inicio;  //Tempo global de inicio
	struct timespec fim;	 //tempo global de fim
	struct timespec periodo; //Periodo de ativação
};
//============================================================================================
struct timespec timeDiff(struct timespec start, struct timespec end)
{
        struct timespec aux;
        if ((end.tv_nsec - start.tv_nsec) < 0) 
        {
                aux.tv_sec = end.tv_sec - start.tv_sec - 1;
                aux.tv_nsec = 1E9 + end.tv_nsec - start.tv_nsec;
        } 
        else 
        {
                aux.tv_sec = end.tv_sec - start.tv_sec;
                aux.tv_nsec = end.tv_nsec - start.tv_nsec;
        }
        return aux;//Retorna uma struct timespec cujo os atributos são a diferença entre os atributos da timespec end e timespec start
}
//============================================================================================
struct timespec timeSum(struct timespec a, struct timespec b)
{
	struct timespec result;

	result.tv_nsec = a.tv_nsec + b.tv_nsec;
	if (result.tv_nsec > (int)1E9-1)
	{
		result.tv_nsec = result.tv_nsec % (int)1E9;
		result.tv_sec = 1 + a.tv_sec + b.tv_sec;
	}
	else
	{
		result.tv_sec = a.tv_sec + b.tv_sec;
	}
	return result;
}
//============================================================================================
int timeLT(struct timespec a, struct timespec b) 
{
	//Retorna 1 se o valor temporal da timespec a é menor que o valor temporal da timespec b
	//Retorna 0 nos outros casos
	if (a.tv_sec < b.tv_sec)
	{
		return 1;
	}
	else{
		if (a.tv_sec == b.tv_sec)
		{
			if (a.tv_nsec < b.tv_nsec)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
}
//============================================================================================
int timeEQ(struct timespec a, struct timespec b)
{
	return a.tv_sec == b.tv_sec && a.tv_nsec == b.tv_nsec;
}
//============================================================================================
struct timespec timeSet(int milliseconds)
{
	struct timespec aux;
	aux.tv_sec = (int)(milliseconds/1000);						// converte ms para s
	aux.tv_nsec = (long int)(milliseconds % 1000) * 1E6;		// converte os restantes ms para ns
	return aux;
}
//============================================================================================
long double timeInMs(struct timespec a) //retorna um double que corresponde ao valor temporal em ms dos atributos da struct timespec a
{
	return (long double)(a.tv_sec * (long double)1E3 + a.tv_nsec / (long double)1E6);
}
//============================================================================================
void* start_routine(void *argumentos)
{
	struct argEntrada *args = (struct argEntrada *)argumentos;
	struct timespec nextExeTime = args->inicio;
	char fichin[80];
	char fichout[80];
	int counter=1;
	//========================================================================================
	while (timeLT(nextExeTime, args->fim) && counter <=3)
	{
		if (clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &nextExeTime, NULL) != 0)//Sistema fica à espera até chegarmos ao tempo da proxima execução
		{
			perror( "Error on clock_nanosleep()" );
			exit( EXIT_FAILURE );
		}
		pthread_mutex_lock(&lock);
		sprintf(fichin,"point_cloud%d.txt",counter);
		sprintf(fichout,"preprocessed%d.txt",counter);
		//Executa a tarefa que foi passada pelos argumentos de entrada
		if (args->tarefa == 0)
		{
			f1(fichin);
		}
		else if (args->tarefa == 1)
		{
			f2();
		}
		else if (args->tarefa == 2)
		{
			f3(fichout);
		}
		nextExeTime = timeSum(nextExeTime, args->periodo);
		counter++;
		pthread_mutex_unlock(&lock);
	}
	pthread_exit(NULL);
}
int main(int argc,char **argv)
{
	pthread_attr_t attr[NUM_T];
	pthread_t thread[NUM_T];
	struct sched_param param[NUM_T];
	struct timespec inicio, fim;				//inicialização de structs que vao ser usadas para calcular o tempo de cada tarefa
	struct argEntrada argumentos[NUM_T];		//declaração dos
	cpu_set_t cpuset;							//declaração da mascara de CPU
	int periodosAtivacao[NUM_T]={T1,T2,T3};		//inicializar os periodos de ativação 
	int i;
	//========================================================================================
	if (mlockall(MCL_CURRENT | MCL_FUTURE) == -1)
	{
		perror( "Error on mlockall()" );
		exit( EXIT_FAILURE );
	}
	//========================================================================================
	CPU_ZERO(&cpuset);										//esvazia o set de CPUs
	CPU_SET(0, &cpuset);									//adiciona o core 0 ao set de CPUs -> Queremos que esta aplicação seja executada numa só thread como pede o enunciado
	if(sched_setaffinity(0, sizeof(cpuset), &cpuset) == -1)	//define a afinidade deste processo só para o CPU0 
	{
		perror( "Error on sched_setaffinity()" );
		exit( EXIT_FAILURE );
	}
	if (clock_gettime(CLOCK_MONOTONIC, &inicio) == -1)
	{
		perror( "Error on clock_gettime()" );
		exit( EXIT_FAILURE );
	}
	inicio = timeSum(inicio, timeSet((int)WAIT_TIME));		//Tempo global de inicio 
	fim = timeSum(inicio, timeSet((int)TIME_OF_EXECUTION));	//Tempo global de fim
	if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    //========================================================================================
    for(i=0;i<NUM_T;i++)
	{
		if (pthread_attr_init(&(attr[i])) != 0)//inicializa os atributos de cada thread
		{
			perror( "Error on pthread_attr_init()" );
			exit( EXIT_FAILURE );
		}
		if (pthread_attr_setaffinity_np(&(attr[i]), sizeof(cpuset), &cpuset) != 0)//Forçar todas as threads para serem executadas no core 0 do processador, para poder haver concorrencia entre as threads
		{
			perror( "Error on pthread_attr_setaffinity_np()" );
			exit( EXIT_FAILURE ); 
		}
		if (pthread_attr_setinheritsched(&(attr[i]), PTHREAD_EXPLICIT_SCHED) != 0)//Impedir que as threads recebam a política de escalonamento da main thread por herança
		{
			perror( "Error on pthread_attr_setinheritsched()" );
			exit( EXIT_FAILURE ); 
		}
		if (pthread_attr_setschedpolicy(&(attr[i]), SCHED_FIFO) != 0)//Define o atributo da política de escalonamento de cada thread para 'policy' -> neste caso FIFO 
		{
			perror( "Error on pthread_attr_setschedpolicy()" );
			exit( EXIT_FAILURE ); 
		}
		//Thread 0 -> (int)Prioridade máxima
		//Thread 1 -> (int)Prioridade máxima - 1
		//Thread 2 -> (int)Prioridade máxima - 2
		//Thread i -> (int)Prioridade máxima - i  
		if ((param[i].sched_priority = sched_get_priority_max(SCHED_FIFO) - i) == -1) //Define a prioridade a ser usada na thread i
		{
			perror( "Error on sched_get_priority_max()" );
			exit( EXIT_FAILURE );
		}
		if (pthread_attr_setschedparam(&(attr[i]), &(param[i])) != 0) //Coloca a prioridade definida anteriormente na thread i
		{
			perror( "Error on pthread_attr_setschedparam()" );
			exit( EXIT_FAILURE );
		}
		//Argumentos de entrada para a thread i 
		argumentos[i].tarefa   = i;										//Tarefa a ser executada 
		argumentos[i].inicio   = inicio;								//Tempo global de inicio
		argumentos[i].fim  	   = fim;									//Tempo global de fim
		argumentos[i].periodo  = timeSet(periodosAtivacao[i]);		    //Periodo de ativação
		if (pthread_create(&(thread[i]), &(attr[i]), start_routine, &(argumentos[i])) != 0)//Criar as threads com os atributos definidos anteriormente
		{
			perror( "Error on pthread_create()" );
			exit( EXIT_FAILURE );
		}
	}
	//========================================================================================
	for (i = 0; i < NUM_T; i++)
	{
		if (pthread_join(thread[i],NULL) != 0)
		{
			perror( "Error on pthread_join()" );
			exit( EXIT_FAILURE );
		}
		if (pthread_attr_destroy(&(attr[i])) != 0)
		{
			perror( "Error on pthread_attr_destroy()" );
			exit( EXIT_FAILURE );
		}
	}
	pthread_mutex_destroy(&lock);
	return 0;
}
