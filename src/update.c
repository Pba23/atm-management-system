#include "header.h"

void updateAccountMenuAgain(struct User u)
{
    int i = 0;
    char input[10];
    char userName[100];
    struct Record r;
    int id;
    struct Record AllRecords[100];
    int numRecords = 0;
    int choice;
    FILE *pf = fopen(RECORDS, "r");
t:
    system("clear");

    printf("\t\t====== Update account, %s =====\n\n", u.name);
    printf("\n\n\nn\t\t\t\t✖ count not found!!\n");
    printf("\nEnter your account number again:");
    int counter;
    scanf("%d", &id);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && id == r.accountNbr)
        {
            printf("\n\t\t-->> What would you update / register :\n");
            printf("\n\t\t[1]- phone number\n");
            printf("\n\t\t[2]- country\n");
            printf("Choose an option: ");
            while (!i)
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
                        int phone;
                        printf("Give the new phone number:");
                        scanf("%d", &phone);
                        getAllRecords(AllRecords, &numRecords);
                        changeNumber(AllRecords, numRecords, phone, u, id);
                        success(u);

                        do
                        {
                            printf("\n\t\tEnter 0 to try again, 1 to return to the main menu, or 2 to exit: ");
                            if (scanf("%d", &choice) != 1)
                            {
                                printf("\nInvalid input. Please enter a valid option.\n");
                                while (getchar() != '\n')
                                    ;
                            }
                            else
                            {
                                switch (choice)
                                {
                                case 1:
                                    mainMenu(u);
                                    break;
                                case 2:
                                    exit(0);
                                    break;
                                default:
                                    printf("Invalid option. Please enter a valid option.\n");
                                    break;
                                }
                            }
                        } while (1);
                        i = 1;
                        break;
                    case 2:
                        char country[100];
                        printf("Give The new Country:");
                        scanf("%s", country);
                        getAllRecords(AllRecords, &numRecords);
                        changeCountry(AllRecords, numRecords, country, u, id);
                        success(u);

                        do
                        {
                            printf("\n\t\tEnter 0 to try again, 1 to return to the main menu, or 2 to exit: ");
                            if (scanf("%d", &choice) != 1)
                            {
                                printf("\nInvalid input. Please enter a valid option.\n");
                                while (getchar() != '\n')
                                    ;
                            }
                            else
                            {
                                switch (choice)
                                {
                                case 1:
                                    mainMenu(u);
                                    break;
                                case 2:
                                    exit(0);
                                    break;
                                default:
                                    printf("Invalid option. Please enter a valid option.\n");
                                    break;
                                }
                            }
                        } while (1);
                        i = 1;
                        break;
                    default:
                        printf("Please choose a valid option: ");
                        break;
                    }
                }
            }
            counter++;
        }
    }
    if (counter == 0)
    {
        updateAccountMenuAgain(u);
    }
}
void updateAccountMenu(struct User u)
{
    int boolean = 0;
    char input[10];
    char userName[100];
    struct Record r;
    int id;
    struct Record AllRecords[100];
    int numRecords = 0;
    int choice;
    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== Update account, %s =====\n\n", u.name);
    printf("\n\n\n\n\n\t\t\t\tEnter your account number:");
    int counter;
    scanf("%d", &id);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && id == r.accountNbr)
        {
            printf("\n\t\t-->> What would you update / register :\n");
            printf("\n\t\t[1]- phone number\n");
            printf("\n\t\t[2]- country\n");
            printf("Choose an option: ");
            while (!boolean)
            {
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';

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
                        int phone;
                        int opt;
                        system("clear");
                        printf("Give the new phone number:");
                        scanf("%d", &phone);
                        getAllRecords(AllRecords, &numRecords);
                        changeNumber(AllRecords, numRecords, phone, u, id);
                        success(u);

                        do
                        {
                            printf("\n\t\tEnter 0 to try again, 1 to return to the main menu, or 2 to exit: ");
                            if (scanf("%d", &choice) != 1)
                            {
                                printf("\nInvalid input. Please enter a valid option.\n");
                                while (getchar() != '\n')
                                    ;
                            }
                            else
                            {
                                switch (choice)
                                {
                                case 1:
                                    mainMenu(u);
                                    break;
                                case 2:
                                    exit(0);
                                    break;
                                default:
                                    printf("Invalid option. Please enter a valid option.\n");
                                    break;
                                }
                            }
                        } while (1);
                    case 2:
                        char country[100];
                        printf("Give The new Country:");
                        scanf("%s", country);
                        getAllRecords(AllRecords, &numRecords);
                        changeCountry(AllRecords, numRecords, country, u, id);
                        success(u);

                        do
                        {
                            printf("\n\t\tEnter 0 to try again, 1 to return to the main menu, or 2 to exit: ");
                            if (scanf("%d", &choice) != 1)
                            {
                                printf("\nInvalid input. Please enter a valid option.\n");
                                while (getchar() != '\n')
                                    ;
                            }
                            else
                            {
                                switch (choice)
                                {
                                case 1:
                                    mainMenu(u);
                                    break;
                                case 2:
                                    exit(0);
                                    break;
                                default:
                                    printf("Invalid option. Please enter a valid option.\n");
                                    break;
                                }
                            }
                        } while (1);
                        break;
                    default:
                        printf("Please choose a valid option: ");
                        break;
                    }
                }
                else
                {
                    printf("Choose a valid option: ");
                }
            }
            counter++;
        }
    }
    if (counter == 0)
    {
        updateAccountMenuAgain(u);
    }
}
