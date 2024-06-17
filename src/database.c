#include "header.h"

int InitDatabase()
{
    sqlite3 *db;

    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        sqlite3_close(db);
        return rc;
    }

    char *request = "CREATE TABLE IF NOT EXISTS `User` (`Id` INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL, `Name` TEXT UNIQUE NOT NULL, `Mdp` TEXT NOT NULL);\
    CREATE TABLE IF NOT EXISTS `Records` (`Id` INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL, `Id_User` INTEGER NOT NULL REFERENCES `User`(`Id`), `Name` TEXT UNIQUE NOT NULL REFERENCES `User`(`Name`), `Account_Id` INTEGER UNIQUE NOT NULL, `Creation_Date` TEXT NOT NULL, `Country` TEXT NOT NULL, `Phone` TEXT NOT NULL, `Balance` INTEGER NOT NULL DEFAULT 0, `Account_Type` TEXT NOT NULL);";
    char *errMsg = 0;

    rc = sqlite3_exec(db, request, NULL, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        printf("%s", errMsg);
        sqlite3_close(db);
        return rc;
    }

    sqlite3_close(db);
    return 0;
};

int AddUserInBDD(struct User *u)
{
    sqlite3 *db;
    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        sqlite3_close(db);
        return rc;
    }

    char *errMsg;

    char *request = malloc(100);
    if (request == NULL) {
        // Gestion de l'erreur d'allocation mémoire
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sprintf(request, "INSERT INTO `USER`(`Name`, `Mdp`) VALUES('%s','%ld')", u->name, hash(u->password));
    
    rc = sqlite3_exec(db, request, NULL, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        printf("%s", errMsg);

        sqlite3_close(db);
        return rc;
    }

    free(request);

    sqlite3_close(db);
    return 0;
}

// Fonction de rappel personnalisée
int callback(void *data, int useless1, char **argv, char **useless2){
    struct User *user = (struct User *)data;

    // Stocker les valeurs des colonnes dans la structure de données
    user->id = atoi(argv[0]);
    strcpy(user->name, argv[1]);
    strcpy(user->password, argv[2]);

    return 0;
}

int SelectUserInBDD(char name[50], char password[50], struct User *u)
{
    sqlite3 *db;
    char *errMsg;

    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        sqlite3_close(db);
        return rc;
    }

    char *request = malloc(100);
    if (request == NULL) {
        // Gestion de l'erreur d'allocation mémoire
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sprintf(request, "SELECT `Id`, `Name`, `Mdp` FROM `USER` WHERE `Name`='%s' AND `Mdp`='%ld'", name, hash(password));
    rc = sqlite3_exec(db, request, callback, u, &errMsg);
    if (rc != SQLITE_OK)
    {
        printf("%s", errMsg);

        sqlite3_close(db);
        return rc;
    }

    sqlite3_close(db);

    if (strlen(u->name) == 0 || strlen(u->password) == 0) {
        return 1;
    }
    return 0;
}

unsigned long hash(char password[50])
{
    unsigned long res = 5381;
    int c;

    // on va se déplacer dans le char caractère par caractère
    while (c = *password++)
    {
        // on déplace de 5 bits vers la gauche, on l'ajoute à lui même et on ajoute la valeur ansi du caractère courrant (qui est stocké dans c)
        res = ((res << 5) + res) + c;
    }
    
    return res;
}

int AddNewRecord(struct Record *r)
{
    sqlite3 *db;
    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        sqlite3_close(db);
        return rc;
    }

    char *request = malloc(200);
    if (request == NULL) {
        // Gestion de l'erreur d'allocation mémoire
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    char *errMsg;

    sprintf(request, "INSERT INTO `Records`(`Id_User`,`Name`,`Account_Id`,`Creation_Date`,`Country`,`Phone`,`Balance`,`Account_Type`) VALUES('%d','%s','%d','%d/%d/%d','%s','%d','%f','%s')", r->userId, r->name, r->accountNbr, r->deposit.month, r->deposit.day, r->deposit.year, r->country, r->phone, r->amount, r->accountType);
    int err = sqlite3_exec(db, request, NULL, 0, &errMsg);
    if (err != SQLITE_OK)
    {
        return err;
    }


    free(request);

    sqlite3_close(db);
    return 0;
}

// Fonction de rappel personnalisée
int callback2(void *data, int useless1, char **argv, char **useless2){
    struct Record *record = (struct Record *)data;
    char date[30];

    // Stocker les valeurs des colonnes dans la structure de données
    record->id = atoi(argv[0]);
    strcpy(record->name, argv[1]);
    strcpy(date, argv[2]);
    strcpy(record->country, argv[3]);
    record->phone = atoi(argv[4]);
    record->amount = atof(argv[5]);
    strcpy(record->accountType, argv[6]);

    sscanf(date, "%d/%d/%d", &record->deposit.month, &record->deposit.day, &record->deposit.year);

    return 0;
}

int GetRecordData(struct Record *r, struct User u)
{
    sqlite3 *db;
    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        sqlite3_close(db);
        return rc;
    }

    char *request = malloc(200);
    char *errMsg;
    if (request == NULL) {
        // Gestion de l'erreur d'allocation mémoire
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sprintf(request, "SELECT `Id`, `Name`, `Creation_Date`, `Country`, `Phone`, `Balance`, `Account_Type` FROM `Records` WHERE `Id_User`='%d' AND `Account_Id`='%d'", u.id, r->accountNbr);
    rc = sqlite3_exec(db, request, callback2, r, &errMsg);
    if (rc != SQLITE_OK)
    {
        sqlite3_close(db);
        return rc;
    }
    
    sqlite3_close(db);
    return 0;
}

int UpdateRecord(struct Record *r)
{
    sqlite3 *db;
    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        sqlite3_close(db);
        return rc;
    }

    char *request = malloc(200);
    char *errMsg;
    if (request == NULL) {
        // Gestion de l'erreur d'allocation mémoire
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sprintf(request, "Update `Records` SET `Id_User`='%d', `Name`='%s', `Country`='%s', `Phone`='%d' WHERE `Id`='%d'", r->userId, r->name, r->country, r->phone, r->id);
    rc = sqlite3_exec(db, request, NULL, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        printf("%s\n", errMsg);
        sqlite3_close(db);
        return rc;
    }
    
    sqlite3_close(db);
    return 0;
}

int RemoveAccountInBDD(int accountNbr, struct User u)
{
    sqlite3 *db;
    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        sqlite3_close(db);
        return rc;
    }

    char *request = malloc(200);
    char *errMsg;
    if (request == NULL) {
        // Gestion de l'erreur d'allocation mémoire
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sprintf(request, "DELETE FROM `Records` WHERE `Id_User`='%d' AND `Account_Id`='%d'", u.id, accountNbr);
    rc = sqlite3_exec(db, request, NULL, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        sqlite3_close(db);
        return rc;
    }
    
    sqlite3_close(db);
    return 0;
}

int GetUserData(struct User *u)
{
    sqlite3 *db;
    char *errMsg;

    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        sqlite3_close(db);
        return rc;
    }

    char *request = malloc(100);
    if (request == NULL) {
        // Gestion de l'erreur d'allocation mémoire
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sprintf(request, "SELECT `Id`, `Name`, `Mdp` FROM `USER` WHERE `Name`='%s'", u->name);
    rc = sqlite3_exec(db, request, callback, u, &errMsg);
    if (rc != SQLITE_OK)
    {
        printf("%s", errMsg);

        sqlite3_close(db);
        return rc;
    }

    sqlite3_close(db);

    if (strlen(u->password) == 0 || strlen(u->name) == 0) {
        return 1;
    }
    return 0;
}

// Fonction de rappel personnalisée
int callback3(void *data, int useless1, char **argv, char **useless2){
    struct Record *record[9];
    memcpy(record, data, sizeof(struct Record*) * 9);

    int count = 0;
    // Stocker les valeurs des colonnes dans la structure de données
    for (int i = 0; i < sizeof(argv);)
    {
        printf("_____________________\n");
        printf("Account Number: %d\n", atoi(argv[i+3]));
        printf("Creation Account Date: %s\n", argv[4]);
        printf("Country : %s\n", argv[i+5]);
        printf("Phone number : %d\n", atoi(argv[i+6]));
        printf("Amount deposited : $%.2lf\n", atof(argv[i+7]));
        printf("Type of Account : %s\n", argv[i+8]);

        i += 8;
    }

    return 0;
}

int GetAllRecordsData(struct Record *r[9], struct User u) 
{
    sqlite3 *db;
    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        sqlite3_close(db);
        return rc;
    }

    char *request = malloc(200);
    char *errMsg;
    if (request == NULL) {
        // Gestion de l'erreur d'allocation mémoire
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sprintf(request, "SELECT * FROM `Records` WHERE `Id_User`='%d'", u.id);
    rc = sqlite3_exec(db, request, callback3, r, &errMsg);
    if (rc != SQLITE_OK)
    {
        sqlite3_close(db);
        return rc;
    }
    
    sqlite3_close(db);
    return 0;
}

int UpdateRecordTransaction(struct Record *r)
{
    sqlite3 *db;
    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        sqlite3_close(db);
        return rc;
    }

    char *request = malloc(200);
    char *errMsg;
    if (request == NULL) {
        // Gestion de l'erreur d'allocation mémoire
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sprintf(request, "Update `Records` SET `Balance`='%.2lf' WHERE `Id`='%d'", r->amount, r->id);
    rc = sqlite3_exec(db, request, NULL, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        printf("%s\n", errMsg);
        sqlite3_close(db);
        return rc;
    }
    
    sqlite3_close(db);
    return 0;
}

int GetRecordData2(struct Record *r, struct User u)
{
    sqlite3 *db;
    int rc = sqlite3_open("database.db", &db);
    if (rc) {
        sqlite3_close(db);
        return rc;
    }

    char *request = malloc(200);
    char *errMsg;
    if (request == NULL) {
        // Gestion de l'erreur d'allocation mémoire
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    sprintf(request, "SELECT `Id`, `Name`, `Creation_Date`, `Country`, `Phone`, `Balance`, `Account_Type` FROM `Records` WHERE `Account_Id`='%d'", r->accountNbr);
    rc = sqlite3_exec(db, request, callback2, r, &errMsg);
    if (rc != SQLITE_OK)
    {
        sqlite3_close(db);
        return rc;
    }
    
    sqlite3_close(db);
    return 0;
}