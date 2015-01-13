#include <stdio.h>

void __attribute__((constructor)) init(void)
{
  printf("Chamado antes de main().\n");
}

void __attribute__((destructor)) destroy(void)
{
  printf("Chamado depois de main().\n");
}

int main(int argc, char *argv[])
{
  printf("Hello!\n");
}
