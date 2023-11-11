#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>


#define buffersize 1024
#define HOST       "*.durp.org"

/*Globals*/
int   pid;
char* miscBuff;

void Notice(int fd)  {

  send(fd, ":*.durp.org NOTICE * :Doing\r\n",    29, 0); 
  send(fd, ":*.durp.org NOTICE * :some\r\n",     28, 0); 
  send(fd, ":*.durp.org NOTICE * :stuff...\r\n", 32, 0); 
}

void StuffList(int fd)  {

  send(fd, ":*.durp.org CAP * LS :account-notify\r\n", 38, 0);  //needs bigger list.
}

void parseNick(char* p)  {

  sscanf(p, "NICK %s", miscBuff);
}

void parseUser(char* p)  {

  sprintf(miscBuff, "boink\n");  //place holder.
}

void ThisThing(char* p)  {

  switch(p[0])  {
  
    case   'C': { printf("%d: that other moment %s\n", pid, "cap ls");               break; }
    case   'N': { parseNick(p); printf("%d: nick moment       %s\n", pid, miscBuff); break; }
    case   'U': { parseUser(p); printf("%d: user moment       %s\n", pid, miscBuff); break; }
    default   : { break; }
  }
}



void SomeFunction(int signo)  {

  int stat;

  printf("Signal handler\nfor number: %d\n", signo);
  
  waitpid(0, &stat, WNOHANG);
  printf("\nStatus: %d\n", stat);
  
  return;
}

int main()  {

  struct timeval MyTimeout;
  MyTimeout.tv_sec  = 5;
  MyTimeout.tv_usec = 0;
  
  struct sockaddr_in ClientAddress;
  struct sockaddr_in ServerAddress;
  
  socklen_t clnt_addr_size;

  int ServerSocket;
  int ClientSocket;
  
  miscBuff = malloc(1024);  //hmmm...
  
  int i = 0;
  
  /********create socket************/
  ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  
  /******setup server address structure****/
  ServerAddress.sin_family = AF_INET;  
  ServerAddress.sin_addr.s_addr = inet_addr("127.0.0.1");  
  ServerAddress.sin_port = htons(6667);
  
  //Bind.
  bind(ServerSocket, (struct sockaddr*)&ServerAddress, sizeof(ServerAddress));
  
  listen(ServerSocket, 20);  //listen for a TCP connection. (internet stylings)
  
  clnt_addr_size = sizeof(ClientAddress);  //zack style
  
  while(1)  {
  
    ClientSocket = accept(ServerSocket, (struct sockaddr*)&ClientAddress, &clnt_addr_size);
    
    if( setsockopt (ClientSocket, SOL_SOCKET, SO_RCVTIMEO,
                   (char *)&MyTimeout, sizeof(MyTimeout)) < 0 )  {
		   
      perror("setsockopt");
    }
    if( setsockopt (ClientSocket, SOL_SOCKET, SO_SNDTIMEO,
                   (char *)&MyTimeout, sizeof(MyTimeout)) < 0 )  {
		   
      perror("setsockopt");
    }

    if ( (pid = fork()) == -1) {
    
      printf( "ERROR pid\n" );
    } 
    
    else if (pid == 0)  {  //child process.
    
      printf("Child process reporting: %d\n", getpid());
    
    /*start some jazz - preamble*/  
      Notice(ClientSocket);
      char* buffer = (char*)calloc(buffersize, sizeof(char));
      recv(ClientSocket, buffer, buffersize, 0);  //generally equivalent to read(2)
      ThisThing(buffer);
      StuffList(ClientSocket);   
      
      //memset(buffer, 0, buffersize);  //use same buffer.
      //sprintf(buffer, );
      send(ClientSocket, "PING bloople\r\n", 14, 0); 

      memset(buffer, 0, buffersize);
      recv(ClientSocket, buffer, buffersize, 0);    
      printf("%s", buffer);
      
      while(1)  {
      
        //memset(buffer, 0, buffersize);
        //sprintf(buffer, );
        send(ClientSocket, "PING *.durp.org\r\n", 17, 0);     
         
	memset(buffer, 0, buffersize);
	recv(ClientSocket, buffer, buffersize, 0);
	printf("%dresponce: %s", i++, buffer);
	
	sleep(60);
      }
      
      close(ClientSocket);
      close(ServerSocket);
      
      return 0;
    }
    
    else  {
    
      close(ClientSocket);
    }
  }
  
  close(ServerSocket);
  
  return 0;
}
