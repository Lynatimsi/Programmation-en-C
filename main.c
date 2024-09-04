#include <stdio.h>
#include <stdlib.h>
#include "fonctions.c"
//Partie I
int main()
{
    FILE*fichier=NULL;
    fichier = fopen("annuaire.txt", "r+");

    if (fichier != NULL)
    {
       //printf("fichier ouvert\n");
       //afficherAnnuaire(fichier);
       //ajouter_personne(fichier, "Timsi " , "Lina \n","0627310655 \n","linatms08@outlook.com \n");
       //rechercherPersonne("", fichier);
       //rechercherPersonnes("07 57 68 67 90", fichier);
    }
    else{
        printf("erreur");
    }

     fclose(fichier);
     return 0;

}

void afficherAnnuaire(FILE *fichier) {
    printf("Annuaire: \n, annuaire.txt");
    char element[500];
while (fgets(element,100,fichier)!=NULL){
    printf("%s", element);}
}

void ajouter_personne(FILE*fichier, char*nom, char*prenom, char*numero, char*email){
fputs(nom,fichier);
fputs(prenom,fichier);
fputs(numero,fichier);
fputs(email,fichier);
}


void rechercherPersonne(char*nom_prenom, FILE* fichier) {
    rewind(fichier); // revenir au début du fichier

    char ligne[100];
    char numero[20];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (strstr(ligne, nom_prenom) != NULL) {
            // extraire le numéro de téléphone de la ligne
        if (fgets(ligne, sizeof(ligne), fichier) != NULL) {
            strcpy(numero, ligne);
            numero[strcspn(numero, "\n")] = 0;
            printf("La personne qui s'appelle %s a comme numéro : %s", nom_prenom, numero);
            return; // sortir de la fonction dès qu'on a trouvé la personne
        }
    }}

    printf("La personne %s n'a pas été trouvée dans l'annuaire\n", nom_prenom);
}

void rechercherPersonnes(char* numero, FILE* fichier) {
    rewind(fichier); // revenir au début du fichier

    char ligne[100];
    char nom[50];
    char prenom[50];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        ligne[strcspn(ligne, "\n")] = '\0'; // supprimer le caractère de fin de ligne

        // Extraire le nom et le prénom de la ligne
        char* token = strtok(ligne, " ");
        strcpy(nom, token);
        token = strtok(NULL, " ");
        strcpy(prenom, token);

        // Lire la ligne suivante (numéro de téléphone)
        if (fgets(ligne, sizeof(ligne), fichier) != NULL) {
            ligne[strcspn(ligne, "\n")] = '\0'; // supprimer le caractère de fin de ligne
            if (strstr(ligne, numero) != NULL) {
                printf("La personne ayant le numéro de téléphone %s s'appelle %s %s\n", numero, prenom, nom);
                return;
            }
        }
    }

    printf("La personne ayant le numéro de téléphone %s n'a pas été trouvée dans l'annuaire\n", numero);
}

// Partie II
//structure de personne
typedef struct {
    char nom[50];
    char prenom[50];
    char telephone[20];
    char mail[100];
} personne;

// Fonction pour lire l'annuaire et remplir un tableau de structures personne
int lireAnnuaire(FILE *fichier, personne *annuaire, int maxPersonnes) {
    int i = 0;
    char ligne[100];

    rewind(fichier); // Pour s'assurer que nous lisons depuis le début du fichier

    while (i < maxPersonnes && fgets(ligne, sizeof(ligne), fichier) != NULL) {
        // Lire le nom
        ligne[strcspn(ligne, "\n")] = '\0'; // Enlever le caractère de nouvelle ligne
        strcpy(annuaire[i].nom, ligne);

        // Lire le prénom
        if (fgets(ligne, sizeof(ligne), fichier) == NULL) break;
        ligne[strcspn(ligne, "\n")] = '\0';
        strcpy(annuaire[i].prenom, ligne);

        // Lire le numéro de téléphone
        if (fgets(ligne, sizeof(ligne), fichier) == NULL) break;
        ligne[strcspn(ligne, "\n")] = '\0';
        strcpy(annuaire[i].telephone, ligne);

        // Lire l'email
        if (fgets(ligne, sizeof(ligne), fichier) == NULL) break;
        ligne[strcspn(ligne, "\n")] = '\0';
        strcpy(annuaire[i].mail, ligne);

        // Ignorer la ligne vide entre les contacts
        fgets(ligne, sizeof(ligne), fichier);

        i++;
    }

    return i; // Retourner le nombre de personnes lues
}
