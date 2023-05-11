// #include "header.h"

// void mainMenu(struct User u)
// {
//     int option;
//     system("clear");
//     printf("\n\n\t\t======= ATM =======\n\n");
//     printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
//     printf("\n\t\t[1]- Create a new account\n");
//     printf("\n\t\t[2]- Update account information\n");
//     printf("\n\t\t[3]- Check accounts\n");
//     printf("\n\t\t[4]- Check list of owned account\n");
//     printf("\n\t\t[5]- Make Transaction\n");
//     printf("\n\t\t[6]- Remove existing account\n");
//     printf("\n\t\t[7]- Transfer ownership\n");
//     printf("\n\t\t[8]- Exit\n");
//     scanf("%d", &option);

//     switch (option)
//     {
//     case 1:
//         createNewAcc(u);
//         break;
//     case 2:
//         // student TODO : add your **Update account information** function
//         // here
//         break;
//     case 3:
//         // student TODO : add your **Check the details of existing accounts** function
//         // here
//         break;
//     case 4:
//         checkAllAccounts(u);
//         break;
//     case 5:
//         // student TODO : add your **Make transaction** function
//         // here
//         break;
//     case 6:
//         // student TODO : add your **Remove existing account** function
//         // here
//         break;
//     case 7:
//         // student TODO : add your **Transfer owner** function
//         // here
//         break;
//     case 8:
//         exit(1);
//         break;
//     default:
//         printf("Invalid operation!\n");
//     }
// };

// void initMenu(struct User *u)
// {
//     int r = 0;
//     int option;
//     system("clear");
//     printf("\n\n\t\t======= ATM =======\n");
//     printf("\n\t\t-->> Feel free to login / register :\n");
//     printf("\n\t\t[1]- login\n");
//     printf("\n\t\t[2]- register\n");
//     printf("\n\t\t[3]- exit\n");
//     while (!r)
//     {
//         scanf("%d", &option);
//         switch (option)
//         {
//         case 1:
//             loginMenu(u->name, u->password);
//             if (strcmp(u->password, getPassword(*u)) == 0)
//             {
//                 printf("\n\nPassword Match!");
//             }
//             else
//             {
//                 printf("\nWrong password!! or User Name\n");
//                 exit(1);
//             }
//             r = 1;
//             break;
//         case 2:
//             // student TODO : add your **Registration** function
//             // here
//             r = 1;
//             break;
//         case 3:
//             exit(1);
//             break;
//         default:
//             printf("Insert a valid operation!\n");
//         }
//     }
// };

// int main()
// {
//     struct User u;
    
//     initMenu(&u);
//     mainMenu(u);
//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_ACCOUNTS 100

struct User {
    int id;
    char name[100];
    char password[100];
};

struct Account {
    int id;
    int user_id;
    char user_name[100];
    int account_id;
    char date_of_creation[20];
    char country[100];
    char phone_number[20];
    float balance;
    char account_type[20];
};

struct User users[MAX_USERS];
struct Account accounts[MAX_ACCOUNTS];
int numUsers = 0;
int numAccounts = 0;

void registerUser(struct User u);
void updateAccountInfo(struct User *u);
void checkAccountDetails(struct User u);
void makeTransaction(struct User u);
void removeAccount(struct User u);
void loginMenu(char name[], char password[]);

void registerUser(struct User u) {
    printf("Enter name: ");
    scanf("%s", u.name);

    // Check if user with the same name already exists
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].name, u.name) == 0) {
            printf("User with the same name already exists.\n");
            return;
        }
    }

    printf("Enter password: ");
    scanf("%s", u.password);

    u.id = numUsers; // Assign a unique ID
    users[numUsers++] = u; // Add user to the array

    // Save user to file
    FILE *file = fopen("./data/users.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%d %s %s\n", u.id, u.name, u.password);
    fclose(file);

    printf("User registered successfully.\n");
}

void updateAccountInfo(struct User *u) {
    int account_id;
    printf("Enter account ID: ");
    scanf("%d", &account_id);

    // Find the account with the specified ID
    struct Account *account = NULL;
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].id == account_id && accounts[i].user_id == u->id) {
            account = &accounts[i];
            break;
        }
    }

    if (account == NULL) {
        printf("Account not found or you don't have permission to update.\n");
        return;
    }

    int option;
    printf("Choose an option to update:\n");
    printf("1. Country\n");
    printf("2. Phone number\n");
    scanf("%d", &option);

    switch (option) {
        case 1:
            printf("Enter new country: ");
            scanf("%s", account->country);
            break;
        case 2:
            printf("Enter new phone number: ");
            scanf("%s", account->phone_number);
            break;
        default:
            printf("Invalid option.\n");
            return;
    }

    // Update account information in the file
    FILE *file = fopen("./data/records.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < numAccounts; i++) {
        fprintf(file, "%d %d %s %d %s %s %s %.2f %s\n",
                accounts[i].id, accounts[i].user_id, accounts[i].user_name,
                accounts[i].account_id, accounts[i].date_of_creation, accounts[i].country,
                accounts[i].phone_number, accounts[i].balance, accounts[i].account_type);
    }

    fclose(file);

    printf("Account information updated successfully.\n");
}

void checkAccountDetails(struct User u) {
    int account_id;
    printf("Enter account ID: ");
    scanf("%d", &account_id);

    // Find the account with the specified ID
    struct Account *account = NULL;
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].id == account_id && accounts[i].user_id == u.id) {
            account = &accounts[i];
            break;
        }
    }

    if (account == NULL) {
        printf("Account not found or you don't have permission to access.\n");
        return;
    }

    printf("Account details:\n");
    printf("User ID: %d\n", account->user_id);
    printf("User Name: %s\n", account->user_name);
    printf("Account ID: %d\n", account->account_id);
    printf("Date of Creation: %s\n", account->date_of_creation);
    printf("Country: %s\n", account->country);
    printf("Phone Number: %s\n", account->phone_number);
    printf("Balance: %.2f\n", account->balance);
    printf("Account Type: %s\n", account->account_type);

    // Calculate and display interest based on account type
    if (strcmp(account->account_type, "savings") == 0) {
        float interest = account->balance * 0.0007;
        printf("Interest Rate: 0.07%%\n");
        printf("Interest: %.2f\n", interest);
    } else if (strcmp(account->account_type, "fixed01") == 0) {
        float interest = account->balance * 0.0004;
        printf("Interest Rate: 0.04%%\n");
        printf("Interest: %.2f\n", interest);
    } else if (strcmp(account->account_type, "fixed02") == 0) {
        float interest = account->balance * 0.0005;
        printf("Interest Rate: 0.05%%\n");
        printf("Interest: %.2f\n", interest);
    } else if (strcmp(account->account_type, "fixed03") == 0) {
        float interest = account->balance * 0.0008;
        printf("Interest Rate: 0.08%%\n");
        printf("Interest: %.2f\n", interest);
    } else {
        printf("You will not get interests because the account is of type current.\n");
    }
}

void makeTransaction(struct User u) {
    int account_id;
    printf("Enter account ID: ");
    scanf("%d", &account_id);

    // Find the account with the specified ID
    struct Account *account = NULL;
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].id == account_id && accounts[i].user_id == u.id) {
            account = &accounts[i];
            break;
        }
    }

    if (account == NULL) {
        printf("Account not found or you don't have permission to make transactions.\n");
        return;
    }

    int option;
    printf("Choose an option:\n");
    printf("1. Deposit\n");
    printf("2. Withdraw\n");
    scanf("%d", &option);

    switch (option) {
        case 1: {
            float amount;
            printf("Enter the amount to deposit: ");
            scanf("%f", &amount);
            account->balance += amount;

            printf("Deposit successful.\n");
            printf("New balance: %.2f\n", account->balance);
            break;
        }
        case 2: {
            float amount;
            printf("Enter the amount to withdraw: ");
            scanf("%f", &amount);

            if (amount > account->balance) {
                printf("Insufficient balance.\n");
                return;
            }
            account->balance -= amount;
            printf("Withdraw successful.\n");
            printf("New balance: %.2f\n", account ->balance);
            break;
        } 
        default:
            printf("Invalid option.\n");
            return;
    }
    
    // Update account information in the file
    FILE *file = fopen("./data/records.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < numAccounts; i++) {
        fprintf(file, "%d %d %s %d %s %s %s %.2f %s\n",
                accounts[i].id, accounts[i].user_id, accounts[i].user_name,
                accounts[i].account_id, accounts[i].date_of_creation, accounts[i].country,
                accounts[i].phone_number, accounts[i].balance, accounts[i].account_type);
    }

    fclose(file);
}

void removeAccount(struct User u) {
    int account_id;
    printf("Enter account ID: ");
    scanf("%d", &account_id);

    // Find the account with the specified ID
    struct Account *account = NULL;
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].id == account_id && accounts[i].user_id == u.id) {
            account = &accounts[i];
            break;
        }
    }

    if (account == NULL) {
        printf("Account not found or you don't have permission to remove.\n");
        return;
    }

    // Remove the account from the array
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].id == account_id) {
            for (int j = i; j < numAccounts - 1; j++) {
                accounts[j] = accounts[j + 1];
            }
            numAccounts--;
            break;
        }
    }

    // Update account information in the file
    FILE *file = fopen("./data/records.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < numAccounts; i++) {
        fprintf(file, "%d %d %s %d %s %s %s %.2f %s\n",
                accounts[i].id, accounts[i].user_id, accounts[i].user_name,
                accounts[i].account_id, accounts[i].date_of_creation, accounts[i].country,
                accounts[i].phone_number, accounts[i].balance, accounts[i].account_type);
    }

    fclose(file);
}


void loginMenu(char name[], char password[]) {
    printf("Enter name: ");
    scanf("%s", name);

    printf("Enter password: ");
    scanf("%s", password);
}

int main() {
    // Load users from file
    FILE *file = fopen("./data/users.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while (fscanf(file, "%d %s %s", &users[numUsers].id, users[numUsers].name, users[numUsers].password) != EOF) {
        numUsers++;
    }

    fclose(file);

    struct User u;
    loginMenu(u.name, u.password);

    // Check if user exists
    int userExists = 0;
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].name, u.name) == 0 && strcmp(users[i].password, u.password) == 0) {
            userExists = 1;
            break;
        }
    }

    if (userExists) {
        printf("Login successful.\n");
        int option;

        do {
            printf("\nMain Menu:\n");
            printf("1. Update Account Information\n");
            printf("2. Check Account Details\n");
            printf("3. Make a Transaction\n");
            printf("4. Remove Account\n");
            printf("5. Logout\n");
            printf("Choose an option: ");
            scanf("%d", &option);

            switch (option) {
                case 1:
                    updateAccountInfo(&u);
                    break;
                case 2:
                    checkAccountDetails(u);
                    break;
                case 3:
                    makeTransaction(u);
                    break;
                case 4:
                    removeAccount(u);
                    break;
                case 5:
                    printf("Logged out.\n");
                    break;
                default:
                    printf("Invalid option. Please try again.\n");
            }
        } while (option != 5);
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}



