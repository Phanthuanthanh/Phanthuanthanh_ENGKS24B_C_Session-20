#include <stdio.h>
#include <string.h>

typedef struct {
    char productId[20];
    char productName[100];
    float importPrice;
    float sellingPrice;
    int quantity;
} Product;

float revenue = 0.0; 

void addProduct(Product products[], int *n);
void displayProducts(Product products[], int n);
void importProduct(Product products[], int *n);
void updateProduct(Product products[], int n);
void sortProducts(Product products[], int n);
void searchProduct(Product products[], int n);
void sellProduct(Product products[], int *n);

int main() {
    int option = 0;
    Product products[100];
    int n = 0; 

    do {
        printf("MENU\n");
        printf("1. Nhap so luong va thong tin san pham\n");
        printf("2. Hien thi danh sach san pham\n");
        printf("3. Nhap san pham\n");
        printf("4. Cap nhat thong tin san pham\n");
        printf("5. Sap xep san pham theo gia (tang/giam)\n");
        printf("6. Tim kiem san pham\n");
        printf("7. Ban san pham\n");
        printf("8. Hien thi doanh thu hien tai\n");
        printf("9. Thoat\n");

        printf("Nhap lua chon: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Nhap so luong san pham: ");
                scanf("%d", &n);
                addProduct(products, &n);
                break;
            case 2:
                displayProducts(products, n);
                break;
            case 3:
                importProduct(products, &n);
                break;
            case 4:
                updateProduct(products, n);
                break;
            case 5:
                sortProducts(products, n);
                break;
            case 6:
                searchProduct(products, n);
                break;
            case 7:
                sellProduct(products, &n);
                break;
            case 8:
                printf("Doanh thu hien tai: %.2f\n", revenue);
                break;
            case 9:
                return 0;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (option != 9);

    return 0;
}

void addProduct(Product products[], int *n) {
    for (int i = 0; i < *n; i++) {
        printf("Nhap thong tin san pham thu %d:\n", i + 1);

        printf("Ma san pham: ");
        scanf("%s", products[i].productId);

        printf("Ten san pham: ");
        getchar();
        fgets(products[i].productName, sizeof(products[i].productName), stdin);
        products[i].productName[strcspn(products[i].productName, "\n")] = '\0';

        printf("Gia nhap: ");
        scanf("%f", &products[i].importPrice);

        printf("Gia ban: ");
        scanf("%f", &products[i].sellingPrice);

        printf("So luong: ");
        scanf("%d", &products[i].quantity);

        revenue -= products[i].quantity * products[i].importPrice;
    }
}

void displayProducts(Product products[], int n) {
    printf("Danh sach san pham:\n");
    for (int i = 0; i < n; i++) {
        printf("San pham thu %d:\n", i + 1);
        printf("Ma san pham: %s\n", products[i].productId);
        printf("Ten san pham: %s\n", products[i].productName);
        printf("Gia nhap: %.2f\n", products[i].importPrice);
        printf("Gia ban: %.2f\n", products[i].sellingPrice);
        printf("So luong: %d\n", products[i].quantity);
    }
}

void importProduct(Product products[], int *n) {
    char productId[20];
    int quantity;
    printf("Nhap ma san pham: ");
    scanf("%s", productId);

    int found = -1;
    for (int i = 0; i < *n; i++) {
        if (strcmp(products[i].productId, productId) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("San pham moi, nhap thong tin:\n");
        strcpy(products[*n].productId, productId);

        printf("Ten san pham: ");
        getchar();
        fgets(products[*n].productName, sizeof(products[*n].productName), stdin);
        products[*n].productName[strcspn(products[*n].productName, "\n")] = '\0';

        printf("Gia nhap: ");
        scanf("%f", &products[*n].importPrice);

        printf("Gia ban: ");
        scanf("%f", &products[*n].sellingPrice);

        printf("So luong: ");
        scanf("%d", &products[*n].quantity);

        revenue -= products[*n].quantity * products[*n].importPrice;
        (*n)++;
    } else {
        printf("Nhap so luong can them: ");
        scanf("%d", &quantity);
        products[found].quantity += quantity;
        revenue -= quantity * products[found].importPrice;
    }
}

void updateProduct(Product products[], int n) {
    char productId[20];
    printf("Nhap ma san pham can cap nhat: ");
    scanf("%s", productId);

    int found = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(products[i].productId, productId) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Khong tim thay san pham!\n");
        return;
    }

    printf("Cap nhat thong tin san pham:\n");
    printf("Ten san pham: ");
    getchar();
    fgets(products[found].productName, sizeof(products[found].productName), stdin);
    products[found].productName[strcspn(products[found].productName, "\n")] = '\0';

    printf("Gia nhap: ");
    scanf("%f", &products[found].importPrice);

    printf("Gia ban: ");
    scanf("%f", &products[found].sellingPrice);

    printf("So luong: ");
    scanf("%d", &products[found].quantity);
}

void sortProducts(Product products[], int n) {
    int choice;
    printf("1. Sap xep tang dan\n");
    printf("2. Sap xep giam dan\n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((choice == 1 && products[i].sellingPrice > products[j].sellingPrice) ||
                (choice == 2 && products[i].sellingPrice < products[j].sellingPrice)) {
                Product temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }

    printf("Sap xep thanh cong\n");
}

void searchProduct(Product products[], int n) {
    char productName[100];
    printf("Nhap ten san pham can tim: ");
    getchar();
    fgets(productName, sizeof(productName), stdin);
    productName[strcspn(productName, "\n")] = '\0';

    printf("Ket qua tim kiem:\n");
    for (int i = 0; i < n; i++) {
        if (strstr(products[i].productName, productName)) {
            printf("Ma san pham: %s\n", products[i].productId);
            printf("Ten san pham: %s\n", products[i].productName);
            printf("Gia nhap: %.2f\n", products[i].importPrice);
            printf("Gia ban: %.2f\n", products[i].sellingPrice);
            printf("So luong: %d\n", products[i].quantity);
        }
    }
}

void sellProduct(Product products[], int *n) {
    char productId[20];
    int quantity;
    printf("Nhap ma san pham can ban: ");
    scanf("%s", productId);

    int found = -1;
    for (int i = 0; i < *n; i++) {
        if (strcmp(products[i].productId, productId) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Khong tim thay san pham!\n");
        return;
    }

    if (products[found].quantity == 0) {
        printf("Het hang!\n");
        return;
    }

    printf("Nhap so luong can ban: ");
    scanf("%d", &quantity);

    if (quantity > products[found].quantity) {
        printf("Khong du so luong! So luong hien co: %d\n", products[found].quantity);
    } else {
        products[found].quantity -= quantity;
        revenue += quantity * products[found].sellingPrice;
        printf("Ban thanh cong! So luong con lai: %d\n", products[found].quantity);
    }
}

