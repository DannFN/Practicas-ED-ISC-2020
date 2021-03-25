#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGHT 23

typedef struct queuenode {
	char data[MAX_LENGHT];
	struct queuenode *next;
} QueueNode;

void enqueue(char *, QueueNode **, QueueNode **, QueueNode **);
char *dequeue(QueueNode **, QueueNode**, QueueNode **);
char *head(QueueNode **);
char *tail(QueueNode **);
void show(QueueNode **);
void clear(QueueNode **, QueueNode**, QueueNode **);
char *delete(char *, QueueNode **);

int main() {
	QueueNode *qNode = NULL;
	QueueNode *qHead = NULL;
	QueueNode *qTail = NULL;

	int opt = 0;
	char val[MAX_LENGHT] = {'\0'};

	do {
		printf("1. Insertar en la fila.\n"
			"2. Extraer de la fila.\n"
			"3. Mostrar inicio de la fila.\n"
			"4. Mostrar fin de la fila.\n"
			"5. Mostrar fila.\n"
			"6. Eliminar elemento de la fila\n"
			"7. Vaciar fila.\n"
			"8. Salir.\n"
			"Opcion:\t");
		scanf("%d", &opt);

		switch(opt) {
			case 1:
				system("cls");
				printf("palabra a introducir: ");
				scanf("%s", &val);
				enqueue(val, &qNode, &qHead, &qTail);
				printf("Se inserto: '%s'.\n\n\n", val);

				break;
			case 2:
			system("cls");
			strcpy(val , dequeue(&qNode, &qHead, &qTail));
			printf("Se extrajo: '%s'.\n\n\n", val);

				break;
			case 3:
				system("cls");
				strcpy(val , head(&qHead));  
				printf("El inicio es: '%s'.\n\n\n", val);

				break;
			case 4:
				system("cls");
				strcpy(val , tail(&qTail));
				printf("El final es: '%s'.\n\n\n", val);

				break;
			case 5:
				system("cls");

				if(qNode != NULL)
					show(&qHead);
				else
					printf("Fila vacia.\n");
				printf("\n\n");

				break;
			case 6:
				system("cls");
				printf("palabra a eliminar: ");
				scanf("%s", &val);
				printf("Se elimino: '%s'.\n\n\n", delete(val, &qHead));

				break;  
			case 7:
				system("cls");

				if(qNode == NULL)
					printf("La fila ya esta vacia.\n");
				else {
					clear(&qNode, &qHead, &qTail);          
					if(qNode == NULL) 
						printf("Fila vaciada.\n");
					else
						printf("Error.\n");  
				}
				printf("\n\n");

				break;
			case 8:
				break; 
			default:
				system("cls");
				printf("Opcion no valida!\n\n");
				break;
		}
	}while(opt != 8);

	return 0;
}

void enqueue(char *newData, QueueNode **queue, QueueNode **head, QueueNode **tail) {
	QueueNode *newNode;
	newNode = (QueueNode *) malloc(sizeof(QueueNode));

	strcpy(newNode->data, newData);

	if(*head == NULL) {
		newNode->next = NULL;
		*queue = newNode;
		*head = *queue;
		*tail = *queue;
	}else {
		if(strcmp(newNode->data, (*head)->data) <= 0) {
			newNode->next = *head;
			*head = newNode;
		}else if(strcmp(newNode->data, (*tail)->data) >= 0) {
			newNode->next = NULL;
			(*queue)->next = newNode;
			*queue = newNode;
			*tail = *queue;
		}else {
			QueueNode *temp = *head;

			while(temp->next != NULL) {
				if((strcmp(newNode->data, temp->data) >= 0) && (strcmp(newNode->data, (temp->next)->data ) < 0)) {
					newNode->next = temp->next;
					temp->next = newNode; 
					break;
				}

				temp = temp->next;
			}
		}
	}
}

char *dequeue(QueueNode **queue, QueueNode **head, QueueNode **tail) {
	QueueNode *temp;
	char *data;
	
	if(*queue == NULL) {
		data = "\0";
	}else if(*head == *tail) {
		temp = *head;
		data = temp->data;
		*head = NULL;
		*queue = NULL;
		*tail = NULL;
	}else {
		temp = *head;
		data = temp->data;
		*head = temp->next;
	}

	return data;
}

char *head(QueueNode **head) {
	if(*head == NULL) {
		return "\0";
	}else {
		return (*head)->data;
	}
}

char *tail(QueueNode **tail) {
	if(*tail == NULL){
		return "\0";
	}else {
		return (*tail)->data;
	}
}

void show(QueueNode **head) {
	QueueNode *temp;
	temp = *head;

	while(temp != NULL) {
		printf("%s", temp->data);
		if(temp->next != NULL) 
			printf(" -> ");
		
		temp = temp->next;
	}
}

void clear(QueueNode **queue, QueueNode **head, QueueNode **tail) {
	while(1) {
		if(*head == *queue) {
			dequeue(queue, head, tail);
			break;	
		}

		dequeue(queue, head, tail);
	}
}

char *delete(char *string, QueueNode **head) {
	if(strcmp((*head)->data, string) == 0) {
		*head = (*head)->next;
		return string;
	}

	QueueNode *temp = *head;

	while((*head)->next != NULL) {
		if(strcmp(((*head)->next)->data, string) == 0) {
			(*head)->next = ((*head)->next)->next;
			break;
		}

		*head = (*head)->next;
	}

	*head = temp;

	return string;
}