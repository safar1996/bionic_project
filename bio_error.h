/*Error reference*/

#include <stdio.h>


const char ERROR[][25] = {"invalid syntax", "invalid variable name", "missing separator",
                          "invalid scope indent", "can't assign value"};


/*
typedef struct{
       char * msg;
       char * code;
       int * linenum;
       char * file;
       char * pos;
       int * errnum;
}Error;
*/


void raiseError(int errnum, char file[25], int lines, char *code){
       

        char *msg;
        if (errnum < 50) msg = ERROR[errnum];
        else msg = " ";

        printf("\nerrno %i, %s in %s line %i:\n  %s\n  ^\n",
          (int)errnum, msg, file, lines, code);

        exit(errnum);
}


