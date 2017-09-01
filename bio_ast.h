#include <string.h>
#include <ctype.h>
#include "bio_lexer.h"
#include "bio_core.h"

void raiseError(int errnum, char file[25], int lines, char *code);

char * _filename;
int _line;




int assignObject(struct Token *code){
    struct Token *Lvalue;
    struct Token *Assign;
    struct Token *Rvalue;

    if (code->type == OBJECT && (code->next->type == ASSIGNMENT || code->next->type == POST_ARITHMATIC) && (code->next->next->type == NUMBER || code->next->next->type == OBJECT)){
       // if (!checkVarname(code->value)){;
       Lvalue = code;
       
       if (code->next->next->type == NUMBER){
          Rvalue = code->next->next;
          if (createVar(Lvalue->value, Rvalue->value, INTEGER, LOCAL, FALSE)) {
               char msg[100];
               strcpy(msg, Rvalue->value);
               strcat(msg, " to ");
               strcat(msg, Lvalue->value);
               raiseError(4, _filename, _line, msg);
          }
       }
    }



return 0;
}





int printObject(struct Token *code){
    //printf("\nwill print.. %s", code->value);
    int found = 0;
    char output[100];
    for (int n = 0;n < STORAGE_PTR;n++){
        if (!strcmp(STORAGE_VAR[n]->name, code->value)){
           found = 1;
           //puts("found");
           if (STORAGE_VAR[n]->type == INTEGER){
              printf("\n%lli\n", STORAGE_VAR[n]->int_value);
              //sprintf(output, "%i", STORAGE_VAR[STORAGE_PTR]->int_value);
           }
        }

    }
    return found;
}


void evalStatement(struct Token *code, int interpreted, char *filename, int line){
     int count = 0;
     _filename = filename;
     _line = line;
     while (1){
          
          if (code->type == OBJECT && code->next != NULL && (code->next->type == ASSIGNMENT || code->next->type == POST_ARITHMATIC)) assignObject(code);
          
          if (interpreted){
              //printf("\n%i", count);
              if (code->next == NULL && count <2) printObject(code);

          }

           if (code->next == NULL) break;
           code = code->next;
           ++count;
     }
     
     
}
