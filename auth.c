#include <termios.h>
#include "header.h"
#include <stdio.h>
char *USERS = "./data/users.txt";

void checkIn(struct User users[], int *numUsers)
{
    FILE *fp;
    char filename[] = "data/users.txt"; // Nom du fichier
    int count = 0;                      // Compteur du nombre d'utilisateurs

    // Ouvrir le fichier en mode lecture
    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }

    // Lire les données du fichier
    while (fscanf(fp, "%d %s %s", &users[count].id, users[count].name, users[count].password) != EOF)
    {
        count++;
    }

    // Fermer le fichier
    fclose(fp);

    // Mettre à jour le nombre d'utilisateurs
    *numUsers = count;
}
int userExists(struct User users[], int numUsers, const char *name)
{
    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(users[i].name, name) == 0)
        {
            return 1; // L'utilisateur existe
        }
    }
    return 0; // L'utilisateur n'existe pas
}
void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;
    int numUsers;
    struct User users[100];
    checkIn(users, &numUsers);
    system("clear");
    while (1)
    {

        printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
        char input[50];
        printf("\n\n\n\n\n\t\t\t\tEnter your name:");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        if (!userExists(users, numUsers, input))
        {
            printf("\n\n\t\t\t\tThis name does'nt exist. Enter another:");
        }
        else
        {
            if (strchr(input, ' ') != NULL)
            {
                printf("\n\nThe name should not contain a space. Try again.\n");
            }
            else
            {
                strcpy(a, input);
                break;
            }
        }
    }
    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    while (1)
    {
        printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
        fgets(pass, sizeof(&pass), stdin);
        pass[strcspn(pass, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

        if (strchr(pass, ' ') != NULL)
        {
            printf("\n\nThe password should not contain a space. Try again.\n");
        }
        else
        {
            break;
        }
    }
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};

const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u.name) == 0)
        {
            fclose(fp);
            char *buff = userChecker.password;
            return buff;
        }
    }

    fclose(fp);
    return "no user found";
}

// Fonction pour enregistrer un nouvel utilisateur et le stocker dans le fichier
void registerUser(struct User users[], int *numUsers, const char *name, const char *password)
{
    // ... (comme précédemment)

    // Ouvrir le fichier en mode écriture
    FILE *fp = fopen("data/users.txt", "w");

    if (fp == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }

    // Écrire les données dans le fichier
    for (int i = 0; i < *numUsers; i++)
    {
        fprintf(fp, "%d %s %s\n", users[i].id, users[i].name, users[i].password);
    }

    // Fermer le fichier
    fclose(fp);

    printf("✔Registration success for the user : %s\n", name);
}
void registerMenu(char a[50], char pass[50])
{
    struct User users[100]; // Tableau de structures pour stocker les données
    int numUsers = 0;
    checkIn(users, &numUsers);

    while (1)
    {
        char input[50];
        printf("\n\n\n\n\n\t\t\t\tEnter your name:");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

        if (userExists(users, numUsers, input))
        {
            printf("\n\n\t\t\t\tThis name already exists. Enter another:");
        }
        else
        {
            if (strchr(input, ' ') != NULL)
            {
                printf("\n\nThe name should not contain a space. Try again.\n");
            }
            else
            {
                strcpy(a, input);
                break;
            }
        }
    }

    while (1)
    {
        printf("\n\n\n\n\n\t\t\t\tEnter your password:");
        fgets(pass, sizeof(&pass), stdin);
        pass[strcspn(pass, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

        if (strchr(pass, ' ') != NULL)
        {
            printf("\n\nThe password should not contain a space. Try again.\n");
        }
        else
        {
            break;
        }
    }

    // Ajoutez le nouvel utilisateur au tableau
    users[numUsers].id = numUsers; // Vous pouvez assigner l'ID de manière incrémentielle si nécessaire
    strcpy(users[numUsers].name, a);
    strcpy(users[numUsers].password, pass);
    numUsers++; // Incrémentez le nombre d'utilisateurs
    registerUser(users, &numUsers, a, pass);
}

void transferOwner(struct User u)
{
    int numRecords;
    struct Record r[100];
    int accountID;
    int count = 0;
    char number[25];
    struct User users[100];
    int numUsers;
    char username[50];
    getAllRecords(r, &numRecords);
    system("clear");
    do
    {
        printf("\n\n\t\tEnter the id of the account you want to transfer ownership : ");
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
            accountID = atoi(number);
            for (int i = 0; i < numRecords; i++)
            {
                if (strcmp(r[i].name, u.name) == 0 && r[i].accountNbr == accountID)
                {
                    count++;
                    printf("\t\t\t\t====Transfering your account number: %d\n\n", r[i].id);
                    printf("Account number: %d\n", r[i].accountNbr);
                    printf("Deposit Date: %d/%d/%d\n", r[i].deposit.day, r[i].deposit.month, r[i].deposit.year);
                    printf("Country: %s\n", r[i].country);
                    printf("Phone number: %d\n", r[i].phone);
                    printf("Amount deposited: %.2f\n", r[i].amount);
                    printf("Type Of Account : %s\n", r[i].accountType);
                }
            }

            if (count == 0)
            {
                printf("\n\n\t\tThis account id does'nt exist or is'nt yours\n");
                stayOrQuit(u);
            }
            else
            {
                checkIn(users, &numUsers);
                printf("Which user you want to tranfer ownership (user name): ");
                fgets(username, sizeof(username), stdin);
                username[strcspn(username, "\n")] = '\0';
                if (!userExists(users, numUsers, username))
                {
                    printf("\n\n\t\tThis user does'nt exist\n");
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
                        if (strcmp(r[i].name, u.name) == 0 && r[i].accountNbr == accountID)
                        {
                            fprintf(fp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                                    r[i].id, r[i].userId, username, r[i].accountNbr,
                                    r[i].deposit.day, r[i].deposit.month, r[i].deposit.year,
                                    r[i].country, r[i].phone, r[i].amount, r[i].accountType);
                        }
                        else
                        {
                            fprintf(fp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n",
                                    r[i].id, r[i].userId, r[i].name, r[i].accountNbr,
                                    r[i].deposit.day, r[i].deposit.month, r[i].deposit.year,
                                    r[i].country, r[i].phone, r[i].amount, r[i].accountType);
                        }
                    }
                    fclose(fp);
                    printf("✔Success change");
                }
                stayOrQuit(u);
            }
        }
    } while (1);
}