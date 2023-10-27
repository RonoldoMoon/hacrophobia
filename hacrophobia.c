#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "acrophobia.h"

//blobib blops.

int fd;

char myChars[] = { 'A', 'B', 'C', 'D',
                   'E', 'F', 'G', 'H',
		   'I', 'J', 'K', 'L',
		   'M', 'N', 'O', 'P',
		   'Q', 'R', 'S', 'T',
		   'U', 'V', 'W', 'X',
		   'Y', 'Z'};

unsigned char RandChar()  {

  unsigned char x;

  read(fd , &x, 1);
  x = ( x % 26 );
  
  return myChars[x];
}

 
void welcome ()  {
 puts(thing);
  printf ("Welcome to the infancy stages of the game Retro Acrophobia!  Bringing back the fear of acronyms into your home\n");
  printf ("May the only board you feel be a game\n\n");
}

int main (int argc, char* pink[])  {

  int choice;

  fd = open("/dev/urandom",  O_RDONLY);
  

  
  if (argc < 2)  {
  
    welcome();
    
    
  
    printf("how many letters would you like: \n?");
    scanf("%d", &choice);
  }
  
  else { sscanf(pink[1], "%d", &choice); }
  
  
  while(choice)  {
  
    putchar(RandChar());
    choice--;
  }
  
  putchar(10);
  
  return 0;
}

