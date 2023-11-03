#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>

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
  
  socklen_t clnt_addr_size; //declare your shit first!!!

  int serv_sock;
  
  
  
  /********create socket************/
  serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  
  /******setup server address structure****/
  ServerAddress.sin_family = AF_INET;  
  ServerAddress.sin_addr.s_addr = inet_addr("127.0.0.1");  
  ServerAddress.sin_port = htons(5566);
  
  //Bind.              typecast address ofServerAddress as sockaddr pointer
  bind(ServerSocket, (struct sockaddr*)&ServerAddress, sizeof(ServerAddress));
  
  listen(serv_sock, 20);  //listen for a TCP connection. (internet stylings)
  
  clnt_addr_size = sizeof(clnt_addr);  //zack style
  
  while(1)  {
  
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&ClientAddress, &clnt_addr_size);
    //hey guese what??? DISTRACTION!!!!!
  
