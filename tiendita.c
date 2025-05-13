#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Lista ligada
typedef struct Product{
    char nameProduct[50];
    float unitCost;
    struct Product* siguiente;
} Product;

typedef struct User{
    char name[100];
    char phoneNumber[10];
    float totalPayment;
    Product* carrito; // Puntero al primer producto de la lista 
} User;

// Carga de productos desde archivo .txt
Product* loadProducts(const char* file){
    FILE* f= fopen(file, "r");
    if ( f == NULL){
        printf("Error al abrir el archivo.\n");
        return NULL;
    }

    // Cada línea del archivo (hasta 149 caracteres) será un nodo Product
    Product* head = NULL;
    Product* current = NULL;

    char line[150];
    while (fgets(line, sizeof(line), f)){

            Product* new = (Product*)malloc(sizeof(Product));
            sscanf(line, "%[^,],%f", new->nameProduct, &new->unitCost);
            new->siguiente= NULL;
            
            //Creación y asignación de nodos
            if (head == NULL ){
                head = new;
                current = new;
            } else {
                current->siguiente = new;
                current = new;
            }
    }
    fclose(f);
    return head;
}

// Para probar que se carga la lista
void showProducts(Product* head){
    Product* current= head;
    int i=1;

    if(current == NULL){
        printf("No se encontró la lista.\n");
        return;
    }

    while(current!=NULL){
        printf("Producto %d:\n", i);
        printf("Nombre %s\n", current->nameProduct);
        printf(" Costo: %.2f\n\n", current->unitCost);
        current = current->siguiente;
        i++;

    }
}

// Agregar al carrito del usuario creando copias de los nodos seleccionados
void addToCart(User* user, Product* current){
    Product* copy = (Product*)malloc(sizeof(Product));
    if(copy == NULL){
        printf("Error al asignar memoria.\n");
        return;
    }

    strcpy(copy->nameProduct, current->nameProduct);
    copy->unitCost = current->unitCost;
    copy->siguiente = NULL;

    // Insertar al INICIO del carrito
    //copy->siguiente = user->carrito;
    //user->carrito = copy;

    // Insertar al final del carrito, manera tradicional
    if (user->carrito == NULL) {
        user->carrito = copy;
    } else {
        Product* current = user->carrito;
        while (current->siguiente != NULL){
            current = current->siguiente;
        }
            current->siguiente = copy;
    }

   user->totalPayment += copy->unitCost;
    printf("Producto agregado: %s ($%.2f)\n", copy->nameProduct, copy->unitCost);

}

// Navegar por la lista de productos
void navegarProductos(Product* head, User* usuario) {
    Product* actual = head;
    char opcion;

    while (1) {
        printf("\nProducto actual: %s ($%.2f)\n", actual->nameProduct, actual->unitCost);
        printf("[S]iguiente | [A]nterior | [C]omprar | [Q]uit\n");
        scanf(" %c", &opcion);

        switch (opcion) {
            case 'S':
            case 's':
                if (actual->siguiente != NULL) {
                    actual = actual->siguiente;
                } else {
                    printf("Estás en el último producto.\n");
                }
                break;
            case 'A':
            case 'a':
                if (actual == head) {
                    printf("Estás en el primer producto. No puedes retroceder más.\n");
                } else {
                    Product* temp = head;
                    while (temp->siguiente != actual) {
                        temp = temp->siguiente;
                    }
                    actual = temp;
                }
                break;
            case 'C':
            case 'c':
                addToCart(usuario, actual);
                printf("Producto agregado al carrito.\n");
                break;
            case 'Q':
            case 'q':
                return;
            default:
                printf("Opción no válida.\n");
        }
    }
}


// Menú
void showMenu(){
    printf("     Bienvenido al menú     \n");
    printf(" Selecciona una opción de acuerdo a lo que desees hacer:\n ");
    printf("1.- Ver mi carrito de compras.\n ");
    printf("2.- Ver mi información de usuario.\n ");
    printf("3.- Ver la lista de productos.\n ");
    printf("4.- Ver catálogo para selección de productos.\n ");
    printf("5.- Salir.\n ");
    printf("Opción: ");

}

int main (){

    Product* productos = loadProducts("products.txt");

    if (productos == NULL) {
        printf("No se pudieron cargar los productos. Saliendo.\n");
        return 1;
    }
    
    User usuario;
    strcpy(usuario.name, "Giselle");
    strcpy(usuario.phoneNumber, "5512437689");
    usuario.totalPayment = 0;
    usuario.carrito = NULL;

    int option;
    while(1) {
        showMenu();
        scanf("%d", &option);

        switch(option){
            case 1:
                printf("Carrito de compras: \n");
                showProducts(usuario.carrito);
                printf("Total a pagar: $%.2f\n",usuario.totalPayment);
            break;
            case 2:
                printf("Información de usuario:\n");
                printf("Nombre: %s\n", usuario.name);
                printf("Teléfono: %s\n", usuario.phoneNumber);
                printf("Total a pagar: $%.2f\n",usuario.totalPayment);
                printf("___________________________________\n");
            break;
            case 3:
                printf("Visualización del catálogo completo de productos: \n");
                showProducts(productos);
            break;
            case 4:
                printf("Lista de productos disponibles a selección:\n\n");
                navegarProductos(productos, &usuario);
            break;
            case 5:
                printf("\nGracias por tu compra, %s.\nTotal a pagar: $%.2f\n\n", usuario.name, usuario.totalPayment);
                return 0;
            default: 
                printf("Opción inválida.\n");
        }
    }

    return 0;
}