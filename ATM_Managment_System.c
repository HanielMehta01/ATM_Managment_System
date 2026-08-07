#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int Account_Number;
    int Pin;
    char Account_Holder_Name[50];
    double Balance;
} UserAccount;
int main()
{
    // App Launch and Welcome Page
    printf("------------------------------------------\n");
    printf("|                                        |\n");
    printf("|    Welcome to ATM Management System    |\n");
    printf("|                                        |\n");
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
        obj.Account_Number = 1;
        obj.Pin = 1234;
        strcpy(obj.Account_Holder_Name, "Haniel Mehta");
        obj.Balance = 10000000.00;
        fwrite(&obj, sizeof(UserAccount), 1, fptr); //(POINTER which goes to user account to put data into accounts.bin file; SIZE of userr account tells compiler how many bites to write; COUNT 1 tells how mant times to write as one user account can be used to write multiple names; FILE_POINTER fptr tells where to write the data of it in the fole accounts.bin)
        fclose(fptr);
        UserAccount temp;
        fptr = fopen("accounts.bin", "rb");
        fread(&temp, sizeof(UserAccount), 1, fptr);
        printf("Account Number: %d\n", temp.Account_Number);
        printf("Account Holder Name: %s\n", temp.Account_Holder_Name);
        printf("Balance: %.2f\n", temp.Balance);
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
    printf("|            Login Portal         |\n");
    printf("----------------------------------\n");
    printf("Select from the below option number: \n");
    printf("1. Create Account\n");
    printf("2. Login\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1)
    {
        UserAccount obj;
        int Temp_Pin = 1;
        printf("Account Creation\n");
        printf("Enter the below credentials: ");
        printf("Account Number = ");
        scanf("%d", &obj.Account_Number);
        printf("Account Holder Name = ");
        scanf("%s", obj.Account_Holder_Name);
        printf("PIN (Should be of more than 1 digit)= ");
        scanf("%d", &obj.Pin);
        while (obj.Pin != Temp_Pin)
        {
            printf("Confirm PIN = ");
            scanf("%d", &Temp_Pin);
            if (obj.Pin == Temp_Pin)
            {
                printf("Account Created Successfully. \n");
            }
            else
            {
                printf("PIN number doesnt match the number you have entered. Please try again. \n");
            }
        }
        fptr = fopen("accounts.bin", "wb");
        fwrite(&obj, sizeof(UserAccount), 1, fptr); // Same meaning as above used to store the new account details to remember the detaisl the next the user logs in.
        fclose(fptr);
    }
    else if (choice == 2)
    {
        int Account_Number, Pin;
        UserAccount temp;
        printf("Enter your credentials to Login to your account. \n");
        printf("Enter your Account Number: ");
        scanf("%d", &Account_Number);
        printf("Enter Your PIN: ");
        scanf("%d", &Pin);
        fptr = fopen("accounts.bin", "rb");
        while (fread(&temp, sizeof(UserAccount), 1, fptr)) // This will go in a loop through all data base matching the acount number and pin to chekc if the acocunt exists or not. If it exists then it will redirect you to the main menu else it will show invalid credentials. Also this line of code is used to check like (pointer to the user account; size of user account tells compiler how many bites to read; count 1 tells how many times to read as one user account can be used to read multiple names; file pointer fptr tells where to read the data of it in the file accounts.bin as defines above "fptr = fopen("accounts.bin","rb");
        {
            if (temp.Account_Number == Account_Number && temp.Pin == Pin)
            {
                int a;
                printf("......Login Successful. \n");
                printf("Welcome %s. \n", temp.Account_Holder_Name);
                printf("Redirecting you to Main Menu. \n");
                printf("-----------------------------------\n");
                printf("|            Main Menu            |\n");
                printf("-----------------------------------\n");
                printf("Select from the below option number: \n");
                printf("1. Check Balance \n");
                printf("2. Deposit Money \n");
                printf("3. Withdraw Money \n");
                printf("4. Change PIN \n");
                printf("5. Exit \n");
                printf("Enter your selected option number: ");
                scanf("%d", &a);
                switch (a)
                {
                case 1:
                    printf("Your current balance is: %.2f\n", temp.Balance);
                    break;
                case 2:
                    double Deposit_Amount;
                    printf("Enter the amount you want to deposit: Re ");
                    scanf("%lf", &Deposit_Amount); // lf used as don't know how much digits is deposited also can be in decimal .
                    temp.Balance += Deposit_Amount;
                    printf("Deposit Successful. ");
                    printf("New balance: %.2lf\n", temp.Balance);
                    break;
                case 3:
                    double Withdraw_Amount;
                    printf("Your current balance is : %.2f\n", temp.Balance);
                    printf("Enter the amount you want to withdraw: Re ");
                    scanf("%lf", &Withdraw_Amount);
                    if (Withdraw_Amount >= temp.Balance - 5000) // Inorder to maintain minimum balance of 5000 in the account. Also checking if the withdraw amount is greater than or equal to the balance in the account.
                    {
                        printf("Insufficient balance. ");
                    }
                    else
                    {
                        temp.Balance -= Withdraw_Amount;
                        printf("Withdrawal Successful. ");
                        printf("New balance: %.2lf\n", temp.Balance);
                    }
                    break;
                case 4:
                    int New_Pin, Confirm_Pin;
                    printf("Enter your new PIN: ");
                    scanf("%d", &New_Pin);
                change_pin:
                    printf("Confirm your new PIN: ");
                    scanf("%d", &Confirm_Pin);
                    {
                        if (New_Pin == Confirm_Pin)
                        {
                            temp.Pin = New_Pin;
                            printf("PIN changed successfully. \n");
                        }

                        else
                        {
                            printf("PINs do not match. \n");
                            goto change_pin;
                        }
                    }
                    if (!(temp.Account_Number == Account_Number && temp.Pin == Pin))
                    {
                        printf("Invalid credentials. Please try again.\n");
                    }
                    break;
                }
            }
            else
            {
                printf("Invalid option. Choice from the above options.\n");
            }
            // Main Menu
        }
    }
}