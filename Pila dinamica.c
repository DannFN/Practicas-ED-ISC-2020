#include <stdio.h>
#include <stdlib.h>

#define SIZE 2

typedef struct stacknode {
	int data;
 	struct stacknode *last;
} StackNode;

void push(int, StackNode **, StackNode **);
int pop(StackNode **, StackNode **);
int peek(StackNode **);
void show(StackNode **);
void clear(StackNode **, StackNode **);
void overturn(StackNode **, StackNode **, StackNode **, StackNode **);

int main() {
  StackNode *sNodes[SIZE] = { NULL };
  StackNode *topNodes[SIZE] = { NULL };

	int opt = 0, val = 0, stack = 0; 

	do {
   	printf("1. Introducir Elemento.\n"
      "2. Sacar elemento.\n"
      "3. Mostrar tope.\n"
      "4. Mostrar pila.\n"
      "5. Vaciar pila.\n"
      "6. volcar pila.\n"
      "7. Salir.\n"
      "Opcion:\t");
    scanf("%d", &opt);

   	switch(opt) {
    	case 1:
        system("cls");
        printf("Valor a introducir: ");
        scanf("%d", &val);
        printf("pila en la que se introducira el valor (1/2): ");
        scanf("%d", &stack);
        push(val, &sNodes[stack - 1], &topNodes[stack - 1]);
        if(peek(&sNodes[stack - 1]) == val)
          printf("Se inserto: %d.\n", val);
        else
          printf("Error.\n");
        printf("\n\n");

       	break;
    	case 2:
       	system("cls");
       	printf("pila de la que se extraera el valor (1/2): ");
       	scanf("%d", &stack);
        val = pop(&sNodes[stack - 1], &topNodes[stack - 1]);
       	if(val != -32768) 
          printf("Se extrajo: %d\n", val);
        else
          printf("Pila vacia.\n"); 	
        printf("\n\n");

       	break;
    	case 3:
        system("cls");
        printf("pila de la que se mostrara el tope (1/2): ");
        scanf("%d", &stack);
        val = peek(&topNodes[stack - 1]);
        if(val != -32768)
          printf("El tope es: %d\n", val);
        else
          printf("%Pila vacia.\n");
        printf("\n\n");

        break;
    	case 4:
       	system("cls");
        printf("pila a mostrar (1/2): ");
        scanf("%d", &stack);
        if (topNodes[stack - 1] != NULL)
          show(&sNodes[stack - 1]);
        else
          printf("%Pila vacia.\n");
        printf("\n\n");

        break;
    	case 5:
        system("cls");
        printf("pila a vaciar (1/2): ");
        scanf("%d", &stack);
        if(topNodes[stack - 1] == NULL)
          printf("La pila ya esta vacia.\n");
        else {
          clear(&sNodes[stack - 1], &topNodes[stack - 1]);
          if(topNodes[stack - 1] == NULL) 
            printf("Pila vaciada.\n");
          else
            printf("Error.\n");  
        }
        printf("\n\n");

        break;
      case 6:
        system("cls");
        printf("pila a volcar (1/2): ");
        scanf("%d", &stack);
        if(topNodes[stack - 1] == NULL) 
          printf("No se puede volcar una pila vacia.\n");
        else {
          overturn(&sNodes[(stack == 1) ? 0 : 1], &topNodes[(stack == 1) ? 0 : 1], &sNodes[(stack == 1) ? 1 : 0], &topNodes[(stack == 1) ? 1 : 0]);
          
          if(topNodes[stack - 1] == NULL) 
            printf("Pila volcada.\n");
          else 
            printf("Error.\n");
        }
        printf("\n\n");

        break;
     	case 7:
     		break; 
      default:
        system("cls");
        printf("Opcion no valida!\n\n");
        break;
    }
	}while(opt != 7);

	return 0;
}

void push(int d, StackNode **s, StackNode **top) {
 	StackNode *newNode;
  newNode = (StackNode *) malloc(sizeof(StackNode));
 	
  newNode->data = d;
	newNode->last = *s;
	*s = newNode;
	*top = *s;
}

int pop(StackNode **s, StackNode **top) {
  StackNode *temp;
  int d;
   
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

int peek(StackNode **top) {
  if(*top == NULL)
    return -32768;
  else
    return (*top)->data;
}

void show(StackNode **s) {
  StackNode *temp;
  temp = *s;

  while(temp != NULL) {
    printf("%d\n", temp->data);
    temp = temp->last;
  }
}


void clear(StackNode **s, StackNode **top) {    
  if(peek(s) != -32768) {
    clear(&((*s)->last), top);
    pop(s, top);
  }
}

void overturn(StackNode **s1, StackNode **top1, StackNode **s2, StackNode **top2) {
  while(peek(s1) != -32768) {
    push(pop(s1, top1), s2, top2);
  }
}