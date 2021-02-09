#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#define EVENTS_FILE "events.txt"
#define MAX 2500
#define USERS_FILE "users.txt"
bool acceptNewRegists;
//===================================================================
// error messages: print message and terminate program
void error(char *msg) 
{
    perror(msg);
    exit(1);
}
//===================================================================
char *hash(char *username, char *password)
{
  int i;
  unsigned int key = 0;
  for (i=0;i < strlen(username);i++)
        key=(key+3)*username[i];
  srand(key);
  for(i=0;i<strlen(password);i++)
  {
    password[i]^=rand()%10;
  }
  return password;
}
//===================================================================
void writeToFile(char *username, char *password)
{
  FILE *fich;
  fich = fopen(USERS_FILE, "a");//Opens file
  if(fich == NULL)
  {
    error("ERROR opening file");
  }
  fprintf(fich,"%s %s\n",username,password);
  fclose(fich);
}
//===================================================================
bool registrationOK(char* usr,int event_no)
{
    char filename[80], aux[255];
    sprintf(filename,"%d.txt",event_no);
    FILE *fich;
    if(access(filename, F_OK ) != -1 )
    {
        //File exists
        fich = fopen(filename, "r");//Abre o ficheiro
        while(1)
        {
          fscanf(fich, "%s",aux);
          if(feof(fich))
            break;
          if(strcmp(usr,aux) == 0)
            return 0;
        }
    }
    return 1;
}
//===================================================================
void addRegistration(char* usr, int event_no)
{
  char filename[80], aux[255];
  sprintf(filename,"%d.txt",event_no);
  FILE *fich;
  fich = fopen(filename, "a");//Opens file
  if(fich == NULL)
  {
    error("ERROR opening file");
  }
  fprintf(fich,"%s\n",usr);
  fclose(fich);
}
//===================================================================
void sendevents(int sock)
{
  FILE *fich;
  fich = fopen(EVENTS_FILE, "r");//Opens file
  if(fich == NULL)
  {
    error("ERROR opening file");
  }
  int eventNumber[MAX];
  int eventSeats[MAX];
  char eventName[MAX][255];
  char eventLocation[MAX][255];
  char eventDate[MAX][255];
  char eventExpectedDuration[MAX][255];
  //char buff[20];
  int aux,n,j,i=0;
  while(1)
  {
    fscanf(fich, "%d %s %s %s %s %d",&eventNumber[i],eventName[i],eventLocation[i],eventDate[i],eventExpectedDuration[i],&eventSeats[i]);//Every event is read from the file
    if(feof(fich))
      break;
    i++;//Counts the number of events
  }
  //sprintf(buff, "%d", i);
  aux = htonl(i);
  n = write(sock,&aux,sizeof(aux));//Informs client the size of list of events
  if (n < 0) 
    error("ERROR writing to socket");
  for(j=0;j<i;j++)//Show the current event offered by the server
  {
    eventNumber[j] = htonl(eventNumber[j]);
    n = write(sock,&eventNumber[j],sizeof(eventNumber[j]));
    if (n < 0) 
      error("ERROR writing to socket");
    n = write(sock,eventName[j],255);
    if (n < 0) 
      error("ERROR writing to socket");
    n = write(sock,eventLocation[j],255);
    if (n < 0) 
      error("ERROR writing to socket");
    n = write(sock,eventDate[j],255);
    if (n < 0) 
      error("ERROR writing to socket");
    n = write(sock,eventExpectedDuration[j],255);
    if (n < 0) 
      error("ERROR writing to socket");
    eventSeats[j] = htonl(eventSeats[j]);
    n = write(sock,&eventSeats[j],sizeof(eventSeats[j]));
    if (n < 0) 
      error("ERROR writing to socket");
  }
  fclose(fich);
}
//===================================================================
bool login(char *username, char *password, int sock)
{
  FILE *fich;
  char user[255],pass[255];
  password = hash(username,password);
  if(access(USERS_FILE, F_OK) == -1 && acceptNewRegists == 1) 
  {
    writeToFile(username,password);
    if (write(sock,"Successful Registration",255) < 0) 
      error("ERROR writing to socket");
    return 1;
  } 
  else if(access(USERS_FILE, F_OK) == -1 && acceptNewRegists == 0)
  {
    if (write(sock,"Server is not accepting new regists",255) < 0) 
      error("ERROR writing to socket");
    return 0;
  }
  fich = fopen(USERS_FILE, "r");//Opens file
  if(fich == NULL)
  {
    error("ERROR opening file");
  }
  bool flaguser = 0;
  while(1)
  {
    fscanf(fich, "%s %s",user,pass);
    if(feof(fich))
      break;
    if(strcmp(user,username) == 0)
    {
      flaguser = 1;
      if(strcmp(pass,password) == 0)
      {
        if (write(sock,"Successful Login",255) < 0) 
          error("ERROR writing to socket");
        fclose(fich);
        return 1;
      }
    }
  }
  fclose(fich);
  if(flaguser == 1)
  {
    if (write(sock,"Password doesn't match with username",255) < 0) 
      error("ERROR writing to socket");
    return 0;
  }
  else if(acceptNewRegists == 1)
  {
    writeToFile(username,password);
    if (write(sock,"Successful Registration",255) < 0) 
      error("ERROR writing to socket");
    return 1;
  }
  else
  {
    if (write(sock,"Server is not accepting new regists",255) < 0) 
      error("ERROR writing to socket");
    return 0;
  }
}
//===================================================================
void events(int sock) 
{
  int n,event_no,seatsleft;
  char buffer[256], username[256], password[256], usr[256];
  bzero(buffer,256);
  n = read(sock,buffer,255);
  if (n < 0) 
    error("ERROR reading from socket");
  printf("\n%s",buffer);

  switch(atoi(buffer))
  {
    case 3:
      sendevents(sock);
      break;
    case 4:
      n = read(sock,username,255);
      if (n < 0) 
        error("ERROR reading from socket");
      n = read(sock,password,255);
      if (n < 0) 
        error("ERROR reading from socket"); 
      if(login(username,password,sock) == 1)
      {
        printf("\nLogin com sucesso!");
        if(write(sock,"1",255) < 0)
          error("ERROR writing to socket");
      }
      else
      {
        printf("\nLogin sem sucesso!");
        if(write(sock,"0",255) < 0)
          error("ERROR writing to socket");
      }
      break;
    case 5:
      if(write(sock,"I got your message 5",255)<0)
        error("ERROR writing to socket");
      break;
    case 6://checks if registration in an event is ok
      
      if(read(sock,&event_no,sizeof(event_no))<0)
        error("ERROR reading from socket");
      if(read(sock,usr,255)<0)
         error("ERROR reading from socket");
      event_no = ntohl(event_no);;
      if(registrationOK(usr,event_no) == 1)
      {
        if(write(sock,"1",255) < 0)
          error("ERROR writing to socket");
      }
      else
      {
        if(write(sock,"0",255) < 0)
          error("ERROR writing to socket");
      }
      break;
      case 7:
        fflush(stdin);
        if(read(sock,buffer,sizeof(int))<0)
          error("ERROR reading from socket");
        seatsleft= atoi(buffer);
        //seatsleft = ntohl(seatsleft);
        printf("\nseatsleft=%d",seatsleft);

    default:
      break;
  }
  //Sends message to client
}
//===================================================================

int main(int argc, char *argv[]) 
{
    //---check command parameters...
    if (argc < 3 || (atoi(argv[2]) != 0 && atoi(argv[2]) != 1 ))
    {
       fprintf(stderr,"ERROR, invalid number of arguments provided\n");
         fprintf(stderr,"Usage %s (int)portno (bool)AcceptNewRegists\n",argv[0]);
         exit(1);
     }

    int sockfd, newsockfd, portno, pid;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;  //server addresses data
    //---presentation msg...
    printf("\n\n\nProgram for TCP sockets\n\n\n");

    //---creates tcp welcome socket (stream)...
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
      error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     acceptNewRegists = atoi(argv[2]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
      error("ERROR on binding");

  //---waits for clients
     listen(sockfd,5); 
     clilen = sizeof(cli_addr);

  //---forever cicle for clients
     while (1) 
     {
      //---accepts a new client
         newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0) error("ERROR on accept");
         pid = fork();
         if (pid < 0)
          error("ERROR on fork");
         if (pid == 0) 
         {  // child (new) process to attend client
             close(sockfd); // sockfd belongs to father process
             events(newsockfd);
             exit(0);
         } 
         else // parent (old) process that keeps wainting for clients
             close(newsockfd); // newsockfd belongs to child process
     } //while
     return 0; /* we never get here */
}