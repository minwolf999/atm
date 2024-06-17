#include "header.h"

void CreateNewAcc(struct User u)
{
    system("clear");

    struct Record r;

    r.userId = u.id;
    strcpy(r.name, u.name);

noAccount:

    printf("\t\t\t===== New Account =====\n");

    printf("\nEnter today's date(mm/dd/yyyy):");
    
    char input[100];

    scanf("%s", input);

    if (sscanf(input, "%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year) != 3 ||
        (r.deposit.day <= 0 || r.deposit.day > 31) ||
        (r.deposit.month <= 0 || r.deposit.month > 12))
    {
        system("clear");
        printf("\e[0;31mWrong format\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to create another account or 2 to exit\n");
    check1:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto noAccount;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check1;
        }
    }

    printf("\nEnter the account number:");
    scanf("%s", input);

    if (sscanf(input, "%d", &r.accountNbr) != 1) {
        system("clear");

        printf("\e[0;31mWrong format\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to create another account or 2 to exit\n");
    check2:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto noAccount;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check2;
        }
    }

    printf("\nEnter the country:");
    scanf("%s", r.country);

    printf("\nEnter the phone number:");
    scanf("%s", input);

    if (sscanf(input, "%d", &r.phone) != 1) {
        system("clear");
        
        printf("\e[0;31mWrong format\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to create another account or 2 to exit\n");
    check3:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto noAccount;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check3;
        }
    }

    printf("\nEnter amount to deposit: $");
    scanf("%s", input);

    if (sscanf(input, "%lf", &r.amount) != 1) {
        system("clear");
        
        printf("\e[0;31mWrong format\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to create another account or 2 to exit\n");
    check4:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto noAccount;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check4;
        }
    }
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);

    if (strcmp(r.accountType, "saving") != 0 && strcmp(r.accountType, "current") != 0 && strcmp(r.accountType, "fixed01") != 0 && strcmp(r.accountType, "fixed02") != 0 && strcmp(r.accountType, "fixed03") != 0) {
        system("clear");

        printf("\e[0;31mWrong Account Type !\e[0m\n");
        
        printf("\nWrite 0 to access the main menu or 1 to create another account or 2 to exit\n");
    check5:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto noAccount;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check5;
        }
    }

    int err = AddNewRecord(&r);
    if (err != 0)
    {
        system("clear");

        printf("\e[0;31mAn account already use this account Nbr\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to create another account or 2 to exit\n");
    check6:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto noAccount;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check6;
        }
    }

    printf("Account created successfully\nWrite 0 to access the main menu or 1 to exit\n");
check:
    scanf("%s", input);

    if (strcmp(input, "0") == 0) {
        mainMenu(u);
    } else if (strcmp(input, "1") == 0) {
        exit(1);
    } else {
        goto check;
    }
}

void UpdateAccount(struct User u)
{
    struct Record r;

    system("clear");

update:
    printf("\t\t\t===== Update Account =====\n");
    printf("\nEnter the account number:");
    
    char input[50];
    scanf("%s", input);

    if (sscanf(input, "%d", &r.accountNbr) != 1) {
        system("clear");
        printf("\e[0;31mWrong format\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to update another account or 2 to exit\n");
    check1:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto update;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check1;
        }
    }

    int err = GetRecordData(&r, u);
    if (err != 0 || r.id == 0)
    {
        system("clear");
        printf("\e[0;31mYou have no account with the number : %d\e[0m\n", r.accountNbr);
        
        printf("\nWrite 0 to access the main menu or 1 to update another account or 2 to exit\n");
    check2:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto update;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check2;
        }
    }

    printf("Previous Country was %s\nEnter the new country : ", r.country);
    scanf("%s", r.country);

    printf("Previous phone number was %d\nEnter the new phone number : ", r.phone);
    scanf("%s", input);

    if (sscanf(input, "%d", &r.phone) != 1) {
        system("clear");
        
        printf("\e[0;31mWrong format\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to update another account or 2 to exit\n");
    check3:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto update;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check3;
        }
    }

    err = UpdateRecord(&r);
    if (err != 0)
    {
        printf("\e[0;31mThere is an error in the program. Contact the administrator\e[0m");
        return;
    }

    printf("Account updated successfully\nWrite 0 to access the main menu or 1 to exit\n");
check:
    scanf("%s", input);

    if (strcmp(input, "0") == 0) {
        mainMenu(u);
    } else if (strcmp(input, "1") == 0) {
        exit(1);
    } else {
        goto check;
    }
}

void RemoveAccount(struct User u)
{
    struct Record r;

    system("clear");

remove:
    printf("\t\t\t===== Remove Account =====\n");
    printf("\nEnter the account number:");
    
    char input[50];
    scanf("%s", input);

    if (sscanf(input, "%d", &r.accountNbr) != 1) {
        system("clear");
        printf("\e[0;31mWrong format\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to remove another account or 2 to exit\n");
    check1:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto remove;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check1;
        }
    }

    int err = RemoveAccountInBDD(r.accountNbr, u);
    if (err != 0)
    {
        system("clear");
        printf("\e[0;31mYou have no account with the number : %d\e[0m\n", r.accountNbr);
        printf("\nWrite 0 to access the main menu or 1 to remove another account or 2 to exit\n");
    check2:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto remove;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check2;
        }
    }

    printf("Account removed successfully\nWrite 0 to access the main menu or 1 to exit\n");
    check:
    scanf("%s", input);

    if (strcmp(input, "0") == 0) {
        mainMenu(u);
    } else if (strcmp(input, "1") == 0) {
        exit(1);
    } else {
        goto check;
    }
}

void TransfertOwnerAccount(struct User u)
{
    struct Record r;
    struct User u2;

    system("clear");
transfert:
    printf("\t\t\t===== Transfert Account =====\n");
    printf("\nEnter the account number : ");
    
    char input[50];
    scanf("%s", input);

    if (sscanf(input, "%d", &r.accountNbr) != 1) {
        system("clear");
        printf("\e[0;31mWrong format\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to transfert another owner account or 2 to exit\n");
    check1:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto transfert;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check1;
        }
    }

    int err = GetRecordData(&r, u);
    if (err != 0 || r.id == 0)
    {
        system("clear");
        printf("\e[0;31mYou have no account with the number : %d\e[0m\n", r.accountNbr);
        
        printf("\nWrite 0 to access the main menu or 1 to transfert another owner account or 2 to exit\n");
    check2:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto transfert;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check2;
        }
    }

    printf("_____________________\n");
    printf("Account Number: %d\n", r.accountNbr);
    printf("Creation Account Date: %d/%d/%d\n", r.deposit.month, r.deposit.day, r.deposit.year);
    printf("Country : %s\n", r.country);
    printf("Phone number : %d\n", r.phone);
    printf("Amount deposited : $%.2lf\n", r.amount);
    printf("Type of Account : %s\n", r.accountType);
    printf("_____________________\n");

    printf("\nEnter the name of the new owner : ");
    scanf("%s", u2.name);

    err = GetUserData(&u2);
        if (err != 0)
    {
        system("clear");
        printf("\e[0;31mThere is no account owner named %d\e[0m\n", r.accountNbr);
        
        printf("\nWrite 0 to access the main menu or 1 to transfert another owner account or 2 to exit\n");
    check3:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto transfert;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check3;
        }
    }

    r.userId = u2.id;
    strcpy(r.name, u2.name);

    err = UpdateRecord(&r);
    if (err != 0)
    {
        system("clear");
        printf("\e[0;31mThere is an error in the program. Contact the administrator\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to transfert another owner account or 2 to exit\n");
    check4:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto transfert;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check4;
        }
    }

    printf("Owner account trasnferted successfully\nWrite 0 to access the main menu or 1 to exit\n");
    check:
    scanf("%s", input);

    if (strcmp(input, "0") == 0) {
        mainMenu(u);
    } else if (strcmp(input, "1") == 0) {
        exit(1);
    } else {
        goto check;
    }
}

void CheckDetails(struct User u)
{
    struct Record r;
    system("clear");

details:

    printf("\t\t\t===== Details Account =====\n");
    printf("\nEnter the account number : ");
    
    char input[50];
    scanf("%s", input);

    if (sscanf(input, "%d", &r.accountNbr) != 1) {
        system("clear");
        printf("\e[0;31mWrong format\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to check another account detail or 2 to exit\n");
    check1:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto details;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check1;
        }
    }

    int err = GetRecordData(&r, u);
    if (err != 0)
    {
        system("clear");
        printf("\e[0;31mYou have no account with the number : %d\e[0m\n", r.accountNbr);
        
        printf("\nWrite 0 to access the main menu or 1 to check another account detail or 2 to exit\n");
    check2:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto details;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check2;
        }
    }

    if (strcmp(r.accountType, "current") == 0) {
        printf("You will not get interests because the account is of type current");
    } else if (strcmp(r.accountType, "saving") == 0) {
        printf("You will get $%.2lf as interest on day %d of every month", (r.amount*0.07)/12, r.deposit.day);
    } else if (strcmp(r.accountType, "fixed01") == 0) {
        printf("You will get $%.2lf as interest on %d/%d/%d", r.amount*0.04, r.deposit.day, r.deposit.month, r.deposit.year);
    } else if (strcmp(r.accountType, "fixed02") == 0) {
        printf("You will get $%.2lf as interest on %d/%d/%d", (r.amount*0.05)*2, r.deposit.day, r.deposit.month, r.deposit.year+2);
    } else if (strcmp(r.accountType, "fixed03") == 0) {
        printf("You will get $%.2lf as interest on %d/%d/%d", (r.amount*0.08)*3, r.deposit.day, r.deposit.month, r.deposit.year+3);
    } else {
        system("clear");
        printf("\e[0;31mYou have no account with the number : %d\e[0m\n", r.accountNbr);
        
        printf("\nWrite 0 to access the main menu or 1 to check another account detail or 2 to exit\n");
    check3:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto details;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check3;
        }
    }

    printf("\nWrite 0 to access the main menu or 1 to exit\n");
check:
    scanf("%s", input);

    if (strcmp(input, "0") == 0) {
        mainMenu(u);
    } else if (strcmp(input, "1") == 0) {
        exit(1);
    } else {
        goto check;
    }
}

void CheckAllAccounts(struct User u)
{
    char input[50];
    struct Record *r[9];
    
    system("clear");

    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);

    int err = GetAllRecordsData(r, u);
    if (err != 0) {
        printf("\e[0;31mYou don't have any account!\e[0m\n");
        printf("Write 0 to access the main menu or 1 to exit\n");
    check1:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            system("clear");
            exit(1);
        } else {
            goto check1;
        }
    }
    
    printf("\nWrite 0 to access the main menu or 1 to exit\n");
check:
    scanf("%s", input);

    if (strcmp(input, "0") == 0) {
        mainMenu(u);
    } else if (strcmp(input, "1") == 0) {
        system("clear");
        exit(1);
    } else {
        goto check;
    }
}

void MakeTransaction(struct User u)
{
    system("clear");
    printf("What type of transaction do you want to do ?\n\n");
    printf("write 0 to return to the main menu\n");
    printf("Write 1 to deposit\n");
    printf("Write 2 to withdraw\n");
    printf("write 3 to make a transaction between 2 user\n");

    char input[50];
check:
    scanf("%s", input);
    
    if (strcmp(input, "0") == 0) {
        mainMenu(u);
    } else if (strcmp(input, "1") == 0) {
        Deposit(u);
    } else if (strcmp(input, "2") == 0) {
        WithDraw(u);
    } else if (strcmp(input, "3") == 0) {
        MakeTransactionBetweenTwoUser(u);
    } else {
        goto check;
    }
}

void MakeTransactionBetweenTwoUser(struct User u)
{
    struct Record rs;
    struct Record rr;
    
    system("clear");
transaction:
    printf("\t\t====== Transaction menu =====\n\n");

    printf("\nEnter the account number to be debited : ");
    
    char input[50];
    scanf("%s", input);

    if (sscanf(input, "%d", &rs.accountNbr) != 1) {
        system("clear");
        printf("\e[0;31mWrong format\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to make another transaction or 2 to exit\n");
    check1:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto transaction;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check1;
        }
    }

    int err = GetRecordData(&rs, u);
    if (err != 0 || rs.id == 0 || strcmp(rs.name, u.name) != 0)
    {
        system("clear");
        printf("\e[0;31mYou have no account with the number : %d\e[0m\n", rs.accountNbr);
        
        printf("\nWrite 0 to access the main menu or 1 to make another transaction or 2 to exit\n");
    check2:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto transaction;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check2;
        }
    } else if (strcmp(rs.accountType, "fixed01") == 0 || strcmp(rs.accountType, "fixed02") == 0 || strcmp(rs.accountType, "fixed03") == 0)
    {
        system("clear");
        printf("\e[0;31mYou can't make transaction with a fixed account\e[0m\n");
        
        printf("\nWrite 0 to access the main menu or 1 to make another transaction or 2 to exit\n");
    check3:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto transaction;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check3;
        }
    }

    printf("\nEnter the account number to be credited : ");
    scanf("%s", input);

    if (sscanf(input, "%d", &rr.accountNbr) != 1) {
        system("clear");
        printf("\e[0;31mWrong format\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to make another transaction or 2 to exit\n");
    check4:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto transaction;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check4;
        }
    }

    err = GetRecordData2(&rr, u);
    if (err != 0)
    {
        system("clear");
        printf("\e[0;31mThere is no account with the number : %d\e[0m\n", rr.accountNbr);
        
        printf("\nWrite 0 to access the main menu or 1 to make another transaction or 2 to exit\n");
    check5:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto transaction;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check5;
        }
    }

    int amountTransaction;
    printf("\nEnter the amount of the transaction : ");
    scanf("%s", input);

    if (sscanf(input, "%d", &amountTransaction) != 1) {
        system("clear");
        printf("\e[0;31mWrong format\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to make another transaction or 2 to exit\n");
    check6:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto transaction;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check6;
        }
    }

    rr.amount += amountTransaction;
    rs.amount -= amountTransaction;
    if (rs.amount < 0) {
        system("clear");
        printf("\e[0;31mError during the transaction\nYou give more than you have\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to make another transaction or 2 to exit\n");
    check7:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto transaction;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check7;
        }
    }

    err = UpdateRecordTransaction(&rr);
    if (err != 0) {
        system("clear");
        printf("\e[0;31mError during the transaction\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to make another transaction or 2 to exit\n");
    check8:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto transaction;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check8;
        }
    }

    err = UpdateRecordTransaction(&rs);
    if (err != 0) {
        system("clear");
        printf("\e[0;31mError during the transaction\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to make another transaction or 2 to exit\n");
    check9:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto transaction;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check9;
        }
    }

    printf("Transaction succed\nWrite 0 to access the main menu or 1 to exit\n");
check:
    scanf("%s", input);

    if (strcmp(input, "0") == 0) {
        mainMenu(u);
    } else if (strcmp(input, "1") == 0) {
        system("clear");
        exit(1);
    } else {
        goto check;
    }
}

void Deposit(struct User u)
{
    struct Record rs;
    
deposit:
    system("clear");
    printf("\t\t====== Deposit menu =====\n\n");

    printf("\nEnter the account number to deposit : ");
    
    char input[50];
    scanf("%s", input);

    if (sscanf(input, "%d", &rs.accountNbr) != 1) {
        system("clear");
        printf("\e[0;31mWrong format\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to make another deposit or 2 to exit\n");
    check1:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto deposit;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check1;
        }
    }

    int err = GetRecordData(&rs, u);
    if (err != 0 || rs.id == 0 || strcmp(rs.name, u.name) != 0)
    {
        system("clear");
        printf("\e[0;31mYou have no account with the number : %d\e[0m\n", rs.accountNbr);
        
        printf("\nWrite 0 to access the main menu or 1 to make another deposit or 2 to exit\n");
    check2:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto deposit;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check2;
        }
    }

    printf("\nEnter the amount to deposit : ");
    
    int amount;
    scanf("%s", input);

    if (sscanf(input, "%d", &amount) != 1) {
        system("clear");
        printf("\e[0;31mWrong format\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to make another deposit or 2 to exit\n");
    check3:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto deposit;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check3;
        }
    }

    rs.amount += amount;
    err = UpdateRecordTransaction(&rs);
    if (err != 0) {
        system("clear");
        printf("\e[0;31mError during the deposit\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to make another deposit or 2 to exit\n");
    check4:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto deposit;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check4;
        }
    }


    printf("Deposit succed\nWrite 0 to access the main menu or 1 to exit\n");
check:
    scanf("%s", input);

    if (strcmp(input, "0") == 0) {
        mainMenu(u);
    } else if (strcmp(input, "1") == 0) {
        system("clear");
        exit(1);
    } else {
        goto check;
    }
}

void WithDraw(struct User u)
{
    struct Record rs;
    
withdraw:
    system("clear");
    printf("\t\t====== Withdraw menu =====\n\n");

    printf("\nEnter the account number to withdraw : ");
    
    char input[50];
    scanf("%s", input);

    if (sscanf(input, "%d", &rs.accountNbr) != 1) {
        system("clear");
        printf("\e[0;31mWrong format\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to make another withdraw or 2 to exit\n");
    check1:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto withdraw;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check1;
        }
    }

    int err = GetRecordData(&rs, u);
    if (err != 0 || rs.id == 0 || strcmp(rs.name, u.name) != 0)
    {
        system("clear");
        printf("\e[0;31mYou have no account with the number : %d\e[0m\n", rs.accountNbr);
        
        printf("\nWrite 0 to access the main menu or 1 to make another withdraw or 2 to exit\n");
    check2:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto withdraw;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check2;
        }
    }

    printf("\nEnter the amount to withdraw : ");
    
    int amount;
    scanf("%s", input);

    if (sscanf(input, "%d", &amount) != 1) {
        system("clear");
        printf("\e[0;31mWrong format\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to make another withdraw or 2 to exit\n");
    check3:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto withdraw;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check3;
        }
    }

    rs.amount -= amount;
    err = UpdateRecordTransaction(&rs);
    if (err != 0) {
        system("clear");
        printf("\e[0;31mError during the withdraw\e[0m");
        
        printf("\nWrite 0 to access the main menu or 1 to make another withdraw or 2 to exit\n");
    check4:
        scanf("%s", input);

        if (strcmp(input, "0") == 0) {
            mainMenu(u);
        } else if (strcmp(input, "1") == 0) {
            goto withdraw;
        } else if (strcmp(input, "2") == 0) {
            exit(1);
        } else {
            goto check4;
        }
    }


    printf("Withdraw succed\nWrite 0 to access the main menu or 1 to exit\n");
check:
    scanf("%s", input);

    if (strcmp(input, "0") == 0) {
        mainMenu(u);
    } else if (strcmp(input, "1") == 0) {
        system("clear");
        exit(1);
    } else {
        goto check;
    }
}