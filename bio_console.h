#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#define VERSION "Bionic 0.1 Beta"


void getInput(void);

void ctrlcHandler(int signum)
{   char choose;
    printf("\nAre you sure want to exit ? (y/n) ");
    choose = getchar();
    if (choose == 'y') exit(0);
    else getInput();
}

void interpreted(void)
{   signal(SIGINT, ctrlcHandler);
    char code[200];
    while (true)
          {  printf("\n> ");
             while (true)
               {  char ch = getchar();
                  if (ch == '\n') break;
                  

                  

               }
             
          }
   // return "OK";

}

int displayConsole(void)
{   printf("\n%s\nType help() for more information.\n",VERSION);
    return 1;
}
    