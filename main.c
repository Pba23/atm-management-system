#include "header.h"
#include "system.c"
#include "auth.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
        createNewAcc(u);
        break;
    case 2:
        updateAccountMenu(u);
        break;
    case 3:
        // student TODO : add your **Check the details of existing accounts** function
        // here
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        // student TODO : add your **Make transaction** function
        // here
        break;
    case 6:
        // student TODO : add your **Remove existing account** function
        // here
        break;
    case 7:
        // student TODO : add your **Transfer owner** function
        // here
        break;
    case 8:
        exit(1);
        break;
    default:
        printf("Invalid operation!\n");
    }
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initMenu(struct User *u) {
    int r = 0;
    char input[10]; // Tableau de caractères pour stocker l'entrée de l'utilisateur

    system("clear");
    printf("\n\n\t\t======= ATM =======\n");
    printf("\n\t\t-->> Feel free to login / register :\n");
    printf("\n\t\t[1]- login\n");
    printf("\n\t\t[2]- register\n");
    printf("\n\t\t[3]- exit\n");

    printf("Choose an option: ");
    while (!r) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

        // Vérifier si la chaîne contient uniquement des chiffres
        int isNumeric = 1;
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] < '0' || input[i] > '9') {
                isNumeric = 0;
                break;
            }
        }

        if (isNumeric) {
            int option = atoi(input);

            switch (option) {
                case 1:
                    loginMenu(u->name, u->password);
                    if (strcmp(u->password, getPassword(*u)) == 0) {
                        printf("\n\nPassword Match!\n");
                    } else {
                        printf("\nWrong password or User Name\n");
                        exit(1);
                    }
                    r = 1;
                    break;
                case 2:
                    registerMenu(u->name, u->password);
                    break;
                case 3:
                    exit(1);
                    break;
                default:
                     printf("Choose a valid option: ");
                    break;
            }
        }else {
             printf("Choose a valid option: ");
        }
    }
}

//  struct User *users = readUserData("./data.users", 2);
int main()
{
    struct User u;

    initMenu(&u);
    mainMenu(u);
    return 0;
}
