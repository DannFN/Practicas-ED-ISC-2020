#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <conio.h>
#include <string.h>
#include <math.h>

#define MAX_HEIGHT 1000
#define LOCAL_INFINITY (1 << 20)

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
} TreeNode;

typedef struct asciinode_struct {
    struct asciinode_struct *left;
    struct asciinode_struct *right;
    int edge_length; 
    int height;     
    int lablen;
    int parent_dir;   
    char label[11];  
} asciinode;

int count_nodes(TreeNode *);
void show_tree(int, TreeNode *);
void preorder(TreeNode *);
void inorder(TreeNode *);
void postorder(TreeNode *);
int search(TreeNode *, int);
int min(TreeNode *);
int max(TreeNode *);

TreeNode *put(TreeNode *, int);
TreeNode *order(TreeNode *, TreeNode *);
TreeNode *delete(TreeNode *, int);

// Adicionales de la practica
void show_ordered_tree(TreeNode *); // Dann
int count_leaves(TreeNode *); //Emilio
int depth(TreeNode *); //Emilio
int tree_type(TreeNode *); //Xenia (Ya está)

// funciones para imprimir el arbol bonito OwO
int PMIN(int, int);
int PMAX(int, int);
asciinode *build_ascii_tree_recursive(TreeNode *);
asciinode *build_ascii_tree(TreeNode *);
void free_ascii_tree(asciinode *);
void compute_lprofile(asciinode *, int, int);
void compute_rprofile(asciinode *, int, int);
void compute_edge_lengths(asciinode *);
void print_level(asciinode *, int, int);
void print_ascii_tree(TreeNode *);

// Contar nodos del arbol
int count_nodes(TreeNode *root) {
	if(root == NULL)
		return 0;
	else
		return (count_nodes(root->left) + 1 + count_nodes(root->right));
}

// Mostrar el arbol siguiendo el algoritmo BFS
void show_tree(int level, TreeNode *root) {
	int i;

	if(root != NULL) {
		show_tree(level + 1, root->right); 
		printf("\n");
		
		for(i = 0; i < level; ++i) 
			printf(" "); 

		printf("%d", root->data);
		show_tree(level + 1, root->left);
	}
}

// Recorrido Preorden
void preorder(TreeNode *root){
	if(root != NULL) {
		printf("%d - ", root->data); 
		preorder(root->left); 
		preorder(root->right); 
	}
}

// Recorrido Inorden
void inorder(TreeNode *root) {
	if(root != NULL) {
		inorder(root->left); 
		printf("%d - ", root->data); 
		inorder(root->right); 
	}
}

// Recorrido Postorden
void postorder(TreeNode *root) {
	if(root != NULL) {
		postorder(root->left); 
		postorder(root->right); 
		printf("%d - ", root->data);
	}
}

// Buscar nodo dentro del arbol
int search(TreeNode *root, int data) {
	if(root == NULL) 
		return(-32768);
	if(data == root->data) 
		return(1);
	if(data < root->data) 
		return(search(root->left, data)); 
	else 
		return(search(root->right, data));
}

// Buscar el elemento mas pequeño
int min(TreeNode *root) {
	if(root == NULL) 
		return(-32768);
	else if(root->left == NULL) 
		return(root->data); 
	else 
		return(min(root->left));
}

// Buscar el elemento mas grande
int max(TreeNode *root) {
	if(root == NULL) 
		return(-32768);
	else if(root->right == NULL) 
		return(root->data); 
	else 
		return(max(root->right));
}

// Insertar un nuevo elemento 
TreeNode *put(TreeNode *root, int data) {
	if(root == NULL) {
		TreeNode *root = (TreeNode *) malloc(sizeof(TreeNode));
		root->data = data;
		root->left = NULL; 
		root->right = NULL; 
		return(root);
	}

	if(data < root->data) 
		root->left = put(root->left, data); 
	else 
		root->right = put(root->right, data);

	return(root);
}

// Ordena el árbol en el proceso de eliminación
TreeNode *order(TreeNode *root, TreeNode *pivot) {
	TreeNode *tmp;
	if(pivot->right != NULL) 
		pivot->right = order(root , pivot->right); 
	else {
		tmp = pivot;
		root->data = pivot->data; 
		pivot = pivot->left; 
		free(tmp);
	}

	return(pivot);
}

// Buscar y eliminar un elemento del arbol
TreeNode *delete(TreeNode *root, int data) {
	TreeNode *tmp;
	if(root == NULL) 
		printf("\n\tArbol Vacio..."); 
	else if(data < root->data)
		root -> left = delete(root->left, data); 
	else if(data > root->data)
		root->right = delete(root->right, data); 
	else {
		tmp = root;

		if(tmp->right == NULL) {
			root = tmp->left; 
			free(tmp);
		}else if(tmp->left == NULL) { 
			root = tmp->right;
			free(tmp);
		}else 
			tmp->left = order(tmp, tmp->left); 
	}

	return(root);
}

// Mostrar arbol ordenado
void show_ordered_tree(TreeNode *root) {
	print_ascii_tree(root);
}

// Contar el numero de hojas
int count_leaves(TreeNode *root) {
	if(root == NULL)
		return 0;

	if(root->left == NULL && root->right == NULL)
		return 1;
	else
		return (count_leaves(root->left) + count_leaves(root->right));
}

// Determinar profundidad
int depth(TreeNode *root) {
	if(root == NULL)
		return 0;

	int depthLeft = 1, depthRight = 1; //empieza a contar desde el nivel 2 en donde se encuentran los primero hijos

	if(root->right != NULL || root->left != NULL){
		if(root->left != NULL)
			depthLeft = 1 + depth(root->left);
		if(root->right != NULL)
			depthRight = 1 + depth(root->right);

		if(depthLeft >= depthRight)
			return depthLeft;
		else
			return depthRight;
	}

	return 0;
}

// Determinar tipo de arbol 
int tree_type(TreeNode *root) {
	// Segun yo, esto deberia de funcionar, usando las formulas que Alacantara puso en la presentación xd, si no funciona me dicen
	int n = count_nodes(root), h = count_leaves(root), d = depth(root);

	if(n == (2 * h) - 1) {
        if(n == pow(2, d) - 1)
			return 1; /*printf("\nEs un Arbol Estrictamente binario.");*/
        
		return 2; /*printf("\nEs un Arbol Binario completo.");*/
	}else 
        return 0; /*printf("\nEs un Arbol Simplemente Binario.")*/
}

/*************************************** No tocar lo que hay dentro de este bloque *********************/
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];

int gap = 3;  
int print_next;    

int PMIN(int x, int y) {
  return (x < y) ? x : y;
}

int PMAX(int x, int y) {
  return (x > y) ? x : y;
}

asciinode *build_ascii_tree_recursive(TreeNode *root) {
  asciinode *node;
  
  if (root == NULL) return NULL;

  node = malloc(sizeof(asciinode));
  node->left = build_ascii_tree_recursive(root->left);
  node->right = build_ascii_tree_recursive(root->right);
  
  if(node->left != NULL)
    node->left->parent_dir = -1;

  if(node->right != NULL)
    node->right->parent_dir = 1;

  sprintf(node->label, "%d", root->data);
  node->lablen = strlen(node->label);

  return node;
}

asciinode *build_ascii_tree(TreeNode *root) {
  asciinode *node;
  
  if (root == NULL) return NULL;
  
  node = build_ascii_tree_recursive(root);
  node->parent_dir = 0;
  
  return node;
}

void free_ascii_tree(asciinode *node) {
  if (node == NULL) return;
  
  free_ascii_tree(node->left);
  free_ascii_tree(node->right);
  free(node);
}

void compute_lprofile(asciinode *node, int x, int y)  {
  int i, isleft;
  
  if (node == NULL) return;

  isleft = (node->parent_dir == -1);
  lprofile[y] = PMIN(lprofile[y], x - ((node->lablen - isleft) / 2));
  
  if(node->left != NULL) {
    for(i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
	    lprofile[y + i] = PMIN(lprofile[y + i], x - i);
  }

  compute_lprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
  compute_lprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

void compute_rprofile(asciinode *node, int x, int y) {
  int i, notleft;
  
  if(node == NULL) return;

  notleft = (node->parent_dir != -1);
  rprofile[y] = PMAX(rprofile[y], x + ((node->lablen - notleft) / 2));
  
  if(node->right != NULL) {
	for(i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
	    rprofile[y + i] = PMAX(rprofile[y + i], x + i);
  }

  compute_rprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
  compute_rprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

void compute_edge_lengths(asciinode *node) {
  int h, hmin, i, delta;
  
  if(node == NULL) return;
  
  compute_edge_lengths(node->left);
  compute_edge_lengths(node->right);

  if(node->right == NULL && node->left == NULL)
	  node->edge_length = 0;
  else {
    if(node->left != NULL) {
        for(i = 0; i < node->left->height && i < MAX_HEIGHT; i++)
		  rprofile[i] = -LOCAL_INFINITY;

	    compute_rprofile(node->left, 0, 0);
	    hmin = node->left->height;
    }else
	    hmin = 0;
    
    if (node->right != NULL) {
	    for(i = 0; i < node->right->height && i < MAX_HEIGHT; i++)
		    lprofile[i] = LOCAL_INFINITY;

	    compute_lprofile(node->right, 0, 0);
	    hmin = PMIN(node->right->height, hmin);
    }else
	    hmin = 0;
	  
    delta = 4;
	
    for(i = 0; i < hmin; i++)
	    delta = PMAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
	  
	if(((node->left != NULL && node->left->height == 1) || (node->right != NULL && node->right->height == 1)) && delta > 4)
      delta--;
	    
    node->edge_length = ((delta + 1) / 2) - 1;
  }

  h = 1;
  
  if(node->left != NULL)
	  h = PMAX(node->left->height + node->edge_length + 1, h);
  
  if(node->right != NULL)
	  h = PMAX(node->right->height + node->edge_length + 1, h);

  node->height = h;
}

void print_level(asciinode *node, int x, int level) {
  int i, isleft;
  
  if (node == NULL) return;
  
  isleft = (node->parent_dir == -1);
  
  if(level == 0) {
	for (i = 0; i < (x - print_next - ((node->lablen - isleft) / 2)); i++)
	    printf(" ");

    print_next += i;
    printf("%s", node->label);
    print_next += node->lablen;
  }else if(node->edge_length >= level) {
    if(node->left != NULL) {
        for(i = 0; i < (x - print_next - (level)); i++)
		    printf(" ");

	    print_next += i;
	    printf("/");
	    print_next++;
    }

	if(node->right != NULL) {
	   for (i = 0;  i< (x - print_next + level); i++)
		    printf(" ");

	    print_next += i;
	    printf("\\");
	    print_next++;
    }
  }else {
    print_level(node->left, x - node->edge_length - 1, level - node->edge_length - 1);
    print_level(node->right, x + node->edge_length + 1, level - node->edge_length - 1);
  }
}

void print_ascii_tree(TreeNode *root) {
    asciinode *proot;
    int xmin, i;

    if(root == NULL) return;

    proot = build_ascii_tree(root);
    compute_edge_lengths(proot);

    for(i = 0; i < proot->height && i < MAX_HEIGHT; i++)
        lprofile[i] = LOCAL_INFINITY;

    compute_lprofile(proot, 0, 0);
    xmin = 0;

    for(i = 0; i < proot->height && i < MAX_HEIGHT; i++)
        xmin = PMIN(xmin, lprofile[i]);

    for (i = 0; i < proot->height; i++) {
        print_next = 0;
        print_level(proot, -xmin, i);
        printf("\n");
    }

    if (proot->height >= MAX_HEIGHT)
        printf("(Este arbol tiene una profundidad mayos a %d, y puede que no se dibuje correctamente.)\n", MAX_HEIGHT);

    free_ascii_tree(proot); 
}

/******************************************************************************************************/

void main(void) {
	int n = 0, i = 0, data = 0, op = 0;
	
	TreeNode *tree = NULL; 

	do {
		system("cls");
		printf("\nOperaciones Basicas con un Arbol Binario\n" 
		" 1. Llenar un arbol de forma aleatoria\n"
		" 2. Llenar un arbol de forma manual\n" 
		" 3. Consultar la existencia de un dato en el arbol\n"
		" 4. Suprimir un dato del arbol\n" 
		" 5. Buscar los elementos minimo y maximo dentro del arbol\n" 
		" 6. Consultar la cantidad de nodos del arbol\n" 
		" 7. Ver recorridos DFS\n" 
		" 8. Ver arbol BFS\n"
		" 9. Ver arbol bonito\n"
		"10. Consultar la cantidad de hojas del arbol\n"
		"11. Consultar la profundidad del arbol\n"
		"12. Consultar el tipo de arbol\n"
		"13. Salir\n"
		"\nIngresa una Opcion: ");
		scanf("%d", &op);
		
		switch(op) {
			case 1: 
				printf("\nNumero de nodos del arbol: "); 
				scanf("%d", &n);
				srand(time(0));
				
				for(i = 0; i < n; ++i) {
					printf("\n\tElemento No. %d: ", i + 1); 
					data = (rand() % (1001)); 
					printf("Dato a insertar: %d", data);
					tree = put(tree, data);
				}

				printf("\n\npresiona cualquier tecla para continuar");
				getch();
				break;

			case 2: 
				printf("\nNumero de nodos del arbol: ");
				scanf("%d", &n);

				for(i = 0; i < n; ++i) {
					printf("\tElemento No. %d: ", i + 1); 
					scanf("%d", &data);
					tree = put(tree, data);
				}

				printf("\n\npresiona cualquier tecla para continuar");
				getch();
				break;

            case 3:
            	printf("\nDato a buscar : "); 
            	scanf("%d", &data);  
            	
				if(search(tree, data) != -32768)
            		printf("\n\tSe encontro el dato %d \n\n", data); 
            	else 
            		printf("\n\tNo se encontro el dato %d", data); 

				printf("\n\npresiona cualquier tecla para continuar");
				getch();
            	break;

        	case 4:
        		printf("\nDato a Suprimir: ");
        		scanf("%d", &data); 
        		delete(tree, data); 

				if (search(tree, data) != -32768)
					printf("\n\tNo se encontro el dato %d, ya fue borrado, u ocurrio un error durante el proceso", data);
				
				printf("\n\npresiona cualquier tecla para continuar");
				getch();
        		break;

            case 5:
            	printf("\n\tMinimo = %d", min(tree)); 
            	printf("\n\tMaximo = %d", max(tree)); 

				printf("\n\npresiona cualquier tecla para continuar");
				getch();
            	break;

            case 6: 
            	printf("\n\tHay %d nodos en el arbol", count_nodes(tree)); 

				printf("\n\npresiona cualquier tecla para continuar");
				getch();
            	break;

        	case 7: 
        		printf("\nRecorrido en Pre-Orden:\n"); 
        		preorder(tree);
        		printf("\nRecorrido En Orden:\n"); 
        		inorder(tree);
        		printf("\nRecorrido en Post-Orden:\n"); 
        		postorder(tree);

				printf("\n\npresiona cualquier tecla para continuar");
				getch();
        		break;

			case 8:
				printf("\nArbol Binario");
				show_tree(0, tree);

				printf("\n\npresiona cualquier tecla para continuar");
				getch();
				break;

			case 9:
				printf("\nArbol Binario\n\n");
				show_ordered_tree(tree);

				printf("\n\npresiona cualquier tecla para continuar");
				getch();
				break;
			
			case 10:
				printf("\n\tHay %d hojas en el arbol", count_leaves(tree)); 

				printf("\n\npresiona cualquier tecla para continuar");
				getch();
				break;

			case 11:
				printf("\n\tEl arbol tiene una profundidad de %d niveles (siendo la raiz el nivel 0)", depth(tree)); 

				printf("\n\npresiona cualquier tecla para continuar");
				getch();
				break;
			
			case 12:
				switch(tree_type(tree)) {
					case 0:
						printf("\n\tEl arbol es de tipo binario");
						break;
					
					case 1:
						printf("\n\tEl arbol es de tipo binario estricto");
						break;

					case 2:
						printf("\n\tEl arbol es de tipo binario completo");
						break;
				}

				printf("\n\npresiona cualquier tecla para continuar");
				getch();
				break;

            case 13:
                exit(1);
                break; 

			default:
				printf("\nOpcion no valida");
				
				printf("\n\npresiona cualquier tecla para continuar");
				getch();
				break;
        }
    }while(op != 13);
}				