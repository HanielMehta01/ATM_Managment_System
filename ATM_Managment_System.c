#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int accountNumber;
    int pin;
    char accountHolderName[50];
    double balance;
} UserAccount;
int main()
{
    // App Launch and Welcome Page
    printf("------------------------------------------\n");
    printf("|    Welcome to ATM Management System    |\n");
    printf("------------------------------------------\n");
    // User Data Base checking or creation if not
    FILE *fptr = fopen("accounts.bin", "rb");
    if (fptr == NULL)
    {
        printf("Data base not found.");
        printf("Creating new data base.... \n");
        printf("Please wait.... \n");
        fptr = fopen("accounts.bin", "wb");
        UserAccount obj;
        obj.accountNumber = 1;
        obj.pin = 1234;
        strcpy(obj.accountHolderName, "Haniel Mehta");
        obj.balance = 10000000.00;
        fwrite(&obj, sizeof(UserAccount), 1, fptr); //(POINTER which goes to user account to put data into accounts.bin file; SIZE of userr account tells compiler how many bites to write; COUNT 1 tells how mant times to write as one user account can be used to write multiple names; FILE_POINTER fptr tells where to write the data of it in the fole accounts.bin)
        fclose(fptr);
        UserAccount temp;
        fptr = fopen("accounts.bin", "rb");
        fread(&temp, sizeof(UserAccount), 1, fptr);
        printf("Account Number: %d\n", temp.accountNumber);
        printf("Account Holder Name: %s\n", temp.accountHolderName);
        printf("Balance: %.2f\n", temp.balance);
        fclose(fptr);
        printf("Data base created successfully. \n");
    }
    else
    {
        printf("Data base found. \n");
        fclose(fptr);
    }
    // User Account Creation or Verification
    printf("----------------------------------\n");
    printf("|              Login             |\n");
    printf("----------------------------------\n");
    printf("Select from the below option number: \n");
    printf("1. Create Account\n");
    printf("2. Login\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1)
    {
        printf("Account Creation\n");
    }
    else if (choice == 2)
    {
        printf("Login\n");
    }
    else
    {
        printf("Invalid option. Choice from the above options.\n");
    }
    // Main Menu
}