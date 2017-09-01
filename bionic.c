#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "bio_ast.h"

#define VERSION "Bionic 0.1 Beta"

char * FILENAME;

void raiseError(int errnum, char file[25], int lines, char *code);
void interpreted(void);

void ctrlcHandler(int signum)
{   
    if (IN_LOOP) IN_LOOP = 0;
    else {
          printf("\nInterrupt Bionic\n");
          exit(1);
         }
}

void interpreted(void)
{   signal(SIGINT, ctrlcHandler);
    char code[200];
    int lines = 0;
    char *state[MAX_STATEMENT];
    int length;
    struct Token *token;
    char buffer[2];
    buffer[1] = '\0';
    int scopes = 0;
    int done = 1;
    while (1){
             printf("\n> ");
             while (true){

               buffer[0] = getchar();

               if (buffer[0] == '(' || buffer[0] == '[' || buffer[0] == '{'){
                  pushStack(buffer[0]);
                  ++scopes;
                }
                else{
                    switch (buffer[0]){
                      case ')':
                          if (popStack() == '(') --scopes;
                          else raiseError(3, FILENAME, lines, buffer);
                          break;
                      case ']':
                           if (popStack() == '[') --scopes;
                           else raiseError(3, FILENAME, lines, buffer);
                           break;
                      case '}':
                           if (popStack() == '{') --scopes;
                           else raiseError(3, FILENAME, lines, buffer);
                           break;
                     }
                }

               strcat(code, buffer);
               if (buffer[0] == '\n'){
                   ++lines;
                   if (scopes == 0){
                      length = splitStatement(state, code);
                      token = parseStatement(state, length, FILENAME, lines);
                      evalStatement(token, 1, FILENAME, lines);
                      lines = 0;
                      strcpy(code, "");
                      break;
                   }
               }
            }

    }
   

}

int displayHeader(void)
{   printf("\n%s\nType help() for more information.\n",VERSION);
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc == 1){
       FILENAME = "<stdin>";
       displayHeader();
       interpreted();
    }
    else if (argc > 1){
       FILENAME = argv[1];
    }


    return 0;

}
   
