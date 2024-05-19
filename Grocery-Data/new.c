#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 100
#define MAX_NAME_LENGTH 50
#define MAX_ADDRESS_LENGTH 100
#define FILENAME "grocery_data.txt"

// Structure to represent an item
typedef struct {
    char name[MAX_NAME_LENGTH];
    float price;
    int quantity;
} Item;

// Structure to represent customer details
typedef struct {
    char name[MAX_NAME_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
} Customer;

// Function prototypes
void saveDataToFile(Item *items, int numItems, Customer customer);
void loadDataFromFile(Item *items, int *numItems, Customer *customer);
void searchItem(Item *items, int numItems, const char *itemName);

int main() {
    Item items[MAX_ITEMS];
    Customer customer;
    int numItems = 0;
    char choice;

    // Load data from file
    loadDataFromFile(items, &numItems, &customer);

    // Search for an item
    searchItem(items, numItems, "ItemName");

    return 0;
}

// Function to save data to file
void saveDataToFile(Item *items, int numItems, Customer customer) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        exit(EXIT_FAILURE);
    }

    // Write customer details
    fprintf(file, "%s\n%s\n", customer.name, customer.address);

    // Write item details
    for (int i = 0; i < numItems; i++) {
        fprintf(file, "%s\n%.2f\n%d\n", items[i].name, items[i].price, items[i].quantity);
    }

    fclose(file);
}

// Function to load data from file
void loadDataFromFile(Item *items, int *numItems, Customer *customer) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        exit(EXIT_FAILURE);
    }

    // Read customer details
    fgets(customer->name, MAX_NAME_LENGTH, file);
    fgets(customer->address, MAX_ADDRESS_LENGTH, file);
    // Remove newline characters
    customer->name[strcspn(customer->name, "\n")] = '\0';
    customer->address[strcspn(customer->address, "\n")] = '\0';

    // Read item details
    while ((*numItems < MAX_ITEMS) && (fscanf(file, "%s%f%d", items[*numItems].name, &items[*numItems].price, &items[*numItems].quantity) == 3)) {
        (*numItems)++;
    }

    fclose(file);
}

// Function to search for an item by name
void searchItem(Item *items, int numItems, const char *itemName) {
    printf("Searching for item: %s\n", itemName);
    int found = 0;
    for (int i = 0; i < numItems; i++) {
        if (strcmp(items[i].name, itemName) == 0) {
            printf("Item found: %s - $%.2f - Quantity: %d\n", items[i].name, items[i].price, items[i].quantity);
            found = 1;
        }
    }
    if (!found) {
        printf("Item not found.\n");
    }
}