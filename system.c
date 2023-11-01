#include "header.h"

const char *RECORDS = "./data/records.txt";

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

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
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
        printf("\n\t\tEnter 0 to try again, 1 to return to the main menu, or 2 to exit: ");
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
    printf("\n✔ Success!\n\n");
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

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");

noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);

    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user\n\n");
            goto noAccount;
        }
    }
    printf("\nEnter the country:");
    scanf("%s", r.country);
    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);

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
        if (strcmp(AllRecords[i].name, u.name) == 0 && AllRecords[i].id == accountNumber)
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
    printf("\n\n\n\n\n\t\t\t\t✖ count not found!!\n");
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
                        printf("\n✔ Number changed with success!");

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
                        printf("\n✔ Number changed with success!");

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
                        printf("\n✔ Number changed with success!");

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
                        printf("\n✔ Country changed with success!");

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
        }
        else if (strcmp(r.accountType, "fixed01") == 0)
        {
            interest = 0.04;
        }
        else if (strcmp(r.accountType, "fixed02") == 0)
        {
            interest = 0.05;
        }
        else if (strcmp(r.accountType, "fixed03") == 0)
        {
            interest = 0.08;
        }
        value = r.amount * interest / 12;
        printf("You will get $%.2f as interest on day %d of every month", value, r.deposit.day);
    }
}
void countDetail(struct User u)
{
    char userName[100];
    FILE *pf = fopen(RECORDS, "r");
    struct Record r;
    int id;
    system("clear");
    printf("\t\t====== Account datail =====\n\n");
    printf("\n\n\n\n\n\t\t\t\tEnter your account number:");
    int counter;
    scanf("%d", &id);
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
        }
    }
}
void operation(char type[10], struct User u)
{
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");
    int id;
    int i;
    float amount;
    int count = 0;
    do
    {
        printf("Enter your account number: ");

        if (scanf("%d", &id) != 1)
        {
            printf("Invalid input. Please enter a valid option.\n");
            while (getchar() != '\n')
                ; // Vide le tampon d'entrée
        }
        else
        {
            struct Record r[100];
            int numRecord;
            getAllRecords(r, &numRecord);
            for (i = 0; i < numRecord; i++)
            {
                if (strcmp(r[i].name, u.name) == 0 && r[i].id == id)
                {
                    if (strcmp(r[i].accountType, "saving") == 0 || strcmp(r[i].accountType, "current") == 0)
                    {
                        if (strcmp(type, "deposit"))
                        {
                            system("clear");

                            int validInput = 0;
                            do
                            {
                                // Demandez à l'utilisateur de saisir le montant du dépôt
                                printf("Give amount to deposit :");
                                if (scanf("%f", &amount) == 1)
                                {
                                    r[i].amount = r[i].amount + amount;
                                    validInput = 1;
                                }
                                else
                                {
                                    // La saisie n'est pas un nombre valide, demandez de ressaisir
                                    printf("Invalid input. Please enter a valid deposit amount.\n");
                                    while (getchar() != '\n')
                                        ; // Vide le tampon d'entrée
                                }
                            } while (!validInput);
                        }
                        if (strcmp(type, "withdraw"))
                        {
                            system("clear");

                            int validInput = 0;
                            do
                            {
                                // Demandez à l'utilisateur de saisir le montant du dépôt
                                printf("Give amount to withdraw:");
                                if (scanf("%f", &amount) == 1)
                                {
                                    r[i].amount = r[i].amount - amount;
                                    validInput = 1;
                                }
                                else
                                {
                                    // La saisie n'est pas un nombre valide, demandez de ressaisir
                                    printf("Invalid input. Please enter a valid deposit amount.\n");
                                    while (getchar() != '\n')
                                        ; // Vide le tampon d'entrée
                                }
                            } while (!validInput);
                        }
                        FILE *fp;
                        char filename[] = "./data/records.txt";

                        if ((fp = fopen(filename, "w")) == NULL)
                        {
                            printf("Error oppenning file : %s\n", filename);
                            return;
                        }

                        for (int i = 0; i < numRecord; i++)
                        {

                            fprintf(fp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                                    r[i].id, r[i].userId, r[i].name, r[i].accountNbr,
                                    r[i].deposit.day, r[i].deposit.month, r[i].deposit.year,
                                    r[i].country, r[i].phone, r[i].amount, r[i].accountType);
                        }

                        fclose(fp);

                        printf("\n\t\t\t✔ Transaction done with success!");
                        stayOrQuit(u);
                    }
                    else
                    {
                        printf("\n\t\tError you are not allowed to do transaction beacause your are %s\n", r[i].accountType);
                        stayOrQuit(u);
                    }
                    count++;
                }
            }
            if (count == 0)
            {
                printf("\nThis is not your count\n");
                operation(type, u);
            }
        }
    } while (1); // Répétez jusqu'à ce que l'utilisateur entre une option valide
}
void transactionMenu(struct User u)
{
    int choice;
    // Code pour initialiser les données nécessaires (comme les comptes) ici
    char op[10];
    do
    {
        system("clear");
        printf("\nTransaction Menu\n");
        printf("[1]. Make a deposit\n");
        printf("[2]. Make a withdrawal\n");
        printf("[3]. Return to Main Menu\n");
        printf("[4]. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a valid option.\n");
            while (getchar() != '\n')
                ; // Vide le tampon d'entrée
        }
        else
        {
            switch (choice)
            {
            case 1:

                strcpy(op, "deposit");
                operation(op, u);
                break;
            case 2:

                strcpy(op, "withdraw");
                operation(op, u);
                break;
            case 3:
                mainMenu(u);
                return;
            case 4:
                exit(0);
                break;
            default:
                printf("Invalid option. Please enter a valid option.\n");
                break;
            }
        }
    } while (1); // Répétez jusqu'à ce que l'utilisateur entre une option valide
}
void removeAccount(struct User u)
{
    int numRecords;
    struct Record AllRecords[100];
    int accountID;
    int count = 0;
    getAllRecords(AllRecords, &numRecords);

    system("clear");
    printf("\n\n\t\tEnter the id of the count to remove : ");

    if (scanf("%d", &accountID) != 1)
    {
        printf("Invalid input. Please enter a valid option.\n");
        while (getchar() != '\n')
            ; // Vide le tampon d'entrée
    }
    for (int i = 0; i < numRecords; i++)
    {
        if (strcmp(AllRecords[i].name, u.name) == 0 && AllRecords[i].id == accountID)
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
            if (strcmp(AllRecords[i].name, u.name) == 0 && AllRecords[i].id == accountID)
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
        printf("\n\n\t\t✔Account removed with success\n");
        stayOrQuit(u);
    }

   
}
