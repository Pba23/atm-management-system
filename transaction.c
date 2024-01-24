#include "header.h"

void transactionMenu(struct User u)
{
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");
    int id;
    int i;
    float amount;
    int count = 0;
    int choice;
    char op[10];
    char number[20];
    char choiceStr[20];
    do
    {
        system("clear");
        printf("\n\t\t\t%s====Transaction Menu for a account from user %s%s\n",CYAN,u.name,RESET);
        printf("Enter your account number: ");
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
        }
        else
        {
            id = atoi(number);
            struct Record r[100];
            int numRecord;
            getAllRecords(r, &numRecord);
            for (i = 0; i < numRecord; i++)
            {
                if (strcmp(r[i].name, u.name) == 0 && r[i].accountNbr == id)
                {
                    if (strcmp(r[i].accountType, "saving") == 0 || strcmp(r[i].accountType, "current") == 0)

                    {
                        do
                        {

                            printf("%s[1]. Make a deposit\n",GREEN);
                            printf("[2]. Make a withdrawal%s\n",RESET);
                            printf("%s[3]. Return to Main Menu%s\n",BLUE,RESET);
                            printf("%s[4]. Exit%s\n",RED,RESET);
                            printf("Enter your choice: ");
                            fgets(choiceStr, sizeof(choiceStr), stdin);
                            choiceStr[strcspn(choiceStr, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

                            // Vérifier si la chaîne contient uniquement des chiffres
                            int isvalidChoice = 1;
                            for (int i = 0; choiceStr[i] != '\0'; i++)
                            {
                                if (choiceStr[i] < '0' || choiceStr[i] > '9')
                                {
                                    isvalidChoice = 0;
                                    break;
                                }
                            }

                            if (!isvalidChoice)
                            {
                                printf("Invalid input. Please enter a valid option.\n");
                            }
                            else
                            {
                                int validInput = 0;
                                choice = atoi(choiceStr);
                                char amountInput[20]; // Pour stocker la saisie du montant
                                if (choice == 1)
                                {

                                    // Demandez à l'utilisateur de saisir le montant du dépôt
                                    do
                                    {
                                        printf("\nEnter amount to deposit: $");
                                        fgets(amountInput, sizeof(amountInput), stdin);

                                        amountInput[strcspn(amountInput, "\n")] = '\0'; // Supprimer le saut de ligne s'il est présent

                                        // Vérification de la validité du montant
                                        if (!isValidAmount(amountInput))
                                        {
                                            printf("Invalid amount. Please enter a valid decimal number.\n");
                                        }
                                        else
                                        {
                                            amount = atof(amountInput);
                                            r[i].amount = r[i].amount + amount;
                                            validInput = 1;
                                            break;
                                        }

                                    } while (1);
                                    break;
                                }
                                else if (choice == 2)
                                {

                                    do
                                    {
                                        // Demandez à l'utilisateur de saisir le montant du dépôt
                                        printf("Give amount to withdraw:");
                                        fgets(amountInput, sizeof(amountInput), stdin);

                                        amountInput[strcspn(amountInput, "\n")] = '\0'; 
                                        if (isValidAmount(amountInput))
                                        {
                                            amount = atof(amountInput);
                                            if (amount <= r[i].amount)
                                            {
                                                r[i].amount = r[i].amount - amount;
                                                validInput = 1;
                                            }
                                            else
                                            {
                                                printf("It's impossible to do a withdrawal superior of your current amount");
                                                stayOrQuit(u);
                                            }
                                            break;
                                        }
                                        else
                                        {
                                            // La saisie n'est pas un nombre valide, demandez de ressaisir
                                            printf("Invalid input. Please enter a valid amount amount.\n");
                                                ; // Vide le tampon d'entrée
                                        }
                                    } while (!validInput);
                                    break;
                                }
                                else if (choice == 3)
                                {

                                    mainMenu(u);
                                    return;
                                }
                                else if (choice == 4)
                                {
                                    exit(0);
                                    break;
                                }
                                else
                                {
                                    printf("Invalid option. Please enter a valid option.\n");
                                }
                            }
                        } while (1);

                        FILE *fp;
                        char filename[] = "./data/records.txt";

                        if ((fp = fopen(filename, "w")) == NULL)
                        {
                            printf("Error oppenning file : %s\n", filename);
                            return;
                        }

                        for (int i = 0; i < numRecord; i++)
                        {

                            fprintf(fp, "%d %d %s %d %d/%d/%d %s %s %.2lf %s\n",
                                    r[i].id, r[i].userId, r[i].name, r[i].accountNbr,
                                    r[i].deposit.day, r[i].deposit.month, r[i].deposit.year,
                                    r[i].country, r[i].phone, r[i].amount, r[i].accountType);
                        }

                        fclose(fp);

                        success(u);
                        stayOrQuit(u);
                    }
                    else
                    {
                        printf("\n\t\t%sError you are not allowed to do transaction beacause your are %s%s\n", RED,r[i].accountType, RESET);
                        stayOrQuit(u);
                    }
                    count++;
                }
            }
            if (count == 0)
            {
                printf("\nThis is not your count\n");
                transactionMenu(u);
            }
            break;
        }
    } while (1); // Répétez jusqu'à ce que l'utilisateur entre une option valide
}