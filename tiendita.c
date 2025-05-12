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
    Product* carrito;
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
        printf("No se encontró la lista");
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

// Menú
void showMenu(){
    printf("     Bienvenido al menú     \n");
    printf(" Selecciona una opción de acuerdo a lo que desees hacer:\n ");
    printf("1.- Ver mi carrito de compras.\n ");
    printf("2.- Ver mi información de usuario.\n ");
    printf("3.- Ver la lista de productos.\n ");
    printf("4.- Salir.\n ");
}

int main (){
    showMenu();

    Product* productos = loadProducts("products.txt");
    showProducts(productos);



    return 0;
}