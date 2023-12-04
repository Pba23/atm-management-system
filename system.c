#include "header.h"
#include <stdbool.h>
#include <ctype.h>
const char *RECORDS = "./data/records.txt";
int isNumber(const char *input)
{
    while (*input)
    {
        if (!isdigit(*input))
        {
            return 0; // Ce n'est pas un nombre
        }
        input++;
    }
    return 1; // Tous les caractères sont des chiffres
}
int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
                  &r->userId,
                  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}
bool isValidAmount(const char *amount)
{
    int len = strlen(amount);
    int dotCount = 0;

    for (int i = 0; i < len; ++i)
    {
        if (!isdigit(amount[i]))
        {
            if (amount[i] == '.')
            {
                dotCount++;
                if (dotCount > 1)
                {
                    return false; // Plus d'un point décimal
                }
            }
            else
            {
                return false; // Contient des caractères non numériques autres que le point décimal
            }
        }
    }

    return true; // Valide s'il n'y a pas plus d'un point et que tous les caractères sont des chiffres ou un seul point
}
void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
            r.id,
            u.id,
            u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}
void stayOrQuit(struct User u)
{
    int choice;
    do
    {
        printf("\n\t\tEnter 1 to return to the main menu, or 2 to exit: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a valid option.\n");
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
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success !\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}
void getAllRecords(struct Record AllRecords[], int *numRecords)
{
    FILE *fp;
    char filename[] = "./data/records.txt"; // Nom du fichier
    int count = 0;                          // Compteur du nombre d'utilisateurs

    // Ouvrir le fichier en mode lecture
    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("Error oppenning file : %s\n", filename);
        exit(1);
    }

    // Lire les données du fichier
    while (fscanf(fp, "%d %d %99s %d %d/%d/%d %99s %d %lf %9s",
                  &AllRecords[count].id,
                  &AllRecords[count].userId,
                  AllRecords[count].name,
                  &AllRecords[count].accountNbr,
                  &AllRecords[count].deposit.day,
                  &AllRecords[count].deposit.month,
                  &AllRecords[count].deposit.year,
                  AllRecords[count].country,
                  &AllRecords[count].phone,
                  &AllRecords[count].amount,
                  AllRecords[count].accountType) == 11)
    {
        count++;
    }
    // Fermer le fichier
    fclose(fp);

    // Mettre à jour le nombre d'utilisateurs
    *numRecords = count;
}
// struct Date
// {
//     int month;
//     int day;
//     int year;
// };

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
bool isValidNumber(const char *accountNumber)
{
    int len = strlen(accountNumber);
    for (int i = 0; i < len; ++i)
    {
        if (!isdigit(accountNumber[i]))
        {
            return false; // Contient des caractères non numériques
        }
    }
    return true; // Tous les caractères sont des chiffres
}

bool isValidDate(struct Date date)
{
    if (date.year < 0)
        return false;
    if (date.month < 1 || date.month > 12)
        return false;

    int daysInMonth[] = {0, 31, 28 + isLeapYear(date.year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (date.day < 1 || date.day > daysInMonth[date.month])
        return false;

    return true;
}
bool isValidPhoneNumber(const char *phone)
{
    // Vérifie si tous les caractères sont des chiffres et que la longueur ne dépasse pas 15
    int len = strlen(phone);
    if (len > 15)
    {
        return false; // Trop long
    }

    for (int i = 0; i < len; ++i)
    {
        if (!isdigit(phone[i]))
        {
            return false; // Contient des caractères non numériques
        }
    }
    return true; // Tous les caractères sont des chiffres et la longueur est valide
}
bool isValidAccountType(const char *accountType)
{
    const char *validTypes[] = {"saving", "current", "fixed01", "fixed02", "fixed03"};
    int numValidTypes = sizeof(validTypes) / sizeof(validTypes[0]);

    for (int i = 0; i < numValidTypes; ++i)
    {
        if (strcmp(accountType, validTypes[i]) == 0)
        {
            return true; // Trouvé un type de compte valide
        }
    }

    return false; // Aucun type de compte valide trouvé
}
bool isNumericString(const char *str)
{
    while (*str)
    {
        if (!isdigit(*str) && *str != '/')
        {
            return false;
        }
        str++;
    }
    return true;
}
bool isValidCountry(const char *country)
{
    size_t length = strlen(country);

    if (length > 15)
    {
        return false; // Dépassement de la longueur maximale
    }

    for (size_t i = 0; i < length; ++i)
    {
        if (!isalpha(country[i]))
        {
            return false; // Caractères non alphabétiques (y compris les espaces)
        }
    }

    return true;
}
void createNewAcc(struct User u)
{
    struct Record r;
    struct Record AllRecords[100];
    int num;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");
    char phoneNumber[20];
    char countNumber[20];
    char country[20];
    char dateInput[15]; // Chaine pour stocker la saisie de la date
    int re = 0;

noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");
    // recuperation de la date
    bool validDate = false;
    while (!validDate)
    {
        printf("\nEnter today's date (dd/mm/yyyy): ");
        if (fgets(dateInput, sizeof(dateInput), stdin))
        {
            dateInput[strcspn(dateInput, "\n")] = '\0'; // Retirer le saut de ligne s'il est présent
            if (strlen(dateInput) == 10 && dateInput[2] == '/' && dateInput[5] == '/' && isNumericString(dateInput))
            {
                if (sscanf(dateInput, "%d/%d/%d", &r.deposit.day, &r.deposit.month, &r.deposit.year) == 3)
                {
                    validDate = isValidDate(r.deposit);
                }
            }
        }
        if (!validDate)
        {
            printf("Please enter a valid date in the format 'dd/mm/yyyy'.\n");
        }
    }
    // recuperation du numero de compte
    bool validnumber = false;
    // bool exist = true;
    while (!validnumber)
    {
        printf("\nEnter the account number: ");
        if (fgets(countNumber, sizeof(countNumber), stdin))
        {
            countNumber[strcspn(countNumber, "\n")] = '\0'; // Retirer le saut de ligne s'il est présent
            if (isValidNumber(countNumber))
            {
                validnumber = true;
            }
        }
        if (!validnumber)
        {
            printf("Please enter a valid number\n");
        }

        sscanf(countNumber, "%d", &r.accountNbr);
        while (getAccountFromFile(pf, userName, &cr))
        {
            if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
            {
                printf("✖ This Account already exists for this user\n\n");
                validnumber = false;
                goto noAccount;
            }
        }
    }
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
        sscanf(country, "%s", r.country);
    }

    bool validPhone = false;
    int phone;
    while (!validPhone)
    {
        printf("\nEnter the phone number (up to 15 digits with no spaces): ");
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
        r.phone = atoi(phoneNumber);
        
    }
    char amountInput[20]; // Pour stocker la saisie du montant
    do
    {
        printf("\nEnter amount to deposit: $");
        fgets(amountInput, sizeof(amountInput), stdin);

        amountInput[strcspn(amountInput, "\n")] = '\0'; // Supprimer le saut de ligne s'il est présent

        // Vérification de la validité du montant
        if (!isValidAmount(amountInput) || atof(amountInput)== 0)
        {
            printf("Invalid amount. Please enter a valid decimal superior to 0 number.\n");
        }
        else
        {
            break;
        }

    } while (1);

    r.amount = atof(amountInput); // Conversion en double
    char accountTypeInput[20];    // Pour stocker la saisie du type de compte
    do
    {
        printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice: ");
        fgets(accountTypeInput, sizeof(accountTypeInput), stdin);
        accountTypeInput[strcspn(accountTypeInput, "\n")] = '\0';
        // Vérification de la validité du type de compte
        if (!isValidAccountType(accountTypeInput))
        {
            printf("Invalid account type. Please choose a valid account type.\n");
        }
        else
        {
        sscanf(accountTypeInput, "%s", r.accountType);
            break;
        }
    } while (1);

    getAllRecords(AllRecords, &num);
    r.id = num;
    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}

void changeCountry(struct Record AllRecords[], int numRecords, char country[100], struct User u, int accountNumber)
{
    FILE *fp;
    char filename[] = "./data/records.txt";

    if ((fp = fopen(filename, "w")) == NULL)
    {
        printf("Error oppenning file : %s\n", filename);
        return;
    }

    for (int i = 0; i < numRecords; i++)
    {
        if (strcmp(AllRecords[i].name, u.name) == 0 && AllRecords[i].accountNbr == accountNumber)
        {
            fprintf(fp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                    AllRecords[i].id, AllRecords[i].userId, AllRecords[i].name, AllRecords[i].accountNbr,
                    AllRecords[i].deposit.day, AllRecords[i].deposit.month, AllRecords[i].deposit.year,
                    country, AllRecords[i].phone, AllRecords[i].amount, AllRecords[i].accountType);
        }
        else
        {
            fprintf(fp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                    AllRecords[i].id, AllRecords[i].userId, AllRecords[i].name, AllRecords[i].accountNbr,
                    AllRecords[i].deposit.day, AllRecords[i].deposit.month, AllRecords[i].deposit.year,
                    AllRecords[i].country, AllRecords[i].phone, AllRecords[i].amount, AllRecords[i].accountType);
        }
    }

    fclose(fp);
}
void changeNumber(struct Record AllRecords[], int numRecords, int number, struct User u, int accountNumber)
{
    FILE *fp;
    char filename[] = "./data/records.txt";

    if ((fp = fopen(filename, "w")) == NULL)
    {
        printf("Error oppenning file : %s\n", filename);
        return;
    }

    for (int i = 0; i < numRecords; i++)
    {
        if (strcmp(AllRecords[i].name, u.name) == 0 && AllRecords[i].accountNbr == accountNumber)
        {
            fprintf(fp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                    AllRecords[i].id, AllRecords[i].userId, AllRecords[i].name, AllRecords[i].accountNbr,
                    AllRecords[i].deposit.day, AllRecords[i].deposit.month, AllRecords[i].deposit.year,
                    AllRecords[i].country, number, AllRecords[i].amount, AllRecords[i].accountType);
        }
        else
        {
            fprintf(fp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                    AllRecords[i].id, AllRecords[i].userId, AllRecords[i].name, AllRecords[i].accountNbr,
                    AllRecords[i].deposit.day, AllRecords[i].deposit.month, AllRecords[i].deposit.year,
                    AllRecords[i].country, AllRecords[i].phone, AllRecords[i].amount, AllRecords[i].accountType);
        }
    }

    fclose(fp);
}

void interestMessage(struct Record r)
{
    float value;
    if (strcmp(r.accountType, "current") == 0)
    {
        printf("You will not get interests because the account is of type current");
    }
    else
    {
        float interest;
        if (strcmp(r.accountType, "saving") == 0)
        {
            interest = 0.07;
            value = r.amount * interest / 12;
            printf("You will get $%.2f as interest on day %d of every month", value, r.deposit.day);
        }
        else if (strcmp(r.accountType, "fixed01") == 0)
        {
            interest = 0.04;
            value = r.amount * interest;
            printf("You will get $%.2f as interest on %d/%d/%d of every month", value, r.deposit.day, r.deposit.month, r.deposit.year + 1);
        }
        else if (strcmp(r.accountType, "fixed02") == 0)
        {
            interest = 0.05;
            value = r.amount * interest * 2;
            printf("You will get $%.2f as interest on %d/%d/%d of every month", value, r.deposit.day, r.deposit.month, r.deposit.year + 2);
        }
        else if (strcmp(r.accountType, "fixed03") == 0)
        {
            interest = 0.08;
            value = r.amount * interest * 3;
            printf("You will get $%.2f as interest on %d/%d/%d of every month", value, r.deposit.day, r.deposit.month, r.deposit.year + 3);
        }
    }
}
char error[50];
void countDetail(struct User u)
{
    char userName[100];
    char number[50];
    FILE *pf = fopen(RECORDS, "r");
    struct Record r;
    int id;
    int count = 0;
    system("clear");
    printf("\t\t====== Account datail =====\n\n");
    printf("%s", error);
    do
    {
        /* code */
        printf("\n\n\n\n\n\t\t\t\tEnter your account number:");
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
            while (getAccountFromFile(pf, userName, &r))
            {
                if (strcmp(userName, u.name) == 0 && id == r.accountNbr)
                {
                    printf("Account number: %d\n", r.accountNbr);
                    printf("Deposit Date: %d/%d/%d\n", r.deposit.day, r.deposit.month, r.deposit.year);
                    printf("Country: %s\n", r.country);
                    printf("Phone number: %d\n", r.phone);
                    printf("Amount deposited: %.2f\n", r.amount);
                    printf("Type Of Account : %s\n", r.accountType);
                    interestMessage(r);
                    stayOrQuit(u);
                    count++;
                }
            }
        }
        if (count == 0)
        {
            strcpy(error, "This account id does'nt exists or is'nt yours");
            // printf("%s", error);
            countDetail(u);
            // stayOrQuit(u);
        }
    } while (1);
}

// void (struct User u)
// {
//     int choice;
//     // Code pour initialiser les données nécessaires (comme les comptes) ici
//     char op[10];
//     do
//     {
//         system("clear");
//         printf("\nTransaction Menu\n");
//         printf("[1]. Make a deposit\n");
//         printf("[2]. Make a withdrawal\n");
//         printf("[3]. Return to Main Menu\n");
//         printf("[4]. Exit\n");
//         printf("Enter your choice: ");

//         if (scanf("%d", &choice) != 1)
//         {
//             printf("Invalid input. Please enter a valid option.\n");
//             while (getchar() != '\n')
//                 ; // Vide le tampon d'entrée
//         }
//         else
//         {
//             switch (choice)
//             {
//             case 1:

//                 strcpy(op, "deposit");
//                 operation(op, u);
//                 break;
//             case 2:

//                 strcpy(op, "withdraw");
//                 operation(op, u);
//                 break;
//             case 3:
//                 mainMenu(u);
//                 return;
//             case 4:
//                 exit(0);
//                 break;
//             default:
//                 printf("Invalid option. Please enter a valid option.\n");
//                 break;
//             }
//             break;
//         }
//     } while (1); // Répétez jusqu'à ce que l'utilisateur entre une option valide
// }
void removeAccount(struct User u)
{
    int numRecords;
    struct Record AllRecords[100];
    int accountID;
    int count = 0;
    char number[20];
    getAllRecords(AllRecords, &numRecords);

    system("clear");
    do
    {
        printf("\n\n\t\tEnter the number of the count to remove : ");
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
            // Vide le tampon d'entrée
        }
        else
        {
            accountID = atoi(number);
            for (int i = 0; i < numRecords; i++)
            {
                if (strcmp(AllRecords[i].name, u.name) == 0 && AllRecords[i].accountNbr == accountID)
                {
                    count++;
                }
            }

            if (count == 0)
            {
                printf("\n\n\t\tThis account id does'nt exist or is'nt yours\n");
                stayOrQuit(u);
            }
            else
            {
                FILE *fp;
                char filename[] = "./data/records.txt";

                if ((fp = fopen(filename, "w")) == NULL)
                {
                    printf("Error oppenning file : %s\n", filename);
                    return;
                }
                for (int i = 0; i < numRecords; i++)
                {
                    if (strcmp(AllRecords[i].name, u.name) == 0 && AllRecords[i].accountNbr == accountID)
                    {
                        count++;
                    }
                    else
                    {
                        fprintf(fp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                                AllRecords[i].id, AllRecords[i].userId, AllRecords[i].name, AllRecords[i].accountNbr,
                                AllRecords[i].deposit.day, AllRecords[i].deposit.month, AllRecords[i].deposit.year,
                                AllRecords[i].country, AllRecords[i].phone, AllRecords[i].amount, AllRecords[i].accountType);
                    }
                }
                fclose(fp);
            }
            {
                success(u);
                stayOrQuit(u);
            }
        }
        /* code */
    } while (1);
}
