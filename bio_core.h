#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int IN_LOOP = 0;


typedef enum {STRING, INTEGER, FLOAT, ARRAY, DICT, FUNCTION, CLASS, DATA} TYPE;
typedef enum {FALSE, TRUE} CONSTANT;
typedef enum {LOCAL, GLOBAL} SCOPE;


struct Var
{
   char *name;
   long long int int_value;
   float float_value;
   char *string_value;
   char *data_value;
   char *byte_value;
   void *pointer;
   TYPE type;
   SCOPE scope;
   CONSTANT is_constant;

}*STORAGE_VAR[2000];

static unsigned int STORAGE_PTR = 0;




int createVar(char *name, char *value, TYPE type, SCOPE scope, CONSTANT is_constant) //Create new variable
{   unsigned short int size_name = sizeof(name) / sizeof(char);
    //Check var name;
    //puts(name);
    //puts(value);
    //printf("\n%i size", size_name);
    if (size_name > 40) return 1;
    /*
    for (int n = 0; n < size_name; n++)
    {   if (!isalpha(name[0]) && name[0] != '_') printf("\ninvalid var name!");
        if (n > 0){
           if (!isalnum(name[n])) printf("\ninvalid varname.");
        }
    }*/

    //Create template:
    struct Var *new_var;
    new_var = malloc(sizeof(struct Var));
   
    //Declare var name:
    new_var->name = malloc(50);
    new_var->name = name;

    //Determinan type of var:
    if (type == INTEGER)
       {   long long int nvalue;
           //new_var->int_value = malloc(sizeof(int));
           sscanf(value, "%lli", &nvalue);
           new_var->int_value = nvalue;
           //printf("\n%i", new_var->int_value);
           //printf("\n value: %i", nvalue);
       }
    else if (type == FLOAT)
       {   float nvalue;
           // new_var->float_value = malloc(sizeof(float));
           sscanf(value, "%f", &nvalue);
           new_var->float_value = nvalue;
       }
    else if (type == STRING)
       {    new_var->string_value = malloc(0);
            new_var->string_value = value;
       }
    else
       {   return 1;
       }
    
    //Assigning attribute of var
    new_var->type = type;
    new_var->scope = scope;
    new_var->is_constant = is_constant;

    //Save var to memory
    STORAGE_VAR[STORAGE_PTR] = new_var;
    
    //Increament memory pointer
    ++STORAGE_PTR;

    //Done
    return 0;
}






struct Node
{
   void *value;
   struct Node *next;
}*STACK = NULL;


int pushStack(void *new_value)
{
   struct Node *newNode;
   newNode = malloc(sizeof(struct Node));
   newNode->value = malloc(0);
   newNode->value = new_value;
   newNode->next = STACK;
   STACK = newNode;
   
   return 0;
}

void *popStack()
{
   void *value;
   if (STACK != NULL) value = STACK->value;
   else return NULL;
   
   struct Node *buff;
   buff = STACK->next;
   free(STACK);
   STACK = buff;

   return value;
}

void clearStack()
{  
   while(popStack() != NULL){}
}





