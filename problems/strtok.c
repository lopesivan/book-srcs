#include <stdio.h> 
#include <string.h> 

/* Isto é um ponteiro para uma constante! */
char *s = "Hello, world!"; 

int main(int argc, char *argv[]) 
{ 
  char *p; 

  p = strtok(s, ", ");   /* Ocorrerá um 'segmentation fault' aqui! */ 
  while (p != NULL) 
  { 
    printf("%s\n", p); 
    p = strtok(NULL, ", "); 
  } 

  return 0; 
} 
