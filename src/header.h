#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sqlite3.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    int phone;
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// authentication functions
void Login_Menu(struct User *u);
void Register(struct User *u);
void Login(struct User *u);

unsigned long hash(char password[50]);

// database functions
int InitDatabase();
int AddUserInBDD(struct User *u);
int SelectUserInBDD(char name[50], char password[50], struct User *u);
int AddNewRecord(struct Record *r);
int GetRecordData(struct Record *r, struct User u);
int UpdateRecord(struct Record *r);
int RemoveAccountInBDD(int accountNbr, struct User u);
int GetUserData(struct User *u);
int GetAllRecordsData(struct Record *r[9], struct User u);
int UpdateRecordTransaction(struct Record *r);
int GetRecordData2(struct Record *r, struct User u);

// User utilisation
void mainMenu(struct User u);
void CreateNewAcc(struct User u);
void UpdateAccount(struct User u);
void TransfertOwnerAccount(struct User u);
void CheckDetails(struct User u);
void CheckAllAccounts(struct User u);
void MakeTransaction(struct User u);
void MakeTransactionBetweenTwoUser(struct User u);
void Deposit(struct User u);
void WithDraw(struct User u);
void RemoveAccount(struct User u);