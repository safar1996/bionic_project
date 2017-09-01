#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define print(a) printf("%s",#a);
#define π 3.14

typedef enum
{  NUMBER,
   STRING,
   ARRAY,
   CONTAINER,
   FUNCTION,
   CLASS
}TYPE;


typedef struct
{  char name[30];
   TYPE type;
   union{
         int *number;
         char *string;
        }value;
   int constant:2;
}Type;



typedef struct
{   unsigned int start;
    unsigned int end;
    unsigned int position;
}Storage;

static Type Bio_Container[5000];
static Type Inter_Container[500];

static Storage Inter_Storage;
static Storage Bio_Storage;








int interactive_mode = 1;

void get_input(void);
int run_code(char code[]);
int bio_arithmatic(char code[250]);

int setVar(char name[], char value[]);





int *sorted(int list[], size_t size);
char *splitString(char *str, char delimeter);




int main(int argc, char *argv[])
{
    
    Bio_Storage.position = 1;
    setVar("safar", "cinta Anty");
    setVar("Anty", "cinta safar");
    
    
    
    char *str[10] = {"safoo",
                       "safar",
                       "anty",
                      };
    str[0] = "riri";
    //str = malloc(0);
    //char **ii = str;
    
    char aa[] = "mibil";
    char *ai = aa;

    str[0] = ai;
    ai++;
    printf("%s", str[0]);
    
    


    //char *rees = splitString("safar,allie okd cjfk, object,,jsjd,h,h,anty,riri",',');
    //printf("%s", rees[0]);
    
    struct Node{
         char msg[100];
         struct Node *next_node;
    };
     struct Node *node0;
     struct Node *node1;
     node1 = malloc(sizeof(struct Node));
     strcpy((*node1).msg, "safar");
     (*node1).next_node = node0;
      node0 = node1;

     strcpy(node1->msg, "riri");

    struct Node *cur_node;
    // cur_node = (*node0)->next_node;
    printf("\n%s", node1->msg);
    
   
    return 0;

}









void get_input(void){

    char code[] = "";
    char input;
    int cur = 1;
    
    int OK = 1;
    char STR[2] = "0";
    while (interactive_mode)
    {
        printf("\n> ");
        while (input != '\n')
        {
           
           input = getchar();
           printf("%c",input);
           if (input != '\n')
           {
                STR[0] = input;
                strcat(code, STR);
           }
           
        }
        
        run_code(code);
        strcpy(code,"");
        input = ' ';
    }


}



int run_code(char code[])
{
     
    // printf("%c ok!\n",code[0]);
     char literal[100][20] = {"NULL"};
     int cur_lit = 0;
     int length = strlen(code);
    // printf("length: %d\n",length);
     int c = 0;
     
     char buffer[100] = "";
     int cur_buff = 0;

     char STR[2] = "0";
    
     
     while (c < length)
     { 
       
        if (code[c] == ' ')
        {
             
             printf("Contain SPACE\n");
             strcpy(literal[cur_lit], buffer);
             printf("Buffer: %s\n",buffer);
             strcpy(buffer, "");
             ++cur_lit;
            
            
        }

        else if ( c == 0 && isdigit(code[c]) )
        { 
            bio_arithmatic(code);
            printf("\nArithmatic");
            
        }

        else if (isalpha(code[c]))
        {
            STR[0] = code[c];
            strcat(buffer, STR);
        }
        
        else if (isdigit(code[c]) && c > 0)
        {
            STR[0] = code[c];
            strcat(buffer, STR);
       
        }
        c++;

     }
    strcpy(literal[cur_lit], buffer);
    ++cur_lit;
    STR[0] = '\t';
    strcpy(literal[cur_lit], STR);
    c = 0;
    printf("cur_lit : %d\n", cur_lit);
    while (strcmp(literal[c], "\t")){
       printf("Literal[%d] = %s\n", c, literal[c]);
       c++;
    }
    
    return 0;
}


int bio_arithmatic(char code[])
{
     return 0;

}



int setVar(char name[], char value[])
{   int STATE;

    
    



    Type object;
    strcpy(object.name, name);
    object.type = STRING;
    if (object.type == STRING)
    {
        object.value.string = malloc(0);
        strcpy(object.value.string, value);
        Bio_Container[Bio_Storage.position] = object;
        ++Bio_Storage.position;
        STATE = 0;
    }
    printf("\n [+]New object created\n\tName: %s\n\tType: %i\n\tValue: %s\n",object.name, object.type, object.value.string);



    return STATE;
}
     

int checkVar(char name[])
{
   return 0;
}





char *splitString(char str[], char delimeter)
{  char cur;
   char *buff;
   buff = malloc(0);
   strcpy(buff, "");
   char *result[100];
   unsigned int n = 0, c = 0, r = 0;
   
   while (1)
   {  

      cur = str[n];
      
      
      
      if (cur != delimeter)
      {
         buff[c] = cur; ++c;
         
      }
       else
      {
         strcpy(buff,"");
         c = 0;
         ++r;
      }
      result[r] = buff;
      if (cur == '\0') break;
       
      ++n;
   }
   for (int n =0;n<=r;n++){
   printf("\n%s", result[n]);
   }
   return result;
}



int *sorted(int list[], size_t size){
     size_t n = 0;
     printf("\nsize :%i",size);
     int greater;
     int rec = 0;
     while (rec < size-1){
     while (n < size-1){
         if (list[n] > list[n+1]){
             greater = list[n];
             list[n] = list[n+1];
             list[n+1] = greater; }
     ++n;
     }
     n = 0; rec++;
     }
     return list;
}