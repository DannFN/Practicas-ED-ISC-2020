#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 2
#define EXP_LIMIT 50

typedef struct stacknode {
	char data;
 	struct stacknode *last;
} StackNode;

typedef struct floatstacknode {
  float data;
  struct floatstacknode *last;
} FloatStackNode; 

void push(char, StackNode **, StackNode **);
char pop(StackNode **, StackNode **);
char peek(StackNode **);
void show(StackNode **);
void clear(StackNode **, StackNode **);
void overturn(StackNode **, StackNode **, StackNode **, StackNode **, char);

void pushFloat(float, FloatStackNode **, FloatStackNode **);
float popFloat(FloatStackNode **, FloatStackNode **);
void showFloat(FloatStackNode **);

int isOperator(char);
int isLeftPar(char);
int isRigthPar(char);
int isOperand(char);
int priority(char);
float evaluate(float, char, float);

int main() {
	StackNode *sNodes[SIZE] = { NULL };
  StackNode *topNodes[SIZE] = { NULL };
  FloatStackNode *sFloatNode = NULL;
  FloatStackNode *topFloatNode = NULL; 
  char str[EXP_LIMIT] = {'\0'};
  char prestr[EXP_LIMIT] = {'\0'};

  int opt = 0;
  int i = 0;
  int j = 0;
  float k = 0;
  float l = 0;
  char m = ' ';
  float n = 0;

  do {
  	printf("1. Convertir In-Fijo a Post-Fijo y Pre-Fijo.\n"
      "2. salir.\n"
      "Opcion:\t");
  	scanf("%d", &opt);

  	switch(opt) {
  		case 1:
  			system("cls");
  			printf("Ingrese la expresion a evaluar:\n\t");
  			scanf("%s", &str);

  			for (i = 0; i < EXP_LIMIT - 1; ++i) {
  				if(str[i] == '\0') {
  					overturn(&sNodes[0], &topNodes[0], &sNodes[1], &topNodes[1], '\0');
						break;
					}else if(isOperand(str[i])) {
  					push(str[i], &sNodes[1], &topNodes[1]);
  				}else {
  					if(peek(&topNodes[0]) == '\0') {
  						push(str[i], &sNodes[0], &topNodes[0]);
  					}else {
  						if(priority(str[i]) == priority(peek(&topNodes[0]))) {
  							push(pop(&sNodes[0], &topNodes[0]), &sNodes[1], &topNodes[1]);
  							push(str[i], &sNodes[0], &topNodes[0]);
  						}else if(priority(str[i]) > priority(peek(&topNodes[0]))) {
  							if(isRigthPar(str[i])) {
  								overturn(&sNodes[0], &topNodes[0], &sNodes[1], &topNodes[1], '(');
  								pop(&sNodes[0], &topNodes[0]);
  							}else {
  								push(str[i], &sNodes[0], &topNodes[0]);
  							}
  						}else if(priority(str[i]) < priority(peek(&topNodes[0]))) {
  							if(peek(&topNodes[0]) != '(') {
  								overturn(&sNodes[0], &topNodes[0], &sNodes[1], &topNodes[1], '\0');
  							}
  							push(str[i], &sNodes[0], &topNodes[0]);
  						}
  					}
  				}
  			}

  			overturn(&sNodes[1], &topNodes[1], &sNodes[0], &topNodes[0], '\0');
  			printf("La expresion en forma postfija es: \n \t");
  			show(&sNodes[0]);
  			printf("\n");

        while(peek(&topNodes[0]) != '\0') {
          if(isOperand(peek(&topNodes[0]))) {
            pushFloat((float)(pop(&sNodes[0], &topNodes[0]) - '0'), &sFloatNode, &topFloatNode);
          }else {
            l = popFloat(&sFloatNode, &topFloatNode);
            m = pop(&sNodes[0], &topNodes[0]);
            n = popFloat(&sFloatNode, &topFloatNode);
            pushFloat(evaluate(n, m, l), &sFloatNode, &topFloatNode);
          }
        }

        k = popFloat(&sFloatNode, &topFloatNode);

  			clear(&sNodes[0], &topNodes[0]);
  			clear(&sNodes[1], &topNodes[1]);

        for(j = 0; j < i + 1; ++j) {
          prestr[j] = str[i - j];
        }

				for(j = 0; j < i + 1; ++j){
          if(isOperand(prestr[j])) {
  					push(prestr[j], &sNodes[1], &topNodes[1]);
  				}else {
  					if(peek(&topNodes[0]) == '\0') {
  						push(prestr[j], &sNodes[0], &topNodes[0]);
  					}else {
  						if(priority(prestr[j]) == priority(peek(&topNodes[0]))) {
                if(isLeftPar(prestr[j])) {
                  overturn(&sNodes[0], &topNodes[0], &sNodes[1], &topNodes[1], ')');
                  pop(&sNodes[0], &topNodes[0]);
                }else {
                  push(prestr[j], &sNodes[0], &topNodes[0]);
                }
              }else if(priority(prestr[j]) > priority(peek(&topNodes[0]))) {
                if(isRigthPar(prestr[j])) {
                  push(prestr[j], &sNodes[0], &topNodes[0]);  
                }else if(isLeftPar(prestr[j])) {
                  overturn(&sNodes[0], &topNodes[0], &sNodes[1], &topNodes[1], ')');
                  pop(&sNodes[0], &topNodes[0]);
                }else {
                  push(prestr[j], &sNodes[0], &topNodes[0]);  
                }
              }else if(priority(prestr[j]) < priority(peek(&topNodes[0]))) {    
                if(isRigthPar(peek(&topNodes[0]))) {
                  push(prestr[j], &sNodes[0], &topNodes[0]);
                }else {
                  push(pop(&sNodes[0], &topNodes[0]), &sNodes[1], &topNodes[1]);
                  push(prestr[j], &sNodes[0], &topNodes[0]);
                }                
              }
  					}
  				} 	
				}
				overturn(&sNodes[0], &topNodes[0], &sNodes[1], &topNodes[1], '\0');
        printf("La expresion en forma prefija es:\n\t");
  			show(&sNodes[1]);
  			printf("\n"); 	

        printf("El resultado es:\n\t%.2f\n", k);

  			clear(&sNodes[0], &topNodes[0]);
  			clear(&sNodes[1], &topNodes[1]);
  			break;

  		case 2:
  			break;
  		
  		default:
  			system("cls");
        printf("Opcion no valida!\n\n");
  			break;
  	}
  }while(opt != 2);

	return 0;
}

void push(char d, StackNode **s, StackNode **top) {
 	StackNode *newNode;
  newNode = (StackNode *) malloc(sizeof(StackNode));
 	
  newNode->data = d;
	newNode->last = *s;
	*s = newNode;
	*top = *s;
}

char pop(StackNode **s, StackNode **top) {
  StackNode *temp;
  char d;
   
  if(*s == NULL) {
    return '\0';
  }else {
    temp = *s;
    d = temp->data;
    *s = temp->last;
    *top = *s;
    free(temp);

    return d;
  }
}

char peek(StackNode **top) {
  if(*top == NULL)
    return '\0';
  else
    return (*top)->data;
}

void show(StackNode **s) {
  StackNode *temp;
  temp = *s;

  while(temp != NULL) {
    printf("%c ", temp->data);
    temp = temp->last;
  }
}

void clear(StackNode **s, StackNode **top) {    
  if(peek(s) != '\0') {
    clear(&((*s)->last), top);
    pop(s, top);
  }
}

void overturn(StackNode **s1, StackNode **top1, StackNode **s2, StackNode **top2, char c) {
  while(peek(s1) != c) {
    push(pop(s1, top1), s2, top2);
  }
}

void pushFloat(float d, FloatStackNode **s, FloatStackNode **top) {
  FloatStackNode *newNode;
  newNode = (FloatStackNode *) malloc(sizeof(FloatStackNode));
  
  newNode->data = d;
  newNode->last = *s;
  *s = newNode;
  *top = *s;
}

float popFloat(FloatStackNode **s, FloatStackNode **top) {
  FloatStackNode *temp;
  float d;
   
  if(*s == NULL) {
    return -32768;
  }else {
    temp = *s;
    d = temp->data;
    *s = temp->last;
    *top = *s;
    free(temp);

    return d;
  }
}

void showFloat(FloatStackNode **s){
  FloatStackNode *temp;
  temp = *s;

  while(temp != NULL) {
    printf("%.2f ", temp->data);
    temp = temp->last;
  }
}

int isOperator(char c) {
	return(c == '+' || c == '-' || c == '/' || c == '*' || c == '^');
}

int isLeftPar(char c) {
	return(c == '(');
}

int isRigthPar(char c) {
	return(c == ')');
}

int isOperand(char c) {
	return(!isOperator(c) && !isLeftPar(c) && !isRigthPar(c));
}

int priority(char c) {
	switch(c) {
		case '(':
	  	return 4;
	  case ')':
	  	return 4;
	  case '^':
	  	return 3;
	  case '*':
	  	return 2;
  	case'/':
	  	return 2;
	  case '+':
	  	return 1;
  	case'-':
	  	return 1;
	}
}

float evaluate(float val1, char operator, float val2) {
  float r = 0;

  switch(operator) {
    case '^':
      r = (float) pow(val1, val2);
      break;
    case '*':
      r = val1 * val2;
      break;
    case'/':
      r = val1 / val2;
      break;
    case '+':
      r = val1 + val2;
      break;
    case'-':
      r = val1 - val2;
      break;
  }

  return r;
}
