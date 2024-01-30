#include "mini_lib.h"

#define TAILLE_BUFFER 2048

void mini_cat(char* nfile) {
    // Déclare un buffer pour stocker les données du fichier
    char buffer[TAILLE_BUFFER];

    // Vérifie si le nom de fichier est valide
    if (nfile == NULL || mini_strlen(nfile) == 0) {
        mini_perror("Nom de fichier incorrect. \n");
        return;
    }

    // Ouvre le fichier en mode lecture
    MYFILE* file = mini_fopen(nfile, 'r');
    if (file == NULL) {
        // En cas d'erreur d'ouverture, affiche un message d'erreur et quitte la fonction
        mini_perror("mini_fopen() ");
        return;
    }

    // Lit les données du fichier et remplit le buffer
    if(mini_fread(buffer, 1, sizeof(buffer), file) == -1) {
        mini_perror("mini_fread() ");
    }

    // Affiche le contenu du buffer à l'aide de mini_printf
    mini_printf(buffer); mini_printf("\n");

    // Ferme le fichier ouvert
    if(mini_fclose(file) == -1) mini_perror("mini_fclose() ");
}