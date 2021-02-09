#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <stdlib.h>
#include <netdb.h> 
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
bool loggedIn = 0;
//===================================================================
// error messages: print message and terminate program
void error(char *msg) 
{
    perror(msg);
    exit(0);
}
//===================================================================
void saveSettings(const char *NOME_DO_FICHEIRO, char* serverip, int currentport)//Guarda no ficheiro
{
	FILE *fich;
	fich = fopen(NOME_DO_FICHEIRO, "w");//Abre o ficheiro
	fprintf(fich, "%s %d",serverip,currentport);//Escreve no ficheiro o enderço IP e o porto destino do servidor
	fclose(fich);//Fecha o ficheiro
}
//===================================================================
void readSettings(const char *NOME_DO_FICHEIRO, char* serverip, int *currentport)//Lê o ficheiro
{
	FILE *fich;
	fich = fopen(NOME_DO_FICHEIRO, "r");//Abre o ficheiro
	fscanf(fich, "%s %d",serverip,currentport);//Lê do ficheiro o enderço IP e o porto destino do servidor
	fclose(fich);//Fecha o ficheiro
}
//===================================================================
bool registrationOK(int event, char* username, int sockfd, struct sockaddr_in serv_addr)
{
	char buff[255];
	int aux4;
	if(connect(sockfd,(const struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
		error("ERROR connecting to socket");
	if(write(sockfd,"6",2)<0)
		error("ERROR writing to socket");
	aux4 = htonl(event);
	if(write(sockfd,&aux4,sizeof(aux4))<0)
		error("ERROR writing to socket");
	if(write(sockfd,username,255)<0)
		error("ERROR writing to socket");
	if(read(sockfd,buff,255)<0)// 0 ou 1
		error("ERROR reading from socket");
	if(strcmp(buff,"1")==0)
		return 1;
	else
		return 0;
}
//===================================================================
int showEvents(int sockfd,struct sockaddr_in serv_addr,int *eventNumber,int **eventSeats,char **eventName,char **eventLocation,char **eventDate,char **eventExpectedDuration)
{
	int counter,eventsno,i;
	int *eventS;
	char buffer[256];
	//Connect to server
	if(connect(sockfd,(const struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
		error("ERROR connecting to socket");
	//Reads and prints list of events offered by the current server
	if(write(sockfd,"3",2)<0)//Sends option 3 to server
		error("ERROR writing to socket");
	bzero(buffer,255);
	if(read(sockfd,&eventsno,sizeof(eventsno))<0)//First messagem from server is the number (integer) of events currently available
		error("ERROR reading from socket");
	counter = ntohl(eventsno);

	printf("\nNúmero de eventos:%d",counter);
	printf("\nList of events:");
	printf("\nEventNumber EventName Location Date ExpectedDuration Vacancies/Seats\n");

	//Allocations
	eventNumber =malloc(sizeof(int)*counter);
	eventName = malloc(sizeof(char)*counter);
	eventLocation = malloc(sizeof(char)*counter);
	eventDate = malloc(sizeof(char)*counter);
	eventExpectedDuration = malloc(sizeof(char)*counter);
	*eventSeats = (int*)malloc(sizeof(int)*counter);
	eventS = malloc(sizeof(int)*counter);

	for(i=0;i<counter;i++)
	{
		if(read(sockfd,&*(eventNumber+i),sizeof(int))<0)
			error("ERROR reading from socket");
		eventName[i] = malloc((255)*sizeof(char));
		if(read(sockfd,eventName[i],255)<0)
			error("ERROR reading from socket");
		eventLocation[i] = malloc((255)*sizeof(char));
		if(read(sockfd,eventLocation[i],255)<0)
			error("ERROR reading from socket");
		eventDate[i] = malloc((255)*sizeof(char));
		if(read(sockfd,eventDate[i],255)<0)
			error("ERROR reading from socket");
		eventExpectedDuration[i] = malloc((255)*sizeof(char));
		if(read(sockfd,eventExpectedDuration[i],255)<0)
			error("ERROR reading from socket");
		if(read(sockfd,&*(*eventSeats+i),sizeof(int))<0)
			error("ERROR reading from socket");
		eventS[i] = ntohl(*(*eventSeats+i));
		eventNumber[i] = ntohl(*(eventNumber+i));
		printf("\n%d %s %s %s %s %d ",eventNumber[i],eventName[i],eventLocation[i],eventDate[i],eventExpectedDuration[i],eventS[i]);//Show the current event offered by the server
	}
	for(i=0;i<counter;i++)
	{
		(*eventSeats)[i] = eventS[i];
	}
	close(sockfd);
	return counter;
}
//===================================================================
int main(int argc, char *argv[]) 
{
	char serverip[80],username[80],password[80],term,confirm;//Strings for server IP, client username and password, terminal and confirmation charaters
	int currentport,option,seats,seatsleft;//Port number, option,seats taken by user;
	int sockfd, sockfd2, sockfd3,sockfd4;//Socket file descriptor;
	int counter,aux,aux2,aux3;
	struct sockaddr_in serv_addr;//Server address data
	struct hostent *server;
	char buffer[256];//Data (bytes) to be receive from server
	int *eventNumber = NULL;
	int *eventSeats = NULL;
	char **eventName = NULL;
	char **eventLocation = NULL;
	char **eventDate = NULL;
	char **eventExpectedDuration = NULL;

	if(access("settings.txt", F_OK ) != -1 ) 
	{
	//File exists
		readSettings("settings.txt", serverip, &currentport);
	} 
	else 
	{
	//File doesn't exist
		currentport = 50000;
		strncpy(serverip,"127.0.0.1", 80);
	}
	//---presentation msg...
	while(1)
	{
		printf("\nSetEvent Client 2017");
		printf("\nby Filipe Conceição and João Barreiros (DEEC-UC)");
		printf("\nCurrent event server: %s",serverip);
		printf("\nCurrent port: %d",currentport);
		printf("\nMenu:");
		printf("\n0. Exit");
		printf("\n1. Set event server");
		printf("\n2. Set port (49152–65535)");
		printf("\n3. Get list of events");
		printf("\n4. Make registration");
		printf("\n5. Show registration list\n");
		printf("\nOption:");


		//Creates tcp socket (stream)
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0) 
			error("ERROR opening socket");
		//Creates tcp socket (stream)
		sockfd2 = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd2 < 0) 
			error("ERROR opening socket");
		sockfd3 = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd3 < 0) 
			error("ERROR opening socket");
		sockfd4 = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd4 < 0) 
			error("ERROR opening socket");

		server = gethostbyname(serverip);//Destination IP address of the server
		bzero((char *) &serv_addr, sizeof(serv_addr));//Clears serv_addr
		serv_addr.sin_family = AF_INET;
		bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
		serv_addr.sin_port = htons(currentport); ////Destination port of the servermust be in network format
		
		if(scanf("%d%c", &option, &term) != 2 || term != '\n')//Enquanto o utilizador não introduzir uma opção
		{
			while(getchar() != '\n');
			printf("\nerror: option must be an integer\n");
			sleep(1);
		}
		else
		{
			switch(option)
			{
				case 0:
					while(1)
					{
						printf("\nAre you sure you want to exit?(y/n)?\n");//Mensagem de confirmação de saída
						confirm = getchar();
						if(confirm == 'y')//Saída confirmada
						{
							printf("\nExiting...\n");
							exit(1);
						}
						else if(confirm =='n')//Saída abortada
						{
							break;
						}
						else//Espera por y/n
						{
							while(getchar() != '\n');
						}
					}
					break;
				case 1:
					printf("\nCurrent event server: %s",serverip);//Mostra o IP destino do servidor atual
					printf("\nSet new event server:");//Pede novo IP destino do servidor
					scanf("%s",serverip);
					printf("\nCurrent event server is now: %s",serverip);//Mostra o IP destino do servidor escolhido
					saveSettings("settings.txt", serverip, currentport);//Guarda o IP e o porto de destino do servidor no ficheiro
					break;
				case 2:
					printf("\nCurrent port number is: %d",currentport);//Mostra o porto de destino do servidor atual
					do
					{
						printf("\nSet event server:");//Pede novo porto destino do servidor
						scanf("%d",&currentport);
						if(currentport < 49152 || currentport > 65535)
						{
							printf("\nPlease select a port number between [49152;65535].");
						}
					}while(currentport < 49152 || currentport > 65535);
					printf("\nCurrent port number is now: %d",currentport);//Mostra o porto destino do servidor escolhido
					saveSettings("settings.txt", serverip, currentport);//Guarda o IP e o porto de destino do servidor no ficheiro
					break;
				case 3:
					if(loggedIn == 1)
					{
						counter = showEvents(sockfd,serv_addr,eventNumber,&eventSeats,eventName,eventLocation,eventDate,eventExpectedDuration);
					}
					else
					{
						printf("\nYou are not logged in");
					}
					printf("\n");
					sleep(1);
					break;
				case 4:
					if(loggedIn == 0)
					{
						//Connect to server
						if(connect(sockfd,(const struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
							error("ERROR connecting");
						if(write(sockfd,"4",2)<0)//Envia a opção 4 ao servidor
							error("ERROR writing to socket");
						printf("\nMake registration:");//Registo do cliente no servidor
						printf("\nUsername:");//Utilizador do cliente a enviar para o servidor
						scanf("%s",username);
						//Sends username to server
						if(write(sockfd,username,strlen(username))<0)
							error("ERROR writing to socket");
						printf("Password:");
						scanf("%s",password);
						//Sends password to server
						if(write(sockfd,password,strlen(password))<0)
							error("ERROR writing to socket");
						//Read server answer
						if(read(sockfd,buffer,255)<0)
							error("ERROR reading from socket");
						printf("%s\n\n",buffer);//Print answer
						if(read(sockfd,buffer,255) < 0)
							error("ERROR reading from socket");
						if(strcmp(buffer,"1") == 0)
							loggedIn = 1;
						else
							loggedIn = 0;
					}
					else	
					{
						printf("\nYou are already logged in");
					}

					if(loggedIn == 1)
					{
						printf("\nDo you want to register in any event?(y/n)?\n");//Mensagem de confirmação de saída
						while(1)
						{
							fflush(stdin);
							confirm = getchar();
							if(confirm == 'y')//Saída confirmada
							{
								counter = showEvents(sockfd2,serv_addr,eventNumber,&eventSeats,eventName,eventLocation,eventDate,eventExpectedDuration);
								printf("\n\nPlease enter the number of the event you wish to register:");
								fflush(stdin);
								scanf("%d",&aux3);
								if(aux3 > 0 && aux3 <= counter)
								{
									if(registrationOK(aux3,username,sockfd3,serv_addr))
									{
										printf("\nHow many seats do you wish to take:");
										fflush(stdin);
										scanf("%d",&seats);				
										if(eventSeats[aux3]-seats >= 0 && seats > 0)
										{	
											if(connect(sockfd4,(const struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
												error("ERROR connecting");
											seatsleft = (eventSeats[aux3]-seats);
											if(write(sockfd4,"7",2)<0)
												error("ERROR writing to socket");
											if(write(sockfd4,&seatsleft,sizeof(seatsleft)<0))
												error("ERROR writing to socket");

											printf("\nSuccessful Registration of %d in event %d\n",seats,aux3);
										}
										else
										{
											printf("\nNumber of seats reserved exceeds remaining ones");
										}
										
									}
									else
									{
										printf("\nAlready registred in event %d\n",aux3);
									}
									
								}
								else
								{
									printf("Invalid option\n");
								}
								break;
							}
							else if(confirm =='n')//Saída abortada
							{
								printf("\nconfirm = n");
								break;
							}
						}
					}
					fflush(stdout);
					sleep(2);
					break;
				case 5:
					//Connect to server
					if(connect(sockfd,(const struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
						error("ERROR connecting");
					if(read(sockfd,buffer,255)<0)
						error("ERROR reading from socket");
					printf("\nRegistration list:");		
					printf("%s\n",buffer);
					sleep(1);
					break;
				default :
				printf("\nInvalid option\n");
				sleep(1);
			}
		}            
	}
	return 0;
}