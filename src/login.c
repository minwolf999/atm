#include "header.h"

void Login_Menu(struct User *u) 
{
    int r, option;
    system("clear");

menu:
    printf("\n\n\t\t======= ATM =======\n");
    printf("\n\t\t-->> Feel free to login / register :\n");
    printf("\n\t\t[1]- login\n");
    printf("\n\t\t[2]- register\n");
    printf("\n\t\t[3]- exit\n");

    scanf("%d", &option);
    switch (option)
    {
        case 1:
            Login(u);
            r = 1;
            break;
            
        case 2:
            Register(u);
            r = 1;
            break;

        case 3:
            exit(1);
            break;

        default:
            system("clear");
            printf("\e[0;31mInsert a valid operator\e[0m\n");
            goto menu;
    }

};

void Register(struct User *u) 
{
    char name[50], password[50];
    struct termios nflags, oflags;

    system("clear");

regis:
    printf("\n\n\t\t===== Register =====\n\n");

    printf("Username : ");
    scanf("%s", u->name);

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }

    printf("\nPassword : ");
    scanf("%s", u->password);

    // restore terminal parameters
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }

    int err = AddUserInBDD(u);
    if (err)
    {
        system("clear");
        goto regis;
    }

    SelectUserInBDD(u->name, u->password, u);
};

void Login(struct User *u) 
{
    struct termios nflags, oflags;
    
    system("clear");

login:
    printf("\n\n\t\t====== Login ======\n\n");

    char name[50];
    char password[50];

    printf("Username : ");
    scanf("%s", name);

    printf("Password : ");

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }

    scanf("%s", password);

    // restore terminal parameters
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }

    int err = SelectUserInBDD(name, password, u);
    if (err != 0)
    {
        system("clear");
        printf("\e[0;31mUsername or Password incorrect !\e[0m");
        goto login;
    }
};