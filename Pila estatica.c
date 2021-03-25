#include <stdio.h>
#include <stdlib.h>

#define NSTACKS 2
#define SSTACK 10

typedef struct pila{
   int data;
   int last;
}Stack;

Stack stacks[NSTACKS][SSTACK] = {{0}};
Stack newnode;
Stack emptynode;
int peeks[NSTACKS] = {0}; 
int v = 0;
int i = 0;

int isEmpty(int p);
int isFull(int p);
void push(int n, int p);
int pop(int p);
int peek(int p);
void show(int p);
void cls(int p);

int main() {

	int opc = 0;
	int val = 0;
	int nstack = 0;

	do {
		printf("\n1. Introducir Elemento.\n"
		"2. Sacar elemento.\n"
		"3. Mostrar tope.\n"
		"4. Mostrar pila.\n"
		"5. vaciar pila.\n"
		"6. Salir\n"
		"Opcion:\t");

		scanf("%d", &opc);

   	switch(opc) {
			case 1: {
				system("cls");
				printf("Valor a introducir:\t");
				scanf("%d", &val);
				printf("Pila en la que se introducira el valor (1/2):\t");
				scanf("%d", &nstack);               
				push(val, nstack);
				break;
    	}
			case 2: {
				system("cls");
				printf("Pila de la que se extraera el valor (1/2):\t");
				scanf("%d", &nstack);
				val = pop(nstack);
				if(val == -32768)
					printf("\nPila vacia");
				else
					printf("\nSe extrajo: %d", val);
				break;
			}
			case 3: {
				system("cls");
				printf("Pila de la que se consultara el valor (1/2):\t");
				scanf("%d", &nstack);
				printf("\nEl tope es: %d", peek(nstack));
				break;
			}
			case 4: {
				system("cls");
				printf("Pila a mostrar (1/2):\t");
				scanf("%d", &nstack);
				show(nstack);
				break;
			}
			case 5: {
				system("cls");
				printf("Pila a vaciar (1/2):\t");
				scanf("%d", &nstack);
				cls(nstack);
				printf("Pila vacia\n");
				break;
			}
			case 6: {
				system("exit");
				break;
			}
			default: {
				system("cls");
				printf("Opcion no valida!");
				break;
			}
		}
	}while(opc != 6);
	return 0;
}

int isEmpty(int p) {
	return peeks[p - 1] == 0;
}

int isFull(int p) {
	return peeks[p - 1] == SSTACK;		
}

void push(int n, int p) {
	if(!isFull(p)) {
		newnode.data = n;
		newnode.last = peeks[p - 1] - 1; 
		stacks[p - 1][peeks[p - 1]] = newnode;
		peeks[p - 1] ++;
	}else{
		printf("Pila llena\n");
	}
}

int pop(int p) {
	v = (isEmpty(p)) ? -32768 : stacks[p - 1][peeks[p - 1] - 1].data;
	stacks[p - 1][peeks[p - 1] - 1] = emptynode;
	peeks[p - 1] --;
 	return v;
}

int peek(int p) {
	return stacks[p - 1][peeks[p - 1] - 1].data;
}

void show(int p) {
	if(!isEmpty(p)) for(i = peeks[p - 1] - 1; i >= 0; i--) printf("\n%d", stacks[p - 1][i].data);
}

void cls(int p) {
	for (i = peeks[p - 1] - 1; i >= 0; i--) stacks[p - 1][i] = emptynode;
	peeks[p - 1] = 0; 
}