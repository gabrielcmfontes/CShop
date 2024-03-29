#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct product {
    char name[50];
    float cost;
    float price;
    int stock;
};

void menu() {
    printf("==== Welcome to the shop ==== \n");
    printf("1 - Add Product \n");
    printf("2 - Show Products \n");
    printf("3 - Remove Product \n");
    printf("4 - Update Product \n");
    printf("5 - Buy Product \n");
    printf("6 - Sell Product \n");
    printf("7 - Show Profit \n");
    printf("s - Exit \n");
    printf("============================= \n");
    printf("Choose an option: \n");
};

void addProduct(struct product *products, int *quantity) {
    printf("Enter product name: \n");
    scanf("%s", products[*quantity].name);
    printf("Enter the cost of the product: \n");
    scanf("%f", &products[*quantity].cost);
    printf("Enter the product price: \n");
    scanf("%f", &products[*quantity].price);
    printf("Enter product stock: \n");
    scanf("%i", &products[*quantity].stock);

    (*quantity)++;
}

void printProducts(struct product *products, int quantity) {
    for(int i = 0; i < quantity; i++) {
        printf("Name: %s\n", products[i].name);
        printf("Cost: $%.2f\n", products[i].cost);
        printf("Price: $%.2f\n", products[i].price);
        printf("Stock: %i\n", products[i].stock);
        printf("\n");
    }
    system("pause");
}

void deleteProduct(struct product *products, int *quantity, const char *name) {
    int found = 0;
    for (int i = 0; i < *quantity; ++i) {
        if (strcmp(products[i].name, name) == 0) {
            for (int j = i; j < *quantity - 1; j++) {
                products[j] = products[j + 1];
            }
            (*quantity)--;
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Product not found.\n");
    }
}

void updateProduct(struct product *products, int *quantity, const char *name) {
    int found = 0;
    for (int i = 0; i < *quantity; ++i) {
        if (strcmp(products[i].name, name) == 0) {
            printf("Enter the new cost of the product: \n");
            scanf("%f", &products[i].cost);
            printf("Enter the new product price: \n");
            scanf("%f", &products[i].price);
            printf("Enter new product stock: \n");
            scanf("%i", &products[i].stock);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Product not found.\n");
    }
}

void buyProduct(struct product *products, int *quantity, const char *name, int *quantityProduct) {
    int found = 0;
    for (int i = 0; i < *quantity ; ++i) {
        if (strcmp(products[i].name, name) == 0) {
            for (int  j = 0; j < *quantityProduct ; ++j) {
                (products[i].stock)++;
            }
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Product not found.\n");
    }
}

void sellProduct(struct product *products, int *quantity, const char *name, float *profit, int *quantityProduct) {
    int found = 0;
    for (int i = 0; i < *quantity ; ++i) {
        if (strcmp(products[i].name, name) == 0) {
            for (int j = 0; j < *quantityProduct ; ++j) {
                (products[i].stock)--;
                *profit += (products[i].price - products[i].cost);
            }
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Product not found.\n");
    }
}

int main() {
    char ans = ' ';
    struct product products[100];
    int quantity = 0, loop = 1, quantityProduct = 0;
    float profit = 0;
    char buffer[100];

    while(loop == 1) {
        menu();
        scanf(" %c", &ans);

        switch(ans) {
            case '1':
                addProduct(products, &quantity);
                break;
            case '2':
                printProducts(products, quantity);
                fgets(buffer, sizeof(buffer), stdin);
                break;
            case '3': {
                printf("Enter the name of the product you want to delete: \n");
                char name[50];
                scanf("%s", name);
                deleteProduct(products, &quantity, name);
                break;
            }
            case '4':{
                printf("Enter the name of the product you want to update: \n");
                char name[50];
                scanf("%s", name);
                updateProduct(products, &quantity, name);
                break;
            }
            case '5':{
                printf("Enter the name of the product you buy: \n");
                char name[50];
                scanf("%s", name);
                printf("Enter the quantity of the product you buy: \n");
                scanf("%i", &quantityProduct);
                buyProduct(products, &quantity, name, &quantityProduct);
                break;
            }
            case '6':{
                printf("Enter the name of the product you sell: \n");
                char name[50];
                scanf("%s", name);
                printf("Enter the quantity of the product you sell: \n");
                scanf("%i", &quantityProduct);
                sellProduct(products, &quantity, name, &profit, &quantityProduct);
                break;
            }
            case '7':{
                printf("Profit: $%.2f \n", profit);
                fgets(buffer, sizeof(buffer), stdin);
                break;
            }
            case 's':
                loop = 0;
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }

        while ((getchar()) != '\n');
    }
    return 0;
}
