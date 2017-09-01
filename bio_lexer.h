#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "bio_error.h"
#define MAX_STATEMENT (1024) // 1 KiloByte



typedef enum {INVALID, ARITHMATIC, POST_ARITHMATIC, ASSIGNMENT, DELIMETER,
              LOGICAL, BITWISE, REDIRECT, DIRECTION,
              SCOPES, PARENTHESS, KEYWORD, NUMBER, STR, OBJECT} TOKEN;


const char _logical[][4] = {"==", "<", ">", ">=", "<=", "and", "or"};
const char _arithmatic[][4] = {"%", "+", "-", "/", "*", "**", "//"};
const char _post_arithmatic[][4] = {"+=", "-=", "/=", "*=", "%=", "//="};
const char _assignment[][4] = {"=", ":"};
const char _redirect[][4] = {">>>", "<<<"};
const char _direction[][4] = {"->", "::"};
const char _bitwise[][4] = {">>", "<<"};
const char _delimeter[][4] = {";", ",", "."};
const char _scope[][4] = {"{", "}"};
const char _parenthess[][4] = {"(", ")"};
const char _keyword[][10] = {"function", "class",
                               "lambda", "type", "if",
                               "for","while","else","toggle",
                               "const", "del", "false", "true",
                               "null","not","is","import","export"
                               };
const unsigned short s_logical = sizeof(_logical)/4,
                   s_arithmatic = sizeof(_arithmatic)/4,
                   s_assignment = sizeof(_assignment)/4,
                   s_redirect = sizeof(_redirect)/4,
                   s_direction = sizeof(_direction)/4,
                   s_bitwise = sizeof(_bitwise)/4,
                   s_delimeter = sizeof(_delimeter)/4,
                   s_scope = sizeof(_scope)/4,
                   s_parenthess = sizeof(_parenthess)/4,
                   s_keyword = sizeof(_keyword)/10,
                   s_post_arithmatic = sizeof(_post_arithmatic)/4;
unsigned short c;

struct Token{ char * value;
                 TOKEN type;
                 struct Token * next; };


TOKEN checkToken(char * token)
{   
    for (c = 0; c < s_assignment;c++){
        if (!strcmp(token, _assignment[c])) return ASSIGNMENT;
    }
    for (c = 0; c < s_post_arithmatic; c++){
        if (!strcmp(token, _post_arithmatic[c])) return POST_ARITHMATIC;
    }
    for (c = 0;c < s_arithmatic;c++){
        if (!strcmp(token, _arithmatic[c])) return ARITHMATIC;
    }
    for (c = 0;c < s_logical;c++){
        if (!strcmp(token, _logical[c])) return LOGICAL;
    }
    for (c = 0;c < s_redirect;c++){
        if (!strcmp(token, _redirect[c])) return REDIRECT;
    }
    for (c = 0;c < s_direction;c++){
        if (!strcmp(token, _direction[c])) return DIRECTION;
    }
    for (c = 0;c < s_bitwise;c++){
        if (!strcmp(token, _bitwise[c])) return BITWISE;
    }
    for (c = 0;c < s_delimeter;c++){
        if (!strcmp(token, _delimeter[c])) return DELIMETER;
    }
    for (c = 0;c < s_keyword;c++){
        if (!strcmp(token, _keyword[c])) return KEYWORD;
    }
    for (c = 0; c < s_parenthess;c++){
        if (!strcmp(token, _parenthess[c])) return PARENTHESS;
    }
    for (c = 0; c < s_scope;c++){
        if (!strcmp(token, _scope[c])) return SCOPES;
    }

    if (!strcmp(token, "\"") || !strcmp(token, "'")) return STR;
    
    int n = 0, okay = 0;
    while (1){
          if (token[n] == '\0'){
             if (n == okay){puts("number"); return NUMBER;}
             break;
          }
          if (isdigit(token[n])) ++okay;
          ++n;
    }

    n = 0;
    okay = 0;
    while (1){
          if (token[n] == '\0'){
              if ( okay == n ) {puts("object");return OBJECT;}
              break;
          }
          if (isdigit(token[0])) return INVALID;
          if (isalnum(token[n]) || isdigit(token[n]) || token[n] == '_') ++okay;
          ++n;
   }
    
   return INVALID;
}

struct Token * parseStatement(char * statement[], unsigned short length, char * filename, unsigned int line)
{    struct Token * first = (struct Token *) malloc(sizeof(struct Token));
     struct Token * curr = (struct Token *) malloc(sizeof(struct Token));
     first->value = statement[0];
     first->type = checkToken(statement[0]);
     if (first->type == INVALID) raiseError(0, filename, line, statement[0]);
     first->next = NULL;
     


     if (length > 1){
        for (int n = 1;n < length;n++){
            curr = first;
            while (curr->next != NULL) curr = curr->next; //goto end of node

            struct Token * token = (struct Token *) malloc(sizeof(struct Token));
            token->value = statement[n];
            //printf("\nstatement[%i] = %s", n, statement[n]);
            token->type = checkToken(statement[n]);
            if (token->type == INVALID) raiseError(0, filename, line, statement[n]);
            curr->next = token;
            curr->next->next = NULL;
         }
     }
     return first; //return first token
}



int splitStatement(char *code[], char input[])
{    int length = 0;
     while (input[length] != '\0') ++length;
     // printf("\n%i last is:%c.",last, input[last-1]);
     --length;
     while (input[length] == ' ') {
            input[length] = '\0';
          // puts("found");
            --length;
     }
     char * word;
     word = malloc(0);
     char * token;
     token = malloc(0);
    // puts(input);
     unsigned short cur_code = 0,
                    cur_word = 0,
                    cur = 0,
                    cur_token = 0;

     while (1){
      //  printf("%i: %c\n",(int)cur, input[cur]);
        if (isalnum(input[cur]) || input[cur] == '_' || input[cur] == '@' || input[cur] == '$' || input[cur] == '.'){
            if (cur_token > 0){
                code[cur_code] = malloc(0);
                strcpy(code[cur_code],token);
                strcpy(token,"");
                cur_token = 0;
                ++cur_code;
            }
            word[cur_word] = input[cur];
          //  puts("puts input[cur] --> word[cur_word]");
            ++cur_word;
            word[cur_word] = '\0';
        }
        else{
            if (input[cur] == ' ' || input[cur] == '\t' || input[cur] == '\n') {
                if (cur_word > 0){
                   code[cur_code] = malloc(0);
                   strcpy(code[cur_code], word);
                   strcpy(word, "");
                   cur_word = 0;
                   ++cur_code;
                }
                if (cur_token > 0){
                   code[cur_code] = malloc(0);
                   strcpy(code[cur_code], token);
                   strcpy(token, "");
                   cur_token = 0;
                   ++cur_code;
                 
                }
                

            }else{
                 if (input[cur] == '\0'){
                    if (cur_word > 0){
                       code[cur_code] = malloc(0);
                       strcpy(code[cur_code], word);
                    }
                    else if (cur_token > 0){
                        code[cur_code] = malloc(0);
                        strcpy(code[cur_code], token);
                    }
                    break;
                 }

                 if (cur_word > 0){
                    code[cur_code] = malloc(0);
                    strcpy(code[cur_code], word);
                    strcpy(word, "");
                    cur_word = 0;
                    ++cur_code;
                 }
                
                 
                 token[cur_token] = input[cur];
                 ++cur_token;
                 token[cur_token] = '\0';
                    
                 
                 
           }
     }
     ++cur;    
     }

return cur_code;
}

     