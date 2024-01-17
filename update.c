#include "header.h"
bool isNumericString2(const char *str)
{
    while (*str)
    {
        if (!isdigit(*str))
        {
            return false;
        }
        str++;
    }
    return true;
}
char error[50] = "";
void updateAccountMenu(struct User u)
{
    int re = 0;
    char input[10];
    char number[10];
    char phoneNumber[20];
    char userName[100];
    struct Record r;
    int id;
    struct Record AllRecords[100];
    int numRecords = 0;
    int choice;
    int j = 1;
    int counter;
    FILE *pf = fopen(RECORDS, "r");
t:
    system("clear");

    printf("\t\t%s====== Update an account for you %s =====%s\n\n",MAGENTA, u.name,RESET);
    printf("%s", error);
    do
    {

        printf("\nEnter your account number:");
        fgets(number, sizeof(number), stdin);
        number[strcspn(number, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

        // Vérifier si la chaîne contient uniquement des chiffres
        int isvalid = 1;
        for (int i = 0; number[i] != '\0'; i++)
        {
            if (number[i] < '0' || number[i] > '9')
            {
                isvalid = 0;
                break;
            }
        }

        if (!isvalid)
        {
            printf("Invalid input. Please enter a valid option.\n");
            // while (getchar() != '\n')
            //     ; // Vide le tampon d'entrée
        }
        else
        {
            id = atoi(number);
            while (getAccountFromFile(pf, userName, &r) && j == 1)
            {

                if (strcmp(userName, u.name) == 0 && id == r.accountNbr)
                {
                    while (!re)
                    {
                        printf("\n\t\t-->> What would you update / register :\n");
                        printf("\n\t\t[1]- phone number\n");
                        printf("\n\t\t[2]- country\n");
                        printf("Choose an option: ");
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
                                bool validPhone = false;
                                while (!validPhone)
                                {
                                    printf("\nEnter the new phone number (up to 15 digits with no spaces): ");
                                    if (fgets(phoneNumber, sizeof(phoneNumber), stdin))
                                    {
                                        phoneNumber[strcspn(phoneNumber, "\n")] = '\0'; // Retirer le saut de ligne s'il est présent
                                        if (strlen(phoneNumber) <= 15 && isValidNumber(phoneNumber))
                                        {
                                            validPhone = true;
                                        }
                                    }
                                    if (!validPhone)
                                    {
                                        printf("Please enter a valid phone number, up to 15 digits with no spaces.\n");
                                    }
                                }
                               
                                getAllRecords(AllRecords, &numRecords);
                                changeNumber(AllRecords, numRecords, phoneNumber, u, id);
                                // success(u);

                                do
                                {
                                    printf("\n\t\t1 to return to the main menu, or 2 to exit: ");
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
                                re = 1;
                                break;
                            case 2:
                                char country[100];
                                bool validcountry = false;
                                while (!validcountry)
                                {
                                    printf("\nEnter the country : ");
                                    if (fgets(country, sizeof(country), stdin))
                                    {
                                        country[strcspn(country, "\n")] = '\0'; // Retirer le saut de ligne s'il est présent
                                        if (strlen(country) <= 15 && isValidCountry(country))
                                        {
                                            validcountry = true;
                                        }
                                    }
                                    if (!validcountry)
                                    {
                                        printf("Please enter a valid country , up to 15 letter with no spaces.\n");
                                    }
                                }

                                getAllRecords(AllRecords, &numRecords);
                                changeCountry(AllRecords, numRecords, country, u, id);
                                // success(u);

                                do
                                {
                                    printf("\n\t\t 1 to return to the main menu, or 2 to exit: ");
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
                                re = 1;
                                break;
                            default:
                                printf("Please choose a valid option: ");
                                break;
                            }
                        }
                        else
                        {
                            printf("not numeric");
                        }
                    }
                    counter++;
                }
            }
            break;
        }
    } while (1);

    if (counter == 0)
    {
        // error = "\n✖ Record not found!!\n";
        strcpy(error, "\n✖ account number not found in yours!!\n");
        updateAccountMenu(u);
    }
    
}
