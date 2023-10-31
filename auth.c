#include <termios.h>
#include "header.h"
#include <stdio.h>
char *USERS = "./data/users.txt";

void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    scanf("%s", a);
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
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", pass);

    // restore terminal
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

// Fonction pour enregistrer un nouvel utilisateur et le stocker dans le fichier
void registerUser(struct User users[], int *numUsers, const char *name, const char *password) {
    // ... (comme précédemment)

    // Ouvrir le fichier en mode écriture
    FILE *fp = fopen("data/users.txt", "w");

    if (fp == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }

    // Écrire les données dans le fichier
    for (int i = 0; i < *numUsers; i++) {
        fprintf(fp, "%d %s %s\n", users[i].id, users[i].name, users[i].password);
    }

    // Fermer le fichier
    fclose(fp);

    printf("Registration success for the user : %s\n", name);
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
void registerMenu(char a[50], char pass[50])
{

    struct User users[100]; // Tableau de structures pour stocker les données
    int numUsers = 0;
    checkIn(users, &numUsers);
    printf("\n\n\n\n\n\t\t\t\tEnter the your name:");
    while (1)
    {
        scanf("%s", a);
        if (userExists(users, numUsers, a))
        {
           printf("\n\n\t\t\t\tThis name already exists enter another:");
        }else {
            break;
        }
    }
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s",pass);

    // Ajoutez le nouvel utilisateur au tableau
    users[numUsers].id = numUsers; // Vous pouvez assigner l'ID de manière incrémentielle si nécessaire
    strcpy(users[numUsers].name, a);
    strcpy(users[numUsers].password,pass);
    (numUsers)++; // Incrémentez le nombre d'utilisateurs
  registerUser(users, &numUsers, a, pass);
    
}
