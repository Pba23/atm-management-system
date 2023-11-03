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
    do
    {
        system("clear");
        printf("\n\t\t\t====Transaction Menu\n");
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
                if (strcmp(r[i].name, u.name) == 0 && r[i].accountNbr == id)
                {
                    if (strcmp(r[i].accountType, "saving") == 0 || strcmp(r[i].accountType, "current") == 0)

                    {
                        do
                        {

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
                                int validInput = 0;

                                if (choice == 1)
                                {

                                    do
                                    {
                                        // Demandez à l'utilisateur de saisir le montant du dépôt
                                        printf("Give amount to deposit :");
                                        if (scanf("%f", &amount) == 1)
                                        {
                                            r[i].amount = r[i].amount + amount;
                                            validInput = 1;
                                            break;
                                        }
                                        else
                                        {
                                            // La saisie n'est pas un nombre valide, demandez de ressaisir
                                            printf("Invalid input. Please enter a valid deposit amount.\n");
                                            while (getchar() != '\n')
                                                ; // Vide le tampon d'entrée
                                        }
                                    } while (!validInput);
                                    break;
                                }
                                else if (choice == 2)
                                {

                                    do
                                    {
                                        // Demandez à l'utilisateur de saisir le montant du dépôt
                                        printf("Give amount to withdraw:");
                                        if (scanf("%f", &amount) == 1)
                                        {
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
                                            while (getchar() != '\n')
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

                            fprintf(fp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
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
                        printf("\n\t\tError you are not allowed to do transaction beacause your are %s\n", r[i].accountType);
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