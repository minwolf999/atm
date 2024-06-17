#include "header.h"

void mainMenu(struct User u)
{
    int option;
    system("clear");

    printf("\n\n\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check accounts\n");
    printf("\n\t\t[4]- Check list of owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Exit\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        CreateNewAcc(u);
        break;
    case 2:
        UpdateAccount(u);
        break;
    case 3:
        CheckDetails(u);
        break;
    case 4:
        CheckAllAccounts(u);
        break;
    case 5:
        MakeTransaction(u);
        break;
    case 6:
        RemoveAccount(u);
        break;
    case 7:
        TransfertOwnerAccount(u);
        break;
    case 8:
        system("clear");
        exit(1);
        break;
    default:
        printf("\e[0;31mInvalid operation!\e[0m\n");
    }
};

int main() 
{
    int err = InitDatabase();
    if (err)
    {
        printf("\e[0;31mError in database functions !\n%d\e[0m", err);
        return 1;
    };

    struct User u;

    Login_Menu(&u);
    mainMenu(u);

    system("clear");
    return 0;
};

