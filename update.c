#include "header.h"
#define RED "\033[1;31m"
#define RESET "\033[0m"

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
    char input[1000];
    char number[1000];
    char phoneNumber[2000];
    char userName[1000];
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
            printf("✖%sInvalid input. Please enter a valid option.%s\n",RED,RESET);
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
                                        printf("✖%sPlease enter a valid phone number, up to 15 digits with no spaces.%s\n",RED,RESET);
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
                                        printf("\n✖%sInvalid input. Please enter a valid option.%s\n",RED,RESET);
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
                                            printf("✖%sInvalid option. Please enter a valid option.%s\n",RED,RESET);
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
                                        printf("✖%sPlease enter a valid country , up to 15 letter with no spaces.%s\n",RED,RESET);
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
                                        printf("\n✖%sInvalid input. Please enter a valid option.%s\n",RED,RESET);
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
                                            printf("✖%sInvalid option. Please enter a valid option.%s\n",RED,RESET);
                                            break;
                                        }
                                    }
                                } while (1);
                                re = 1;
                                break;
                            default:
                                printf("%sPlease choose a valid option:%s ",RED,RESET);
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
        printf("%s",RED);
        strcpy(error, "\n✖ account number not found in yours!!\n");
        printf("%s",error);
        printf("%s",RESET);
        fail(u);
        // updateAccountMenu(u);
    }
    
}
