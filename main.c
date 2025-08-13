#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char name[50];
char phone[20];
char email[50];

int contactCount = 0;

void saveContact(const char *name, const char *phone, const char *email) {
    FILE *file = fopen("contacts.txt", "a");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    
    fprintf(file, "%s %s %s\n", name, phone, email);
    fclose(file);
    contactCount++;
}

void addContact() {
    printf("Enter name: ");
    scanf("%49s", name);
    printf("Enter phone: ");
    scanf("%19s", phone);
    printf("Enter email: ");
    scanf("%49s", email);
    
    saveContact(name, phone, email);
    printf("\nContact added successfully.\n");
}

void searchContact() {
    char searchName[50];
    printf("\nEnter name to search: ");
    scanf("%49s", searchName);
    
    FILE *file = fopen("contacts.txt", "r");
    if (file == NULL) {
        printf("\nNo contacts found.\n");
        return;
    }
    
    int found = 0;
    while (fscanf(file, "%49s %19s %49s", name, phone, email) != EOF) {
        if (strcmp(name, searchName) == 0) {
            printf("\nFound contact - Name: %s, Phone: %s, Email: %s\n", name, phone, email);
            found = 1;
            break;
        }
    }
    
    fclose(file);
    
    if (!found) {
        printf("\nContact not found.\n");
    }
}

void deleteContact() {
    char deleteName[50];
    printf("\nEnter name to delete: ");
    scanf("%49s", deleteName);
    
    FILE *file = fopen("contacts.txt", "r");
    if (file == NULL) {
        printf("\nNo contacts found.\n");
        return;
    }
    
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        fclose(file);
        printf("Error opening temporary file.\n");
        return;
    }
    
    int found = 0;
    while (fscanf(file, "%49s %19s %49s", name, phone, email) != EOF) {
        if (strcmp(name, deleteName) != 0) {
            fprintf(tempFile, "%s %s %s\n", name, phone, email);
        } else {
            found = 1;
        }
    }
    
    fclose(file);
    fclose(tempFile);
    
    if (found) {
        remove("contacts.txt");
        rename("temp.txt", "contacts.txt");
        contactCount--;
        printf("\nContact deleted successfully.\n");
    } else {
        remove("temp.txt");
        printf("\nContact not found.\n");
    }
}

void editContact() {
    char editName[50];
    printf("\nEnter name to edit: ");
    scanf("%49s", editName);
    
    FILE *file = fopen("contacts.txt", "r");
    if (file == NULL) {
        printf("\nNo contacts found.\n");
        return;
    }
    
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        fclose(file);
        printf("Error opening temporary file.\n");
        return;
    }
    
    int found = 0;
    while (fscanf(file, "%49s %19s %49s", name, phone, email) != EOF) {
        if (strcmp(name, editName) == 0) {
            found = 1;
            printf("Editing contact - Name: %s, Phone: %s, Email: %s\n", name, phone, email);
            printf("Enter new name: ");
            scanf("%49s", name);
            printf("Enter new phone: ");
            scanf("%19s", phone);
            printf("Enter new email: ");
            scanf("%49s", email);
        }
        fprintf(tempFile, "%s %s %s\n", name, phone, email);
    }
    
    fclose(file);
    fclose(tempFile);
    
    if (found) {
        remove("contacts.txt");
        rename("temp.txt", "contacts.txt");
        printf("\nContact edited successfully.\n");
    } else {
        remove("temp.txt");
        printf("\nContact not found.\n");
    }
}

int main () {
    int choice;
    
    while (1) {
        printf("\nContact Management System\n");
        printf("\n1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Delete Contact\n");
        printf("4. Edit Contacts\n");
        printf("5. Exit\n");
        printf("\nEnter your choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                searchContact();
                break;
            case 3:
                deleteContact();
                break;
            case 4:
                editContact();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
    
    return 0;
}