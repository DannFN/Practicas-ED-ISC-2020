#include <stdio.h>
#include <stdlib.h>

typedef struct queuenode {
	int data;
 	struct queuenode *next;
} QueueNode;

void enqueue(int, QueueNode **, QueueNode **);
int dequeue(QueueNode **, QueueNode**);
int head(QueueNode **);
int last_inserted_node(QueueNode **);
void show(QueueNode **);
void clear(QueueNode **, QueueNode**);

int main() {
	QueueNode *qNode = NULL;
	QueueNode *qHead = NULL;

	int opt = 0, val = 0; 

	do {
   	printf("1. Insertar en la fila.\n"
      "2. Extraer de la fila.\n"
      "3. Mostrar inicio.\n"
      "4. Mostrar fila.\n"
      "5. Vaciar fila.\n"
      "6. Salir.\n"
      "Opcion:\t");
    scanf("%d", &opt);

   	switch(opt) {
    	case 1:
        system("cls");
        printf("Valor a introducir: ");
        scanf("%d", &val);
        enqueue(val, &qNode, &qHead);

        /*
         * printf("breakpoint\n");
				 */

        if(last_inserted_node(&qNode) == val)
          printf("Se inserto: %d.\n", val);
        else
          printf("Error.\n");
        printf("\n\n");

       	break;
    	case 2:
       	system("cls");
        val = dequeue(&qNode, &qHead);
       	
       	if(val != -32768) 
          printf("Se extrajo: %d\n", val);
        else
          printf("Fila vacia.\n"); 	
        printf("\n\n");

       	break;
    	case 3:
        system("cls");
        val = head(&qHead);
        
        if(val != -32768)
          printf("El inicio es: %d\n", val);
        else
          printf("Fila vacia.\n");
        printf("\n\n");

        break;
    	case 4:
        system("cls");

        if(qNode != NULL)
          show(&qHead);
        else
          printf("Fila vacia.\n");
        printf("\n\n");

        break;
      case 5:
        system("cls");

        if(qNode == NULL)
          printf("La fila ya esta vacia.\n");
        else {
          clear(&qNode, &qHead);          
          if(qNode == NULL) 
            printf("Fila vaciada.\n");
          else
            printf("Error.\n");  
        }
        printf("\n\n");

        break;
     	case 6:
     		break; 
      default:
        system("cls");
        printf("Opcion no valida!\n\n");
        break;
    }
	}while(opt != 6);

	return 0;
}

void enqueue(int data, QueueNode **queue, QueueNode **head) {
	QueueNode *newNode;
	newNode = (QueueNode *) malloc(sizeof(QueueNode));

	newNode->data = data;

	if(*head == NULL) {
		newNode->next = newNode;
		*queue = newNode;
		*head = *queue;
	}else {
		newNode->next = *head;
		(*queue)->next = newNode;
		*queue = newNode;
	}
}

int dequeue(QueueNode **queue, QueueNode **head) {
	QueueNode *temp;
	int data;
	
	if(*queue == NULL) {
		data = -32768;
	}else if(*head == *queue) {
		temp = *head;
		data = temp->data;
		*head = NULL;
		*queue = NULL;
	}else {
		temp = *head;
		data = temp->data;
		*head = temp->next;
		(*queue)->next = *head;
	}

	return data;
}

int head(QueueNode **head) {
	if(*head == NULL) {
		return -32768;
	}else {
		return (*head)->data;
	}
}

int last_inserted_node(QueueNode **queue) {
	if(*queue == NULL){
		return -32768;
	}else {
		return (*queue)->data;
	}
}

void show(QueueNode **head) {
	QueueNode *temp;
	temp = *head;

	while(1) {
		if(temp->next == *head){
			printf("%d -> %d ->... ", temp->data, (temp->next)->data);			
    	break;
		}

		printf("%d -> ", temp->data);
    temp = temp->next;	
	}
}

void clear(QueueNode **queue, QueueNode **head) {
	while(1) {
		if(*head == *queue) {
			dequeue(queue, head);
			break;	
		}

    dequeue(queue, head);
  }
}
