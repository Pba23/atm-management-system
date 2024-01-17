#include "header.h"
#include "system.c"
#include "update.c"
#include "transaction.c"
#include "auth.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

void initMenu(struct User *u)
{
    int r = 0;
    char input[10]; // Tableau de caractères pour stocker l'entrée de l'utilisateur

    system("clear");
    printf("%s\n\n\t\t======= ATM =======%s\n",CYAN,RESET);
    printf("%s\n\t\t-->> Feel free to login / register :%s\n",MAGENTA,RESET);
    printf("%s\n\t\t[1]- login%s\n",GREEN,RESET);
    printf("%s\n\t\t[2]- register%s\n",GREEN,RESET);
    printf("%s\n\t\t[3]- exit%s\n",RED,RESET);

    printf("Choose an option: ");
    while (!r)
    {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

        // Vérifier si la chaîne contient uniquement des chiffres
        int isNumeric = 1;
        for (int i = 0; input[i] != '\0'; i++)
        {
            if (input[i] < '0' || input[i] > '9')
            {
                isNumeric = 0;
                break;
            }
        }

        if (isNumeric)
        {
            int option = atoi(input);

            switch (option)
            {
            case 1:
                loginMenu(u->name, u->password);
                // if (strcmp(u->password, getPassword(*u)) == 0)
                // {
                //     printf("\n\nPassword Match!\n");
                // }
                // else
                // {
                //     printf("\nWrong password or User Name\n");

                //     exit(1);
                // }
                r = 1;
                break;
            case 2:
                registerMenu(u->name, u->password);
                mainMenu(*u);
                break;
            case 3:
                exit(1);
                break;
            default:
                printf("Choose a valid option: ");
                break;
            }
        }
        else
        {
            printf("Choose a valid option: ");
        }
    }
}
void mainMenu(struct User u)
{
    int option;
    char input[50]; // Chaine de caractères pour stocker l'entrée utilisateur

    while (1)
    {
        system("clear");
        printf("\n\n\t\t%s======= Welcome to our bank, Mr(s) %s =======%s\n\n", CYAN, u.name, RESET);
        printf("\n\t\t%s-->> Feel free to choose one of the options below <<--%s\n", MAGENTA, RESET);
        printf("\n\t\t%s[1]- Create a new account%s\n", GREEN, RESET);
        printf("\n\t\t%s[2]- Update account information%s\n", GREEN, RESET);
        printf("\n\t\t%s[3]- Check accounts%s\n", GREEN, RESET);
        printf("\n\t\t%s[4]- Check list of owned accounts%s\n", GREEN, RESET);
        printf("\n\t\t%s[5]- Make Transaction%s\n", GREEN, RESET);
        printf("\n\t\t%s[6]- Remove existing account%s\n", GREEN, RESET);
        printf("\n\t\t%s[7]- Transfer ownership%s\n", GREEN, RESET);
        printf("\n\t\t%s[8]- Exit%s\n", RED, RESET);
        printf("\n\t\t%s[9]- Log out%s\n", RED, RESET);
        printf("\nEnter your choice: ");

        if (fgets(input, sizeof(input), stdin))
        {
            input[strcspn(input, "\n")] = '\0'; // Retirer le saut de ligne s'il est présent

            if (isNumber(input))
            {
                option = atoi(input); // Convertir la chaîne en entier
                switch (option)
                {
                case 1:
                    createNewAcc(u);
                    break;
                case 2:
                    updateAccountMenu(u);
                    break;
                case 3:
                    countDetail(u);
                    break;
                case 4:
                    checkAllAccounts(u);
                    break;
                case 5:
                    transactionMenu(u);
                    break;
                case 6:
                    removeAccount(u);
                    break;
                case 7:
                    transferOwner(u);
                    break;
                case 8:
                    exit(0); // Utilisation de 0 pour une sortie propre
                    break;
                case 9:
                    initMenu(&u);
                    break;
                default:
                    printf("Invalid operation!\n");
                }
            }
            else
            {
                printf("Please enter a valid number.\n");
            }
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
