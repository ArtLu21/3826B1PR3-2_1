#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_CHECK 100

int inputInt()
{
    char line[100];
    int number;

    while (1)
    {
        fgets(line, sizeof(line), stdin);

        if (sscanf(line, "%d", &number) == 1)
            return number;

        printf("Error! Enter an integer: ");
    }
}

int findProduct(char barcode[][5], int productCount, char code[])
{
    int i;

    for (i = 0; i < productCount; i++)
    {
        if (strcmp(barcode[i], code) == 0)
            return i;
    }

    return -1;
}

void addProduct(char barcode[][5], char name[][101],
    int price[], int discount[], int* productCount)
{
    char code[100];
    int i;

    if (*productCount >= MAX_PRODUCTS)
    {
        printf("Maximum number of items reached!\n");
        return;
    }

    printf("Enter the barcode (4 digits): ");
    fgets(code, sizeof(code), stdin);
    code[strcspn(code, "\n")] = '\0';

    if (strlen(code) != 4)
    {
        printf("Error! The barcode must contain 4 digits.\n");
        return;
    }

    for (i = 0; i < 4; i++)
    {
        if (code[i] < '0' || code[i] > '9')
        {
            printf("Error! The barcode must contain only digits.\n");
            return;
        }
    }

    if (findProduct(barcode, *productCount, code) != -1)
    {
        printf("A product with this barcode already exists!\n");
        return;
    }

    strcpy(barcode[*productCount], code);

    printf("Enter the product name: ");
    fgets(name[*productCount], 101, stdin);
    name[*productCount][strcspn(name[*productCount], "\n")] = '\0';

    if (strlen(name[*productCount]) == 0)
    {
        printf("The product name cannot be empty!\n");
        return;
    }

    printf("Enter the price of the item: ");
    price[*productCount] = inputInt();

    if (price[*productCount] <= 0)
    {
        printf("The price must be greater than zero!\n");
        return;
    }

    printf("Enter the discount (from 1 to 50 percent): ");
    discount[*productCount] = inputInt();

    if (discount[*productCount] < 1 || discount[*productCount] > 50)
    {
        printf("Incorrect discount!\n");
        return;
    }

    (*productCount)++;

    printf("Item added!\n");
}

int scanProduct(char barcode[][5], char name[][101],
    int price[], int discount[], int productCount)
{
    char code[100];
    int index;

    printf("Enter the product barcode: ");
    fgets(code, sizeof(code), stdin);
    code[strcspn(code, "\n")] = '\0';

    index = findProduct(barcode, productCount, code);

    if (index == -1)
    {
        printf("Product not found!\n");
        return -1;
    }

    printf("Product found!\n");
    printf("Barcode: %s\n", barcode[index]);
    printf("Name: %s\n", name[index]);
    printf("Price: %d RUB\n", price[index]);
    printf("Discount: %d%%\n", discount[index]);

    return index;
}

void addToCheck(int index, int checkProduct[],
    int checkCount[], int* checkSize)
{
    int i;

    if (index == -1)
        return;

    for (i = 0; i < *checkSize; i++)
    {
        if (checkProduct[i] == index)
        {
            checkCount[i]++;
            printf("Item added to the receipt. Quantity: %d\n",
                checkCount[i]);
            return;
        }
    }

    if (*checkSize >= MAX_CHECK)
    {
        printf("The receipt is full!\n");
        return;
    }

    checkProduct[*checkSize] = index;
    checkCount[*checkSize] = 1;

    (*checkSize)++;

    printf("Item added to the receipt!\n");
}

void printCheck(char name[][101], int price[], int discount[],
    int checkProduct[], int checkCount[], int checkSize)
{
    int i;
    int total = 0;
    int totalDiscount = 0;
    int productTotal;
    int productPrice;

    if (checkSize == 0)
    {
        printf("The receipt is still empty.\n");
        return;
    }

    printf("\n        RECEIPT      \n");

    printf("%-20s %8s %8s %8s %12s\n", "Product", "Price", "Quantity", "Discount", "Total");

    for (i = 0; i < checkSize; i++)
    {
        int index = checkProduct[i];

        productPrice = price[index] * checkCount[i];

        productTotal = productPrice * (100 - discount[index]) / 100;

        total += productPrice;
        totalDiscount += productPrice - productTotal;

        printf("%-20s %8d %8d %7d%% %12d\n",
            name[index],
            price[index],
            checkCount[i],
            discount[index],
            productTotal);
    }

    printf("                                 \n");

    printf("Total cost: %d RUB\n", total);
    printf("Total discount: %d RUB\n", totalDiscount);
    printf("TOTAL DUE: %d RUB\n", total - totalDiscount);

    printf("                    \n");
}

int main()
{
    char barcode[MAX_PRODUCTS][5] = {
        "1001",
        "1002",
        "1003",
        "1004",
        "1005"
    };

    char name[MAX_PRODUCTS][101] = {
        "Milk",
        "Bread",
        "Cheese",
        "Apple",
        "Chocolate"
    };

    int price[MAX_PRODUCTS] = { 90, 45, 350, 120, 100 };
    int discount[MAX_PRODUCTS] = { 10, 5, 15, 20, 10 };

    int checkProduct[MAX_CHECK];
    int checkCount[MAX_CHECK];

    int productCount = 5;
    int checkSize = 0;

    int choice;
    int index;

    while (1)
    {
        printf("\n        CASH REGISTER         \n");
        printf("1. Add a new product\n");
        printf("2. Scan an item and display its description\n");
        printf("3. Scan the item and add it to the receipt\n");
        printf("4. Display current receipt\n");
        printf("5. Complete purchase\n");
        printf("0. Exit program\n");
        printf("                  \n");

        printf("Choose an action: ");
        choice = inputInt();

        switch (choice)
        {
        case 1:
            addProduct(barcode, name, price, discount,
                &productCount);
            break;

        case 2:
            scanProduct(barcode, name, price, discount,
                productCount);
            break;

        case 3:
            index = scanProduct(barcode, name, price, discount,
                productCount);

            addToCheck(index, checkProduct, checkCount,
                &checkSize);
            break;

        case 4:
            printCheck(name, price, discount,
                checkProduct, checkCount, checkSize);
            break;

        case 5:
            if (checkSize == 0)
            {
                printf("\nCannot complete an empty purchase!\n");
                break;
            }

            printf("\nGenerating final receipt...\n");

            printCheck(name, price, discount,
                checkProduct, checkCount, checkSize);

            printf("\n1. Start a new purchase\n");
            printf("0. Exit\n");
            printf("Your choice: ");

            choice = inputInt();

            if (choice == 1)
            {
                checkSize = 0;
                printf("\nNew purchase started!\n");
            }
            else if (choice == 0)
            {
                printf("\nProgram finished.\n");
                return 0;
            }
            else
            {
                printf("\nInvalid choice!\n");
            }

            break;

        case 0:
            printf("\nProgram finished.\n");
            return 0;

        default:
            printf("\nInvalid menu item! Please try again.\n");
        }
    }

    return 0;
}
