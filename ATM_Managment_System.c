#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
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
    // User database checking or creation if not
    char path[500];
    _getcwd(path, sizeof(path));
    printf("\nProgram is running from: %s\n", path);
    FILE *fptr = fopen("accounts.bin", "rb");
    printf("\nProgram is opening accounts.bin\n");
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
        fwrite(&obj, sizeof(UserAccount), 1, fptr);
        /*
           POINTER that points to user account to put data into accounts.bin file;
           SIZE of user account tells the compiler how many bytes to write;
           COUNT 1 tells how many times to write, as one user account can be used to write multiple names;
           FILE_POINTER fptr tells where to write the data in the file accounts.bin
        */
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
        printf("Data base found! \n");
        fclose(fptr);
    }
    // User Account Creation or Verification
    printf("-----------------------------------\n");
    printf("|            Login Portal         |\n");
    printf("-----------------------------------\n");
    printf("Select from the below option number: \n");
    printf("1. Create Account\n");
    printf("2. Login into your account\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1)
    {
        UserAccount obj;
        int Temp_Pin = 0;
        printf("------------------------------------\n");
        printf("|         Account Creation          |\n");
        printf("------------------------------------\n");
        printf("Enter the below credentials:- \n ");
        int accountExists;
        do
        {
            accountExists = 0;
            printf("Account Number = ");
            scanf("%d", &obj.Account_Number);
            fptr = fopen("accounts.bin", "rb"); // To check if the account number is already in use by another user.
            UserAccount temp;
            while (fread(&temp, sizeof(UserAccount), 1, fptr))
            {
                if (temp.Account_Number == obj.Account_Number)
                {
                    accountExists = 1;
                    break;
                }
            }
            fclose(fptr);
            if (accountExists == 1)
            {
                printf("This Account Number already exists. Please select a new one.\n");
            }
        } while (accountExists == 1);
        printf("Account Holder Name = ");
        scanf(" %49[^\n]", obj.Account_Holder_Name);
        /*
        "%[^\n]" => ^ This means it accepts every character (including blank spaces)
        except a newline. We can limit the number of characters it takes by %49, 
        as the limit is 50.
        */
    re_pin:
        printf("PIN (4 digits)= ");
        scanf("%d", &obj.Pin);
        if (obj.Pin >= 1000 && obj.Pin <= 9999)
        {
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
        }
        else
        {
            printf("Enter a valid PIN Number.");
            goto re_pin;
        }
        printf("Money you want to deposit in your account = ");
        scanf("%lf", &obj.Balance);
        fptr = fopen("accounts.bin", "ab");
        fwrite(&obj, sizeof(UserAccount), 1, fptr); 
        /* 
        Same meaning as above: used to store the new account details 
        to remember the details the next time the user logs in.
        */
        fclose(fptr);
    }
    else if (choice == 2)
    {
        int Account_Number, Pin;
        int loginSuccess = 0;
        UserAccount temp;
    login_again:
        loginSuccess = 0;
        fptr = fopen("accounts.bin", "rb+");
        printf("Enter your credentials to Login to your account. \n");
        printf("Enter your Account Number: ");
        scanf("%d", &Account_Number);
        printf("Enter Your PIN: ");
        scanf("%d", &Pin);
        while (fread(&temp, sizeof(UserAccount), 1, fptr))
        {
            printf("Checking Account: %d \n", temp.Account_Number);
            /*
            This will loop through all database records matching the account number and
            PIN to check if the account exists or not. If it exists, then it will redirect
            you to the main menu; else it will show invalid credentials. Also, this line of
            code is used to check, like (pointer to the user account; size of user account
            tells the compiler how many bytes to read; count 1 tells how many times to read
            as one user account can be used to read multiple names; file pointer fptr
            tells where to read the data in the file accounts.bin, as defined above
            "fptr = fopen("accounts.bin", "rb");
            It will then move the pointer to the next account after stopping to search
            i.e(it will go to account wich is next in database just  after the account
            which we want as per the code which is written)
            */
            if (temp.Account_Number == Account_Number && temp.Pin == Pin)
            {
                loginSuccess = 1;
                break;
            }
        }
        if (loginSuccess == 0)
        {
            printf("Invalid credentials. Please try again. \n");
            fclose(fptr);
            goto login_again;
        }
        int a, oldpin, New_Pin, Confirm_Pin;
        double Deposit_Amount, Withdraw_Amount;
        printf("......Login Successful. \n");
        printf("Welcome %s. \n", temp.Account_Holder_Name);
        printf("Redirecting you to Main Menu. \n");
        printf("-----------------------------------\n");
        printf("|            Main Menu            |\n");
        printf("-----------------------------------\n");
    more:
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
            printf("Enter the amount you want to deposit: Re ");
        deposit:
            scanf("%lf", &Deposit_Amount); // lf used as don't know how much digits is deposited also can be in decimal .
            if (Deposit_Amount <= 0)
            {
                printf("Invalid amount. Please enter a positive value.\n");
                goto deposit;
            }
            else
            {
                temp.Balance += Deposit_Amount;
            }
            printf("Deposit Successful. ");
            printf("New balance: %.2lf\n", temp.Balance);
            break;
        case 3:
        re_withdraw:
            printf("Your current balance is : %.2f\n", temp.Balance);
            printf("Enter the amount you want to withdraw: Re ");
            scanf("%lf", &Withdraw_Amount);
            if (Withdraw_Amount <= 0 || Withdraw_Amount > temp.Balance - 5000)
            /*
            Inorder to maintain minimum balance of 5000 in the account.
            Also checking if the withdraw amount is greater than or equal to the balance in the account.
            */
            {
                printf("Insufficient balance. ");
                goto re_withdraw;
            }
            else
            {
                temp.Balance -= Withdraw_Amount;
                printf("Withdrawal Successful. ");
                printf("New balance: %.2lf\n", temp.Balance);
            }
            break;
        case 4:
        old_pin:
            printf("Enter your old PIN: ");
            scanf("%d", &oldpin);
            if (oldpin != temp.Pin)
            {
                printf("Incorrect PIN! Please try again.\n");
                goto old_pin;
            }
            else
            {
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
            }
            break;
        case 5:
        exit:
            fseek(fptr, -sizeof(UserAccount), SEEK_CUR);
            /*
            This line of code is used to move the file pointer back to the position of the current user account in the file.
            As above, when it goes to the database, when it gets a matching account and PIN, it transfers details to UserAccount temp
            and then moves one account ahead in the database, so when entering the new details of the user account it will write in the
            next position of the file, so to avoid that we use this line of code to move back to the position of the current user
            account in the file.
            */
            fwrite(&temp, sizeof(UserAccount), 1, fptr);
            printf("Thank you for using our ATM. Have a great day!\n");
            goto end;
        default:
            printf("Invalid option. Please try again.\n");
            goto more;
        }
        printf("Do you want to perform another transaction? (1 for Yes, 0 for No): ");
        int another_transaction;
        scanf("%d", &another_transaction);
        if (another_transaction == 1)
        {
            goto more;
        }
        else
        {
            goto exit;
        }
    end:
        fclose(fptr);
    }
}
